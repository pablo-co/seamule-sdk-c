/*
 * Copyright (c) 2015-2015 Pablo Cárdenas <pcardenasoliveros@gmail.com>
 *
 * SeaMule is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef SEAMULE_SDK_C_SEAMULE_SDK_H
#define SEAMULE_SDK_C_SEAMULE_SDK_H

#include <jansson.h>
#include "seamule.h"
#include "network.h"
#include "api.h"


struct seamule_t *seamule_easy_init();

SEAMULE_CODE seamule_easy_cleanup(struct seamule_t * seamule);

int seamule_easy_main(struct seamule_t *seamule, int argc, char *argv[], seamule_process *process);

SEAMULE_CODE seamule_open(struct seamule_t **seamule);

SEAMULE_CODE seamule_easy_setopt(struct seamule_t *data, SEAMULE_OPTION option, ...);

SEAMULE_CODE seamule_setopt(struct seamule_t *data, SEAMULE_OPTION option, va_list param);

SEAMULE_CODE set_str_opt(char **char_pointer, char *s);

#endif //SEAMULE_SDK_C_SEAMULE_SDK_H
