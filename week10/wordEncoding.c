#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 15
#define MAX 100000

typedef struct node_t {
    char word[MAX_LENGTH + 1];
    int amount;
    struct node_t *left;
    struct node_t *right;
} word_t;

typedef struct huff_code {
    word_t* data[MAX + 1];
    int last_index;
} heap_t;

heap_t* init_heap(int m) {
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
    if (heap == NULL) {
        printf("Memory allocation failed for heap structure\n");
        return NULL;
    }
    heap->last_index = 0;
    return heap;
}

word_t* get_word(char word[], int amount) {
    word_t* newWord = (word_t*)malloc(sizeof(word_t));
    strcpy(newWord->word, word);
    newWord->amount = amount;
    newWord->left = newWord->right = NULL;  // Set left and right to NULL
    return newWord;
}

word_t* get_node(word_t *left, word_t *right) {
    word_t* newNode = (word_t*)malloc(sizeof(word_t));
    newNode->amount = left->amount + right->amount;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

void insert(heap_t* heap, char word[], int amount) {
    heap->last_index++;
    word_t* newWord = get_word(word, amount);
    heap->data[heap->last_index] = newWord;

    int curr = heap->last_index;
    while (curr > 1) {
        int parent = curr / 2;
        int parent_amount = heap->data[parent]->amount;
        int curr_amount = heap->data[curr]->amount;

        if (parent_amount > curr_amount) {
            word_t* tmp = heap->data[parent];
            heap->data[parent] = heap->data[curr];
            heap->data[curr] = tmp;
            curr = parent;
        } else {
            break;
        }
    }
    return;
}

word_t* delete_min(heap_t* heap) {
    word_t* min_node = heap->data[1];
    heap->data[1] = heap->data[heap->last_index];
    heap->last_index--;

    int curr = 1;
    while (curr * 2 <= heap->last_index) {
        int left = curr * 2;
        int right = curr * 2 + 1;
        int smaller = left;

        if (right <= heap->last_index && heap->data[right]->amount < heap->data[left]->amount) {
            smaller = right;
        }

        if (heap->data[curr]->amount > heap->data[smaller]->amount) {
            word_t* tmp = heap->data[curr];
            heap->data[curr] = heap->data[smaller];
            heap->data[smaller] = tmp;
            curr = smaller;
        } else {
            break;
        }
    }
    return min_node;
}

void insert_t(heap_t* heap, word_t* left, word_t* right) {
    heap->last_index++;
    word_t* newNode = get_node(left, right);  
    heap->data[heap->last_index] = newNode;

    int curr = heap->last_index;
    while (curr > 1) {
        int parent = curr / 2;
        int parent_amount = heap->data[parent]->amount;
        int curr_amount = heap->data[curr]->amount;

        if (parent_amount > curr_amount) {
            word_t* tmp = heap->data[parent];
            heap->data[parent] = heap->data[curr];
            heap->data[curr] = tmp;
            curr = parent;
        } else {
            break;
        }
    }
    return;
}

bool isLeaf(word_t* word) {
    return (word->left == NULL && word->right == NULL);
}

void print_code(word_t* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        print_code(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        print_code(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {
        printf("%s: ", root->word);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

void solve(heap_t* heap) {
    int max_size = heap->last_index;
    for (int i = 1; i < max_size; i++) {
        word_t* left = delete_min(heap);
        word_t* right = delete_min(heap);
        insert_t(heap, left, right);
    }

    int arr[MAX_LENGTH], top = 0;
    word_t* root = heap->data[1];  // The root of the Huffman tree is at heap->data[1]
    print_code(root, arr, top);
}

int main() {
    heap_t* min_heap = NULL;
    int m, n, i;
    char word[MAX_LENGTH + 1];

    scanf("%d", &m);

    min_heap = init_heap(m);
    for (i = 0; i < m; i++) {
        scanf("%s %d", word, &n);
        insert(min_heap, word, n);
    }

    solve(min_heap);
    return 0;
}
