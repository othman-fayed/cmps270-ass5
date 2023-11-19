#include <stdio.h>
#include "helper.h"
#include "sequential.c"
#include "threadHelper.c"

void executeProcedure(size_t length)
{
    printf("Array generation started.\n");
    int *array = generateRandomArrays(length);
    printf("Array length: %lu\n", length);
    //

    startClock(0);
    printf(
        "[Sequential] Result: %lu - Processing time: %f\n",
        executeSequential(array, length),
        stopClock(0));

    startClock(0);
    printf(
        "[pthreads(1)] Result: %lu - Processing time: %f\n",
        executePthreads(array, length, 1),
        stopClock(0));

    startClock(0);
    printf(
        "[pthreads(2)] Result: %lu - Processing time: %f\n",
        executePthreads(array, length, 2),
        stopClock(0));

    startClock(0);
    printf(
        "[pthreads(4)] Result: %lu - Processing time: %f\n",
        executePthreads(array, length, 4),
        stopClock(0));

    startClock(0);
    printf(
        "[pthreads(32)] Result: %lu - Processing time: %f\n",
        executePthreads(array, length, 32),
        stopClock(0));
}

int main(void)
{
    executeProcedure(1000);
    executeProcedure(1000000);
    executeProcedure(1000000000);
}