#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define __avl_tree__
#include "week9.h"
#define max(a,b) (((a)>(b)) ? (a) : (b))
#ifndef __avl_tree__
typedef struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t avl_t;
#endif

// Create a node
avl_t *newNode(int data) {
    avl_t *newNode = (avl_t*)malloc(sizeof(avl_t));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return (newNode);
}

// return height of that node
int height(avl_t *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

// Right rotate
avl_t *rightRotate(avl_t *y) {
    avl_t *x = y->left;
    avl_t *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
avl_t *leftRotate(avl_t *x) {
    avl_t *y = x->right;
    avl_t *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get the balance factor
int getBalance(avl_t *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insert node
avl_t *insert(avl_t *node, int data) {
    // Find the correct position to insertNode the node and insertNode it
    if (node == NULL){
        return (newNode(data));
    }
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
    node->right = insert(node->right, data);
    } else {
    return node;
    }

    // Update the balance factor of each node and
    // Balance the tree
    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && data < node->left->data) {
        return rightRotate(node);
    }
    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

avl_t *minValueNode(avl_t *node) {
    avl_t *current = node;

    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Delete a nodes
avl_t *delete(avl_t *root, int data) {
  // Find the node and delete it
    if (root == NULL)
        return root;

    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            avl_t *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            avl_t *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main(void) {
    avl_t *t = NULL;
    int n, i;
    int command, data;
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
                print_tree(t);
                break;
        }
    }
    return 0;
}