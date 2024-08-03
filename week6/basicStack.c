#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

// typedef node_t stack_t;

node_t* push(node_t *s, int value){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->data = value;
    newNode->next = NULL;
    if (s == NULL){
        s = newNode;
        return s;
    }
    newNode->next = s;
    return newNode;
}

void top(node_t* s){
    if (s != NULL){
        printf("%d\n",s->data);
        return;
    }
    printf("Stack is empty.");
    return;
}

node_t* pop(node_t* s){
    if (s == NULL){
        return s;
    }
    node_t* temp = s;
    s = s->next;
    free(temp);
    return s;
}

void empty(node_t* s){
    if (s == NULL){
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack is not empty.\n");
    return;
}

void size(node_t* s){
    int size = 0;
    node_t* temp = s;
    while (temp != NULL){
        temp = temp->next;
        size++;
    }
    printf("%d\n",size);
    return;
}

int main(void) {
    node_t *s = NULL;
    int n, i, command, value;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d", &value);
                s = push(s, value);
                break;
            case 2:
                top(s);
                break;
            case 3:
                s = pop(s);
                break;
            case 4:
                empty(s);
                break;
            case 5:
                size(s);
                break;
            }
    }
return 0;
}