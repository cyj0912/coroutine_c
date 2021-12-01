#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "coroutine.h"

unsigned long long next_item;

void fib()
{
    printf("%s: begin\n", __FUNCTION__);
    int a, b;
    a = 0;
    b = 1;
    while (1) {
        next_item = a + b;
        printf("%s: producing %llu\n", __FUNCTION__, next_item);
        a = b;
        b = next_item;
        yield_next = main_coroutine;
        co_yield();
    }
    printf("%s: end\n", __FUNCTION__);
}

void square_seq(Coroutine *generator)
{
    printf("%s: begin\n", __FUNCTION__);
    int i;
    for (i = 0; i < 20; i++) {
        yield_next = generator;
        co_yield();
        printf("%s: squared=%llu\n", __FUNCTION__, next_item * next_item);
    }
    printf("%s: end\n", __FUNCTION__);
}

int main()
{
    co_init();
    Coroutine *co = co_create(&fib);
    square_seq(co);
    return 0;
}

