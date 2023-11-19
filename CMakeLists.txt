cmake_minimum_required(VERSION 3.22)
project(Assignment_5 C)

set(CMAKE_C_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include_directories(.)

add_executable(race
        count_race.c
        helper.c
        helper.h)

add_executable(mutex
        helper.c
        helper.h
        count_mutex.c)

add_executable(private
        helper.c
        helper.h
        count_private.c)

add_executable(cache
        helper.c
        helper.h
        count_cache.c)
add_executable(tests
        testing/padding.c)
add_executable(nopadding
        testing/nopadding.c)
add_executable(private_returns
        helper.c
        helper.h
        count_private_returns.c)
