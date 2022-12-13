#include <stdio.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Matrix.h"

struct matrix_st{
    float **values;
    int row;
    int col;
};

Matrix mat_create( size_t rows, size_t cols){
    Matrix newMatrix;
    
    newMatrix = (Matrix)malloc(sizeof(struct matrix_st));
    newMatrix->values = (float**)malloc(((int)(rows))*sizeof(float*));
    
    newMatrix->row = (int) rows;
    newMatrix->col = (int) cols;

    for(int i = 0; i < (int) rows; i++){
        newMatrix->values[i] = (float*)malloc(sizeof(float)*((int)(cols)));
        for(int j = 0; j < (int) cols; j++){
            if(rows == cols && i == j){
                newMatrix->values[i][j] = 1.000;
            }
            else{
                newMatrix->values[i][j] = 0.000;
            }
        }
    }
    return newMatrix;
}

void mat_destroy( Matrix mat){
    for(int i = 0; i < mat->row; i++){
        free(mat->values[i]);
    }
    free(mat->values);
    free(mat);
}

void mat_init( Matrix mat, const float data[] ){
    int x = 0;
    for(int i = 0; i < mat->row; i++){
        for(int j = 0; j < mat->col; j++){
            mat->values[i][j] = data[x];
            x++;
        }
    }
}

Matrix mat_duplicate( const Matrix mat){
    
    if(mat == NULL || mat->values == NULL){
        return NULL;
    }

    Matrix newMatrix;
    
    newMatrix = (Matrix)malloc(sizeof(struct matrix_st));
    newMatrix->values = (float**)malloc(((int)(mat->row))*sizeof(float*));
    
    for(int i = 0; i < mat->row; i++){
        newMatrix->values[i] = (float*)malloc(sizeof(float)*((int)(mat->col))); 
        for(int j = 0; j < mat->col; j++){
            newMatrix->values[i][j] = mat->values[i][j];
        }
    }
    
    return newMatrix;
}

bool mat_equals( const Matrix m1, const Matrix m2){
    if(m1->row != m2->row){
        return false;
    }
    else{
        for(int i = 0; i < m1->row; i++){
            if( m1->col != m2->col){
                return false;
            }
            for(int j = 0; j < m1->col; j++){
                if(m1->values[i][j] != m2->values[i][j]){
                    return false;
                }
            }
        }
    }
    return true;
}

void mat_scalar_mult( Matrix mat, float data){
    for(int i = 0; i < mat->row; i++){
        for(int j = 0; j < mat->col; j++){
            mat->values[i][j] *= data;
        }
    }
}

Matrix mat_mult( const Matrix m1, const Matrix m2){
    if(m1 == NULL || m1->values == NULL){
        return NULL;
    }
    if(m2 == NULL || m2->values == NULL){
        return NULL;
    }
    if(m1->col != m2->row){
        return NULL;
    }
    Matrix newMatrix;
    
    newMatrix = (Matrix)malloc(sizeof(struct matrix_st));
    newMatrix->values = (float**)malloc(((int)(m1->row))*sizeof(float*));
    
    newMatrix->row = m1->row;
    newMatrix->col = m2->col;

    for(int i = 0; i < m1->row; i++){
        newMatrix->values[i] = (float*)malloc(sizeof(float)*((int)(m2->col)));
        for(int j = 0; j < m2->col; j++){
            float temp = 0;
            for(int k = 0; k < m1->col; k++){
                temp += m1->values[i][k] * m2->values[k][i];
            }
            newMatrix->values[i][j] = temp;
        }
    }
    return newMatrix;
}

Status mat_get_cell( const Matrix mat, float *data, size_t row, size_t col){
    if( mat->row < (int)row){
        return BadRowNumber;
    }
    if( mat->col < (int)col){
        return BadColNumber;
    }
    *data = mat->values[((int)row) - 1][((int)col) - 1];
    return Success;
}

Status mat_get_row( const Matrix mat, float data[], size_t row){
    if( mat->row < (int)row){
        return BadRowNumber;
    }
    for(int i = 0; i < mat->col; i++){
        data[i] = mat->values[(int)row - 1][i];
    }
    return Success;
}

Status mat_set_cell( Matrix mat, float data, size_t row, size_t col){
    if( mat->row < (int)row){
        return BadRowNumber;
    }
    if( mat->col < (int)col){
        return BadColNumber;
    }
    mat->values[((int)row) - 1][((int)col) - 1] = data;
    return Success;
} 

Status mat_set_row( Matrix mat, const float data[], size_t row){
    Status s;
    float empty[mat->col];
    if((s = mat_get_row(mat, empty, row)) == Success){
        for(int i = 0; i < mat->col; i++){
            mat->values[(int)row - 1][i] = data[i];
        }
    }
    return s;
}

Matrix mat_transpose( const Matrix mat){
    
    Matrix newMatrix; 
    
    newMatrix = (Matrix)malloc(sizeof(struct matrix_st));
    newMatrix->values = (float**)malloc(((int)(mat->col))*sizeof(float*));
    
    newMatrix->row = mat->col;
    newMatrix->col = mat->row;

    for(int i = 0; i < mat->col; i++){
        newMatrix->values[i] = (float*)malloc(sizeof(float)*((int)(mat->row)));
        for(int j = 0; j < mat->row; j++){
            newMatrix->values[i][j] = mat->values[j][i];
        }
    }

    return newMatrix;
}

void mat_print( const Matrix mat, FILE *stream){
    
    fprintf(stream, "%d rows, %d columns:\n", mat->row, mat->col);
    for(int i = 0; i < mat->row; i++){
        for(int j = 0; j < mat->col; j++){
            if(mat->values[i][j] >= 1000){
                fprintf(stream, "%.3f", mat->values[i][j]);
            }
            else if(mat->values[i][j] >= 100){
                fprintf(stream, " %.3f", mat->values[i][j]);
            }
            else if(mat->values[i][j] >= 10){
                fprintf(stream, "  %.3f", mat->values[i][j]);
            }
            else{
                fprintf(stream, "   %.3f", mat->values[i][j]);
            }
        }
        fprintf(stream, "\n");
    }
}
