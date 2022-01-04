#include <string.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>


int **multiply(int **matrix,int rows, int exponent){
  int **prod = malloc(rows *sizeof(int*));
  int **iter = malloc(sizeof(int *) * rows);
  for(int i =0; i < rows; i++){
    prod[i] = (int*)malloc(rows * sizeof(int*));
    iter[i] = malloc(sizeof(int) * rows);
  }
  for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            iter[i][j] = matrix[i][j];
        }
    }


  if(exponent > 1){
    for(int i = 0; i < rows; i++){
            for(int j = 0; j < rows; j++){
                prod[i][j] = 0;
            }
        }

  for(int r = 1; r < exponent; r++){
    for(int i =0; i < rows; i++){
      for(int j = 0; j < rows; j++){
        for(int k = 0; k < rows; k++){
          prod[i][j] += iter[i][k] * matrix[k][j];
        }
      }
    }
   for(int i = 0; i < rows; i++){
                     for(int j = 0; j < rows; j++){
                         iter[i][j] = prod[i][j];
                     }
                 }
    if(r != exponent-1){
                 for(int i = 0; i < rows; i++){
                    for(int j = 0; j < rows; j++){
                        prod[i][j] = 0;
                    }
                }
                 }

  }


         

for(int i = 0; i < rows; i++){
                for(int j = 0; j < rows; j++){
                    matrix[i][j] = prod[i][j];
                }
                
        }
    for(int i = 0; i < rows; i++){
                free(prod[i]);
            }
            free(prod);

            for(int i = 0; i < rows; i++){
                free(iter[i]);
            }
            free(iter);
            return matrix;
  
  }
  for(int i = 0; i < rows; i++){
                free(prod[i]);
            }
            free(prod);

            for(int i = 0; i < rows; i++){
                free(iter[i]);
            }
            free(iter);
            return matrix;

    
  
}

int **same(int **matrix, int rows, int exponent){
  int **prod = malloc(rows *sizeof(int*));
  int **iter = malloc(sizeof(int *) * rows);
  for(int i =0; i < rows; i++){
    prod[i] = (int*)malloc(rows * sizeof(int*));
    iter[i] = malloc(sizeof(int) * rows);
  }
  for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            iter[i][j] = matrix[i][j];
        }
    }
  int exp = exponent;
    if(exp == 1){
        for(int i = 0; i < rows; i++){
            free(prod[i]);
        }
        free(prod);

        for(int i = 0; i < rows; i++){
            free(iter[i]);
        }
        free(iter);

        return matrix;
    }
    return NULL;
}

int **identity(int **matrix, int rows, int exponent){
  int **idMatrix = malloc(sizeof(int * ) * rows);
  int **temp = malloc(sizeof(int * ) * rows);
  
  for(int i = 0; i < rows; i++){
    idMatrix[i] = malloc(sizeof(int) * rows);
    temp[i] = malloc(sizeof(int) * rows);
  }

  for(int i =0; i < rows; i++){
    for(int j = 0; j < rows; j++){
      temp[i][j] = matrix[i][j];
    }
  }



  if(exponent == 0){
    for(int i = 0; i < rows; i++){
      for(int j = 0; j < rows; j++){
        if(i == j){
          idMatrix[i][j] = 1;
        }
        else{
          idMatrix[i][j] = 0;
        }
      }
    }

    for(int i = 0; i < rows; i++){
      for(int j = 0; j < rows; j++){
        matrix[i][j] = idMatrix[i][j];
      }
    }
    for(int i = 0; i < rows; i++){
      free(idMatrix[i]);
    }
    free(idMatrix);
    for(int i = 0; i < rows; i++){
      free(temp[i]);
    }
    free(temp);
    return matrix;
  }
  return NULL;
}

/*
int **exponentiate(int **matrix, int rows, int exponent){

  if(exponent > 1){
    for(int r = 0; r < exponent; r++){
      multiply(matrix, rows, exponent);
    }
  }
  
}
*/


/*
int **identity(int **matrix, int rows, int exponent){
    int **prod = malloc(rows *sizeof(int*));
  int **iter = malloc(sizeof(int *) * rows);
  for(int i =0; i < rows; i++){
    prod[i] = (int*)malloc(rows * sizeof(int*));
    iter[i] = malloc(sizeof(int) * rows);
  }
  for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            iter[i][j] = matrix[i][j];
        }
    }

    
}
*/

/*
int** multiply(int** matrix,int** bass,int row){


int ** sum=(int**)malloc(row*sizeof(int*));
int i;
int j;
int k;
for(i=0;i<row;i++){
  sum[i]=(int*)malloc(row*sizeof(int*));
}


for( i=0; i<row; ++i){

  for( j=0; j<row; ++j){
      for( k=0; k<row; ++k){
          sum[i][j]+=matrix[i][k]*bass[k][j];
      }
}
}




for(i=0;i<row;i++){
  for( j=0;j<row;j++){
    matrix[i][j]=sum[i][j];

  }
}


return matrix;

}
*/


int main(int argc, char **argv){
  FILE* file;

if((file = fopen(argv[1],"r"))==NULL){
    printf("error");
    return EXIT_FAILURE;
}

else{
    file = fopen(argv[1],"r");
    int rows;

    fscanf(file,"%i\n", &rows);
    int **matrix = malloc(sizeof(int *) * rows);
    

    for (int i = 0; i < rows; ++i) {
	    matrix[i] = malloc(sizeof(int) * rows);
        
    }
    
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            int val;
            fscanf(file, "%i", &val);
            matrix[i][j] = val;

        }
        fscanf(file, "\n");

    }
    
    
    int exponent;
    fscanf(file, "%i", &exponent);

    if(exponent == 0){
      matrix = identity(matrix, rows, exponent);
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            printf("%i", matrix[i][j]);
            if(j + 1 != rows){
                printf(" ");
            }
        }
        printf("\n");
    }
    }

    if(exponent == 1){
      matrix = same(matrix, rows, exponent);
      for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            printf("%i", matrix[i][j]);
            if(j + 1 != rows){
                printf(" ");
            }
        }
        printf("\n");
    }
    }

    



    matrix = multiply(matrix, rows, exponent);

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows; j++){
            printf("%i", matrix[i][j]);
            if(j + 1 != rows){
                printf(" ");
            }
        }
        printf("\n");
    }

    for(int i = 0; i < rows; i++){
        free(matrix[i]);
        
        }
    free(matrix);

    fclose(file);
    
   
}

 
}