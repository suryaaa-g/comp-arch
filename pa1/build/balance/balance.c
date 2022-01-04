
#include<stdio.h>
#include<strings.h>
#include<stdlib.h>
#include<ctype.h>

char get_brace(char symbol);

void push(char stack[], char elem, int *top) {
    
    stack[*top] = elem;
    
    *top = *top + 1;
}

char peek_stack(char stack[], int *top) {
    
    return stack[*top - 1];
}

char pop(char stack[], int *top) {
    if (*top == 0) 
        
        return '\0';
    *top = *top - 1;

    char popped_char = stack[*top];
    return popped_char;
}

int check_counter_brace(char curr_elem, char popped_elem) {
    
    if ((curr_elem == ')' && popped_elem == '(') || 
        (curr_elem == '}' && popped_elem == '{') ||
        (curr_elem == ']' && popped_elem == '['))
        return 1;
    
    
    return 0;
}





int main(int argc, char **argv) {
    char *str_to_be_checked = argv[1];
    char stack[10000];
    int stack_top = 0;
    int *stack_top_ptr = &stack_top;

    int i;
    i =0;
    while(str_to_be_checked[i] != '\0'){
        char curr_elem = str_to_be_checked[i];
        if (curr_elem == '(' || curr_elem == '{' || curr_elem == '[')
            
            push(stack, curr_elem, stack_top_ptr);

        else if (curr_elem == ')' || curr_elem == '}' || curr_elem == ']') {
           
            char popped = peek_stack(stack, stack_top_ptr);

            if (!check_counter_brace(curr_elem, popped)) {
                
                printf("%d: %c", i, curr_elem);
                return EXIT_FAILURE;
            }

            pop(stack, stack_top_ptr);
        }
        i++;
    }

if (stack_top == 0) {
        //printf( "%d", stack_top);
        return EXIT_SUCCESS;
    }
   printf("open: ");
   while (stack_top != 0) {
        
        char stack_top_brace = pop(stack, stack_top_ptr);
        

        printf("%c", get_brace(stack_top_brace));
    }


    return EXIT_FAILURE;




}



char get_brace(char brace) {
  
    if (brace == '(') return ')';
    if (brace == '{') return '}';
    if (brace == '[') return ']';

    printf("\nError in input string");
    exit(0);
}

