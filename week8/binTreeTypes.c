#include <week8.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#ifndef __bin_tree__

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t tree_t;

#endif

typedef struct queue_node {
    tree_t* tree_node;
    struct queue_node* next;
} queue_node;

typedef struct queue_t {
    queue_node* front;
    queue_node* rear;
} queue_t;

void enqueue(queue_t* q, tree_t* node) {
    queue_node* temp = (queue_node*)malloc(sizeof(queue_node));
    temp->tree_node = node;
    temp->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

tree_t* dequeue(queue_t* q) {
    if (q->front == NULL) {
        return NULL;
    }

    queue_node* temp = q->front;
    tree_t* tree_node = temp->tree_node;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return tree_node;
}

int is_full(tree_t* t){

    if ((t->left != NULL && t->right == NULL) || (t->left == NULL && t->right != NULL)){
        return 0;
    }
    else if (t->left == t->right){
        return 1;
    }
    return MIN(is_full(t->left), is_full(t->right));
}

int height(tree_t* t){
    if (t == NULL){
        return -1;
    }
    int hl = height(t->left);
    int hr = height(t->right);
    return (hl > hr)?hl + 1:hr + 1;
}

int size(tree_t* t){
    if (t == NULL){
        return 0;
    }
    return size(t->left) + size(t->right) + 1;
}

int is_perfect(tree_t* t){
    int h = height(t);
    int expected_size = (1 << (h + 1)) -1;
    return (expected_size == size(t)) ? 1 : 0;
}

int is_complete(tree_t* t){
    if (t == NULL){
        return 1;
    }
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    enqueue(q, t);
    bool check = false;

    //* if find NULL for the first time other node should be NULL with BFS
    while (q->front != NULL){
        tree_t* tmp = dequeue(q);
        if (tmp == NULL){
            check = true;
        } else {
            if (check){
                free(q);
                return 0;
            }

            enqueue(q, tmp->left);
            enqueue(q, tmp->right);
        }
    }
    free(q);
    return 1;
}

int is_degenerate(tree_t* t){
    if (t == NULL){
        return 1;
    }
    if (t->left != NULL && t->right != NULL){
        return 0;
    }
    return MAX(is_degenerate(t->left), is_degenerate(t->right));
}

int is_skewed(tree_t* t){
    if (t == NULL){
        return 1;
    }
    tree_t * tmp = t;
    bool is_left_valid = (tmp->left != NULL) ? true : false;
    
    while (tmp != NULL){
        if (is_left_valid){
            if (tmp->right != NULL){
                return 0;
            }
            tmp = tmp->left;
        } else {
            if (tmp->left != NULL){
                return 0;
            }
            tmp = tmp->right; 
        }
    }
    return 1;
}

int main(void) {
    tree_t *t = NULL;
    int n, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right
    scanf("%d", &n);
    for (i=0; i < n; i++) {
        scanf("%d %d %d", &parent, &child, &branch);
        t = attach(t, parent, child, branch);
    }
    printf("%d %d %d %d %d\n", is_full(t),is_perfect(t), is_complete(t), is_degenerate(t), is_skewed(t));
    return 0;
}