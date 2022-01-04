
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>




int main(int argc, char **argv) {	


	char *phrase = argv[1];

	int phrase_length = strlen(phrase);

    char *rlePhrase = malloc(((2 * phrase_length) + 1) * sizeof(char));
	//char rlePhrase[20000];
	
	int rlePhrase_length = 2 * phrase_length;

	int i, j;
	int count = 1;
	//int isDigit = 0;
	int pos = 0;

	/*
	1. loop through phrase and check if any numbers (yes = break) (no = continue)
	2. then check for similar characters (2 for loops);
	*/
	for(i = 0; i < phrase_length;){
		if (phrase[i] >= '0' && phrase[i] <= '9') {
			printf("error\n");
 			free(rlePhrase);
 			return 0;	
 		}

		// Now we can check the neighboring characters

		for(j = i + 1; j < phrase_length; j++){
			if(phrase[j] != phrase[i]){
				break;
			}
			count++;
		}
		//find the leftover characters
		int r = (rlePhrase_length + 1) - pos;
		int size = snprintf(rlePhrase + pos, r, "%c%d", phrase[i], count);

		pos += size;
		if(pos > phrase_length){
			rlePhrase = phrase;
			break;
		}
		i += count;
		count = 1;
		



	}
	rlePhrase[phrase_length] = '\0';
	printf("%s\n", rlePhrase);

	free(rlePhrase);

	return 0;
}























