#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
#define TRUE 1
#define FALSE 0

typedef struct node {
    int data;
    struct node *next;
}node;

node **globalHead;
void printList(node *);
void insertNodeAtEnd(node **, int);
void insertNodeAtStart(node **, int);
node* insertNodeWithSingleHeadPointer(node *, int);
void insertNodeAtPosition(node **, int, int);
int isValidIndex(node *, int);
void insertNodeAfterTarget(node **, int, int);
void deleteNodeAtEnd(node **);
void deleteNodeAtStart(node **);
void deleteNodeAtPosition(node **, int);
void reverseList(node **);
void reverseListUsingRecursion(node *, node *);
void printListUsingRecursion(node *);
void printReverseListUsingRecursion(node *);
void swapListAdjacentNodes(node **);
int findMiddleOfList(node *);
void introduceLoopInList(node **, int);
node* detectLoopInList(node *);
void resolveLoopInList(node **);

void resolveLoopInList(node **head) {
    node *cur;
    cur = detectLoopInList(*head);
    if(cur) {
        node *tmp=*head;
        while(tmp->next != cur->next) {
            tmp = tmp->next;
            cur = cur->next;
        }
        printf("Loop resloved in list, was present at node %d\n", cur->next->data);
        cur->next = NULL;
    }
}

node* detectLoopInList(node *head) {
    node *moveSlow, *moveFast;
    int iteration=0;
    moveSlow = head;
    //moveFast = head->next;
    moveFast = head;
    while(moveFast && moveFast->next) {
        iteration++;
        moveFast = moveFast->next->next;
        moveSlow = moveSlow->next;
        if(moveFast == moveSlow) {
            printf("\nLoop exist in list. Detected in %d iterations\n", iteration);
            return moveFast;
        }
    }
    printf("\nList doesn't contain any loop\n");
    return NULL;
}

void introduceLoopInList(node **head, int position) {
    if(!isValidIndex(*head, position)) return;
    node *tmp,*temp;
    tmp = temp = *head;
    int count=1, key;
    while(tmp->next) tmp = tmp->next;

    if(position == 1) {
        tmp->next = *head;
        key = (*head)->data;
    }
    else {
        while(count++ != position) temp = temp->next;
        tmp->next = temp;
        key = temp->data;
    }
    printf("Loop introduced in list at position %d having value %d\n", position, key);
}

int findMiddleOfList(node *head) {
    /* find the middle element of a singly linked list without iterating the list more than once*/
    node *moveSlow,*moveFast;
    moveSlow = moveFast =  head;

    if(!head) {
        printf("Empty list\n");
        return 0;
    }

    while(moveFast && moveFast->next) {
        moveSlow = moveSlow->next;
        moveFast = moveFast->next->next;
    }
    return moveSlow->data;
}

void swapListAdjacentNodes(node **head) {
    node *cur=*head;

    if(!cur || !cur->next) {
        printf("Swap fail, list is having 0 or 1 node\n");
        return;
    }

    while(cur && cur->next) {
        int value = cur->data;
        cur->data = cur->next->data;
        cur->next->data = value;
        cur = cur->next->next;
    }
    printf("Adjacent nodes swapped:\n");
}

void reverseListUsingRecursion(node *prev, node *cur) {
    if(cur->next) {
        reverseListUsingRecursion(cur, cur->next);
        cur->next = prev;
    }
    else {
        *globalHead = cur;
         cur->next = prev;
    }
}

void printReverseListUsingRecursion(node *head) {
    if(!head) return;
    printReverseListUsingRecursion(head->next);
    printf("%d ", head->data);
}

void printListUsingRecursion(node *head) {
    if(!head) return;
    printf("%d ",head->data);
    printListUsingRecursion(head->next);
}

void reverseList(node **head) {
	node *cur = *head;
	node *back, *tmp;
	back = NULL; tmp = cur;
    
    if(!cur || !cur->next) {
        printf("Not a valid list for reversal, having only 0 or 1 node\n");
        return;
    }
	while(cur) {
		tmp = cur->next;
		cur->next = back;
		back = cur;
		cur = tmp;
	}
	*head = back;
    printf("Reversed list:\n"); 
}

void deleteNodeAtPosition(node **head, int position) {
    if(!isValidIndex(*head, position)) return;
    if(!*head) {
        printf("Invalid operation, List is empty");
        return;
    }
    printf("Deleted node from position %d\n", position);
    node *tmp, *prev;
    int count = 1;
    tmp = prev = *head;
    if(position == 1) {
        *head = tmp->next;
        tmp->next = NULL;
        free(tmp);
        return;
    }
    while(count++ != position) {
        prev = tmp;
        tmp = tmp->next;
    }
    prev->next = tmp->next;
    tmp->next = NULL;
    free(tmp);
}

void deleteNodeAtStart(node **head) {
    if(!*head) {
        printf("Invalid operation, List is empty\n");
    }
    node *tmp = *head;
    *head = (*head)->next;
    tmp->next = NULL;
    free(tmp);
    printf("Deleted node from start\n");
}

void deleteNodeAtEnd(node **head) {
    if(!*head) {
        printf("Invalid operation, List is empty\n");
    }
    node *tmp, *prev;
    tmp = prev = *head;
    while(tmp->next && tmp->next->next) {
        tmp=tmp->next;
    }
    prev = tmp->next;
    tmp->next = NULL;
    free(prev);
    printf("Deleted node from end\n");
}

void insertNodeAfterTarget(node **head, int value, int key) {
    node *temp = (node *)malloc(sizeof(node));
    node *tmp = *head;
    temp->data = value;
    temp->next = NULL;
    if(!*head) {
        printf("Target value %d doesn't exist, list is empty\n", key);
        return;
    }
    while(tmp && (tmp->data != key)) {
        tmp = tmp->next;
    }
    if(tmp) {
        temp->next = tmp->next;
        tmp->next = temp;
    }
    else {
        printf("Insert fail, target value %d doesn't exist in this list\n", key);
        return;
    }
    printf("Added new node %d after target value %d\n", value, key);
}

int isValidIndex(node *head, int position) {
    int count=1;
    if(position <= 0) {
        printf("%d is not a valid index for this list\n", position);
        return 0;
    }
    while(head) {
        count++;
        head = head->next;
    }
    if(position > count) {
        printf("%d is not a valid index for this list\n", position);
        return 0;
    }
    return 1;
}

void insertNodeAtPosition(node **head, int value, int position) {
    if(!isValidIndex(*head, position)) return;
    int count=2;
    node *tmp=*head, *temp = (node *)malloc(sizeof(node));
    node *prev = *head;
    temp->data = value;
    temp->next = NULL;
    if(!*head) {
        *head = temp;
    }
    else {
        tmp = tmp->next;
        while(count++ != position) {
            prev = tmp;
            tmp = tmp->next;
        }
        prev->next = temp;
        temp->next = tmp;
    }
    printf("Added new node %d at position %d\n", value, position);
}

node* insertNodeWithSingleHeadPointer(node *head, int value) {
    node *temp = (node *)malloc(sizeof(node));
    temp->data = value;
    temp->next = NULL;
    if(head) {
        node *tmp=head;
        while(tmp->next)tmp=tmp->next;
        tmp->next = temp;
    }
    else {
        head = temp;
    }
    printf("Added new node %d at end\n", value);
    return head;
}

void insertNodeAtStart(node **head, int value) {
    node *temp = (node *)malloc(sizeof(node));
    temp->data = value;
    temp->next = *head;
    *head = temp;
    printf("Added new node %d at start\n", value);
}

void insertNodeAtEnd(node **head, int value) {
    node *temp = (node *)malloc(sizeof(node));
    temp->data = value;
    temp->next = NULL;
    if(!*head) {
        *head = temp;
    }
    else {
        node *tmp = *head;
        while(tmp->next)tmp=tmp->next;
        tmp->next = temp;
    }
    printf("Added new node %d at end\n", value);
}

void printList(node *head) {
    int nodeCount=0;
    printf("Node list is: ");
    while(head){
        printf("%d ",head->data);
        head = head->next;
        nodeCount++;
        if(nodeCount > MAX_NODES) {
            if(detectLoopInList(head)) {
                printf("\nPossible circular loop exist in list. Exit print\n");
                break;
            }
        }
    }
    printf("\n");
}

int main() {
    node *head=NULL;
    int i=0,size,input[] = {14,23,1,2,5,12,7,31,53};
    size = sizeof(input)/sizeof(int);
    while(i<size) insertNodeAtEnd(&head, input[i++]);
    printList(head);

    reverseList(&head);
    printList(head);
    insertNodeAtStart(&head, 0);
    head = insertNodeWithSingleHeadPointer(head, 4);
    insertNodeAtPosition(&head, 5, 4);
    insertNodeAfterTarget(&head, 15, 2);
    printList(head);

    printf("List print using recursion: ");
    printListUsingRecursion(head);
    printf("\n");
    printf("List print in reverse order using recursion: ");
    printReverseListUsingRecursion(head);
    printf("\n");

    insertNodeAfterTarget(&head, 23, 10);
    printList(head);
    deleteNodeAtEnd(&head);
    deleteNodeAtStart(&head);
    deleteNodeAtPosition(&head, 4);
    printList(head);
    deleteNodeAtPosition(&head, 3);

    printList(head);
    reverseList(&head);
    printList(head);

    globalHead = &head;
    printf("Reversing list using recursion:\n");
    reverseListUsingRecursion(NULL, head);
    printList(head);

    swapListAdjacentNodes(&head);
    printList(head); 

    printf("Middle element of list is: %d\n", findMiddleOfList(head));

    introduceLoopInList(&head, 2);
    detectLoopInList(head);
    resolveLoopInList(&head);
    printList(head);

    return 0;
}