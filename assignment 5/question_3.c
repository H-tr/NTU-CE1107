#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void createExpTree(BTNode** root,char* prefix)
{
 //Write your code here
    Stack* s = malloc(sizeof(Stack));
    s->head = NULL;
    s->size = 0;

    (*root) = malloc(sizeof(BTNode));
    push(s, (*root));

    BTNode* cur = *root;
    int len = 0;
    int info = -1;

    while (prefix[len] != '\0') {
        if (prefix[len] <= '9' && prefix[len] >= '0') {
            if (info == -1)
                info = prefix[len] - '1' + 1;
            else
                info = info * 10 + prefix[len] -'1' + 1;
        }
        else if (prefix[len] == ' ') {
            if (info != -1) {
                cur->item = info;
                cur->left = cur->right = NULL;
                info = -1;
                
                if(!isEmptyStack(*s)) {
                    cur = peek(*s);
                    pop(s);
                }
            }
        }
        else {
            cur->item = prefix[len];
            cur->left = malloc(sizeof(BTNode));
            cur->right = malloc(sizeof(BTNode));

            push(s, cur->right);
            cur = cur->left;
        }
        len++;
    }
    cur->item = info;
    cur->left = cur->right = NULL;
}

void printTree(BTNode *node){
    if (node->left == NULL && node->right == NULL)
        printf("%d ", node->item);
    else {
        printTree(node->left);
        printf("%c ", node->item);
        printTree(node->right);
    }
    //Write your code here
}


void printTreePostfix(BTNode *node){
   //Write your code here
    if (node->left == NULL && node->right == NULL)
        printf("%d ", node->item);
    else {
        printTreePostfix(node->left);
        printTreePostfix(node->right);
        printf("%c ", node->item);
    }
}

double computeTree(BTNode *node) {
    if (node->left == NULL && node->right == NULL) {
        return (double)node->item;
    }
    else {
        switch (node->item) {
            case '+': return computeTree(node->left) + computeTree(node->right);
            case '-': return computeTree(node->left) - computeTree(node->right);
            case '*': return computeTree(node->left) * computeTree(node->right);
            case '/': return computeTree(node->left) / computeTree(node->right);
        }
    }
//Write your code here
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}