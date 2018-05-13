#include "ky/task.h"
#include "ky/syscall.h"
#include "ky/assert.h"
#include "ky/log.h"

#include <stdlib.h>

ucontext_t main_context;

static void
_runner(f_task task_start)
{
   task_start();

   /* The functions will always end with the 'end' syscall, which will properly
    * destroy the task */
   ky_terminate();
}

static const size_t _stack_size = 8u * (1u << 20u); /* 8 MiB */

static uint8_t *
_stack_new(void)
{
   return malloc(_stack_size);
}

KAPI void
arch_task_setup(s_task *task)
{
   ucontext_t *const ctx = &(task->context.uctx);

   /* For the PC arch, we create our own stacks, of a much bigger size */
   task->context.stack = _stack_new();
   ctx->uc_stack.ss_sp = task->context.stack;
   ctx->uc_stack.ss_size = _stack_size;

   const int ret = getcontext(ctx);
   KY_ASSERT(ret == 0);
   makecontext(ctx, (void(*)()) _runner, 1, task->start);
}

KAPI void
arch_task_cleanup(s_task *task __unused__)
{
   // FIXME
   //free(task->context.stack);
}

KAPI void
arch_init(void)
{
}

static void
_idle_main(void)
{
   for (;;)
     {
        ky_yield();
     }
}

s_task ky_idle_task =
{
   .start = _idle_main,
   .stack = NULL,
   .stack_size = 0u,
   .status = KY_TASK_STATUS_INACTIVE,
   .priority = KY_TASK_PRIORITY_NORMAL,
};
