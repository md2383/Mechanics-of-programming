// 
// File: trie.c 
// Starter trie module for an integer-keyed trie ADT data type
// @author CS@RIT.EDU
// @author Miguel Dias Pinto md2383
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#include "trie.h"

#define STACK_ALLOC_UNIT = 1;

/// Node_s: binary tree node
/// Node is a pointer to a dynamically allocated struct Node_s.
/// NodeH is a pointer to a pointer to a struct Node_s.
typedef struct Node_s {
    struct Node_s *left;
    Entry *data;
    struct Node_s *right;
} * Node;

typedef Node * NodeH;          ///< handle to a trie node

/// Trie_s: this is where the root node is stored
struct Trie_s {
    Node root;
};

// global constants for bit operations and sizes
// used by the application program

/// Create a Trie instance and initialize its fields.
/// @return pointer to the Trie object instance or NULL on failure
/// @post Trie is NULL on failure or initialized with a NULL trie root
Trie ibt_create( void ){
    Trie new;

    new = (Trie) malloc( sizeof(struct Trie_s) );

    if(new != 0){
        new->root = NULL;
    }
    return new;
}


/// Destroy the trie and free all storage.
/// Uses Trie's Delete_value function to free app-specific (key and) value;
/// If the Trie's Delete_value function is NULL,
/// then call free() on the value in (key,value).
/// @param trie a pointer to a Trie instance
/// @pre trie is a valid Trie instance pointer
/// @post the storage associated with the Trie and all data has been freed
void ibt_destroy( Trie trie){

    if( trie->root != NULL ){
        free( trie->root );
    }
    free( trie );
}

///Checks the bit value of the specific key at 31-d
///@param key, d
///@return bit value
ikey_t bit( ikey_t key, int d){
    return (key << (31-d));
}

///creates an empty node from Entry
///@param e
///@return new node
Node createEmptyNode(Entry *e){
    Node n = (Node)malloc(sizeof(Node));
    n->data = e;
    n->left = NULL;
    n->right = NULL;
    return n;
}

///creates an empty node without a given Entry
///@return new node
Node createEmptyNodeNoEntry(){
    Node n = (Node)malloc(sizeof(Node));
    Entry *e = (Entry *)malloc(sizeof(Entry));
    n->data = e;
    n->left = NULL;
    n->right = NULL;
    return n;
}

///splits the nodes left or right based on the bit
///@param a, b, d
///return the root node
Node split(Node a, Node b, int d){
    Node c = createEmptyNodeNoEntry();
    ikey_t key1 = a->data->key, key2 = b->data->key;
    switch(bit(key1, d)*2 + bit(key2, d))
    {
        case 0: c->left = split(a, b, d+1); break;
        case 1: c->left = a; c->right = b; break;
        case 2: c->right = a; c->left = b; break;
        case 3: c->right = split(a, b, d+1); break;
    }
    return c;
}

///inserts an entry into the node given the d and nodes.
///@param n, e, d
///@return root node
Node insertR(Node n, Entry *e, int d){
    if (n == NULL){
        return createEmptyNode(e);
    }
    if(n->left == NULL && n->right == NULL){
        return split(createEmptyNode(e), n, d);
    }
    if(bit(e->key, d) == 0){
        n->left = insertR(n->left, e, d+1);
    } else {
        n->right = insertR(n->right, e, d+1);
    }
    return n;
}

/// insert an entry into the Trie as long as the entry is not already present
/// @param trie a pointer to a Trie instance
/// @param TODO what needs to be copied into the trie node
/// @post the trie has grown to include a new entry IFF not already present
void ibt_insert( Trie trie, Entry e){
    trie->root = insertR(trie->root, &e, 0);
}

///looks for the most similar key compared to the root
///@param root, key, d
///@return the search result
Entry *quickSearch(Node root, ikey_t key, int d){
    if (root == NULL){
        Entry *e = (Entry *)malloc(sizeof(Entry));
        return e;
    }
    if (root->left == NULL && root->right == NULL){
        return root->data;
    }
    if(bit(key, d) == 0){ //%d == 0?
        return quickSearch(root->left, key, d++);
    }
    else{
        return quickSearch(root->right, key, d++);
    }
    return NULL;
}
/// search for the key in the trie by finding
/// the closest entry that matches key in the Trie.
/// @param trie a pointer to a Trie instance
/// @param key the key to find 
/// @return entry representing the found entry or a null entry for not found
Entry ibt_search( Trie trie, ikey_t key){
    Entry *e = quickSearch(trie->root, key, 0);
    Entry a = *e;
    return a;
}

///counts the number of nodes
///@param root, d
///@return number of nodes
size_t countnodes(Node root, int d){
    if (root == NULL){
        return (size_t) d;
    }
    if (root->left == NULL && root->right == NULL){
        d++;
        return d;
    }
    if(root->left != NULL){
        int newd = countnodes(root->left, d++);
        d += newd;
    }
    if(root->right != NULL){
        int newd = countnodes(root->right, d++);
        d += newd;
    }
    return (size_t) d;
}

///counts the number of leafs
///@param root, d
///@return the number of leafs
size_t countleaf(Node root, int d){
    if (root == NULL){
        return (size_t) d;
    }
    if (root->left == NULL && root->right == NULL){
        d++;
        return d;
    }
    if(root->left != NULL){
        int newd = countnodes(root->left, d);
        d = newd;
    }
    if(root->right != NULL){
        int newd = countnodes(root->right, d);
        d = newd;
    }
    return (size_t) d;
}

///gets the height of the tree
///@param root, d
///@return height of the tree
size_t getheight(Node root, int d){
    if (root == NULL){
        return (size_t) d;
    }
    if (root->left == NULL && root->right == NULL){
        d++;
        return d;
    }
    if(root->left != NULL){
        int newd = countnodes(root->left, d++);
        if( d < newd )
            d = newd;
    }
    if(root->right != NULL){
        int newd = countnodes(root->right, d++);
        if( d < newd )
            d = newd;
    }
    return (size_t) d;
}

/// get the size of the trie or number of leaf elements
/// @param trie a pointer to a Trie instance
/// @return size of trie 

size_t ibt_size( Trie trie){
    return countleaf(trie->root, 0);
}

/// get the node count of the trie: the number of internal nodes
/// @param trie a pointer to a Trie instance
/// @return the count of internal nodes

size_t ibt_node_count( Trie trie){
    return countnodes(trie->root, 0); 
}

/// get height of the trie
/// @param trie a pointer to a Trie instance
/// @return height of trie

size_t ibt_height( Trie trie){
    return getheight(trie->root, 0);
}

///prints out the values of the trie to a stream
///@param root, f
///@return 0
int Show_value(Node root, FILE * f){
    if (root == NULL){
        return 0;
    }
    if (root->left == NULL && root->right == NULL){
        fprintf(f, "%d: (%s, %s: %s, %s, %s)\n", root->data->key, root->data->givenIP, root->data->country_code, root->data->country_name, root->data->province, root->data->city);
        return 0;
    }
    if(root->left != NULL){
        Show_value(root->left, f);
        fprintf(f, "%d: (%s, %s: %s, %s, %s)\n", root->data->key, root->data->givenIP, root->data->country_code, root->data->country_name, root->data->province, root->data->city);
    }
    if(root->right != NULL){
        fprintf(f, "%d: (%s, %s: %s, %s, %s)\n", root->data->key, root->data->givenIP, root->data->country_code, root->data->country_name, root->data->province, root->data->city);
        Show_value(root->right, f);
    }
    return 0;
}

/// Perform an in-order traversal to show each (key, value) in the trie. 
/// Uses Trie's Show_value function to show each leaf node's data,
/// and if the function is NULL, output each key and value in hexadecimal.
///
/// @param trie a pointer to a Trie instance
/// @param stream the stream destination of output
void ibt_show( Trie trie, FILE * stream){
    Show_value(trie->root, stream);
}
