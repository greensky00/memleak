/*
 * Copyright 2013 Jung-Sang Ahn <jungsang.ahn@gmail.com>.
 * All Rights Reserved.
 */

#ifndef _JSAHN_MEMLEAK_H
#define _JSAHN_MEMLEAK_H

#include <stdint.h>

#ifndef _MALLOC_OVERRIDE
    #define malloc(size) memleak_alloc(size, __FILE__, __LINE__)
    #define free memleak_free

#endif

void * memleak_alloc(size_t size, char *file, size_t line);
void memleak_free(void *addr);

#endif
