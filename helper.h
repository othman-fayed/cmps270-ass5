// #ifndef HELPER_H
// #define HELPER_H

#include <stdlib.h>

typedef struct {
    size_t thread_count;
    size_t array_size;
    /**
     * array on runs
     */
    clock_t *times;
    /**
     * array on runs
     */
    size_t *counts;
} RunResult;


/**
 * generates an array of random integers with values between 0 and 5 (inclusive).
 */
extern int *generateRandomArrays(size_t count);

/**
 * starts a clock with assigned id [between 0-99]. overriden if id already exists
 */
extern void startClock(size_t id);

/**
 * stops clock with assigned it. returns time taken or -1 if id is invalid
 */
extern double stopClock(size_t id);

extern void *executePthreads(
        int *array,
        int length,
        int threadCount,
        void *(*start_routine));

extern void printResultsVertical(RunResult *results, size_t resultsCount, size_t noOfRuns);

extern int countOnes(int *array, size_t start, size_t end);

// #endif