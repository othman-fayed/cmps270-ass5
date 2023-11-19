#include <stdio.h>
#include <pthread.h>
#include "helper.h"

#define Array_SIZE(X) sizeof (X) / sizeof (X[0])

size_t thread_count_race;
int *array_race;
size_t array_length_race;
size_t partition_size_race;

void *doPart(void *rank) {
//    pthread_t tid = pthread_self();
    size_t count = 0;
    size_t i = (size_t) rank * partition_size_race;
    size_t endIndex = i + partition_size_race;
//    printf("[%lu] Start Index: %lu - End Index: %lu - Thread id: %lu\n", rank, i, endIndex, tid);
    for (; i < endIndex; i++) {
        if (array_race[i] == 1) {
            count++;
        }
    }
    return (void *) count;
}

int run() {
    size_t counter = 0;
    //
    pthread_t threads[thread_count_race];
    for (size_t i = 0; i < thread_count_race; i++) {
        pthread_create(&threads[i], NULL, doPart, (void *) i);
    }

    for (size_t i = 0; i < thread_count_race; i++) {
        int countResult;
        pthread_join(threads[i], (void **) &countResult);
        counter = counter + countResult;
    }

    return counter;
}


int main() {
    size_t noOfRuns = 100;
    //size_t threadsToTest[] = {1, 32};
    size_t threadsToTest[] = {1, 2, 4, 32};
    //size_t sizesToTest[] = {1000000000};
    size_t sizesToTest[] = {1000, 1000000, 1000000000};
//    size_t sizesToTest[] = {1000, 1000000};

    size_t resultsCount = Array_SIZE (sizesToTest) * Array_SIZE (threadsToTest);
    RunResult *results = (RunResult *) malloc(sizeof(RunResult) * resultsCount);
    if (results == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        // Handle error and return
    }

    size_t resultIndex = 0;
    for (int sizeIndex = 0; sizeIndex < Array_SIZE (sizesToTest); ++sizeIndex) {
        array_length_race = sizesToTest[sizeIndex];
        printf("Array_race generation started.\n");
        array_race = generateRandomArrays(array_length_race);
        printf("Array_race generation Completed.\n");

        printf("\n============\nArray size #%lu\n============\n", sizesToTest[sizeIndex]);
        for (int threadIndex = 0; threadIndex < Array_SIZE(threadsToTest); ++threadIndex) {
            thread_count_race = threadsToTest[threadIndex];
            partition_size_race = (array_length_race / thread_count_race);
            //printf("\n___________\nThread #%lu\n___________\n", thread_count_race);
            RunResult *result = &results[resultIndex++];
            result->array_size = array_length_race;
            result->thread_count = thread_count_race;
            result->times = (clock_t *) malloc(sizeof(clock_t) * noOfRuns);
            result->counts = (size_t *) malloc(sizeof(size_t) * noOfRuns);
            //
            for (size_t runNo = 0; runNo < noOfRuns; ++runNo) {
                //printf("\n----------\nRun #%lu\n----------\n", runNo + 1);
//                results[resultIndex] = (struct RunResult *) malloc(sizeof(struct RunResult *));
                clock_t c = clock();
                result->counts[runNo] = run();
                result->times[runNo] = clock() - c;
                //printf("Processing time: %f\n", result->times[runNo]);
            }
        }

    }

    printf("\n\n____________________\nR  E  S  U  L  T  S\n____________________\n\n");

    printResultsVertical(results, resultsCount, noOfRuns);

    // Free allocated memory
    for (size_t i = 0; i < resultsCount; ++i) {
        free(results[i].times);
        free(results[i].counts);
    }

    free(results);
    free(array_race);
}
