#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "helper.h"

int *array;
int length;
int count;

int count1s() {
    int i;
    count = 0;
    for (i = 0; i < length; i++) {
        if (array[i] == 1) {
            count++;
        }
    }
    return count;
}

clock_t t[100];

/**
 * generates an array of random integers with values between 0 and 5 (inclusive).
 */
int *generateRandomArrays(size_t count) {
    int *list = (int *) malloc(sizeof(int) * count);
    // Use current time as
    // seed for random generator
    srand(time(0));

    for (size_t i = 0; i < count; i++) {
        list[i] = rand() % 5;
    }

    return list;
}

/**
 * starts a clock with assigned id. ignored if id already exists
 */
void startClock(size_t id) {
    if (id < 0 || id > 99) {
        return;
    }
    t[id] = clock();
}

/**
 * stops clock with assigned it. returns -1 if id is invalid
 */
double stopClock(size_t id) {
    clock_t elapsed = clock() - t[id];
    return ((double) elapsed) / CLOCKS_PER_SEC; // in seconds
}


void printResultsVertical(RunResult *results, size_t resultsCount, size_t noOfRuns) {
    for (int j = 0; j < 2; ++j) {
        if (j) {
            printf(",");
        }
        for (int i = 0; i < resultsCount; ++i) {
            if (i) {
                printf(",");
            }
            if (results[i].array_size == 1000) {
                printf("1K");
            } else if (results[i].array_size == 1000000) {
                printf("1M");
            } else if (results[i].array_size == 1000000000) {
                printf("1G");
            } else {
                printf("%lu", results[i].array_size);
            }
            printf(" x %lu", results[i].thread_count);
        }
    }
    printf("\n");
    for (int j = 0; j < noOfRuns; ++j) {
        int i;
        for (i = 0; i < resultsCount; ++i) {
            if (i) {
                printf(",");
            }
            printf("%lu", results[i].counts[j]);
        }
        for (i = 0; i < resultsCount; ++i) {
//            if (i) {
//                printf(",");
//            }
            printf(",%lu", results[i].times[j]);
        }
        printf("\n");
    }
}

void printResultsHorizontal(RunResult *results, size_t resultsCount, size_t noOfRuns) {
    for (int i = 0; i < resultsCount; ++i) {
        RunResult *result = &results[i];

        printf("%lu,%lu", result->array_size, result->thread_count);
        for (int ii = 0; ii < noOfRuns; ++ii) {
            printf(",%lu", result->counts[ii]);
        }
        printf("\n");
        printf("%lu,%lu", result->array_size, result->thread_count);
        for (int ii = 0; ii < noOfRuns; ++ii) {
            printf(",%lu", result->times[ii]);
        }
        printf("\n");
    }
}

int countOnes(int *array, size_t start, size_t end) {
    int count = 0;
    while (start < end) {
        if (array[start] == 1) {
            ++count;
        }
        ++start;
    }
    return count;
}