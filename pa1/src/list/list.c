
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure 
struct node {

	int data;
	struct node* next;
};

// counter- counts the # of nodes created
int counter=0;
struct node *head = NULL;


void nodefree(struct node * start) {

	struct node * ptr = start;

	while (ptr!=NULL) {
		start = start->next;
		free(ptr);
		ptr = start;
	}
}


/*method to create a new node, returns that node with the data
	mallocs space for the node*/
struct node *makeNode (int data) {

	struct node* new = (struct node *)malloc (sizeof(struct node));
	new->data = data;
	new->next = NULL;
	counter++;
	return new;
}


/*method to delete a node from the list
	if the node is not there, then it does nothing
	returns the start of the list*/

struct node* delete (int data) {

	if (head==NULL) {
		return head;
	}

	struct node* ptr = head;
	struct node* prev = NULL;

	/*loop thougho check for the number*/
	while (ptr !=NULL) {
		if (ptr->data == data) {
			if (prev==NULL) {
				counter = counter-1;
				prev = ptr;
				ptr = ptr->next;
				head=ptr;
				free(prev);
				return head;
			}
			/*if there, delete the link and free the space*/
			prev->next = ptr->next;
			free(ptr);
			counter = counter -1;
			return head;
		}
		prev = ptr;
		ptr = ptr->next;
	}

	return head;

}



/*method to insert a new node into the linked list, will not insert a duplicate
	returns 1 for a success, 0 for a failure*/
struct node* insert (int data) {

	if (head==NULL) {
		head = makeNode(data);
		return head;
	}

	struct node * ptr = head;
	struct node * prev = NULL;

	
	/*loop through to check if item is there already*/
	while (ptr!=NULL) {
		if (ptr->data == data) {
			return head;
		}else if (ptr->data > data) {
			if (prev==NULL) {
				prev = makeNode(data);
				prev->next = ptr;
				head=prev;
				return head;
			}else{
				prev->next = makeNode(data);
				prev = prev->next;
				prev->next=ptr;
				return head;
			}

		}
		
		prev = ptr;
		ptr = ptr->next;
		
	}

	/*if it wasnt, create a new node and add to end*/

	prev->next = makeNode(data);
	

	return head;
}



int main (int argc, char** argv) {

	/*opens a file from the argument*/
	 int value;
    char operator;
    struct node* start;

    //Scan and add/remove LL
    while(scanf("%c %d", &operator, &value) != -1){

        if(operator == 'i'){

            start = insert(value);
			int i = 0;
    struct node *iter = start;

    
    while(iter != NULL){
       
        i++;
        iter = iter->next;
    }
   
    printf("%i :", i);

    struct node *iter2 = start;
    int num;

    
    while(iter2 != NULL){

        num = iter2->data;
        printf(" %i", num);
        iter2 = iter2->next;

    }

    

    printf("\n");

        }

        if(operator == 'd'){

           start =  delete(value);
		   int i = 0;
    struct node *iter = start;

    
    while(iter != NULL){
        
        i++;
        iter = iter->next;
    }
    //print length in required format
    printf("%i :", i);

    struct node *iter2 = start;
    int num;

    //Go through LL and print each iteration on one line
    while(iter2 != NULL){

        num = iter2->data;
        printf(" %i", num);
        iter2 = iter2->next;

    }

    //printf("\n");

    printf("\n");
            

        }

    }

    
    
    nodefree(start);
    
    return EXIT_SUCCESS;
}