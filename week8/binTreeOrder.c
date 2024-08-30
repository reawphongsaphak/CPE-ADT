#include <stdio.h>
#include <stdlib.h>
#include <week8.h>
#ifndef __bin_tree__
typedef struct node {
int data;
struct node *left;
struct node *right;
} node_t;
typedef node_t tree_t;
#endif

void print_preorder(tree_t* t){
    if (t == NULL){
        return;
    }
    int node = t->data;
    printf("%d ",node);
    print_preorder(t->left);
    print_preorder(t->right);
    return;
}

void print_postorder(tree_t* t){
    if (t == NULL){
        return;
    }
    int node = t->data;
    print_postorder(t->left);
    print_postorder(t->right);
    printf("%d ",node);
    return;
}

void print_inorder(tree_t* t){
    if (t == NULL){
        return;
    }
    int node = t->data;
    print_inorder(t->left);
    printf("%d ",node);
    print_inorder(t->right);
    return;
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
    print_preorder(t);
    printf("\n");
    print_postorder(t);
    printf("\n");
    print_inorder(t);
    printf("\n");
    return 0;
}