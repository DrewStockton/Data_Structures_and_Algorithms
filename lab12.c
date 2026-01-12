/*****************************************************************************
* CMP_SC 2050
* Lab 12
* By Drew Stockton (ATS85B)
* December 5th 2025
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab12.h"

//Creates a struct animal with malloc and copies parameters in
Animal* create_animal(int legs, const char* name) 
{
    if (!name) return NULL;
    Animal* animal = (Animal*)malloc(sizeof(Animal));
    if (!animal) return NULL;
    
    animal->num_of_legs = legs;
    strncpy(animal->name, name, 19);
    animal->name[19] = '\0';
    
    return animal;
}
//Mallocs a heap node and initializes fields
Heap* create_node(Animal* data)
{
    if (!data) return NULL;
    
    Heap* node = (Heap*)malloc(sizeof(Heap));
    if (!node) return NULL;
    
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->size = 1;
    
    return node;
}
//Updates size of a node based on size of each side
void update_size(Heap* node) 
{
    if (!node) return;
    
    int left_size = 0;
    int right_size = 0;
    
    if (node->left) 
    {
        left_size = node->left->size;
    }
    
    if (node->right)
    {
        right_size = node->right->size;
    }
    
    node->size = 1 + left_size + right_size;
}
//Swaps data of two nodes
void swap_data(Heap* a, Heap* b)
{
    if (!a || !b) return;
    
    Animal* temp = a->data;
    a->data = b->data;
    b->data = temp;
}
//calls insert_key
void insert(HeapInstance* heap, Animal* data)
{
    if (!heap || !data) return;
    
    heap->root = insert_key(heap->root, data, heap->cmp);
}
//Recursive function to insert a key into the heap
Heap* insert_key(Heap* root, Animal* data, AnimalCompareFunc cmp) 
{
    if (!data || !cmp) return root; //check for NULL
    
    if (!root) return create_node(data); //if root is null then create new node
    
    int left_size = 0;
    int right_size = 0;
    
    if (root->left) 
    {
        left_size = root->left->size; //get left side size
    } 
    if (root->right)
    {
        right_size = root->right->size; //get right side size
    }
    if (left_size <= right_size) 
    {
        root->left = insert_key(root->left, data, cmp); //insert into left side if its smaller, if not then insert into right side
    }
    else 
    {
        root->right = insert_key(root->right, data, cmp);
    }

    update_size(root); //calls update function to update new size

    if (root->left && cmp(root->left->data, root->data)) 
    {
        swap_data(root, root->left);
    }

    if (root->right && cmp(root->right->data, root->data)) 
    {
        swap_data(root, root->right);
    }
    
    return root;
}
//prints the heap using level-order traversal
void print_level_order(Heap* root)
{
    if (!root) //check for NULL
    {
        printf("Empty heap\n");
        return;
    }
    Heap** queue = (Heap**)malloc(sizeof(Heap*) * 1000);//malloc queue for nodes
    if (!queue) return;
    
    int front = 0;
    int rear = 0;
    
    queue[rear++] = root;
    
    while (front < rear) 
    {
        Heap* current = queue[front++];
        
        if (current) //print animal and data
        {
            printf("%s(%d) ", current->data->name, current->data->num_of_legs);
            
            if (current->left) {
                queue[rear++] = current->left;
            }
            if (current->right) {
                queue[rear++] = current->right;
            }
        }
    }
    
    printf("\n");
    free(queue);
}
// Compare function for min-heap based on number of legs
int compare_by_legs_min(Animal* a, Animal* b)
{
    if (!a || !b) return 0;

    if (a->num_of_legs < b->num_of_legs) 
    {
        return 1;
    }
    return 0;
}
// Compare function for max-heap based on number of legs
int compare_by_legs_max(Animal* a, Animal* b)
{
    if (!a || !b) return 0;

    if (a->num_of_legs > b->num_of_legs) 
    {
        return 1;
    }
    return 0;
}
// Compare function for min-heap based on name 
int compare_by_name_asc(Animal* a, Animal* b)
{
    if (!a || !b) return 0;
    
    int result = strcmp(a->name, b->name); 
    if (result < 0) 
    {
        return 1; 
    }
    return 0;
}
//Compare function for max-heap based on name
int compare_by_name_desc(Animal* a, Animal* b)
{
    if (!a || !b) return 0;
    
    int result = strcmp(a->name, b->name); 
    if (result > 0) 
    {
        return 1; 
    }
    return 0;
}
//recursively free a heap
void free_heap_node(Heap* heap_node)
{
    if (!heap_node) return;
    
    free_heap_node(heap_node->left);
    free_heap_node(heap_node->right);
    
    if (heap_node->data) 
    {
        free(heap_node->data);
    }
    free(heap_node);
}
//free all nodes
void free_heap(HeapInstance* heap)
{
    if (!heap) return;
    
    free_heap_node(heap->root);
    heap->root = NULL;
}
