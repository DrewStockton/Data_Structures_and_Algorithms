#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab3.h"

Student** read_students_from_file(const char* filename)
{
    FILE *fp;
    fp = fopen("students.txt","r");
    if (fp==NULL)
    {
        return NULL;
    }
    int grades[NUM_GRADES]
    fscanf(fp, "%d %d %d %d %d",&grades[0],&grades[1],&grades[2],&grades[3],&grades[4]);


    Student **s;
    int * p;
    p = malloc(NUM_GRADES * sizeof(Student*)+sizeof(int));
    p[0] = NUM_GRADES;
    p++
    s = (Student**)p;
    for (int i=0; i<CLASSES; i++)
    {
        p = malloc(grades[i]*(sizeof(Student)+sizeof(int)));
        p[0] = grades[i];
        p++;
        s[i]=p;
    }


    char firstname[50];
    char lastname[50];
    char letter;
    float gpa;
    int row =0;
    for (int i=0; i<NUM_GRADES; i++)
    {
        fscanf(fp, "%s %s %c %f", firstname,lastname,&letter,&gpa);
        switch (letter)
        {
            case 'A':
                row=0;
                break;
            case 'B':
                row=1;
                break;
            case 'C':
                row=2;
                break;
            case 'D':
                row=3;
                break;
            case 'F':
                row=4;
                break;
        }
        int count[] = {0,0,0,0,0};
        strcpy(s[row][count[row]].name, firstname);
        strcpy(s[row][count[row]].lastname, lastname);
        strcpy(s[row][count[row]].gpa, gpa);
        count[row]++;
    }
}
