#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "word_tree.h"

TreeNode*  nTreeNode(char * c){
    TreeNode * t = NULL;
    t = malloc(sizeof(TreeNode));
    t->word = malloc(strlen(c) + 1);
    strcpy(t->word, c);
    t->frequency = 1;
    t->left = NULL;
    t->right = NULL;
    return t;
    }

void insert_word(TreeNode ** root, const char * word){
    char newWord[strlen(word) + 1];
    strcpy(newWord, word);

    if( *root == NULL){
        *root = nTreeNode(newWord);
    }
    else{
        int comp = strcasecmp(newWord, (*root)->word);
        if(comp == 0){
            (*root)->frequency++;
            }
        else{
            if(comp > 0){
                insert_word(&((*root)->right), newWord);
            }
            else{
                insert_word(&((*root)->left), newWord);
            }
        }
    }
}
