cmake_minimum_required(VERSION 3.2)
project(seamule_sdk_c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ljansson -lcurl")

set(SOURCE_FILES main.c)
add_executable(seamule_sdk_c ${SOURCE_FILES} src/seamule-sdk.h src/seamule-sdk.c src/network.h src/network.c src/api.h src/api.c src/response.h src/response.c main.h main.c src/errors.h src/seamule.h src/seamule.c)