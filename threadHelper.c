#include <stdio.h>
#include "helper.h"
#include "threadHelper.h"

void *execute(void *p, int length)
{
    size_t count;
    int i;
    count = 0;
    for (i = 0; i < length; i++)
    {
        if (array[i] == 1)
        {
            count++;
            count++;
        }
    }
    return count;
}

void *executePthreads(int *array, int length, int threadCount, )
{
    pthread_t threads[threadCount];

    for (size_t i = 0; i < threadCount; i++)
    {
        pthread_create(&threads[i], NULL, execute, (void *)0);
    }

    for (size_t i = 0; i < threadCount; i++)
    {
        pthread_join(&threads[i], NULL);
    }

    return 0;
}