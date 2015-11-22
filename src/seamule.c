/*
 * Copyright (c) 2015-2015 Pablo Cárdenas <pcardenasoliveros@gmail.com>
 *
 * SeaMule is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include "seamule.h"

void init_seamule(struct seamule_t *seamule) {
    seamule->path_alloc = 0;
    seamule->domain_alloc = 0;
    seamule->protocol_alloc = 0;
}

void close_seamule(struct seamule_t *seamule) {
    if (seamule->path_alloc) {
        free(seamule->path);
    }

    if (seamule->domain_alloc) {
        free(seamule->domain);
    }

    if (seamule->protocol_alloc) {
        free(seamule->protocol);
    }

    free(seamule);
}