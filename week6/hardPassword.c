#include <stdio.h>
#include <stdlib.h>
#define MAX 100000

typedef struct node{
    char data;
    struct node* next;
} stack;

int solve(char text[]);
int is_empty(stack* s);
stack* push(stack* s, char ch);
stack* pop(stack* s);

int main(){
    char text[MAX];
    fgets(text, MAX, stdin);
    printf("%d\n",solve(text));
    return 0;
}

int solve(char text[]){
    stack* s = NULL;
    int i = 0;
    while (text[i] != 'x'){
        s = push(s, text[i]);
        i++;
    }
    i+=1;
    while (text[i] != 'y'){
        if (text[i] == s->data){
            s = pop(s);
        }
        i++;
    }
    return is_empty(s);
}

stack* push(stack* s, char ch){
    stack* newNode = (stack*)malloc(sizeof(stack));
    newNode->data = ch;
    newNode->next = NULL;
    if ( s == NULL){
        s = newNode;
        return s;
    }
    
    newNode->next = s;
    s = newNode;
    return s;
}

stack* pop(stack* s){
    stack* temp = s;
    s = s->next;
    free(temp);
    return s;
}

int is_empty(stack* s){
    if (s == NULL){
        return 1;
    }
    return 0;
}