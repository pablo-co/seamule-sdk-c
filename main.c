/*
 * Copyright (c) 2009-2014 Petri Lehtinen <petri@digip.org>
 *
 * Jansson is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include <stdlib.h>
#include <string.h>

#include <jansson.h>
#include "src/seamule-sdk.h"

json_t *process(const json_t *payload);

int main(int argc, char *argv[]) {
    SEAMULE *seamule = seamule_easy_init();
    seamule_easy_setopt(seamule, SEAMULEOPT_DOMAIN, "0.0.0.0:5678");
    int result = seamule_easy_main(seamule, argc, argv, process);
    seamule_easy_cleanup(seamule);

    return result;
}

json_t *process(const json_t *payload) {

    json_error_t error;

    if (!payload) {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return NULL;
    }

    if (!json_is_array(payload)) {
        fprintf(stderr, "error: payload is not an array\n");
        json_decref(payload);
        return NULL;
    }

    int i;
    for (i = 0; i < json_array_size(payload); i++) {
        json_t *data, *type, *position_x, *position_y;

        data = json_array_get(payload, i);
        if (!json_is_object(data)) {
            fprintf(stderr, "error: commit data %d is not an object\n", (int) (i + 1));
            json_decref(payload);
            return NULL;
        }

        //Check al the values of the pieces
        type = json_object_get(data, "type");
        if (!json_is_integer(type)) {
            fprintf(stderr, "error: commit %d: type is not an integer\n", (int) (i + 1));
            return NULL;
        }

        position_x = json_object_get(data, "x");
        if (!json_is_integer(position_x)) {
            fprintf(stderr, "error: commit %d: x is not an integer\n", (int) (i + 1));
            return NULL;
        }

        position_y = json_object_get(data, "y");
        if (!json_is_integer(position_y)) {
            fprintf(stderr, "error: commit %d: y is not an integer\n", (int) (i + 1));
            return NULL;
        }

        //TODO create the piece and attach it to the board
    }

}