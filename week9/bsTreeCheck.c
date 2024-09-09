#include <stdio.h>
#include <stdlib.h>
#define __bin_tree__
#include <week9.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define INT_MIN -100000
#define INT_MAX 100000
#ifndef __bin_tree__
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t tree_t;
#endif

int isBST(tree_t* t, int min, int max);

int is_bst(tree_t* t){
    return isBST(t, INT_MIN, INT_MAX);
}

int isBST(tree_t* t, int min, int max){
    if (t == NULL){
        return 1;
    }
    if (t->data < min || t->data > max){
        return 0;
    }
    return isBST(t->left, min, t->data - 1) && isBST(t->right, t->data + 1, max);
}

int height(tree_t* t){
    if (t == NULL){
        return -1;
    }
    int hl = height(t->left);
    int hr = height(t->right);
    return MAX(hl, hr) +1;
}

int is_avl(tree_t* t){
    if (t == NULL){
        return 1;
    }
    int hl = height(t->left);
    int hr = height(t->right);
    if (abs(hl - hr) > 1){
        return 0;
    }
    int check_l = is_avl(t->left);
    int check_r = is_avl(t->right);
    return check_l && check_r && is_bst(t);
}

int main(void) {
    tree_t *t = NULL;
    int n, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d %d", &parent, &child, &branch);
        t = attach(t, parent, child, branch);
    }
    // printf("%d\n", is_bst(t));
    printf("%d %d\n", is_bst(t), is_avl(t));
    return 0;
}