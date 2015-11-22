/*
 * Copyright (c) 2015-2015 Pablo Cárdenas <pcardenasoliveros@gmail.com>
 *
 * SeaMule is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include <string.h>
#include <stddef.h>
#include "response.h"

#include "api.h"
#include "seamule-sdk.h"

json_t *request_jobs(struct seamule_t *seamule) {
    char *url = get_base_url(seamule, SEAMULE_API_JOBS, SEMAULE_API_FORMAT);
    struct response_t *response;

    json_t *root;
    json_error_t error;

    response = get(url);
    if (!response) {
        goto error;
    }

    switch (response->code) {
        case 200:
            break;
        default:
            fprintf(stderr, "The server responded with a %d. \"%s\":\n", response->code, url);
            goto error;
    }

    if (!response->data) {
        fprintf(stderr, "The server didn't send any data %d. \"%s\":\n", response->code, url);
        goto error;
    }

    root = json_loads(response->data, 0, &error);
    response_close(response);
    free(url);

    return root;

    error:
    response_close(response);
    free(url);
    return NULL;
}


json_t *create_job(struct seamule_t *seamule) {
    char *url = get_base_url(seamule, SEAMULE_API_JOBS, SEMAULE_API_FORMAT);
    struct response_t *response;

    json_t *root;
    json_error_t error;

    json_t *worker = json_object();
    response = post(url, worker);
    if (!response) {
        goto error;
    }

    switch (response->code) {
        case 422:
            fprintf(stderr, "The are no jobs for processing from \"%s\":\n", url);
            break;
        case 403:
            fprintf(stderr, "Not authorized from \"%s\":\n", url);
        default:
            break;
    }

    if (!response->data) {
        goto error;
    }

    root = json_loads(response->data, 0, &error);
    response_close(response);
    json_decref(worker);
    free(url);

    return root;

    error:
    response_close(response);
    json_decref(worker);
    free(url);
    return NULL;
}

json_t *send_result(struct seamule_t *seamule, char *id, json_t *result) {
    char *job_url = join_url(id, SEAMULE_API_JOB, SEMAULE_API_FORMAT);
    char *url = get_base_url(seamule, SEAMULE_API_JOBS, job_url);
    struct response_t *response;

    json_t *root;
    json_error_t error;

    response = patch(url, result);
    if (!response) {
        goto error;
    }

    switch (response->code) {
        case 422:
            fprintf(stderr, "The are no jobs for processing from \"%s\":\n", url);
            break;
        case 403:
            fprintf(stderr, "Not authorized from \"%s\":\n", url);
        default:
            break;
    }

    root = json_loads(response->data, 0, &error);
    response_close(response);
    free(url);

    return root;

    error:
    response_close(response);
    free(url);
    return NULL;
}

char *join_url(char *url, char *path, char *extension) {
    size_t url_size = strlen(url);
    size_t path_size = strlen(path);
    size_t extension_size = strlen(extension);
    size_t total_size = url_size + path_size + extension_size + 1;
    char *url_with_path = (char *) malloc(total_size);

    snprintf(url_with_path, total_size, path, url, extension);

    return url_with_path;
}

char *get_base_url(struct seamule_t *seamule, char *path, char *extension) {
    char *url = build_url(seamule->protocol, seamule->domain, seamule->path);
    char *url_with_path = join_url(url, path, extension);

    free(url);

    return url_with_path;
}

char *build_url(const char *protocol, const char *domain, const char *path) {
    size_t protocol_size = strlen(protocol);
    size_t domain_size = strlen(domain);
    size_t path_size = strlen(path);
    size_t total_size = protocol_size + domain_size + path_size;

    char *url = (char *) malloc(total_size * sizeof(char));
    strcpy(url, protocol);
    strcat(url, domain);
    strcat(url, path);

    return url;
}