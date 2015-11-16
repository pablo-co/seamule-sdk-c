/*
 * Copyright (c) 2015-2015 Pablo Cárdenas <pcardenasoliveros@gmail.com>
 *
 * SeaMule is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef SEAMULE_SDK_C_SEAMULE_H
#define SEAMULE_SDK_C_SEAMULE_H

#define INIT(name, type, number) SEAMULEOPT_##name = type + number

#define SEAMULE_OPTTYPE_LONG 0
#define SEAMULE_OPTTYPE_STRING 10000

#define SEAMULE_SDK_MAJOR_VERSION  0
#define SEAMULE_SDK_MINOR_VERSION  0
#define SEAMULE_SDK_MICRO_VERSION  1

typedef enum {
    /* The protocol that will be used for requests */
    INIT(PROTOCOL, SEAMULE_OPTTYPE_STRING, 1),

    /* The domain or IP in which SeaMule is located */
    INIT(DOMAIN, SEAMULE_OPTTYPE_STRING, 2),

    /* The path in which SeaMule is mounted at */
    INIT(PATH, SEAMULE_OPTTYPE_STRING, 3),

    /* Instruct Seamule to use a certain receive buffer */
    INIT(BUFFER_SIZE, SEAMULE_OPTTYPE_LONG, 4),

    SEAMULEOPT_LASTENTRY /* the last unused */
} SEAMULE_OPTION;

typedef enum {
    SEAMULE_OK,
    SEAMULE_FAILED,
    SEAMULE_CANCELLED,
    SEAMULE_OUT_OF_MEMORY
} SEAMULE_CODE;

struct seamule_t {
    char *protocol;
    char *domain;
    char *path;
    char *buffer_size;
};

typedef struct seamule_t SEAMULE;

typedef json_t *(seamule_process)(const json_t *);

#endif //SEAMULE_SDK_C_SEAMULE_H
