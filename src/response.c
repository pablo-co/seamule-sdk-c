/*
 * Copyright (c) 2015-2015 Pablo Cárdenas <pcardenasoliveros@gmail.com>
 *
 * SeaMule is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */
#include <stdlib.h>
#include "response.h"


int response_init(struct response_t *response, int buffer_size) {
    response->data = (char *) malloc(buffer_size);
}

void response_close(struct response_t *response) {
    free(response->data);
    free(response);
}