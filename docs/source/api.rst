===============================================================================
NanoK API
===============================================================================

This document explains the C runtime API that NanoK provides to write a
NanoK-base application. This does not cover the internal API of NanoK (which is
also made available to the application, but does not contribute to the its
runtime.


nk_init()
-------------------------------------------------------------------------------

This C API is **not** a syscall, contrary to most of the NanoK API. This
function shall be run prior performing any NanoK configuration. It initializes
NanoK internals. NanoK cannot operate properly prior calling this function.


nk_event_new()
-------------------------------------------------------------------------------

nk_task_add()
-------------------------------------------------------------------------------


nk_yield()
-------------------------------------------------------------------------------

nk_await()
-------------------------------------------------------------------------------

nk_run()
-------------------------------------------------------------------------------


