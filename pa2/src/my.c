#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//Methods we need to make
void print(int row, int column, double** matrix);

double** transpose(double** matrix, int row, int column);

double** multiply(double** matrix1, int row1, int col1, double** matrix2, int row2, int col2);

//double** invertMatrix(double** matrix, int row, int col);

void freeMatrix(double **matrix, int row);

double** inverseMatrix(double **matrix, int dim);

void divider(double **matrix, int row, int factor_to_divide, int cols);

double** invert(double **matrix, int row, int col);

int main(int argc, char **argv){
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

   //int placeHolder = 0;

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
               /*placeHolder=*/  fscanf(train_file, "%lf", &Y_matrix[i][0]);
               //if(placeHolder != 1) return 1;
               //Y_matrix[i][0] = placeHolder;
           }
           else{
               /*placeHolder = */fscanf(train_file, " %lf", &train_matrix[i][j]);
               //if(placeHolder!= 1) return 1; 
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


    /*Test 1: Math Section 
    *
    * So basically after you're done with an operation , you can free the matrix you used
    * 1. After M^T * M
    *  -- free M
    * 2. After (M^t * M)^-1 
    * -- free product (M^t) * M
    * 3. After inverse * M^t
    * -- free transposed and inverse
    * 4. After * Y
    * -- you get W
    * -- free Y matrix and the second product
    * Carry W matrix over to the Data file
    */
    //start to transpose 

    
    double **tranposed = transpose(train_matrix, train_rows, train_cols);

    //multiply
    double **product = multiply(tranposed, train_cols, train_rows, train_matrix, train_rows, train_cols);
    
    //og matrix is not needed
    freeMatrix(train_matrix, train_rows);
    
    //double **inverse = invertMatrix(train_cols, product);

    double **inverse = inverseMatrix(product, train_cols);

    freeMatrix(product, train_cols);
   
    double **sec_product = multiply(inverse, train_cols, train_cols, tranposed, train_cols, train_rows);

    freeMatrix(tranposed, train_cols);
    freeMatrix(inverse, train_cols);

    double **W = multiply(sec_product, train_cols, train_rows, Y_matrix, train_rows, 1);
    if(W == NULL) return 1; 

    //Test to see if i can print out W
    //print(W, 1);

    /*Success*/
    

    /*free used matrices */
    freeMatrix(Y_matrix, train_rows);
    freeMatrix(sec_product, train_cols);

    fclose(train_file);
    
    
    
    /*NEXT STEP TO USE DATA FILE
    * -- Only matrix you need to carry over is W
    * */

    
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
                //printf("%lf", check);
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

    
    
    

    freeMatrix(data_matrix, data_rows);
    freeMatrix(result, data_rows);
    freeMatrix(W, train_cols);
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

double** inverseMatrix(double **matA, int row_col) {
    /**
 * Using the pseudocode, make the inverse method
 *  Steps:
 *      *NOTE* : Rows = COLS
 * 1. Allocate space for identity matrix
 * 2. set identity matrix values
 * 3. Copy original values (parameter matrix) to another *      - *temp* matrix (call this T)
 * 
 *  Start Inverse algo
 *  1. f (factor) will be set to M[p][p]
 *  2. for loop runs till rows, divides the rows
 *  3. another for loop to subtract 
 *  4. Subtract again
 *  5. Basically you'll be returning the identity matrix 
 *      - whatever ops u do on OG youll do on identity
 * */
	double** Identity = malloc(row_col * sizeof(double*));

	for(int k = 0; k < row_col; k++) {
		Identity[k] = malloc(row_col * sizeof(double*));
	}

	// Initialising Identity Matrix Values:

	for(int r = 0; r < row_col; r++) {
		for(int c = 0; c < row_col; c++) {
			if(r == c) {
				Identity[r][c] = 1;
			} else {
				Identity[r][c] = 0;
			}
		}
	}

	// copy OG matrix to a 'temp'
	double** copy = malloc(row_col * sizeof(double*));

	for(int k = 0; k < row_col; k++) {
		copy[k] = malloc(row_col * sizeof(double));
	}

	for(int r = 0; r < row_col; r++) {
		for(int c = 0; c < row_col; c++) {
			double num = matA[r][c];
			copy[r][c] = num;
		}
	}

	/*Pseudo code starts
    * 1. make a var that stores the division value 
    * 2. then copy those values into the matrix 
    
    */

	for(int p = 0; p < row_col; p++) {
		double f = copy[p][p];

		

		for (int k = 0; k < row_col; k++) {
			double temp_copy = copy[p][k] / f;
			copy[p][k] = temp_copy;
			double temp_identity = Identity[p][k] / f;
			Identity[p][k] = temp_identity;
		}

		for (int i = p + 1; i < row_col; i++) {
			f = copy[i][p];

			

			for (int k = 0; k < row_col; k++) {
				//double temp_copy = copy[i][k] - (f * copy[p][k]);
				//double temp_identity = Identity[i][k] - (f * Identity[p][k]);
				copy[i][k] = copy[i][k] - (f * copy[p][k]);//temp_copy;
				Identity[i][k] = Identity[i][k] - (f * Identity[p][k]);//temp_identity;
			}
		}
	}

	for (int p = row_col - 1; p >= 0; p--) {
		for (int i = p - 1; i >= 0; i--) {
			double f = copy[i][p];

			

			for (int k = 0; k < row_col; k++) {
				//double temp_copy = copy[i][k] - (f * copy[p][k]);
				//double temp_identity = Identity[i][k] - (f * Identity[p][k]);
				copy[i][k] = copy[i][k] - (f * copy[p][k]);//temp_copy;
				Identity[i][k] = Identity[i][k] - (f * Identity[p][k]);//temp_identity;
			}
		}
	}

	freeMatrix(copy, row_col);
	return Identity;
}



double **transpose(double **matrix, int row, int col){
    double **temp = (double**)malloc(sizeof(double*) * col);
    for(int i = 0; i < col; i++){
        temp[i] = (double*)malloc(sizeof(double*) * row);
    }
    for(int i = 0 ; i < row; i++){
        for(int j = 0; j < col; j++){
            temp[j][i] = matrix[i][j];
        }
    }
    //free matrix

    /*
    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            matrix[i][j] = temp[i][j];
        }
    }

    for(int i = 0; i < col; i++){
        free(temp[i]);
    }
    free(temp);
    */

    return temp;
}


//Print method --> gonna do it in main 

// void printMatrix(double **matrix, int rows){

// }




// Method to inverse --> trashed; idk why this doesnt work gonna redo step by step
    
 
// double **invertMatrix(double **Ogmatrix, int rows, int col){

//     //identity matrix
//     double **identity = malloc((rows) * sizeof(double*));

//     //allocate space for values
//     for(int i = 0; i < rows; i++){
//         identity[i] = (double*)malloc((rows) * sizeof(double*));

//     }

//     //fill identity matrix
//     for(int row = 0; row < rows; row++){
//         for(int col = 0; col < rows; col++){
//             if(row == col){
//                 identity[row][col] = 1;
//             }
//             else{
//                 identity[row][col] = 0;
//             }
//         }
//     }

//     /**
//      * Step 1 Complete: Fill inverse matrix
//     */



//    /***
//     * Step 2: Copy values of OG to a copy
//     *   so you dont change anything
//    */

//   double **copy = malloc(rows * sizeof(double*));

//   for(int cop = 0; cop < rows; cop++){
//       copy[cop] = malloc((col *2) * sizeof(double));
//   }
  
//   for(int r = 0; r < rows; r++){
//       for(int c = 0; c < col; c++){
//           //double num = Ogmatrix[r][c];
//           copy[r][c] = Ogmatrix[r][c];
//       }
//   }

//   /*
//   * Step 3: Algo
//   * */
//     for(int p = 0; p < rows; p++){
//         double f = copy[p][p];

//         //divide first
//         for(int k = 0; k < rows; k++){
//             double copy_val = copy[p][k] / f;
//             copy[p][k] = copy_val;
//             double identity_val = identity[p][k] / f;
//             identity[p][k] = identity_val;
//         }
//         //subtract next
//         for(int i = p + 1; i < rows; i++){
//             f = copy[i][p];
//             for(int k = 0; i < rows; k++){
//                 double copy_val2 = copy[i][k] - (f * copy[p][k]);
//                 double identity_val2 = identity[i][k] - (f * identity[p][k]);
//                 copy[i][k] = copy_val2;
//                 identity[i][k] = identity_val2;
//             }
//         }
//     }
//     for(int p = rows - 1; p > 0; p--){
//         for(int i = p -1; i >= 0; i--){
//             double f = copy[i][p];

//             for(int k = 0; k < rows; k++){
//                 double val1 = copy[i][k] - (f * copy[p][k]);

//                 double val2 = identity[i][k] - (f * identity[p][k]);
//                 copy[i][k] = val1;
//                 identity[i][k] = val2;
//             }
//         }
//     }
//     freeMatrix(copy, rows);
//     return identity;
// }



double** multiply(double** matrix1, int row1, int col1, double** matrix2, int row2, int col2){
    /*
     * Steps
     * 1. every matrix will have its each rows and cols
     * 2. I need to allocate space for the matrix and the values within the matrix
     * 3. then simply multiply just like mexp
     *  
    */
   double val = 0;

   double **product = (double**)malloc(sizeof(double*) * row1);

   for(int i = 0; i < row1; i++){
       product[i] = (double *)malloc(sizeof(double)* col2);
   }

   for(int i = 0; i < row1; i++){
       for(int j = 0; j < col2; j++){
           for(int k = 0; k < col1; k++){
               val = val + matrix1[i][k] * matrix2[k][j];
           }
           product[i][j] = val;
           //val has to be set to 0 again to store next
           val = 0;
       }
   }

    return product;
}


void freeMatrix(double **matrix, int rows){
    if(matrix == NULL){
        return;
    }
    for(int i = 0; i < rows; i++){
        free(matrix[i]);
    }
    free(matrix);
}  


// void divider(double **matrix, int row, int factor_to_divide, int cols){
//     if(matrix == NULL){
//         return;
//     }
//     for(int i = 0; i < cols; i++){
//         matrix[row][i] = matrix[row][i] / factor_to_divide;
//     }
// }


// void divideRow (double ** matrix, int row, double factor, int columns) {

// 	if (matrix == NULL) return;

// 	int i;
// 	for (i=0; i<columns; i++) {
// 		matrix[row][i] = matrix[row][i]/factor;
// 	}



// }
 
//  /*method that subtracts  row A */
// void subtractRow (double ** matrix, int A, int B, double multiplier, int columns) {

// 	if (matrix==NULL) return;
// 	int i;
// 	for (i = 0; i<columns; i++) {
// 		matrix[B][i] = (matrix[B][i] - (multiplier * matrix[A][i]));
// 	}
// }

