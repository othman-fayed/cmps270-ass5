#include "helper.h"

size_t executeSequential(int *array, int length)
{
    size_t count;
    int i;
    count = 0;
    for (i = 0; i < length; i++)
    {
        if (array[i] == 1)
        {
            count++;
        }
    }
    return count;
}
