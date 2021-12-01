#include <stdlib.h>
#include <stdint.h>
#include "coroutine.h"

Coroutine *main_coroutine;

Coroutine *current_coroutine;
Coroutine *yield_next;

void co_init()
{
    Coroutine *co = (Coroutine *)malloc(sizeof(Coroutine));
    co->stack_ptr = NULL;
    co->stack_alloc = NULL;
    main_coroutine = co;
    current_coroutine = co;
}

Coroutine *co_create(void (*func)())
{
    Coroutine *co = (Coroutine *)malloc(sizeof(Coroutine));
    // TODO: stack alignment
    co->stack_alloc = malloc(4096 * 32);
    size_t stack_addr = (size_t)co->stack_alloc;
    size_t *sptr = (size_t *)(stack_addr + 4096 * 32);
    sptr -= 1;
    *sptr = (size_t)func;
    sptr -= 6; // number of registers to restore
    co->stack_ptr = sptr;
    return co;
}

