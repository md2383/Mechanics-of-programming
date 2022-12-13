// 
//
// Binary Search Tree definitions
//
// Author: CS @ RIT.EDU

#ifndef _WORD_TREE_H_
#define _WORD_TREE_H_

/// The definition of the tree structure
typedef struct TreeNode_st {
    char *       word;          ///< the word held in this node
    unsigned int frequency;     ///< how many times it has been seen
    struct TreeNode_st * left;  ///< node's left child
    struct TreeNode_st * right; ///< node's right child
} TreeNode;

// FUNCTIONS STUDENTS ARE REQUIRED TO IMPLEMENT

/// insert_word inserts a word into the binary search tree
/// by allocating nodes dynamically. If not present already,
/// insert the word and count one for the frequency.
/// If already present, increment the frequency and delete any
/// memory that was allocated in anticipation of inserting a value.
///
/// insert_word duplicates the word when it stores it.
///
/// @param handle - a pointer to the pointer to the root of the tree
/// @param word - string containing the word to be inserted
/// @pre handle must not be NULL

void insert_word( TreeNode ** root, const char * word );

/// find_word returns the number of times the word occurred.
/// @param node - a pointer to the root of the tree
/// @param word - string containing the word to find
/// @pre node must not be NULL
/// @return positive number if present or 0 if word is absent

int find_word( TreeNode * node, const char * word );

/// print_tree recursively traverses the tree and prints the payload.
/// output format is one COUNT\tWORD pair for each word in the tree.
/// @param node - a pointer to the root of the tree

void print_tree( const TreeNode * node );

#endif // WORD_TREE_H

