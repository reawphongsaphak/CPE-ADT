#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "week9.h"
#define MAX 100000

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;

typedef node_t bst_t;

int i;
int arr[MAX];

bst_t* insert(bst_t* t, int val){
    bst_t* newNode = (bst_t*)malloc(sizeof(bst_t));
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;

    if (t == NULL){
        return newNode;
    }

    bst_t* prev = NULL;
    bst_t* tmp = t;

    while (tmp != NULL){
        prev = tmp;
        if (val > tmp->data){
            tmp = tmp->right;
        } else {
            tmp = tmp->left;
        } 
    }

    if (val > prev->data){
        prev->right = newNode;
    } else {
        prev->left = newNode;
    }

    return t;
}

bst_t* delete(bst_t* t, int target){
    if (t == NULL){
        return t;
    }
    if (target > t->data){
        t->right = delete(t->right, target);
    } else if (target < t->data){
        t->left = delete(t->left, target);
    } else {
        //* leaf node
        if (t->left == NULL & t->right == NULL){
            free(t);
            return NULL;
        } 
        //* case 1 child
        if (t->left == NULL){
            bst_t* tmp = t->right;
            free(t);
            return tmp;
        } else if (t->right == NULL){
            bst_t* tmp = t->left;
            free(t);
            return tmp;
        }
        //* case 2 childs
        if (t->left != NULL && t->right != NULL) {
            bst_t* tmp = t->right;
            while (tmp->left != NULL) {
                tmp = tmp->left;
            }
            t->data = tmp->data;
            t->right = delete(t->right, tmp->data);
        }
    }
    return t;
}

int find (bst_t* t, int target){
    while (t != NULL){
        if (t->data == target) {
            return 1;
        } else if (target > t->data) {
            t = t->right;
        } else { t = t->left;}
    }
    return 0;
}

int find_min(bst_t* t){
    while (t->left != NULL){
        t = t->left;
    }
    return t->data;
}

int find_max(bst_t* t){
    while (t->right != NULL){
        t = t->right;
    }
    return t->data;
}

int size(bst_t* t){
    if (t == NULL){
        return 0;
    }
    return size(t->left) + size(t->right) + 1;
}

int find_k_th(bst_t* t, int pos){
    int l_size = 0;
    while (t != NULL){
        l_size = size(t->left);
        if (pos == l_size + 1){
            return t->data;
        } else if (pos <= l_size) {
            t = t->left;
        } else {
            t = t->right;
            pos = pos - l_size - 1;
        }
    }
    return -1;
}

int main(void) {
    bst_t *t = NULL;
    int n, i;
    int command, data, k;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                t = insert(t, data);
                break;
            case 2:
                scanf("%d", &data);
                t = delete(t, data);
                break;
            case 3:
                scanf("%d", &data);
                printf("%d\n", find(t, data));
                break;
            case 4:
                printf("%d\n", find_min(t));
                break;
            case 5:
                printf("%d\n", find_max(t));
                break;
            case 6:
                scanf("%d", &k);
                printf("%d\n", find_k_th(t, k));
                break;
        }
    }
return 0;
}