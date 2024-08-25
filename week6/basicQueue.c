#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

typedef node_t queue_t;

queue_t* enqueue(queue_t* q,int value){
    queue_t* newNode = (queue_t*)malloc(sizeof(queue_t));
    newNode->data = value;
    newNode->next = NULL;

    if (q == NULL){
        q = newNode;
        return q;
    }
    
    queue_t* temp = q;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    return q;
}

queue_t* dequeue(queue_t* q){
    if (q == NULL){
        printf("Queue is empty.\n");
        return q;
    }
    queue_t* temp = q;
    q = q->next;
    printf("%d\n",temp->data);
    free(temp);
    return q;
}

void show(queue_t* q){
    if (q == NULL){
        printf("Queue is empty.");
        return;
    }

    queue_t* temp = q;
    while (temp != NULL){
        printf("%d ",temp->data);
        temp = temp->next;
    }
    return;
}

void empty(queue_t* q){
    if (q == NULL){
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue is not empty.\n");
    return;
}

void size(queue_t* q){
    int size = 0;
    queue_t* temp = q;
    while (temp != NULL){
        size++;
        temp = temp->next;
    }
    printf("%d\n",size);
    return;
}

int main(void) {
    queue_t *q = NULL;
    int n, i, command, value;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d", &value);
                q = enqueue(q, value);
                break;
            case 2:
                q = dequeue(q);
                break;
            case 3:
                show(q);
                break;
            case 4:
                empty(q);
                break;
            case 5:
                size(q);
                break;
        }
    }
    return 0;
}