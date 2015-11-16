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
    char *url = get_base_url(seamule, SEAMULE_API_JOBS);
    struct response_t *response;

    json_t *root;
    json_error_t error;

    response = get(url);
    if (!response) {
        return NULL;
    }

    switch (response->code) {
        case 200:
            break;
        default:
            fprintf(stderr, "The server responded with a %d. \"%s\":\n", response->code, url);
            return NULL;
    }

    if (!response->data) {
        fprintf(stderr, "The server didn't send any data %d. \"%s\":\n", response->code, url);
        return NULL;
    }

    root = json_loads(response->data, 0, &error);
    free(response->data);

    return root;
}


json_t *create_job(struct seamule_t *seamule) {
    char *url = get_base_url(seamule, SEAMULE_API_JOBS);
    struct response_t *response;

    json_t *root;
    json_error_t error;

    response = post(url, NULL);
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
        return NULL;
    }

    root = json_loads(response->data, 0, &error);
    free(response->data);

    return root;
}

json_t *send_result(struct seamule_t *seamule, char* id, json_t *result) {
    char *url = get_base_url(seamule, SEAMULE_API_JOB);
    join_url(url, id);
    struct response_t *response;

    json_t *root;
    json_error_t error;

    response = post(url, NULL);
    switch (response->code) {
        case 422:
            fprintf(stderr, "The are no jobs for processing from \"%s\":\n", url);
            break;
        case 403:
            fprintf(stderr, "Not authorized from \"%s\":\n", url);
        default:
            break;
    }
    printf("%s\n", response->data);
    if (!response->data) {
        return NULL;
    }

    root = json_loads(response->data, 0, &error);
    free(response->data);

    return root;
}

char *join_url(char *url, char *path) {
    size_t url_size = strlen(url);
    size_t jobs_size = strlen(path);
    char *url_with_path = (char *) malloc(url_size + jobs_size + 1);

    snprintf(url_with_path, url_size + jobs_size + 1, path, url);

    return url_with_path;
}

char *get_base_url(struct seamule_t *seamule, char *path) {
    char *url = build_url(seamule->protocol, seamule->domain, seamule->path);
    return join_url(url, path);
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