#include <stdio.h>
#include <stdlib.h>
typedef struct heap {
    int *data;
    int last_index;
} heap_t;

void bfs(heap_t* h){
    int max_size = h->last_index;
    for (int i = 1; i < max_size + 1; i++){
        printf("%d ", h->data[i]);
    }
    printf("\n");
}

heap_t* init_heap(int m){
    heap_t* heap = (heap_t*)malloc(sizeof(heap_t));
    if (heap == NULL) {
        printf("Memory allocate failed for heap structure\n");
        return NULL;
    }
    
    heap->data = (int*)malloc(sizeof(int) * m);
    if (heap->data == NULL) {
        printf("Memory allocate failed for heap data\n");
        free(heap);
        return NULL;
    }
    heap->last_index = 0;
    return heap;
}

void insert(heap_t* heap, int data){
    heap->last_index ++;
    heap->data[heap->last_index] = data;    //* add new data at last_index    
    int curr = heap->last_index;
    while (curr > 1) {
        int parent = curr / 2;
        if (heap->data[curr] > heap->data[parent]) {    //* swap with its parent if its greater
            int temp = heap->data[parent];
            heap->data[parent] = heap->data[curr];
            heap->data[curr] = temp;
            curr = parent;
        } else {
            break;
        }
    }
    return;
}

void delete_max(heap_t* heap){
    heap->data[1] = heap->data[heap->last_index];
    heap->last_index --;
    int curr = 1;

    while (curr < heap->last_index) {
        int child1 = (2 * curr);
        int child2 = (2 * curr) + 1;
        if (heap->data[curr] < heap->data[child1]){
            int temp = heap->data[child1];
            heap->data[child1] = heap->data[curr];
            heap->data[curr] = temp;
            curr = child1;
        } else if (heap->data[curr] < heap->data[child2]) {
            int temp = heap->data[child2];
            heap->data[child2] = heap->data[curr];
            heap->data[curr] = temp;
            curr = child2;
        } else {
            break;
        }
    }
    return;
}

int find_max(heap_t* heap){
    return (heap->data[1] == 0) ? -1: heap->data[1];
}

void update_key(heap_t* heap, int old, int new){
    int i = 1;
    while (heap->data[i] != old) {
        i++;
    }
    heap->data[i] = new;
    int curr = i;
    if (new > old) {
        while (curr > 1) {
            int parent = curr / 2;
            if (heap->data[curr] > heap->data[parent]) {    //* swap with its parent if its greater
                int temp = heap->data[parent];
                heap->data[parent] = heap->data[curr];
                heap->data[curr] = temp;
                curr = parent;
            } else {
                break;
            }
        }
    } else if (new < old) {
        while (curr < heap->last_index) {
        int child1 = (2 * curr);
        int child2 = (2 * curr) + 1;
            if (heap->data[curr] < heap->data[child1]){
                int temp = heap->data[child1];
                heap->data[child1] = heap->data[curr];
                heap->data[curr] = temp;
                curr = child1;
            } else if (heap->data[curr] < heap->data[child2]) {
                int temp = heap->data[child2];
                heap->data[child2] = heap->data[curr];
                heap->data[curr] = temp;
                curr = child2;
            } else {
                break;
            }
        }
    } else {
        return;
    }
}

int main(void) {
    heap_t *max_heap = NULL;
    int m, n, i;
    int command, data;
    int old_key, new_key;
    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);

    for (i = 0; i < n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                insert(max_heap, data);
                break;
            case 2:
                delete_max(max_heap);
                break;
            case 3:
                printf("%d\n", find_max(max_heap));
                break;
            case 4:
                scanf("%d %d", &old_key, &new_key);
                update_key(max_heap, old_key, new_key);
                break;
            case 5:
                bfs(max_heap);
                break;
        }
    }
    return 0;
}