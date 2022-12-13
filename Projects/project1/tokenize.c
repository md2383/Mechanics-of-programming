//Project1cd Courses/CS243/Projects/project1
//File: tokensize.c
//Name: Miguel Dias Pinto md2383@rit.edu
//
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "classes.h"

//CC_WS         (Whitespace)                = 0
//CC_NL         ('\n')                      = 1
//CC_ALPHA      (Alphabetic & Underscore)   = 2
//CC_ZERO       (Digit 0)                   = 3
//CC_OCTAL      (Octal/Decimal digits 1-7)  = 4
//CC_DECMIAL    (Decimal digits 8 & 9)      = 5
//CC_SLASH      ('/')                       = 6
//CC_STAR       ('*')                       = 7
//CC_ARITH      (other arithmetic op +,-,%) = 8
//CC_OTHER      (other ASCII character)     = 9
//CC_EOF        (end of file)               = 10
//CC_ERROR      (anything else)             = 11

const char *delim = " \t\n\r";

//#states, start and accepting all predefined at 0
int states = 0;
int start = 0;
int accept = 0;

//struct of each matrix cell
typedef struct matrix_cell{
    int state;
    char* action;
} cell;

//the matrix
static cell **matrix;


//Prints the matrix to output
void print_matrix(){
    printf("Scanning using the following matrix:\n");
    printf("     0    1    2    3    4    5    6    7    8    9   10   11");
    for(int i = 0; i < states; i++){
        
        //Checks for if there has to be a space before the first number or not
        if(i < 10){
            printf("\n %d", i);
        }
        else{
            printf("\n%d", i);
        }

        //loops through each value inside the matrix printing them
        for(int j = 0; j < 12; j++){
            matrix[i][j].action = strtok(matrix[i][j].action, delim);
            if(matrix[i][j].state < 0 || matrix[i][j].state > 9){
                printf("  %d%s", matrix[i][j].state, matrix[i][j].action);
            }
            else{
                printf("   %d%s", matrix[i][j].state, matrix[i][j].action);
            }
        }
    }

    //goes to a new line at the end of the printing
    printf("\n");
}

//Checks the next state based on the ASCII value
int check_ascii(int state, int ascii){
    int temp;
    if( ascii == 32){       
        temp = 0;
    }
    else if( ascii == 10){
        temp = 1;
    }
    else if( ( ascii <= 65 && ascii >= 90 ) || ascii == 95 || ( ascii >= 97 && ascii <= 122 ) ){
        temp = 2;
    }
    else if( ascii == 48){
        temp = 3;
    }
    else if( ascii >= 49 && ascii <= 55){
        temp = 4;
    }
    else if( ascii == 56 || ascii == 57){
        temp = 5;
    }
    else if( ascii == 47){
        temp = 6;
    }
    else if( ascii == 42){
        temp = 7;
    }
    else if( ascii == 37 || ascii == 43 || ascii == 45){
        temp = 8;
    }
    else if( ascii < -1 ||  ascii > 127){
        temp = 11;
    }
    else if( ascii < 0){
        temp = 9;
    }
    else{
        temp = 10;
    }
    return matrix[state][temp].state;
}

//main function that takes in input and builds everything
int main(int argc, char * argv[]){

    //checks to see if the file is being used correctly
    if(!(argc > 1)){
        fprintf(stderr, "usage: ./tokenize tmfile\n");
        exit(EXIT_FAILURE);
    }

    //if its being used correctly
    else{
        int len = 100000;
        char buff[len];
        char *ptr = NULL;
        char *token = NULL;
        FILE *f;

        f = fopen( argv[1], "r");
        
        //checks if the file exists, otherwise exits with error
        if(f == NULL){
            perror( argv[1] );
            exit(EXIT_FAILURE);
        }

        int n;  //int used to loop through the matrix

        //while the input is NOT null
        while((ptr = fgets(buff, len, f)) != NULL){
            
            //split input using delimiters
            token = strtok(buff, delim);
                
                //only run code if it doesn't start with a #
                if(!(token[0] == '#')){

                    //check for 'states'
                    if(strcmp(token, "states") >= 0){ 
                        token = strtok (NULL, delim);
                        char *end;
                        states = (int)(strtol(token, &end, 10));

                        //allocate enough memory
                        matrix = (cell **)malloc( states * sizeof(cell *));
                        for(int i = 0; i < states; i++){

                            //allocate enough memory
                            matrix[i] = (cell *)malloc( 12 * sizeof(cell));
                            for(int j = 0; j < 12; j++){

                                //This builds an empty matrix with everything set as '-1d'
                                matrix[i][j].action = (char *)malloc(sizeof(char *) * 1);
                                matrix[i][j].state = -1;
                                matrix[i][j].action = "d";
                            }
                        }
                    }

                    //check for 'start'
                    else if(strcmp(token, "start") >= 0){
                        token = strtok (NULL, delim);
                        char *end;
                        start = (int)(strtol(token, &end, 10));
                    }

                    //check for 'accept'
                    else if(strcmp(token, "accept") >= 0){
                        token = strtok (NULL, delim);
                        char *end;
                        accept = (int)(strtol(token, &end, 10));
                    }

                    //check if it is on the numbers
                    else if(isdigit(token[0])){
                        char *end;
                        n = (int)(strtol(token, &end, 10));
                        token = strtok (NULL, " ");

                        //while the token isn't Null, loop through each value and add it to the matrix
                        while(token != NULL){
                            int a, b = 0;
                            char c = ' ';

                            //these if statements find the state column and character
                            if(token[1] == '/'){ 
                                a = token[0] - '0';
                                if(isdigit(token[3])){
                                    b = (token[2] - '0') * 10;
                                    b += (token[3] - '0');
                                    c = (char)token[4];
                                }
                                else{
                                    b = token[2] - '0';
                                    c = (char)token[3];
                                }
                            }
                            else{
                                a = ( token[0] - '0') * 10;
                                a += token[1] - '0';
                                if(isdigit(token[4])){
                                    b = (token[3] - '0') * 10;
                                    b += (token[4] - '0');
                                    c = (char)token[5];
                                }
                                else{
                                    b = token[3] - '0';
                                    c = (char)token[4];
                                }
                            } 
                            matrix[n][a].state = b;
                            //because we set everything to d before, we just check if its s and replace it
                            if(c == 's'){
                                matrix[n][a].action = "s";
                            }
                            token = strtok (NULL, " ");
                            }
                    }
                }
        }

        //Closes the file
        fclose(f);
        
        //prints the matrix
        print_matrix();

        //Creates all the values for the char inputs
        char tempc = getchar();
        int cRow = start;
        char *word = (char*)malloc(1);
        bool prev_accepted = true;
        int i = 0;
    
        //while the charatcer exists
        while(tempc != -1){

            //checks if it's the starting state
            if(cRow == start){

                //checks if its a previously accepted state
                if(prev_accepted == true){
                    printf("%d ", cRow);
                }
            }

            //sends to the following row
            cRow = check_ascii(cRow, (int)tempc);
            
            //checks if it is previously accepted, if so print the value of the row
            if(prev_accepted == true){
                printf("%d ", cRow); 
            }
            
            //creates the 'word' from characters
            word = (char*)realloc(word, i + 1);
            word[i] = tempc;
            
            //checks if the current row is the accepting row
            if(cRow == accept){

                //checks if the previous was accepted, if so it prints, else it just sets the bool to true
                if(prev_accepted == true){
                    word[i] = '\0';
                    printf("recognized '%s'\n", word);
                    cRow = start;
                    free(word);
                    word = (char*)malloc(1);
                    i = -1;
                }
                else{
                    prev_accepted = true;
                    cRow = start;
                    free(word);
                    word = (char*)malloc(1);
                    i = -1;
                }
            }

            //checks if rejected
            if(cRow < 0){
                printf("rejected\n");
                prev_accepted = false;
                free(word);
                word = (char*)malloc(1);
                i = -1;
                cRow = start;
            }
            i++;
            tempc = getchar();
        }
    //at the end of the file, its equal to eof
    if(tempc == EOF){
        printf("0 9 EOF\n");
    }
}
    return 0;    
}
