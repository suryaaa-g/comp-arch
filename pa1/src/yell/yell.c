

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



/*
int my_strlen(char *string) //Function to calculate length of given string
{
    int i;
    for(i=0;string[i]!='\0';i++);
    return i;
}
*/


int main(int argc, char **argv)
{
  if(strcmp(argv[1], " ") == 0){
    printf(" !!\n");
    return 0;
  }
  
  
  if(argc != 2 || argc ==1 || argv[1] == NULL){
    printf("%s", "");
  }
    
    if(strlen(argv[1]) <= 1){
      
      return 0;
    
    }
    
  char* target;
  target = malloc(strlen(argv[1]) + 10);
  strcpy(target, argv[1]);

  
  //testing to see if string copied
  //printf("%s", target);

  int k;

  for(k = 0; k <strlen(argv[1]) + 1 ; k++){
    
    
    if (target[k] <='z' && target [k]>='a') {
      target[k] = toupper(target[k]);
      
    }
    
  }
 char* exclamation = "!!";

  /*
  if(strlen(argv[1]-1)){
    printf("%s", "!!");
  }
  else{
    
    printf("%s%s", target, exclamation);
  }
  */


  
  printf("%s%s", target, exclamation);


 
  free(target);

  return 0;
  

    
}



    
     

    
    





