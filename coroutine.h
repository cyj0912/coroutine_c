#pragma once

typedef struct Coroutine_st {
    void *stack_ptr;
    void *stack_alloc;
} Coroutine;

extern Coroutine *main_coroutine;

extern Coroutine *current_coroutine;
extern Coroutine *yield_next;

void co_yield();

void co_init();

Coroutine *co_create(void (*func)());

