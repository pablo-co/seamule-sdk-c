/*
 * Copyright (c) 2015-2015 Pablo Cárdenas <pcardenasoliveros@gmail.com>
 *
 * SeaMule is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef SEAMULE_SDK_C_RESPONSE_H
#define SEAMULE_SDK_C_RESPONSE_H

struct response_t {
    long code;
    char *data;
};

/**
 * response_init - Initialize a response object
 *
 * @response: The (statically allocated) response object
 * @buffer_size: The amount of bytes that should be allocated for
 * the data field.
 *
 * Initializes a statically allocated response object. The object
 * should be cleared with response_close when it's no longer used.
 *
 * Returns 0 on success, -1 on error (out of memory).
 */
int response_init(struct response_t *response, int buffer_size);

/**
 * response_close - Release all resources used by a response object
 *
 * @response: The response
 *
 * Destroys a statically allocated response object.
 */
void response_close(struct response_t *response);

#endif //SEAMULE_SDK_C_RESPONSE_H
