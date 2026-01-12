/*****************************************************************************
* CMP_SC 2050
* Lab 10
* By Drew Stockton
* November 7th 2025
*****************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "lab10.h"

/* createNode: mallocs memory for a Node, sets data to data and left/right to NULL*/
BSTNode* createNode(int data)
{
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if (!node) return NULL;
    node->data = data;
    node->left = NULL, node->right = NULL;

    return node;
}
/*insertNode
    uses recursion to sort through the BST, making sure to go down the appropriate side

*/
BSTNode* insertNode(BSTNode* root, int data, int* success)
{
    if (root == NULL)
    {
        BSTNode* node = createNode(data);
        if(node==NULL)
        {
            *success = 0;
            return 0;
        }
        *success = 1;
        return node;
    }

    if (data < root->data)
    {
        root->left = insertNode(root->left, data, success);
    }
    else if (data > root->data)
    {
        root->right = insertNode(root->right, data, success);
    }
    else
    {
        *success = 0;
    }

    return root;

}
/* getHeightHelper: uses recursion to sort through the BST, finding the height*/
int getHeightHelper(BSTNode* node)
{
   if (node == NULL) return -1;

   int leftHeight = getHeightHelper(node->left);
   int rightHeight = getHeightHelper(node->right);

   int height;
   if (leftHeight > rightHeight)
   {
        height = leftHeight + 1;
   }
   else
   {
    height = rightHeight + 1;
   }

   return height;
}
/* uses recursion to sort the BST and make sure each node is valid */
int isValidBSTHelper(BSTNode* node, int min, int max)
{
    if (node == NULL) return 1;
    
    if (node->data <= min || node->data >= max)
    {
        return 0;
    }

    if (isValidBSTHelper(node->left, min, node->data) == 0)
    {
        return 0;
    }

    if (isValidBSTHelper(node->right, node->data, max) == 0)
    {
        return 0;
    }

    return 1;
}
//uses recursion to free each node, going all the way down the left first, then right
void freeNodes(BSTNode* node)
{
    if (node == NULL) return;

    freeNodes(node->left);
    freeNodes(node->right);
    free(node);
}

//-------- main functions ---------------------------------


/*initBST: initializes a BST, returns NULL if malloc fails*/
BST* initBST()
{
    BST* b = (BST *)malloc(sizeof(BST));
    if (!b) return NULL;
    b->root = NULL;
    b->size = 0;

    return b;
}
// insertBST: inserts a BST using insertNode, grows the size if it successfully inserts
int insertBST(BST* tree, int data)
{
    if (tree == NULL) return 1;
    int success = 0;
    tree->root = insertNode(tree->root, data, &success);

    if (success == 1)
    {
        tree->size++;
        return 0;
    }
    else
    {
        return 1;
    }


}
//getHeightBST: uses getHeightHelper to find the height
int getHeightBST(BST *tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        return -1;
    }
    return getHeightHelper(tree->root);
}
/*getMinimum & getMaximum
    each function goes down a side of the BST, and returns the value at the end (since its sorted, will be the biggest or smallest)

*/
int getMinimum(BST* tree)
{
    if (tree == NULL || tree->root == NULL) return -1;

    BSTNode* node = tree->root;
    while (node->left != NULL)
    {
        node = node->left;
    }

    return node->data;
}
int getMaximum(BST* tree)
{
    if (tree == NULL || tree->root == NULL) return -1;
    BSTNode* node = tree->root;
    while (node->right != NULL)
    {
        node = node->right;
    }

    return node->data;

}


//isValidBST: uses helper function and returns 0 or 1 on success
int isValidBST(BST* tree)
{
    if (tree==NULL) return 0;
    return isValidBSTHelper(tree->root,INT_MIN,INT_MAX);
}

//freeBST: uses freeNodes to free the BST
void freeBST(BST* tree)
{
    if (tree == NULL) return;
    freeNodes(tree->root);
    free(tree);
}

