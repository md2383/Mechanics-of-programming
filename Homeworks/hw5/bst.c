// File: $Id: bst.c,v 1.0 2023/06/29 15:19:00 csci243 Exp $
//
// Binary Search Tree implementation
//
// Author: md2383

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/// build_tree() 
///     Dynamically build BST by allocating nodes on the heap
///             Note that the BST will support duplicate values by
///             placing them into the left child's subtree
///
/// args -
///        root - a pointer to the pointer to the root of the tree
///               to build this tree on to.
///        elements - array of integers to add to the tree
///        count - the number of integers in the array
void build_tree(TreeNode** root, const int elements[], const int count) {
    *root = NULL;

    //Loop through each 'count' to build the tree
    for (int i = 0; i < count; i++) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = elements[i];
        newNode->left = NULL;
        newNode->right = NULL;

        //Create new root if root is NULL
        if (*root == NULL) {
            *root = newNode;
        } else {
            TreeNode* current = *root;
            while (1) {
            
                //Puts the data on the left if it is less than current data
                if (newNode->data <= current->data) {
                    if (current->left == NULL) {
                        current->left = newNode;
                        break;
                    } else {
                        current = current->left;
                    }
                } 
                
                //Puts the data on the right if it is not less than the current data
                else {
                    if (current->right == NULL) {
                        current->right = newNode;
                        break;
                    } else {
                        current = current->right;
                    }
                }
            }
        }
    }
}

/// traverse()
///    Recursively traverses the tree and prints the value of each
///    node.
///
/// args -
///        root - a pointer to the root of the tree to traverse
///        type - the traversal type
void traverse(const TreeNode* root, const TraversalType type) {

    //If the tree exists, loop through the order
    if (root != NULL) {
        if (type == PREORDER) {
            printf("%d\n", root->data);
            traverse(root->left, type);
            traverse(root->right, type);
        } else if (type == INORDER) {
            traverse(root->left, type);
            printf("%d\n", root->data);
            traverse(root->right, type);
        } else if (type == POSTORDER) {
            traverse(root->left, type);
            traverse(root->right, type);
            printf("%d\n", root->data);
        }
    }
}

/// cleanup_tree()
///    Cleanup all memory management associated with the nodes on the heap
///
/// args
///      root - the current root of the tree
void cleanup_tree(TreeNode* root) {

    //If the root exists, clear the memory
    if (root != NULL) {
        cleanup_tree(root->left);
        cleanup_tree(root->right);
        free(root);
    }
}

/// main()
///    Allows input and output to run with the making of tree's
///
/// args
///      argc - # of command line arguments
///      argv - command line arguments
int main(int argc, char *argv[]) {
    //If there isn't a second argument return
    if(argc != 2){
      fprintf(stderr, "Usage: %s #\n", argv[0]);
      return EXIT_FAILURE;
    }
    
    //If the number is less than or equal to 0 return
    int count = atoi(argv[1]);
    if( count <= 0){
      fprintf(stderr, "# must be greater than 0\n");
      return EXIT_FAILURE;
    }
    
    //Create an empty root node
    TreeNode* root = NULL;

    //Prompt user for the number of elements to be in the tree
    printf("Enter %d integer values to place in the tree:\n", count);
    int* elements = (int*)malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        scanf("%d", &elements[i]);  //Add each number into the element
    }
    
    //Build the tree using the size of the elements
    build_tree(&root, elements, count);
    
    //Prints all element values
    printf("Input values:\n");
    for (int i = 0; i < count; i++) {
        printf("%d\n", elements[i]);
    }
    
    //Perform a preorder traversal
    printf("Preorder:\n");
    traverse(root, PREORDER);

    //Perform an inorder traversal
    printf("Inorder:\n");
    traverse(root, INORDER);

    //Perform a postorder traversal
    printf("Postorder:\n");
    traverse(root, POSTORDER);

    //Clean up the memory
    cleanup_tree(root);
    
    //Free the elements memory
    free(elements);
    
    
    return 0;
}

