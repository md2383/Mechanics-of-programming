// File: $Id: offspring.h
//
// Project 2: Offspring Family Tree
// Author: Miguel Dias Pinto (md2383)

#ifndef OFFSPRING_H
#define OFFSPRING_H

#include "trimit.h"

// Struct to represent nodes in the tree.
typedef struct TreeNode_N {
    char *name;
    struct TreeNode_N **children;
    size_t child_count;
} TreeNode;

/**
 * Creates a new node for the tree.
 *
 * @param name name of the node.
 * @return pointer to new node.
 */
TreeNode *createNode(const char *name);

/**
 * Destroys tree and frees memory
 *
 * @param tree tree root node to destroy
 */
void destroyTree(TreeNode *tree);

/**
 * Finds the node with the name in the tree.
 *
 * @param tree tree root node to start search in.
 * @param name name of node
 * @return pointer to node, or NULL if not found.
 */
TreeNode *findNode(TreeNode *tree, const char *name);

/**
 * Prints node and offspring
 *
 * @param node node to be printed
 */
void printNode(TreeNode *root);

/**
 * Finds Tree size (# of nodes)
 *
 * @param root Tree root node
 * @param name name of node to find size for
 * @return size of the tree
 */
size_t getTreeSize(TreeNode *root, const char *name);

/**
 * Find height of Tree
 *
 * @param root Tree root node
 * @param name name of node to find height for
 * @return height of the tree
 */
int getTreeHeight(TreeNode *root, const char *name);

/**
 * Initializes tree with a NULL node.
 *
 * @param root pointer to tree root node.
 */
void initializeTree(TreeNode **root);

/**
 * Add's child to parent if found in tree
 *
 * @param root pointer to tree root node.
 * @param parentName name of parent node.
 * @param childName name of child node.
 */
void handleAddCommand(TreeNode **root, const char *parentName, const char *childName);

/**
 * Finds a node in the treee
 *
 * @param root pointer to tree root node.
 * @param name name of node to find.
 */
void handleFindCommand(TreeNode *root, const char *name);

/**
 * Print's list of available commands
 */
void handleHelpCommand();

/**
 * Takes a file as input and creates a node accordingly
 *
 * @param root pointer to tree root node
 * @param filename name of file
 */
void fileToTree(TreeNode **root, const char *filename);

#endif // OFFSPRING_H
