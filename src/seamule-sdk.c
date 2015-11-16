/*
 * Copyright (c) 2015-2015 Pablo Cárdenas <pcardenasoliveros@gmail.com>
 *
 * SeaMule is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include <jansson.h>
#include <string.h>
#include "seamule-sdk.h"

struct seamule_t *seamule_easy_init() {
    SEAMULE_CODE result = SEAMULE_OK;
    struct seamule_t *data;

    result = seamule_open(&data);
    if (result) {
        fprintf(stderr, "Error: seamule_open failed\n");
        return NULL;
    }

    return data;
}

SEAMULE_CODE seamule_easy_cleanup(struct seamule_t *seamule) {
    free(seamule);
    return SEAMULE_OK;
}

SEAMULE_CODE seamule_open(struct seamule_t **seamule) {
    SEAMULE_CODE result = SEAMULE_OK;
    struct seamule_t *data;

    /* Very simple start-up: alloc the struct, init it with zeroes and return */
    data = calloc(1, sizeof(struct seamule_t));
    if (!data) {
        fprintf(stderr, "Error: calloc of seamule_t failed\n");
        return SEAMULE_OUT_OF_MEMORY;
    }

    data->protocol = (char *) malloc(strlen(SEAMULE_API_PROTOCOL) * sizeof(char));
    strcpy(data->protocol, SEAMULE_API_PROTOCOL);

    data->domain = (char *) malloc(strlen(SEAMULE_API_DOMAIN) * sizeof(char));
    strcpy(data->domain, SEAMULE_API_DOMAIN);

    data->path = (char *) malloc(strlen(SEAMULE_API_PATH) * sizeof(char));
    strcpy(data->path, SEAMULE_API_PATH);

    *seamule = data;

    return result;
}

SEAMULE_CODE seamule_easy_setopt(struct seamule_t *data, SEAMULE_OPTION option, ...) {
    va_list arg;
    SEAMULE_CODE result;

    if (!data) {
        return SEAMULE_CANCELLED;
    }

    va_start(arg, option);

    result = seamule_setopt(data, option, arg);

    va_end(arg);
    return result;
}

SEAMULE_CODE seamule_setopt(struct seamule_t *data, SEAMULE_OPTION option, va_list param) {
    SEAMULE_CODE result = SEAMULE_OK;

    switch (option) {
        case SEAMULEOPT_PROTOCOL:
            free(data->protocol);
            result = set_str_opt(&data->protocol, va_arg(param, char *));
            break;
        case SEAMULEOPT_DOMAIN:
            free(data->domain);
            result = set_str_opt(&data->domain, va_arg(param, char *));
            break;
        case SEAMULEOPT_PATH:
            free(data->path);
            result = set_str_opt(&data->path, va_arg(param, char *));
            break;
        case SEAMULEOPT_BUFFER_SIZE:
            data->buffer_size = va_arg(param, long);
            break;
    }
    return result;
}

int seamule_easy_main(struct seamule_t *seamule, int argc, char *argv[], seamule_process *process) {
    json_t *jobs, *first_job, *payload, *id;
    json_error_t error;

    jobs = request_jobs(seamule);
    if (!jobs) {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return 1;
    }

    if (!json_is_array(jobs)) {
        fprintf(stderr, "error: root is not an array\n");
        json_decref(jobs);
        return 1;
    }

    if (json_array_size(jobs) == 0) {
        first_job = create_job(seamule);
    } else {
        first_job = json_array_get(jobs, 0);
    }

    if (!first_job) {
        fprintf(stderr, "error: root is empty\n");
        json_decref(jobs);
        return 1;
    }

    if (!json_is_object(first_job)) {
        fprintf(stderr, "error: job %d is not an object\n", 1);
        json_decref(first_job);
        return 1;
    }

    id = json_object_get(first_job, "id");
    if (!json_is_string(id)) {
        fprintf(stderr, "error: job id is not a string\n");
        json_decref(id);
        return 1;
    }

    payload = json_object_get(first_job, "payload");

    json_t *result = process(payload);

    if (result) {
        send_result(seamule, result, json_string_value(id));
    }

    json_decref(jobs);
    json_decref(first_job);
    json_decref(payload);
}

SEAMULE_CODE set_str_opt(char **char_pointer, char *string) {
    if (*char_pointer == NULL) {
        free(*char_pointer);
    }

    if (string) {
        string = strdup(string);
        if (!string) {
            return SEAMULE_OUT_OF_MEMORY;
        }
        *char_pointer = string;
    }

    return SEAMULE_OK;
}
