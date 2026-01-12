/*****************************************************************************
* CMP_SC 2050
* Lab 6
* By Drew Stockton
* October 10th 2025
*****************************************************************************/
#include <stdio.h>
#include "lab6.h"
#include "stdlib.h"

int makeList(Node **list)
{
    if (list == NULL) //seg fault check
    {
        return 1;
    }
   *list = malloc(sizeof(Node)); //malloc new dummy Node
    if (*list == NULL) //seg fault check
    {
        return 1;
    }
   (*list)->next = NULL; //set dummy node to NULL
   (*list)->data = NULL;

   return 0;

}
int getSize(Node *list)
{
    if (list == NULL)//seg fault check
    {
        return 0;
    }
    int count = 0;

    Node* n = list->next;
    if (n==NULL)//seg fault check
    {
        return 0;
    }
    while(n != NULL)
    {
        count++; //counts elements
        n = n->next;
    }

    return count;
}
void * getAtIndex(Node *list, int index)
{
    if (list == NULL || index < 0)//seg fault check
    {
        return NULL;
    }
    int size = getSize(list);
    if (index >= size)//seg fault check
    {
        return NULL;
    }
    Node* n = list->next;
    int i=0;
    while (n != NULL)
    {
        if (i==index)
        {
            return n->data;
        }
        n = n->next;
        i++;
    }
    return NULL;
}
int insertAtTail(Node *list, void *data)
{
    if (list == NULL)//seg fault check
    {
        return 1;
    }
    Node* n = malloc(sizeof(Node));
    if (n==NULL)//seg fault check
    {
        return 1;
    }
    n->data = data;
    n->next = NULL;

    Node* c = list;
    while (c->next != NULL) //when it reaches the end
    {
        c = c->next;
    }
    c->next = n;

    return 0;
}
void * removeFromHead(Node *list)
{
    if (list == NULL || list->next == NULL)//seg fault check
    {
        return NULL;
    }
    Node* remove = list->next; //puts a freeable node in the list
    void* data = remove->data;

    list->next = remove->next;
    free(remove); //free

    return data; //return what was freed
}
void freeList(Node **list)
{
    if (list == NULL || *list == NULL)//seg fault check
    {
        return;
    }
    Node* n = *list; //new node
    Node* c;

    while (n != NULL) //while looping the function, free each part
    {
        c = n->next;
        free(n);
        n = c;
    }
    *list = NULL; //set whole list to NULL
}
