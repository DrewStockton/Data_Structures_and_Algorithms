#include <stdio.h>
#include <stdlib.h>
#include "lab2.h"

int makeArray(int **array, int size)
{
    if (array == NULL || size <= 0) //if array is null or size invalid, break
    {
        return 1;
    }
    int * a = (int *)malloc(size * sizeof(int)); //allocate an array to have the same size of the input
    if (a == NULL) //if this malloc fails, then break
    {
        return 1;
    }
    *array = a;
    return 0;

}
void initArray(int *array, int size)
{
    if (array == NULL || size<0) //if array is null or size invalid, break
    {
        return;
    }
    for(int i=0; i<size; i++)
    {
        array[i] = 0; //set each element to 0
    }

}
int multiplyOdd(int *array, int size, int multiplicand)
{
    if (array == NULL || size <0)  //if array is null or size invalid, break
    {
        return 0;
    }
    int count = 0;
    for (int i=0; i<size; i++)
    {
        if (array[i] == 0 || array[i]%2 != 0) //if element is zero or odd, 
        {
            array[i] *= multiplicand; //multiply element
            count++;
        }
    }
    return count;//return total amount of odd elements
}
void freeArray(int **array)
{
    if (array != NULL && *array != NULL) //check for null
    {
        free(*array); //free the memory
        *array=NULL; //keeps the pointer out of memory
    }
}
