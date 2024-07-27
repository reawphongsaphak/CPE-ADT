#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

node_t* append(node_t* head){
    int value;
    scanf("%d", &value);
    node_t* newNode = (node_t*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return head;
    }

    node_t* temp = head;    //* make a pointer name temp that point to head
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}


void get(node_t* head) {
    int n;
    scanf("%d", &n);

    node_t* temp = head;
    for (int i = 0; i < n; i++){
        temp = temp->next;
    }
    printf("%d\n", temp->data);
}

void show(node_t* head){
    node_t* temp = head;
    if (head == NULL){printf("\n"); return;}
    while(temp->next != NULL){
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("%d\n",temp->data);
}

node_t* reverse(node_t* head){
    struct node* prev = NULL;
    struct node* curr = head;
    struct node* next = NULL;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}

node_t* cut(node_t* head){
    int first, second;
    scanf("%d %d",&first, &second);
    
    node_t* temp = head;
    node_t* temp2;
    for (int i = 0; i < first; i++){
        temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    head = temp;

    node_t* temp4;
    for (int i = 0; i < ((second - first)); i++){
        temp = temp->next;
    }
    if (temp->next == NULL){
        return head;
    }
    node_t* temp5 = temp;
    temp = temp->next;
    while (temp->next != NULL){
        temp4 = temp;
        temp = temp->next;
        free(temp4);
    }
    temp5->next = NULL;
    free(temp);
    return head;
}

int main(void) {
    node_t *startNode;
    int n,i;
    char command;
    startNode = NULL;

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf(" %c", &command);

        switch (command) {
            case 'A':
                startNode = append(startNode);
                break;
            case 'G':
                get(startNode);
                break;
            case 'S':
                show(startNode);
                break;
            case 'R':
                startNode = reverse(startNode);
                break;
            case 'C':
                startNode = cut(startNode);
                break;
            default:
                break;
        }
    }
    return 0;