#include "lab1.h"
#include <stdio.h>
int getMedian(int array[], int size, int *result)
{
    if (array == NULL || size <= 0 || result == NULL) //checking for invalid items
    {
        return 1;
    }
    int temp = 0;
    for (int i=0; i<size-1; i++)
    {
        if (array[i] > array[i+1])
        {
            temp = array[i+1];
            array[i+1] = array[i]; //sorting smallest to largest
            array[i] = temp;
        }

    }
    if (size %2 ==1 ) //if odd size, then find median
    {
        *result = array[size/2];
    }
    if (size%2 == 0)
    {
        int x = size/2;
        *result = (array[x-1] + array[x+1])/2; //if even size, then add the 2 cloest nums and find average
    }
    return 0;
}
int sumNegative(int array[], int size, int *result)
{
    int sum = 0;
    if (array == NULL || size <= 0 || result == NULL)//checking for invalid items
    {
        return 1;
    }
    int isZero =0;
    for (int i=0; i<size; i++)
    {
        if (array[i] < 0)
        {
            sum += array[i]; //if neg. then add sum
        }
        if (array[i]==0)
        {
            isZero++; //counter for all the zeros 
        }
    }
    if(isZero == size) //if the entire array is zeroes, fail
    {
        return 1;
    }
    *result = sum;
    return 0;
}
int sumEven(int array[], int size, int *result)
{
    int sum = 0;
    if (array == NULL || size <= 0 || result == NULL)//checking for invalid items
    {
        return 1;
    }
    for (int i=0; i<size; i++)
    {
        if (array[i]%2 == 0)
        {
            sum += array[i]; //if array is even then add to a total
        }
    }
    *result = sum;
    return 0;
}
