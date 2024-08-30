#include <stdio.h>
#include <stdlib.h>
#include "week8.h"

#ifndef __bin_tree__
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t tree_t;
#endif

int check(tree_t* t, int s){
    if (t == NULL){
        return 0;
    }
    s = s - t->data;
    if (s == 0){
        return check(t->left, s) + check(t->right, s) + 1;
    }
    return check(t->left, s) + check(t->right, s);
}

int  countPathsWithSum(tree_t* t, int s){
    if (t == NULL){
        return 0;
    }
    int count = 0;
    count += check(t, s);
    count += countPathsWithSum(t->left, s);
    count += countPathsWithSum(t->right, s);
    
    return count;
}

int main(void) {
    tree_t *t = NULL;
    int n, s, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right
    scanf("%d %d", &n, &s);
    for (i = 0; i < n; i++) {
        scanf("%d %d %d", &parent, &child, &branch);
        t = attach(t, parent, child, branch);
    }
    printf("%d\n", countPathsWithSum(t, s));
    return 0;
}