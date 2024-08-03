#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
} node_t;

typedef node_t stack;
typedef node_t queue;

void enqueue(queue** q, int data);
int dequeue(queue** q);
void show(queue* q);
int is_sort(queue* q);

void push(stack** s, int data);
int pop(stack** s);

queue* q_rear = NULL;

int main(){
    int n, temp;
    scanf("%d", &n);
    
    queue* q = NULL;
    stack* s = NULL;
    
    queue* sorted_q = NULL;

    for (int i = 0; i < n; i++){
        scanf("%d", &temp);
        enqueue(&q, temp);
    }

    int count = 1;
    while(q != NULL){
        int data = dequeue(&q);

        if (count == data){
            enqueue(&sorted_q, data);
            count++;
        }else {
            push(&s, data);
        }

        while (s != NULL && s->data == count){
            int data = pop(&s);
            enqueue(&sorted_q, data);
            count++;
        }
    }
    while (s != NULL){
        int data = pop(&s);
        enqueue(&sorted_q, data);
    }
    
    // show(sorted_q);
    printf("%d", is_sort(sorted_q));
    return 0;
}

void enqueue(queue** q, int data){
    queue* newNode = (queue*)malloc(sizeof(queue));
    newNode->data = data;
    newNode->next = NULL;
    if (*q == NULL){
        *q = newNode;
        q_rear = newNode;
        return;
    }

    q_rear->next = newNode;
    q_rear = newNode;
    return;
}

int dequeue(queue** q){
    if (*q == NULL){
        return 0;
    }
    queue* temp = *q;
    *q = (*q)->next;
    int data = temp->data;
    free(temp);
    return data;
}

void push(stack** s, int data){
    stack* newNode = (stack*)malloc(sizeof(stack));
    newNode->data = data;
    newNode->next = NULL;
    if (*s == NULL){
        *s = newNode;
        return;
    }
    newNode->next = *s;
    *s = newNode;
    return;
}

int pop(stack** s){
    stack* temp = *s;
    *s = (*s)->next;
    int data = temp->data;
    free(temp);
    return data;
}

void show(queue* q){
    queue* temp = q;
    while (temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int is_sort(queue* q){
    queue* curr = q->next;
    queue* prev = q;
    while (curr != NULL){
        if (curr->data < prev->data){
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }
    return 1;
}