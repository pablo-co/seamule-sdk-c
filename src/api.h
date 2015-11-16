/*
 * Copyright (c) 2015-2015 Pablo Cárdenas <pcardenasoliveros@gmail.com>
 *
 * SeaMule is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef SEAMULE_SDK_C_API_H
#define SEAMULE_SDK_C_API_H

#include <jansson.h>
#include "seamule.h"
#include "network.h"

#define SEAMULE_API_PROTOCOL "http://"

#define SEAMULE_API_DOMAIN "0.0.0.0:5678"

#define SEAMULE_API_PATH "/"

#define SEAMULE_API_JOBS "%sjobs.json"
#define SEAMULE_API_JOB "%sjobs/%s.json"

json_t *request_jobs(struct seamule_t * seamule);

json_t *create_job(struct seamule_t * seamule);

json_t *send_result(struct seamule_t *seamule, char* id, json_t *result);

char *join_url(char *url, char *path);

char *get_base_url(struct seamule_t *seamule, char *path);

char *build_url(const char *protocol, const char *domain, const char *path);

#endif //SEAMULE_SDK_C_API_H
