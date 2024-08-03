#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
} queue_t;

queue_t* l_rear = NULL;
queue_t* r_rear = NULL;

void enqueue(queue_t** q, int data, char side);
void dequeue(queue_t** q);
void show(queue_t* q);

int main(){

    queue_t* l_q = NULL;
    queue_t* r_q = NULL;

    int len_f = 0;              //* length of furry
    scanf("%d", &len_f);
    len_f = len_f * 100;        //* convert to centimeter

    int n, val;
    char side;
    scanf("%d", &n);

    for (int i = 0; i < n; i++){
        scanf("%d %c", &val, &side);

        switch(side){
            case 'L':
                enqueue(&l_q, val, side);
                break;
            case 'R':
                enqueue(&r_q, val, side);
                break;
        }
    }

    int count = 0;
    int s = 1;
    while (l_q != NULL || r_q != NULL){
        int cap = len_f;

        if (s % 2 == 1){
            while (cap >= 0){

                if (l_q == NULL){
                    s += 1;
                    count ++;
                    break;
                }

                if (cap - l_q->data >= 0){
                    int data = l_q->data;
                    cap -= data;
                    dequeue(&l_q);
                } else {
                    s += 1;
                    count ++;
                    break;
                }
            }
        }

        else if(s % 2 == 0){

            while (cap >= 0){
                if (r_q == NULL){
                    s += 1;
                    count ++;
                    break;
                }
                
                if (cap - r_q->data >= 0){
                    int data = r_q->data;
                    cap -= data;
                    dequeue(&r_q);
                } else {
                    s += 1;
                    count ++;
                    break;
                }
            }
           
        }     
    }
    printf("%d\n", count);

    return 0;
}


void enqueue(queue_t** q, int data, char side){
    queue_t* newNode = (queue_t*)malloc(sizeof(queue_t));
    newNode->data = data;
    newNode->next = NULL;
    
    if (*q == NULL){
        *q = newNode;
        switch(side) {
            case 'L':
                l_rear = newNode;
                return;
            case 'R':
                r_rear = newNode;
                return;
        }
    }

    switch(side) {
        case 'L':
            l_rear->next = newNode;
            l_rear = newNode;
            return;
        case 'R':
            r_rear->next = newNode;
            r_rear = newNode;
            return;
    }
}

void show(queue_t* q){
    queue_t* temp = q;
    while (temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void dequeue(queue_t** q){
    queue_t* temp = *q;
    *q = (*q)->next;
    free(temp);
    return;
}

