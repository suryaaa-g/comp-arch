#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

 double** transpose(double** a_matrix, int rows,int cols){// transpose function
    double **temp_matrix = (double**)malloc(sizeof(double*)*cols);// create a temp matrix to return at the end 
    for(int i= 0 ; i < cols; i++){
        temp_matrix[i] = (double*)malloc(sizeof(double*)*rows);

    }
     for(int i = 0; i < rows; i++){
         for(int j = 0; j < cols; j++){
            temp_matrix[j][i]=a_matrix[i][j];// transposing is switching rows and cols so switch rols and cols of this first matrix 
         }
     }
     
    //  for(int i = 0; i <cols; i++) {
    //      for (int j = 0; j < rows; j++) {
    //          printf("[%d][%d]:%lf" , i, j, temp_matrix[i][j]);
    //      }
    //  }

    return temp_matrix;

}
    





double** multiply( double** a_matrix, int arows, int acols,double** b_matrix,int brows,int bcols){
    // int crows = 0;
    // int ccols = 0;
// double ** a_matrix =(double**)malloc(sizeof(double*)*arows);
//double ** b_matrix = (double**)malloc(sizeof(double*)*brows);//allocate space for both rows and cols
double **c_matrix = (double**)malloc(sizeof(double*)*arows);// create a new matrix using arows to return at the end 
double sum = 0;// dummy var
//for(int i = 0; i < arows;i++){
    //a_matrix[i]= (double**)malloc(sizeof(double*)*acols);

//}
//for(int i = 0; i< brows;i++){
   // b_matrix[i]= (double**)malloc(sizeof(double*)*bcols);
//}
for(int i = 0; i< arows;i++){   
    c_matrix[i]= (double*)malloc(sizeof(double)*bcols);
}
if(acols == brows){
for(int i = 0; i< arows;i++){//multiplying both matrices
    for(int j = 0; j < bcols;j++){
        sum = 0;
        for(int k = 0; k < acols;k++){
           sum +=a_matrix[i][k]*b_matrix[k][j];  //make sum = to the multiplication of both matrices
        }
        c_matrix[i][j] = sum;  // make c matrix = sum
        }
    }
//    for(int i = 0; i < arows;i++) {
//        for(int j = 0; j < acols;j++){
//            a_matrix[i][j]=b_matrix[i][j];
//        }
//    }
//    for(int i = 0; i < crows; i++){
//        for(int j = 0; j < ccols;j++){
//            c_matrix[i][j]=a_matrix[i][j];
//        }
//    }
}
// for(int i = 0 ; i < arows;i++){
//     for(int j = 0 ; j < bcols;j++){
//         tempc[i][j]=c_matrix[i][j];
//     }
// }


// for(int i = 0; i < arows;i++){
//     free(c_matrix[i]);
// }
// free(c_matrix);


return c_matrix;  //we return the final matrix which is the c matrix

}






// void divideRow (double ** matrix, int row, double factor, int columns) {

//  if (matrix == NULL) return;

//  int i;
//  for (i=0; i<columns; i++) {
//      matrix[row][i] = matrix[row][i]/factor;
//  }



// }
 
//  /*method that subtracts  row A */
// void subtractRow (double ** matrix, int A, int B, double multiplier, int columns) {

//  if (matrix==NULL) return;
//  int i;
//  for (i = 0; i<columns; i++) {
//      matrix[B][i] = (matrix[B][i] - (multiplier * matrix[A][i]));
//  }
// }



double** invert( double** original_matrix, int rows){
    double** n_matrix = malloc(sizeof(double)*rows);

    for(int i = 0; i < rows; i++){
        n_matrix[i] =  malloc(rows*sizeof(double*));
    }


    for(int i = 0; i < rows;i++){
        for(int j = 0; j < rows;j++){
            if(i==j){
                n_matrix[i][j]=1;

            }else{
                n_matrix[i][j]=0;
            }
        }
    }

  
     
double f;
    for( int p = 0; p < rows;p++){
        f = original_matrix[p][p];

        for(int j = 0; j < rows;j++){
            original_matrix[p][j]=original_matrix[p][j]/f;
            n_matrix[p][j]=n_matrix[p][j]/f;
        }   
        for(int i = p+1;i < rows;i++){
            f=original_matrix[i][p];
        
            for(int j = 0; j < rows; j++){
                original_matrix[i][j] = original_matrix[i][j]-(original_matrix[p][j]*f);
                n_matrix[i][j]= n_matrix[i][j]-(n_matrix[p][j] * f);  
            }
        }
    }
    for(int p = rows-1; p>=0; p--){
        for(int i = p-1;i >= 0;i--){
            f = original_matrix[i][p];
            for(int k = 0; k < rows;k++){
                original_matrix[i][k]= original_matrix[i][k] - (f*original_matrix[p][k]);
                n_matrix[i][k]=n_matrix[i][k]-(f*n_matrix[p][k]);
            }
        }
    }
    for(int i = 0; i < rows;i++){
        free(original_matrix[i]);
    }
    free (original_matrix);
    return n_matrix;
    
}







int main(int argc, char**argv){
  /*
    Input file
    1. What type? data or train 
        - first train file
        - First Column will be all 1's
        - Last Column : Y matrix: Consists of home prices : Train File
        - Find the W matrix (transpose, multiply, inverse methods)
        

    2. Store W matrix
       Store X matrix in Data file
        - remember to fill first col with 1
        - create a y matrix to store prices (when you calculate)
        - multiply x matrix * w matrix = prices matrix

            - Return The y matrix     
    */

    //declaring variables we need
    FILE* train_file;
    int train_rows = 0;
    int train_cols = 0;
    char type[6]; //stores the text in file (first line?)
    
    
    train_file = fopen(argv[1], "r"); //reading the file
   
   //check if file has data
    if(train_file == NULL){
        printf("does not exist, sorry\n");
        return 1;
    }

    //file has data, scan the arguments needed 

    fscanf(train_file, "%s", type); //this is trash 
    fscanf(train_file, "%d", &train_cols); //1st line is cols (k)
     train_cols++;
    fscanf(train_file, "%d", &train_rows); //second is rows (n)
   
    /*
    * checking to see if arguments are correct  
    *
    */
    
    //printf("attribute is %s, col number is %d, row number * is %d", type, train_cols, train_rows);
   

   //Allocate space for matrices
   double **train_matrix = (double**) malloc (sizeof(double*) * train_rows);
   double **Y_matrix = (double**) malloc(sizeof(double*) * train_rows);

   int placeHolder = 0;

   for(int i =0; i < train_rows; i++){
       train_matrix[i] = (double *)malloc(sizeof(double) * train_cols);
       Y_matrix[i] = (double *)malloc(sizeof(double));
   }
   
   for(int i = 0; i < train_rows; i++){
      
       

       for(int j = 0; j < train_cols + 1 ; j++){
           if(j == 0){
               train_matrix[i][j] = 1.0;
           }
           else if(j == train_cols){
               placeHolder=  fscanf(train_file, "%lf", &Y_matrix[i][0]);
               if(placeHolder != 1) return 1;
               //Y_matrix[i][0] = placeHolder;
           }
           else{
               placeHolder = fscanf(train_file, " %lf", &train_matrix[i][j]);
               if(placeHolder!= 1) return 1; 
               //train_matrix[i][j] = placeHolder;
           }

       }
   }



//print matrix    

/*
   for (int i=0; i<train_rows; i++) {
		for (int j=0; j<train_cols; j++) {
			printf("%.0f ", train_matrix[i][j]);
		}
		printf("\n");
	} 
	printf("\n");

*/


    /*Test 1: Math Section */
    //start to transpose 

    
    double **tranposed = transpose(train_matrix, train_rows, train_cols);

    //multiply
    double **product = multiply(tranposed, train_cols, train_rows, train_matrix, train_rows, train_cols);
    
    //og matrix is not needed
    for(int i = 0; i < train_rows; i++){
        free(train_matrix[i]);
    }
    free(train_matrix);
    
    //double **inverse = invertMatrix(train_cols, product);

    double **inverse = invert(product, train_cols);

    // for(int i = 0; i < train_cols; i++){
    //     free(product[i]);
    // }
    // free(product);

    //freeMatrix(product, train_cols);
   
    double **sec_product = multiply(inverse, train_cols, train_cols, tranposed, train_cols, train_rows);

    for(int i = 0; i < train_cols; i++){
        free(tranposed[i]);
    }
    free(tranposed);

    for(int i = 0; i < train_cols; i++){
        free(inverse[i]);
    }
    free(inverse);

    //freeMatrix(tranposed, train_cols);
    //freeMatrix(inverse, train_cols);

    double **W = multiply(sec_product, train_cols, train_rows, Y_matrix, train_rows, 1);
    if(W == NULL) return 1; 

    //Test to see if i can print out W
    
    
    for(int i = 0; i < train_rows; i++){
        free(Y_matrix[i]);
    }
    free(Y_matrix);

    for(int i = 0; i < train_cols; i++){
        free(sec_product[i]);
    }
    free(sec_product);

    //freeMatrix(Y_matrix, train_rows);
    //freeMatrix(sec_product, train_cols);

    fclose(train_file);
    
    
    
    /*NEXT STEP TO USE DATA FILE*/

    
    FILE* data_file;
    int data_rows = 0;
    int data_cols = 0;
    char type2[7];
    
    data_file = fopen(argv[2], "r");

    if(data_file == NULL){
        printf("no file exists\n");
        return 1;
    }

    fscanf(data_file, "%s", type2); //this is trash 
    fscanf(data_file, "%d", &data_cols); //1st line is cols (k)
     data_cols++;
    fscanf(data_file, "%d", &data_rows);

    //Allocate space for data matrix
    double **data_matrix = (double**)malloc(sizeof(double*) * data_rows);

    for(int i = 0; i < data_rows; i++){
        data_matrix[i] = (double*)malloc(sizeof(double) * data_cols);

    }
    
    int check = 0;
    for(int i =0; i < data_rows; i++){
        for(int j = 0; j < data_cols; j++){
            if(j == 0){
                data_matrix[i][j] = 1.0;
            }
            else{
                check = fscanf(data_file, "%lf", &data_matrix[i][j]);
                if(check!=1) return 1;
            }
        }
    }

    /*
    for(int i =0; i < data_rows; i++){
        for(int j = 0; j < data_cols; j++){
            printf("%.0f ", data_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    */



    
    double **result = multiply(data_matrix, data_rows, data_cols, W, train_cols, 1);
    if(result == NULL) return 1;

    for(int i = 0; i < data_rows; i++){
        for(int j = 0; j < 1; j++){
            printf("%.0f", result[i][j]);
        }
        printf("\n");
    }

    
    for(int i = 0; i < data_rows; i++){
        free(data_matrix[i]);
    }
    free(data_matrix);
    
    for(int i = 0; i < data_rows; i++){
        free(result[i]);
    }
    free(result);

    for(int i = 0; i < train_cols; i++){
        free(W[i]);
    }
    free(W);

    //freeMatrix(data_matrix, data_rows);
    //freeMatrix(result, data_rows);
    //freeMatrix(W, train_cols);
    fclose(data_file);
    
    
    /*
   for(int i = 0; i < train_rows; i++){
       free(train_matrix[i]);
       free(Y_matrix[i]);
   }
   free(train_matrix);
   free(Y_matrix);
   */

   return 0;
   
  

} 