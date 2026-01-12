/*****************************************************************************
* CMP_SC 2050
* Lab 5
* By Drew Stockton
* October 3rd 2025
*****************************************************************************/
#include <stdio.h>
#include "lab5.h"

Node* initList()
{
    return NULL; //returns a NULL struct
}

Node* insertAtTail(Node* head, int data, int* error)
{
    Node* n = malloc(sizeof(Node)); //malloc a new node
    if (n == NULL)//memory leak check
    {
        *error = 1; 
        return head;
    }
    n->data = data;
    n->next = NULL;

    if (head == NULL)//memory leak check
    {
        *error = 0;
        return n;
    }

    Node* c = head;
    while (c->next != NULL)//find tail
    {
        c = c->next;
    }
    c->next = n;
    *error=0;
    return head;
}

Node *removeFromHead(Node* head, int* data)
{
    if (head==NULL)//memory leak check
    {
        return NULL;
    }
    *data=head->data; 
    Node* newHead = head->next;
    free(head);
    return newHead; //return new node without the part you removed
}
void printList(Node *head)
{
   int size = 0;
   Node *c = head;
   while (c != NULL) //find size
   {
        size++;
        c=c->next;
   }

    int* list = (int *)malloc(size * sizeof(int)); //malloc an int array
    c = head;
    int s = 0;
    while (c != NULL) 
    {
        list[s++] = c->data; //input values of node into array
        c = c->next;
    }

    for (int i = size - 1; i >= 0; i--) //for loop backwards, printing the array 
    {
        printf("%d", list[i]);
        if (i > 0) 
        {
            printf(", ");
        }
    }
    printf("\n");
    free(list);
}
int listContains(Node* head, int data)
{
    
    Node* c = head;
    while (c != NULL)
    {
        if (c->data == data) //if the list contains the value
        {
            return 1;
        }
        c=c->next;
    }
    return 0;
}

void freeList(Node* head)
{
    Node* c = head;
    while (c != NULL)
    {
        Node* next = c->next; //give new node the value
        free(c); //free old node
        c=next; //set old node to new node
    }
}
