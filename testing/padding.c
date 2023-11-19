//
// Created by othman on 11/20/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4

struct PaddedCounter {
    int privateCount;
    char padding[64 - sizeof(int)];
};

struct PaddedCounter privateCounts[NUM_THREADS];

void *incrementCounter(void *threadId) {
    long tid = (long)threadId;

    for (int i = 0; i < 1000000; ++i) {
        privateCounts[tid].privateCount++;
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    clock_t start, end;

    // Record start time
    start = clock();

    // Create threads
    for (long t = 0; t < NUM_THREADS; t++) {
        if (pthread_create(&threads[t], NULL, incrementCounter, (void *)t)) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    // Join threads
    for (long t = 0; t < NUM_THREADS; t++) {
        if (pthread_join(threads[t], NULL)) {
            fprintf(stderr, "Error joining thread\n");
            return 1;
        }
    }

    // Record end time
    end = clock();

    // Print results
    for (int i = 0; i < NUM_THREADS; ++i) {
        printf("Thread %d count: %d\n", i, privateCounts[i].privateCount);
    }

    // Calculate and print execution time
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", cpu_time_used);

    return 0;
}
