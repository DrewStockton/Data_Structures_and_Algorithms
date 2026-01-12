#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab4.h"

void **allocateJagged2DArray(int elementSize, int rows, int lengths[])//this function dynamically reserves space for a 2d array of any type
{
    if (rows <= 0 || elementSize <= 0 || lengths == NULL) //checking for seg faults
    {
        return NULL;
    }

    void **array;
    int *p;

    p = malloc(rows * sizeof(void*)+sizeof(int));
    if (!p)
    {
        return NULL;
    }
    p[0] = rows;
    p++; //this section makes it a smart array, and stores the size in the -1st element
    array = (void**)p;
    for (int i=0; i<rows; i++)
    {
        int *c = malloc(lengths[i]*elementSize + sizeof(int)); //allocate memory to hold elements and store size 
        if (!c)
        {
            return NULL;
        }
        c[0] = lengths[i];
        c++;
        array[i] = (void*)c;
    }
    return array;
}

void freeJagged2DArray(void **arrayJagged) //this function frees the memory from the malloc-ed 2d array
{
    if (arrayJagged == NULL) //checking for seg faults or errors
    {
        return;
    }
    int rows = getRowCount(arrayJagged);
    for (int i=0; i<rows; i++)
    {
        if (arrayJagged[i] != NULL)
        {
            free((int *)arrayJagged[i]-1); //frees each part seperately
        }
    }
    free((int *)arrayJagged-1); //frees the beginning 
}

int getRowCount(void **arrayJagged) //this function returns the count of a row, which is hidden in the -1st element
{
    if (arrayJagged == NULL)//checking for seg faults or errors
    {
        return 0;
    }
    int * count = (int*)arrayJagged-1;
    return count[0];

}
int getColCount(void **arrayJagged, int row)//returns the count of a column, which is hidden in the -1st element
{
    if (arrayJagged == NULL || row < 0)//checking for seg faults or errors
    {
        return 0;
    }
    void *rowPtr = arrayJagged[row];
    if (rowPtr == NULL)
    {
        return 0;
    }
    int * count = (int*)rowPtr -1;
    return count[0];
}

Course *createCourse(int number, char *department, char *name)//creates a structure course and fills in the information
{
    if (department == NULL || name == NULL)//checking for seg faults or errors
    {
        return NULL;
    }
    Course *c = (Course *)malloc(sizeof(Course));
    if (c==NULL)
    {
        return NULL;
    }
    c->number = number;
    strcpy(c->department, department);
    strcpy(c->name, name);
    return c;
}

void freeCourse(Course *pCourse)//frees memory from course
{
    free(pCourse);
}

int getCourseInfo(Course *pCourse, char *outputString) //i could not get this specific function to work. I just put in return 0 so the rest of it worked.
{
    return 0;

}

int setCourseNumber(Course *pCourse, int number) //sets course number 
{
    if (!pCourse)//checking for seg faults or errors
    {
        return 0;
    }
    pCourse->number = number;//copies info to structure
    return 1;
}

int setCourseName(Course *pCourse, char *name)//sets course name
{
    if (!pCourse || !name)//checking for seg faults or errors
    {
        return 0;
    }
    strcpy(pCourse->name, name);//copies info to structure
    return 1;
}

int setCourseDepartment(Course *pCourse, char *department)//sets course name
{
    if (!pCourse || !department)//checking for seg faults or errors
    {
        return 0;
    }
    strcpy(pCourse->department, department);//copies info to structure
    return 1;
}
