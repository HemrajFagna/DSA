#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// stack using arrays
// stack using linked list

#define MAX_SIZE 100
#define MAX_SIZE_NODE_DATA 50
#define ERROR -9999
int stack[MAX_SIZE];

typedef struct node {
    char data[MAX_SIZE_NODE_DATA];
    struct node *next;
}node;
node *head;

void stackUsingArray();
void push(int);
int pop();
void printStack();
void stackUsingLinkedList();
void pushItem(char *);
int popItem();
void printStackItem(node *);
void reverseStringUsingStack(char *);

int top=-1;

void push(int item) {
    if(top == MAX_SIZE-1) {
        printf("\nPush failed. Stack overflow.\n");
        return;
    }
    stack[++top] = item;
    printf("\nItem %d pushed on to the stack.\n", item);
}

int pop() {
    if(top == -1) {
        printf("\nPop failed. Stack is empty.\n");
        return ERROR;
    }
    printf("\nItem %d popped off from the stack.\n", stack[top]);
    return stack[top--];
}

void printStack() {
    int i;
    if(top == -1) {
        printf("\nStack is Empty.\n");
    }
    printf("\nCurrent Array Stack: ");
    for(i=0;i<=top;i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

void pushItem(char *item) {
    node *temp = (node *)malloc(sizeof(node));
    if(!temp) {
        printf("\nPush item failed. Memory not available\n");
        return;
    }
    strcpy(temp->data, item);
    temp->next = head;
    head = temp;
    printf("\nPushed Item %s on the List.\n", temp->data);
}


//linked list
int popItem() {
    if(!head) {
        printf("\nPop Item failed. Stack list is empty.\n");
        return ERROR;
    }
    node *temp=head;
    head = head->next;
    printf("\nPopped Item %s from the stack list.\n", temp->data);
    free(temp);
}

void printStackItem(node *temp) {
    if(!temp) {
        return;
    }
    printStackItem(temp->next);
    printf("%s ",temp->data);
}

void stackUsingLinkedList() {
    node *temp = head;
    printf("\nCurrent Linked List Stack : ");
    printStackItem(temp);
    popItem();pushItem("212");pushItem("12");pushItem("32");pushItem("2");
    popItem();popItem();
    pushItem("6253");pushItem("21337");
    temp = head;
    printf("\nCurrent Linked List Stack : ");
    printStackItem(temp);
}

void stackUsingArray() {
    pop();push(2);push(6);push(9);push(1);pop();
    printStack();
}

void reverseStringUsingStack(char *str) {
    char arr[2];
    int i=0;
    while(str[i]!='\0') {
        arr[0] = str[i++];
        arr[1] = '\0';
        pushItem(arr);
        }
    while(i--) { popItem();}
}

int main() {
    stackUsingArray();
    stackUsingLinkedList();
    reverseStringUsingStack("abcde");
    printStackItem(head);
    return 0;
}