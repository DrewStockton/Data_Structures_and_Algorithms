/*****************************************************************************
* CMP_SC 2050
* Lab 9
* By Drew Stockton
* October 31st 2025
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "lab9.h"

/* createArray: mallocs size for an array, stores the size in the -1st element*/
void * createArray(int arraySize, int elementSize)
{
    if (arraySize<=0 || elementSize<=0)
    {
        return NULL;
    }
    int *p;
    p=malloc(arraySize*elementSize + sizeof(int));
    p[0]=arraySize;
    p++;
    return p;
}

//arraySize: returns the -1st element of the array which holds the size
int arraySize(void * array)
{
    if (array == NULL)
    {
        return 0;
    }
    int * size = (int *)array-1;
    return *size;
}

/*BinarySearch
    recursive helper function for find package 
    if the num we want to find is less than the middle, we search the lower half
    otherwise, we search the top (left) half of the array

    if element not found, returns -1


*/
int BinarySearch(Package *array, Package *query, int low, int high)
{
    int mid;
    if (low >= high)
    {
        return -1;
    }
    mid = low + (high - low)/2;
    if (query->deliveryDistance < array[mid].deliveryDistance)
    {
        return BinarySearch(array,query,low,mid);
    }
    else if (query->deliveryDistance > array[mid].deliveryDistance)
    {
        return BinarySearch(array,query,mid + 1,high);
    }
    return mid;
}

/* findPackage: calls the binarysearch function and returns the location of the package, if found*/
int findPackage(Package * array, Package * query)
{
    if (array == NULL || query == NULL)
    {
        return -1;
    }
    int n = arraySize(array);
    if (n<=0)
    {
        return -1;
    }
    return BinarySearch(array,query,0,n);
    
}


//comparePackages: two variables set to the values being compared. returns pos., neg. or 0
int comparePackages(Package * array, Package * query)
{
    int a = array->deliveryDistance;
    int b = query->deliveryDistance;

    if (a < b)
    {
        return -1;
    }
    else if (a > b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//destroyArray: calls the free() function on the -1st element (the beginning of the element) which frees the memory
void destroyArray(void * array)
{
    if (array==NULL)
    {
        return;
    }

    int * size = (int *)array-1;
    free(size);
}
