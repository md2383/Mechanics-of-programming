#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "word_tree.h"

int main( int argc, char * argv[]  ){
    char *buf = NULL;
    size_t len = 0;
    char *token = NULL;
    char *word = NULL;

    TreeNode* rt = NULL;



    while(getline(&buf, &len, stdin) > 0){
        
        token = strtok(buf, " ");
        while(token != NULL){
           word = token;
           if(word[strlen(word) - 1] == '\n'){
               word[strlen(word) - 1] = '\0';
            }
            for(int i = 0; i < (int) strlen(word); i++){
                if(!(isalpha(word[i]) || isdigit(word[i]) || word[i] == '-' || word[i] == '_' || word[i] == '\'')){
                    if(i == 0){
                        word++;
                    }
                    else{
                        word[strlen(word) - 1] = '\0';
                    }
                }
            }
        insert_word(&rt, word);
        //printf("Word: %s \n", word);
        token = strtok(NULL, " ");
        }
    }
    printf("Query Results: \n");
    for(int i = 1; i < argc; i++){
        printf("%d\t%s\n", find_word(rt, argv[i]), argv[i]);
    }
    printf("Word Tree: \n");
    print_tree(rt);
    if(buf != NULL){
        free( buf );
    }
    return 0;
}


