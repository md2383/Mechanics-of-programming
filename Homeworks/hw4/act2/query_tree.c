#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "word_tree.h"

//Function finds a word inside node
int find_word(TreeNode*  node, const char* word){
    if(node != NULL){
        int compareWrd = strcasecmp(word,(node)-> word);
        if( compareWrd == 0){
            return (node)->frequency;
            }
        else{
            if(compareWrd < 0){
                return find_word((node)->left, word);
            }
            else{
                return find_word((node)->right, word);
            }
        }
    }
    else{
        return 0;
    }
}


//Function prints tree from node
void print_tree(const TreeNode* node){
    if((node) != NULL){
        if((node) -> right != NULL){
            print_tree((node)->right);
        }
        printf("%d\t%s\n", (node)->frequency, (node)->word);
        if((node)-> left != NULL){
            print_tree((node)->left);
        }
    }
}
