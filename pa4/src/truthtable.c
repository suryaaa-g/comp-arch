#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct circuitDirective {
    char block[17];
    int n;
    int s;
    int *inputs;
    int *outputs;
    int *selectors;
};
            /** DECLARATION OF THE METHODS I WILL BE USING (GATES)**/
void AND(int *val, int input1, int input2, int output1);
void NAND(int *val, int input1, int input2, int output1);
void NOR(int *val, int input1, int input2, int output1);
void DECODER(int *val, int n, int *input_index, int *output_index);

/********************************************************************************/



void resetValues(int size, int *arr) {
    int i;
    for (i = 0; i < size; i++) {
        arr[i] = 0;
    }
    arr[1] = 1;
}


int indexOf(int size, char **arr, char *var) {
    int i;
    for (i = 0; i < size; i++) {
        if (strcmp(arr[i], var) == 0) {
            return i;
        }
    }
    return -1;
}

/********************************** METHODS  ***********************************************/


void AND(int *values, int iindex1, int iindex2, int oindex) {
    values[oindex] = values[iindex1] && values[iindex2];
}

void NAND(int *values, int iindex1, int iindex2, int oindex) {
    values[oindex] = !(values[iindex1] && values[iindex2]);
}

void NOR(int *values, int iindex1, int iindex2, int oindex) {
    values[oindex] = !(values[iindex1] || values[iindex2]);
}
void PASS(int *values, int iindex, int oindex) {
    values[oindex] = values[iindex];
}



/****DECODER METHODS:****************************************/
void coder(int *values, int n, int *iindex, int *oindex){
    int i;
    for (i = 0; i < pow(2, n); i++) {
        values[oindex[i]] = 0;
    }
}

void coder2(int *values, int n, int *iindex, int *oindex){
    int i;
    int s = 0;
    for (i = 0; i < n; i++) {
        s += values[iindex[i]] * pow(2, n - i - 1);
    }
    values[oindex[s]] = 1;
}

/****END DECODER METHODS:****************************************/

void DECODER(int *values, int n, int *iindex, int *oindex) {
   
    coder( values, n,  iindex,  oindex);
    
    coder2( values, n,  iindex,  oindex);
    
}


void initialize(char **vars, int size){
    
    vars[0] = "0\0";
    vars[1] = "1\0";
}

int pow2(int inputs){
    int final = pow(2, inputs);
    return final;
}

void freeStuff(int input_var, struct circuitDirective* dir, int freeCounter){
    if(input_var > 99999){
        for(int i = 0; i < freeCounter; i++){
            free(dir[i].inputs);
            free(dir[i].outputs);
            free(dir[i].selectors);
        }
    }
    else{
        for(int i = 0; i < freeCounter -1; i++){
            free(dir[i].inputs);
	 	        free(dir[i].outputs);
                 free(dir[i].selectors);	
        }
    }
}


void printOutput(int len1, int len2, int* arr){
    for(int i = 0; i < len1; i++){
        printf(" %d", arr[len2 + i + 2]);
    }
    printf("\n");
}

void printIn(int input, int *arr){
    for(int i = 0; i < input; i++){
        printf("%d ", arr[i + 2]);
    }
    printf("|");
}



// struct circuitDirective* spaceMaker(int isize, int osize, int* dir, char type){
//     struct circuitDirective* type1 = dir;
//     struct circuitDirective* type2 = dir;
//     //struct circuitDirective* type3 = NULL;
    
//     if(strcmp(&type, "i") == 0){
//         type1->inputs = malloc(isize*sizeof(int));
//         return type1;
//     }
//     if(strcmp(&type, "o") == 0){
//         type2->outputs = malloc(osize*sizeof(int));
//     }
//     return NULL;

// }

    // int* spaceMaker(int size, struct circuitDirective* dir, char* type){
    //     if(strcmp(type, "input")){
    //         return dir->inputs = malloc(size * sizeof(int));
    //     }
    //     return dir->outputs = malloc(size * sizeof(int));
        
    // }

    

/********************************** END - METHODS  ***********************************************/


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Invalid input arguments\n");
        return 0;
    }

    FILE *file = fopen(argv[1], "r");
   

    
    int count = 0;
    //make directives with struct circuitDirective
    struct circuitDirective* directives = NULL;
    int size = 2;
    int input_var = 0;
    int output_var = 0;
    int total = 0;
    char dir[17];
    char **vars = NULL;
    int *gate_vars; 

    //store input details
    fscanf(file, " %s", dir);
    fscanf(file, "%d", &input_var);

    size += input_var;
    vars = malloc(size * sizeof(char *));
    
    initialize(vars, size);
    

    int i;
    for (i = 0; i < input_var; i++) {
        vars[i + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%16s", vars[i + 2]);
    }
                                                    
    //store output details
    fscanf(file, " %s", dir);
    fscanf(file, "%d", &output_var);
    size += output_var;
    vars = realloc(vars, size * sizeof(char *));

    
    // while(i <= output_var){
        
    //     vars[i + input_var + 2] = malloc(17 * sizeof(char));
    //     fscanf(file, "%*[: ]%16s", vars[i + input_var + 2]);
    //     i++;
    // }


    for (i = 0; i < output_var; i++) {
        vars[i + input_var + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%16s", vars[i + input_var + 2]);
    }
    struct circuitDirective my_directive; 
    
    //keeps track of how many items i need to free, (find an easier way to do this)
    int freeCount = 0; 

    //get directives
    while (!feof(file)) {
	    freeCount++;
        int numInputs = 2, numOutputs = 1;
        
        int sc = fscanf(file, " %s", dir); 
        if (sc != 1) break;
        count++;
        my_directive.n = 0;
        my_directive.s = 0;
        strcpy(my_directive.block, dir);

        // if (strcmp(dir, "NOT") == 0) numInputs = 1;
        // if (strcmp(dir, "PASS") == 0) {
        //     numInputs = 1;
        // }
        if(strcmp(dir, "NOT")==0 || strcmp(dir, "PASS") == 0){
            numInputs = 1;
        }
        
        // if(strcmp(dir, "DECODER") == 0 || strcmp(dir, "MULTIPLEXER") == 0){
        //     fscanf(file, "%d", &numInputs);
        //     my_directive.n = numInputs;
        //     my_directive.s = numInputs;
        //     numOutputs = pow(2, numInputs);
        // }
        
        if (strcmp(dir, "DECODER") == 0) {
            fscanf(file, "%d", &numInputs);
            my_directive.n = numInputs;
            numOutputs = pow2(numInputs);
        }
        if (strcmp(dir, "MULTIPLEXER") == 0) {
            fscanf(file, "%d", &numInputs);
            my_directive.s = numInputs;
            numInputs = pow2(numInputs);
        }

        

        // Allocating space for the inputs, outputs, and selectors 

         my_directive.inputs = malloc(numInputs * sizeof(int));
       
         my_directive.outputs = malloc(numOutputs * sizeof(int));
       

        
         my_directive.selectors = malloc(my_directive.s * sizeof(int));

        
        char v[20];

        for (i = 0; i < numInputs; i++) {
            fscanf(file, "%16s", v);
            my_directive.inputs[i] = indexOf(size, vars, v);
        }
         for (i = 0; i < my_directive.s; i++) {
            fscanf(file, "%16s", v);
            my_directive.selectors[i] = indexOf(size, vars, v);
        }
 
        for (i = 0; i < numOutputs; i++) {
            fscanf(file, "%16s", v);
            int idx = indexOf(size, vars, v);
            if (idx == -1) {
                size++;
                total++;
                vars = realloc(vars, size * sizeof(char *)); // FREE
                vars[size - 1] = malloc(17 * sizeof(char));
                strcpy(vars[size - 1], v);
                my_directive.outputs[i] = size - 1;
            }
            else my_directive.outputs[i] = idx;
        }
        
        //add curr_directive to list of directives
        if (!directives) directives = malloc(sizeof(struct circuitDirective));
        else directives = realloc(directives, count * sizeof(struct circuitDirective));
        directives[count - 1] = my_directive;
  
    }

    // initialize gate_vars array 
    gate_vars = malloc(size * sizeof(int));
    resetValues(size, gate_vars);
   

    //run this infinitely till we reach the end and break
    for(int i = 0; i < 100000; i++){
        printIn(input_var, gate_vars);
       

         for (i = 0; i < count; i++) {
            my_directive = directives[i];
            
            // go about solving each gate and changing the inputs and outputs necessary
            if (strcmp(my_directive.block, "NOT") == 0){
               gate_vars[my_directive.outputs[0]] = !gate_vars[my_directive.inputs[0]];      
            }
            if (strcmp(my_directive.block, "OR") == 0) {
                gate_vars[my_directive.outputs[0]] = gate_vars[my_directive.inputs[0]] || gate_vars[my_directive.inputs[1]];
            }


            if (strcmp(my_directive.block, "AND") == 0){
                AND(gate_vars, my_directive.inputs[0], my_directive.inputs[1], my_directive.outputs[0]);
            } 
            if (strcmp(my_directive.block, "NOR") == 0){ 
                NOR(gate_vars, my_directive.inputs[0], my_directive.inputs[1], my_directive.outputs[0]);
            }
            if (strcmp(my_directive.block, "NAND") == 0){
                NAND(gate_vars, my_directive.inputs[0], my_directive.inputs[1], my_directive.outputs[0]);
            } 
            if (strcmp(my_directive.block, "XOR") == 0) {
                gate_vars[my_directive.outputs[0]] = gate_vars[my_directive.inputs[0]] ^ gate_vars[my_directive.inputs[1]];
            } 


            if(strcmp(my_directive.block, "DECODER") == 0){
                DECODER(gate_vars, my_directive.n, my_directive.inputs, my_directive.outputs);
            }
            if(strcmp(my_directive.block, "MULTIPLEXER") == 0){
                //int out = my_directive.outputs[0];
                int s = 0;
                int i = 0;
                while(i < my_directive.s){
                    s += gate_vars[my_directive.selectors[i]] * pow(2, my_directive.s - i - 1);
                    i++;
                }
                gate_vars[my_directive.outputs[0]] = gate_vars[my_directive.inputs[s]];
               
            }
        }

        //Print outputs

        printOutput(output_var, input_var, gate_vars);


        // Need a condition so the loop can break: 

        int breakVal = 0;
        for (i = input_var + 1; i > 1; i--) {
            gate_vars[i] = !gate_vars[i];
            if (gate_vars[i] == 1) {
                breakVal = 1;
                break;
            }
        }

       
        if (!breakVal) break;
    }
   
    

    // Freeing the variables i allocated space for 

    /*
    1. Gate vars  (done) no errors
    2. vars (done) no erros
    3. directives and their components (selectors etc)  no errors
    4. keep testing to figure out stuff (got everything, fix the output for test cases 7, 4)
    
    
    */
        free(gate_vars);
    
        
    for (i = size-1; i >= 2; i--) {
    	free(vars[i]);
    }
    
   
    freeStuff(input_var, directives, freeCount);

    free(vars);
    
    free(directives);
    

    
    fclose(file);
    return 0;
}

