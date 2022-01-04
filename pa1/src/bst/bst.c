#include<stdio.h>
#include<stdlib.h>


struct BstNode {
    int data;
    struct BstNode* left;
    struct BstNode* right;
};
struct BstNode *root;
//root = NULL;

/*
struct BstNode* getnewNode(int data){
    struct BstNode *newNode = malloc(sizeof(struct BstNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct BstNode* insert(struct BstNode* tree, int data){
    if(tree == NULL){
        tree = getnewNode(data);
        return root; 
    }
    else if(data <= tree->data){
        tree->left = insert(tree->left, data);
    }
    else{
        tree->right = insert(tree->right, data);
    }

}

*/

void insert(struct BstNode* node, int data){
    if(node == NULL){
        node = malloc(sizeof(struct BstNode));
        node ->data = data;
        node->right = NULL;
        node->left = NULL;
        root = node;
        printf("inserted\n");
        return;
    }

    // struct node * ptr = root;
	// struct node * parent = NULL;
    else if(data > node->data){
        //slide to the right
        if(node->right == NULL){
            struct BstNode *new = malloc(sizeof(struct BstNode));
            new->data = data;
            node->right = new;
            new->right = NULL;
            new->left = NULL;
            printf("inserted\n");
            return;
        }
        insert(node->right, data);
    }

    else if(data < node->data){
        //slide to the left
        if(node->left == NULL){
            struct BstNode *new = malloc(sizeof(struct BstNode));
            new->data = data;
            node->left = new;
            new->left = NULL;
            new->right = NULL;
            printf("inserted\n");
            return;
        }
        insert(node->left,data );
    }

    
    else if(data == node->data){
        printf("not inserted\n");
        return;
    }
    else{
        printf("error %d %d\n", node->data, data);
    }

    return;



}

void search (int data) {

	if (root == NULL) {
		printf("absent\n");
		return;
	}

	struct BstNode * ptr = root;

	while (ptr!=NULL) {
		if (ptr->data == data) {
			printf("present\n");
			return;
		} else if (ptr->data < data) {
			ptr = ptr->right;
		} else {
			ptr = ptr->left;
		}
	}

	if (ptr==NULL) {
		printf("absent\n");
	}

	return;

}

void freeTree(struct BstNode* tree){
    if(tree == NULL){
        return;
        }
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree);
    return;
}

/*
int maxFinder(struct BstNode *root){
	if(root->right == NULL){

	}
}
*/
int maxfind (struct BstNode * root) {

	struct BstNode * ptr = root;

	if (ptr->right==NULL) {
		int data = ptr->data;
		free(ptr);
		return data;
	} else {
		return maxfind(ptr->right);
	}
}
void printNodes(struct BstNode* tree){
    if(tree != NULL){
        printf("(");
        if(tree->left != NULL){
            printNodes(tree->left);
        }
        // printf("(");
        // printNodes(tree->left);
        printf("%d", tree->data);
        if(tree->right != NULL){
            printNodes(tree->right);
        }
        
        printf(")");
    }
    
    return;
}

void delete (int data) {

	if (root==NULL) {
		printf("absent\n");
		return;
	}

	struct BstNode * ptr=root;
	struct BstNode * parent = NULL;

	while (ptr!=NULL) {

		if (ptr->data==data) {


			/*if no children*/
			if (ptr->right ==NULL && ptr->left == NULL) {
				/*if the start node*/
				if (parent==NULL) {
					root=NULL;
					free(ptr);
					return;
				} else {
					/*set either parent.left or right to NULL, free the curr node*/
					if (data < parent->data) {
						parent->left = NULL;
						free(ptr);
						printf("deleted\n");
						return;
					} else {
						parent->right = NULL;
						free(ptr);
						printf("deleted\n");
						return;
					}
				}
			}


				/*if only a right child*/
			if (ptr->right !=NULL && ptr->left == NULL) {
				if (parent==NULL) {
					root = ptr->right;
					free (ptr);
					printf("deleted\n");
					return;
				} else {

					if (parent->data > data) {
						parent->left = ptr->right;
					}else {
						parent->right = ptr->right;
					}

					free(ptr);
					printf("deleted\n");
					return;
				}
			}
				/*if only a left child*/
			if (ptr->left !=NULL && ptr->right == NULL) {
				if (parent==NULL) {
					root = ptr->left;
					free (ptr);
					printf("deleted\n");
					return;
				} 
			}


			/*if two children
			if(ptr->right!=NULL && ptr->left!= NULL) {
				//int replacement = maxfind(ptr->left);
				ptr->data = replacement;
				printf("deleted\n");
				return;
			}
		*/

		}else if (ptr->data>data) {
			parent = ptr;
			ptr = ptr->left;
		}else {
			parent = ptr;
			ptr = ptr->right;
		}


	}

	/*if the item was not found*/

	printf("absent\n");
	return;


}


int main(int argc, char **argv){
 
    int data;
    char c;
    while(scanf("%c", &c) != -1){
        if(c == 'i'){
            scanf("%d", &data);
            insert(root, data);
        }
        if(c == 's'){
            scanf("%d", &data);
            search(data);
        }
        if(c == 'd'){
            scanf("%d", &data);
            delete(data);
        }
		if(c == 'p'){
			printNodes(root);
			printf("\n");
		}
        
		
    }

    freeTree(root);
    return EXIT_SUCCESS;
}



