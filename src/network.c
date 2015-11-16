/*
 * Copyright (c) 2015-2015 Pablo Cárdenas <pcardenasoliveros@gmail.com>
 *
 * SeaMule is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

#include "network.h"
#include "response.h"

size_t write_response(void *ptr, size_t size, size_t nmemb, void *stream) {
    struct write_result_t *result = (struct write_result_t *) stream;

    if (result->pos + size * nmemb >= SEAMULE_NETWORK_BUFFER_SIZE - 1) {
        fprintf(stderr, "error: too small buffer\n");
        return 0;
    }

    memcpy(result->data + result->pos, ptr, size * nmemb);
    result->pos += size * nmemb;

    return size * nmemb;
}

struct response_t *get(const char *url) {
    CURL *curl = NULL;
    CURLcode status;
    struct curl_slist *headers = NULL;
    struct response_t *response = (struct response_t *) malloc(sizeof(struct response_t));

    response_init(response, SEAMULE_NETWORK_BUFFER_SIZE);

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
        goto error;
    }

    if (!response->data) {
        goto error;
    }

    struct write_result_t write_result = {
            .data = response->data,
            .pos = 0
    };

    curl_easy_setopt(curl, CURLOPT_URL, url);

    /* SeaMule API requires a User-Agent header with a value of SeaMule-Worker*/
    headers = curl_slist_append(headers, "User-Agent: SeaMule-Worker");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_result);

    status = curl_easy_perform(curl);
    if (status != 0) {
        fprintf(stderr, "error: unable to request data from \"%s\":\n", url);
        fprintf(stderr, "%s\n", curl_easy_strerror(status));
        goto error;
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response->code);

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    curl_global_cleanup();

    /* zero-terminate the result */
    response->data[write_result.pos] = '\0';

    return response;

    error:
    if (response->data)
        free(response->data);
    if (curl)
        curl_easy_cleanup(curl);
    if (headers)
        curl_slist_free_all(headers);
    curl_global_cleanup();
    return NULL;
}

struct response_t *post(const char *url, json_t *json) {
    CURL *curl = NULL;
    CURLcode status;
    struct curl_slist *headers = NULL;
    struct response_t *response = (struct response_t *) malloc(sizeof(struct response_t));
    response_init(response, SEAMULE_NETWORK_BUFFER_SIZE);

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
        goto error;
    }

    if (!response->data) {
        goto error;
    }

    struct write_result_t write_result = {
            .data = response->data,
            .pos = 0
    };

    curl_easy_setopt(curl, CURLOPT_URL, url);

    /* SeaMule API requires a User-Agent header with a value of SeaMule-Worker*/
    headers = curl_slist_append(headers, "User-Agent: SeaMule-Worker");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_result);

    status = curl_easy_perform(curl);
    if (status != 0) {
        fprintf(stderr, "error: unable to request data from \"%s\":\n", url);
        fprintf(stderr, "%s\n", curl_easy_strerror(status));
        goto error;
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response->code);

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    curl_global_cleanup();

    /* zero-terminate the result */
    response->data[write_result.pos] = '\0';

    return response;

    error:
    if (response->data)
        free(response->data);
    if (curl)
        curl_easy_cleanup(curl);
    if (headers)
        curl_slist_free_all(headers);
    curl_global_cleanup();
    return NULL;
}

struct response_t *patch(const char *url, json_t *json) {
    CURL *curl = NULL;
    CURLcode status;
    struct curl_slist *headers = NULL;
    struct response_t *response = (struct response_t *) malloc(sizeof(struct response_t));
    response_init(response, SEAMULE_NETWORK_BUFFER_SIZE);

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl) {
        goto error;
    }

    if (!response->data) {
        goto error;
    }

    struct write_result_t write_result = {
            .data = response->data,
            .pos = 0
    };

    curl_easy_setopt(curl, CURLOPT_URL, url);

    /* SeaMule API requires a User-Agent header with a value of SeaMule-Worker*/
    headers = curl_slist_append(headers, "User-Agent: SeaMule-Worker");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_result);

    status = curl_easy_perform(curl);
    if (status != 0) {
        fprintf(stderr, "error: unable to request data from \"%s\":\n", url);
        fprintf(stderr, "%s\n", curl_easy_strerror(status));
        goto error;
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response->code);
    /*if (code != 200) {
        fprintf(stderr, "error: server responded with code %ld\n", code);
        goto error;
    }*/

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    curl_global_cleanup();

    /* zero-terminate the result */
    response->data[write_result.pos] = '\0';

    return response;

    error:
    if (response->data)
        free(response->data);
    if (curl)
        curl_easy_cleanup(curl);
    if (headers)
        curl_slist_free_all(headers);
    curl_global_cleanup();
    return NULL;
}