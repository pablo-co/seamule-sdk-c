/*
 * Copyright (c) 2015-2015 Pablo Cárdenas <pcardenasoliveros@gmail.com>
 *
 * SeaMule is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef SEAMULE_SDK_C_NETWORK_H
#define SEAMULE_SDK_C_NETWORK_H

#include <stddef.h>
#include <jansson.h>
#include "api.h"
#include "response.h"

#define SEAMULE_NETWORK_BUFFER_SIZE 1024 * 1024  /* 1024 KB */

struct write_result_t {
    char *data;
    int pos;
};

struct response_t *get(const char *url);

struct response_t *post(const char *url, json_t *json);

struct response_t *patch(const char *url, json_t *json);

size_t write_response(void *ptr, size_t size, size_t nmemb, void *stream);

#endif //SEAMULE_SDK_C_NETWORK_H
