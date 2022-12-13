/// http://www.dreamincode.net/forums/topic/55572-conways-game-of-life/
/// downloaded by copy-paste on 8/19/2015 and modified to use an infinite loop
/// and have different Rule functions.
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; the mix of TAB and spaces indentation
/// needs correction, and spacing between tokens is inconsistent.
/// The course style puts the '{' at the end of the function header, not
/// on a line of its own. You should make the formatting consistent.
/// </li>
/// <li>  documentation: documentation is non-existent except for this block.
/// </li>
/// </ol>
///
/// Miguel Dias Pinto - md2383@rit.edu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void header(void)
{
      printf("\n\t..Welcome to the Game of life..\n");
}

int getNeighbours(int size, char life[size][size], int r1, int c1)
{
      int row = r1, col = c1;
      int neighbours = 0;
      if(strcmp(&life[row][col], "*") == 0)
        {
        if(life[row - 1][col - 1] == '*')
           ++neighbours;
        if(life[row - 1][col] == '*')
           ++neighbours;
        if(life[row - 1][col + 1] == '*')
           ++neighbours;
        if(life[row][col - 0] == '*')
           ++neighbours;
        if(life[row][col + 1] == '*')
           ++neighbours;
        if(life[row + 1][col - 1] == '*')
           ++neighbours;
        if(life[row + 1][col] == '*')
           ++neighbours;
        if(life[row + 1][col + 1] == '*')
           ++neighbours;
      }
      return neighbours;
}

void birthRule(int size, char life[size][size])
{
      int neighbours = 0;
      char tempLife[size][size];
      
      for(int row = 0; row < size; row++){
          for(int col = 0; col < size; col++){

              neighbours = getNeighbours(size, life, row, col);

              if(life[row][col] == '*'){
                  if(neighbours >= 2 && neighbours <= 3){
                      tempLife[row][col] = '*';
                  }
                  else{
                      tempLife[row][col] = ' ';
                  }
              }
              else if(life[row][col] == ' '){
                  if(neighbours == 3){
                      tempLife[row][col] = '*';
                  }
                  else{
                      tempLife[row][col] = ' ';
                  }
              }
          }
      }

      for(int i = 0; i < size; i++){
          for(int j = 0; j < size; j++){
              life[i][j] = tempLife[i][j];
          }
      }

      return;
}

void print(int size, char life[size][size]){
    int row, col;
    for(row = 0; row < size; row++){
        for(col = 0; col < size; col++){
            printf("%c", life[row][col]);
        }
        puts("");
    }
}



int main(int argc, char *argv[])
{
    int num = argc;
    int size = 20;

    if(num > 1){
        size = atoi(argv[1]);
        }

    char life[size][size];
    int loops = 100;
    int orgs;
    int row, col;
    int count = 0;

    for(row = 0; row < size; row++){
        for(col = 0; col < size; col++){
            life[row][col] = ' ';
        }
    }

    header();

    printf("\nPlease enter the initial number of organisms: ");
    scanf("%i", &orgs);
    srand( 31 );

    for(int i = 0; i<orgs; i++)
      {
          row = rand() % size;
          col = rand() % size;
          life[row][col] = '*';                     //Fix 2: removed one '=' to make it the value rather than a boolean.
      }

      print(size, life);
      count++;

    while ( count < loops ) {
          birthRule(size, life);
          print(size, life);
          count++;
        }    
    return 0;
}
