/// 
/// File: triangle.c 
/// 
/// A program to print out multiple triangles of the form:
/// <pre>
///    *
///  ***
/// ****  
/// </pre>
/// 
/// @author md2383 : Miguel Dias Pinto
/// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>

/**
 *  Function: drawTriangle
 *
 *  Description: Draw a triangle whose base width is 'size'.
 *  Note: If size is even, the function makes a 'size + 1' triangle. 
 * 
 *  @param size  the width of the base of the triangle to draw
 */
// TODO_WRITE_DRAWTRIANGLE_FUNCTION HERE
void drawTriangle(int size){
  
  //if even
  if(size %2 == 0){
    size++;
  }
  
  int width = size;
  
  for (int row = 1; row <= size; row += 2) {
        int spaces = (width - row) / 2;
        for (int i = 0; i < spaces; i++) {
            printf("  ");
        }
        for (int j = 0; j < row; j++) {
            printf("*");
        }
        printf("\n");
    }
}
      

/**
 *  Function: main 
 *
 *  Description: draws pyramid triangles of size 1, 5, and 6.
 *
 *  @returns errorCode  error Code; EXIT_SUCCESS if no error
 */
// TODO_WRITE_MAIN_FUNCTION HERE
int main(void) {
    int triangleSize1 = 1;
    int triangleSize2 = 5;
    int triangleSize3 = 6;
    
    drawTriangle(triangleSize1);    //draw the first size
    printf("\n");
    drawTriangle(triangleSize2);    //draw the second size
    printf("\n");
    drawTriangle(triangleSize3);    //draw the third size

    return 0;
}

