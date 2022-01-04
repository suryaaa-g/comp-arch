#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>


int logTwo (int num) {

	int i=0;

	while (num>1) {
		if (num%2!=0) return -1;
		num = num/2;
		i++;
	}


	return i;
}


int toString (char * string) {

	int i =0, j=0;
	int result =0;
	for (i=0; string[i]!='\0'; i++) {
	}

	for (j=0; j<i; j++) {
		result = result * 10;
		result +=  (int)(string[j]) - 48;
	}

	return result;

}



void concat(char* subtext, char** arg, char a[2]){
	strcat(subtext, "test.");
    strcat(subtext, arg[3]);
    strcat(subtext, ".");
    strcat(subtext, a);
    strcat(subtext, ".");
    strcat(subtext, arg[1]);
    strcat(subtext, ".");
    strcat(subtext, arg[2]);
    strcat(subtext, ".");
    strcat(subtext, arg[4]);
   
}






int main(int argc, char** argv){
    FILE *f;
    char s;
    char a[2];
    int temp; //= findSize(argv[argc-1]);
	int i = 0;

    char *x = argv[argc-1];

    int index = 0;
    int countSlash = 0;
    
    for(int i = 0; i < strlen(x); i++){
        char charVal = x[i];
        if(charVal == '/'){
            countSlash++;

        }
		
    }
      for(int i = 0; i < strlen(x); i++){
          char charVal = x[i];
          if(countSlash == 0){
              break;
          }
          else if(charVal == '/'){
              countSlash--;
          }
          index++;
      }
    temp =  index;



    int temp2; 

	char *y = &argv[argc-1][temp];





    int ret =0;
	
    while(i < strlen(y)){
        char charVal = y[i];
        if(isdigit(charVal)){
            ret = i;
            break;
        }
		i++;
    }
    temp2 =  ret;


    sprintf(a, "%d", atoi(&argv[argc-1][temp + temp2]));

    char *subtext = malloc((strlen(argv[argc-1]) + 100) * sizeof(char));

    strncpy(subtext, &argv[argc-1][0], strlen(argv[argc-1]) - 10);

    subtext[strlen(argv[argc-1])- 10] = '\0';

   
	concat(subtext, argv, a);
	strcat(subtext, &argv[argc-1][strlen(argv[argc-1]) - 4]);

    f = fopen(subtext, "r");

    while((s = fgetc(f)) != EOF){
        printf("%c", s);
    }
    fclose(f);
    free(subtext);
    return EXIT_SUCCESS;    
}





