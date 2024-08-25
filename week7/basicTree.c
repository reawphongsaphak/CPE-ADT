#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

typedef struct node{
    int val;
    struct node* parent;
    struct node* next_sibling;
    struct node* first_child;
}tree_t;

typedef struct stack{
    int data;
    struct stack* next;
}stack;

typedef struct queue_node {
    tree_t* tree_node;
    struct queue_node* next;
} queue_node;

typedef struct queue_t {
    queue_node* front;
    queue_node* rear;
} queue_t;

void bfs(tree_t* t);
void dfs(tree_t* t);

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

stack* push(stack *s, int value){
    stack* newNode = (stack*)malloc(sizeof(stack));
    newNode->data = value;
    newNode->next = NULL;
    if (s == NULL){
        s = newNode;
        return s;
    }
    newNode->next = s;
    return newNode;
}

int pop(stack** s){
    if (*s == NULL){
        return -1;
    }
    stack* temp = *s;
    int data = (*s)->data;
    *s = (*s)->next;
    free(temp);
    return data;
}

tree_t* find(tree_t* t, int val){
    if (t == NULL || t->val == val){
        return t;
    }
    tree_t*pos = find(t->first_child, val);
    if (pos != NULL){
        return pos;
    }
    else{return find(t->next_sibling, val);}
}

tree_t* attach(tree_t* t, int parent, int val){
    tree_t* newNode = (tree_t*)malloc(sizeof(tree_t));
    newNode->val = val;
    newNode->parent = NULL;
    newNode->next_sibling = NULL;
    newNode->first_child = NULL;
    if (t == NULL){
        return newNode;
    }

    tree_t* pos = find(t, parent);
    if (pos->first_child == NULL){
        newNode->parent = pos;
        pos->first_child = newNode;
        return t;
    } else{ 
        tree_t* temp = pos->first_child;
        while (temp->next_sibling != NULL){
            temp = temp->next_sibling;
        }
        newNode->parent = pos;
        temp->next_sibling = newNode;
    } return t;
}

void free_sub_tree(tree_t* t){
    if (t == NULL) {
        return;
    }

    tree_t* child = t->first_child;
    while (child != NULL) {
        tree_t* next = child->next_sibling;
        free_sub_tree(child);                   
        child = next;
    }

    free(t);
}

tree_t* detach(tree_t* t, int val){
    tree_t* pos = find(t,val);
    if (pos->parent->first_child == pos){
        pos->parent->first_child = pos->parent->first_child->next_sibling;
    }
    else if (pos->parent->first_child != pos){
        tree_t* temp = pos->parent->first_child;
        while (temp->next_sibling != pos){
            temp = temp->next_sibling;
        }
        temp->next_sibling = pos->next_sibling;
    }
    free_sub_tree(pos);
    return t;
}

int search(tree_t* t, int val){
    if (t == NULL){
        return 0;
    }
    else if (t->val == val){
        return 1;
    }
    else{return MAX(search(t->first_child, val),search(t->next_sibling, val));}
}

int degree(tree_t* t, int val){
    tree_t* pos = find(t, val);
    int count = 0;
    if (pos->first_child == NULL){
        return 0;
    }
    tree_t* temp = pos->first_child;
    while (temp != NULL){
        count++;
        temp = temp->next_sibling;
    }
    return count;
}

int is_root(tree_t* t, int val){
    if (t-> val == val){
        return 1;
    }
    return 0;
}

int is_leaf(tree_t* t, int val){
    tree_t* pos = find(t, val);
    if (pos->first_child == NULL){
        return 1;
    }
    return 0;
}

void siblings(tree_t* t, int val){
    tree_t* pos = find(t, val);
    if (pos->parent == NULL){
        printf("\n");
        return;
    }
    tree_t* temp = pos->parent->first_child;
    while(temp!= NULL){
        if (temp->val != val){
            printf("%d ", temp->val);
        }
        temp = temp->next_sibling;
    }
    printf("\n");
    return;
}

int depth(tree_t* t, int val){
    int depth = 0;
    tree_t* pos = find(t, val);
    tree_t* temp = pos;
    while (temp != t){
        depth++;
        temp = temp->parent;
    }
    return depth;
}

void print_path(tree_t* t, int start, int end){
    stack* s = NULL;
    tree_t* pos_start = find(t, start);
    tree_t* pos_end = find(t, end);
    tree_t* temp = pos_end;
    while (temp != pos_start->parent){
        s = push(s, temp->val);
        temp = temp->parent;
    }
    while (s != NULL){
        printf("%d ", pop(&s));
    }
    printf("\n");
    return;
}

int path_length(tree_t* t, int start, int end){
    tree_t* pos_start = find(t, start);
    tree_t* pos_end = find(t, end);
    tree_t* temp = pos_end;
    int count = 0;
    while (temp != pos_start->parent){
        count++;
        temp = temp->parent;
    }
    return count;
}

void ancestor(tree_t* t, int end){
    stack* s = NULL;
    tree_t* pos_end = find(t, end);
    tree_t* temp = pos_end;
    while (temp != t->parent){
        s = push(s, temp->val);
        temp = temp->parent;
    }
    while (s != NULL){
        printf("%d ", pop(&s));
    }
    printf("\n");
    return;
}

void descendant(tree_t* t, int val){
    tree_t* pos = find(t, val);
    bfs(pos);
    printf("\n");
    return;
}

void bfs(tree_t* t) {
    if (t == NULL) {
        return;
    }
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    enqueue(q, t);
    while (q->front != NULL) {
        tree_t* current = dequeue(q);
        printf("%d ", current->val);

        tree_t* child = current->first_child;
        while (child != NULL) {
            enqueue(q, child);
            child = child->next_sibling;
        }
    }
    free(q);
    return;
}

void dfs(tree_t* t){
    if (t == NULL){
        return;
    }
    int node = t->val;
    printf("%d ",node);
    dfs(t->first_child);
    dfs(t->next_sibling);
    return;
}

void print_tree(tree_t* t){
    if (t == NULL){
        return;
    }
    int node = t->val;
    int space = 0;
    tree_t* temp = t;
    while (temp->parent != NULL){
        space++;
        temp = temp->parent;
    }

    for (int i = 0; i < space; i++){
        printf("    ");
    }

    printf("%d\n",node);
    print_tree(t->first_child);
    print_tree(t->next_sibling);
}

int main(void) {
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d %d", &parent, &child);
                t = attach(t, parent, child);
                break;
            case 2:
                scanf("%d", &node);
                t = detach(t, node);
                break;
            case 3:
                scanf("%d", &node);
                printf("%d\n", search(t, node));
                break;
            case 4:
                scanf("%d", &node);
                printf("%d\n", degree(t, node));
                break;
            case 5:
                scanf("%d", &node);
                printf("%d\n", is_root(t, node));
                break;
            case 6:
                scanf("%d", &node);
                printf("%d\n", is_leaf(t, node));
                break;
            case 7:
                scanf("%d", &node);
                siblings(t, node);
                break;
            case 8:
                scanf("%d", &node);
                printf("%d\n", depth(t, node));
                break;
            case 9:
                scanf("%d %d", &start, &end);
                print_path(t, start, end);
                break;
            case 10:
                scanf("%d %d", &start, &end);
                printf("%d\n",path_length(t, start, end));
                break;
            case 11:
                scanf("%d", &node);
                ancestor(t, node);
                break;
            case 12:
                scanf("%d", &node);
                descendant(t, node);
                break;
            case 13:
                bfs(t);
                break;
            case 14:
                dfs(t);
                break;
            case 15:
                print_tree(t);
            break;
        }
    }
    return 0;
}