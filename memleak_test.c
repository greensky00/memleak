/*
 * Copyright 2013 Jung-Sang Ahn <jungsang.ahn@gmail.com>.
 * All Rights Reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "memleak.h"

void basic_test()
{
    uint8_t *a;
    uint64_t *b;
    uint32_t *c;
    uint16_t *d;
    void *str;
    int ret;

    d = malloc(sizeof(uint16_t));

    memleak_start();

    a = (uint8_t*)calloc(0, sizeof(uint8_t));
    b = (uint64_t*)malloc(sizeof(uint64_t));
    c = (uint32_t*)malloc(sizeof(uint32_t));
    c = (uint32_t*)realloc(c, sizeof(uint32_t)*24);

    ret = posix_memalign(&str, 512, 512);

    free(a);
    free(b);

    memleak_end();
}

int main()
{
    basic_test();
    return 0;
}

