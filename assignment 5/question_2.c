#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExpLL);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
    if (!isEmptyLinkedList(*inExpLL))
        removeAllNodes(inExpLL);
    LinkedList* ll = malloc(sizeof(LinkedList));

    ll->head = NULL;
    ll->size = 0;
    
    int len = 0;
    enum ExpType en;
    int inte = -1;
    int temp;

    while (infix[len] != '\0') {
        if ((infix[len] <= '9') && (infix[len] >= '0')) {
            en = OPERAND;
            if (inte == -1)
                inte = infix[len] - ('1' - 1);
            else
                inte = 10 * inte + infix[len] - '1' + 1;
        }
        else {
            if (len != 0 && inte != -1)
                insertNode(ll, inte, en);
            en = OPT;
            inte = -1;
            insertNode(ll, infix[len], en);
        }
        ++len;
    }

    if (inte != 0)
        insertNode(ll, inte, en);

    ListNode* cur = ll->head;
    Stack* s = malloc(sizeof(Stack));
    s->head = NULL;
    s->size = 0;

    while (cur) {
        if (cur->type == OPERAND)
            insertNode(inExpLL, cur->item, OPERAND);
        else {
            switch (cur->item) {
                case ')':
                    push(s, ')');
                    break;
                case '(':
                    while (!isEmptyStack(*s) && peek(*s) != ')') {
                        temp = peek(*s);
                        pop(s);
                        insertNode(inExpLL, temp, OPT);
                    }
                    if (!isEmptyStack(*s))
                        pop(s);
                    break;
                case '+':
                    while (!isEmptyStack(*s) && peek(*s) != ')' && peek(*s) != '-' && peek(*s) != '+') {
                        temp = peek(*s);
                        pop(s);
                        insertNode(inExpLL, temp, OPT);
                    }
                    push(s, '+');
                    break;
                case '-':
                    while (!isEmptyStack(*s) && peek(*s) != ')' && peek(*s) != '+' && peek(*s) != '-') {
                        temp = peek(*s);
                        pop(s);
                        insertNode(inExpLL, temp, OPT);
                    }
                    push(s, '-');
                    break;
                case '*':
                    while (!isEmptyStack(*s) && peek(*s) == '/' && peek(*s) == '*') {
                        temp = peek(*s);
                        pop(s);
                        insertNode(inExpLL, temp, OPT);
                    }
                    push(s, '*');
                    break;
                case '/':
                    while (!isEmptyStack(*s) && peek(*s) == '*' && peek(*s) == '/') {
                        temp = peek(*s);
                        pop(s);
                        insertNode(inExpLL, temp, OPT);
                    }
                    push(s, '/');
            }
        }
        cur = cur->next;
    }
    while (!isEmptyStack(*s)) {
        temp = peek(*s);
        pop(s);
        insertNode(inExpLL, temp, OPT);
    }
    //Write your code here
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}