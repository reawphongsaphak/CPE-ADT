#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int player;
    int num;
    struct node* prev;
    struct node* next;
} node_t;

void addNode(node_t** head,int val, int player);
void delNode(node_t** head, int player);
void gameplay(node_t** head, int num);
void show(node_t** head);
void show_r(node_t** head);
int check (int n, int num);

int main() {
    int number_of_player, num;
    node_t* head = NULL;
    scanf("%d %d", &number_of_player, &num);

    for (int i = 0; i < number_of_player; i++){
        int n;
        scanf("%d", &n);
        addNode(&head, n, i+1);
    }

    gameplay(&head, num);
    // show(&head);

    return 0;
}

void gameplay(node_t** head, int num){
    int n = 1;
    node_t* temp = *head;
    while (temp != temp->next){
        // printf("count : %d\n", n);
        if (check(n, num)){
            temp->num -= 1;
            // printf("player : %d have num : %d\n", temp->player, temp->num);
        }
        if (temp->num == -1) {
            temp = temp->next;
            // printf("player : %d is out\n", temp->prev->player);
            delNode(head, temp->prev->player);
            
            n++;
            continue;
        }
        n++;
        temp = temp->next;
    }
    // show(&*head);
    printf("%d", temp->player);
}

//* check condition to count
int check (int n, int num){
    if (n%num == 0){
        return 1;
    }
    while(n > 0){
        if (n % 10 == num){
            return 1;
        }
        n /= 10;
    }
    return 0;
}

void addNode(node_t** head,int val, int player){
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->num = val;
    newNode->player = player;

    if ((*head) == NULL){
        newNode->next = newNode;
        newNode->prev = newNode;
        *head = newNode;
        return;
    }
    
    node_t* last = (*head)->prev;
    newNode->next = *head;
    (*head)->prev = newNode;
    newNode->prev = last;
    last->next = newNode;
}

//* delete by player
void delNode(node_t** head, int player){
    if (*head == NULL){
        return;
    }
    node_t* curr = *head;
    do {
        if (curr->player == player) {
            if (curr->next == curr) {
                free(curr);
                *head = NULL;
                return;
            }

            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            if (curr == *head){
                *head = curr->next;
            }
            free(curr);
            return;
        }
        curr = curr->next;
    } while (curr != *head);
}

void show(node_t** head){
    if (*head == NULL){
        printf("List is empty\n");
        return;
    }
    node_t* temp = *head;
    while (temp->next != *head){
        printf("player : %d have num : %d\n", temp->player, temp->num);
        temp = temp->next;
    }
    printf("player : %d have num : %d\n", temp->player, temp->num);
}
