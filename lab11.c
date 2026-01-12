/*****************************************************************************
* CMP_SC 2050
* Lab 11
* By Drew Stockton
* November 14th 2025
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lab11.h"


typedef struct _BSTNode { 
    void *data;
    struct _BSTNode *left;
    struct _BSTNode *right;
} BSTNode;

typedef struct _BST {
    BSTNode *root;
    int size;
    GETKEYFUNCTION getKey;
    PRINTDATAFUNCTION printData;
}BST;


//function mallocs a BST and uses the function pointers
BST* initBST(GETKEYFUNCTION getKeyDelegate, PRINTDATAFUNCTION printDataDelegate)
{
    if (!getKeyDelegate || !printDataDelegate) return NULL;

    BST *tree = malloc(sizeof(BST));

    tree->root = NULL;
    tree->size = 0;
    tree->getKey = getKeyDelegate;
    tree->printData = printDataDelegate;
    return tree;
}

//helper function for insertBST
//this function makes a node, and then uses the keys to insert a node at the correct position recursively
BSTNode* insertNodeHelper(BST* tree, BSTNode* root, void* data)
{
    if (!tree || !data) return root;
    if (!root)
    {
        BSTNode* node = malloc(sizeof(BSTNode));
        if (!node) return NULL;
        node->data = data;
        node->left = node->right = NULL;
        tree->size++;
        return node;
    }

    int key = tree->getKey(data);
    int rootKey = tree->getKey(root->data);

    if (key < rootKey)
        root->left = insertNodeHelper(tree, root->left, data);
    else if (key > rootKey)
        root->right = insertNodeHelper(tree, root->right, data);
    return root;
}
//uses the helper function to insert
void insertBST(BST* tree, void* data)
{
    if (!tree || !data) return;
    tree->root = insertNodeHelper(tree, tree->root, data);
}

//searches the left side to find minimum
void * getMinimum(BST* tree) 
{
    if (!tree || !tree->root) return NULL;

    BSTNode *node = tree->root;
    while (node->left != NULL)
        node = node->left;

    return node->data;
}
//searches right side to find maximum
void * getMaximum(BST* tree) 
{
    if (!tree || !tree->root) return NULL;

    BSTNode *node = tree->root;
    while (node->right != NULL)
        node = node->right;

    return node->data;
}
//helper function for freeBST: frees an individual node using recursion to free until the end of the tree
void freeNode(BSTNode* node)
{
    if (!node) return;

    freeNode(node->left);
    freeNode(node->right);

    
    free(node);
}
//calls freeNode to free the entire tree, then the tree itself
void freeBST(BST* tree)
{
    if (!tree) return;

    freeNode(tree->root);
    free(tree);
}
//returns size of BST
int getSize(BST * tree)
{
    if (tree==NULL) return 0;
    return tree->size;
}
//uses recursion to print the entire left side, then the right, so its in ascending order
void inOrderPrintBST(BST *tree)
{
    if (tree == NULL || tree->root == NULL) return;

    BSTNode *node = tree->root;

    BST left = *tree;
    left.root = node->left;
    inOrderPrintBST(&left);

    tree->printData(node->data);

    BST right = *tree;
    right.root = node->right;
    inOrderPrintBST(&right);

    tree->printData(node->data);
}
