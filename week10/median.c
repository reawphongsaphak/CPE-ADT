#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int* data;
    int last_index;
} heap_t;

heap_t* initHeap(int n){
    heap_t *newHeap = (heap_t*)malloc(sizeof(heap_t));
    newHeap->data = (int*)malloc(sizeof(int) * n);
    newHeap->last_index = -1;
    return newHeap;
}

//* ===================================================
//*               function for min heap
//* ===================================================
void insert_min(heap_t *heap, int num) {
    heap->last_index++;
    heap->data[heap->last_index] = num;  //* add new data at last_index
    int curr = heap->last_index;
    while (curr > 0) {
        int parent = curr / 2;
        if (heap->data[curr] < heap->data[parent]) {  //* swap with its parent if it's smaller
            int temp = heap->data[parent];
            heap->data[parent] = heap->data[curr];
            heap->data[curr] = temp;
            curr = parent;
        } else {
            break;
        }
    }
}

int delete_min(heap_t *heap) {    
    int tmp = heap->data[0];
    heap->data[0] = heap->data[heap->last_index];
    heap->last_index--;
    int curr = 0;

    while (curr <= heap->last_index) {
        int left = 2 * curr;
        int right = 2 * curr + 1;
        int smallest = curr;

        if (left <= heap->last_index && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right <= heap->last_index && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }

        if (smallest != curr) {
            int temp = heap->data[smallest];
            heap->data[smallest] = heap->data[curr];
            heap->data[curr] = temp;
            curr = smallest;
        } else {
            break;
        }
    }
    return tmp;
}

//* ===================================================
//*               function for max heap
//* ===================================================
void insert_max(heap_t *heap, int num) {
    heap->last_index++;
    heap->data[heap->last_index] = num;  //* add new data at last_index
    int curr = heap->last_index;
    while (curr > 0) {
        int parent = curr / 2;
        if (heap->data[curr] > heap->data[parent]) {  //* swap with its parent if it's greater
            int temp = heap->data[parent];
            heap->data[parent] = heap->data[curr];
            heap->data[curr] = temp;
            curr = parent;
        } else {
            break;
        }
    }
}

int delete_max(heap_t *heap) {
    int tmp = heap->data[0];
    heap->data[0] = heap->data[heap->last_index];
    heap->last_index--;
    int curr = 0;

    while (curr <= heap->last_index) {
        int left = 2 * curr;
        int right = 2 * curr + 1;
        int largest = curr;

        if (left <= heap->last_index && heap->data[left] > heap->data[largest]) {
            largest = left;
        }
        if (right <= heap->last_index && heap->data[right] > heap->data[largest]) {
            largest = right;
        }

        if (largest != curr) {
            int temp = heap->data[largest];
            heap->data[largest] = heap->data[curr];
            heap->data[curr] = temp;
            curr = largest;
        } else {
            break;
        }
    }
    return tmp;
}

//* ===================================================
//*           function for solve proplem
//* ===================================================
void add_num(heap_t *min_h, heap_t *max_h, int num) {
    insert_max(max_h, num);

    int tmp = delete_max(max_h);
    insert_min(min_h, tmp);

    //* balancing two heaps
    if (min_h->last_index > max_h->last_index) {
        tmp = delete_min(min_h);
        insert_max(max_h, tmp);
    }
}

double find_median(heap_t *min_h, heap_t *max_h) {
    if (max_h->last_index > min_h->last_index) {
        return max_h->data[0];
    } else {
        return ((double)max_h->data[0] + (double)min_h->data[0]) / 2;
    }
}

int main() {
    int n, num;
    scanf("%d", &n);

    heap_t *min_h = initHeap(n);
    heap_t *max_h = initHeap(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num);
        add_num(min_h, max_h, num);
        printf("%.1lf\n", find_median(min_h, max_h));
    }

    //* Free allocated memory
    free(min_h->data);
    free(max_h->data);
    free(min_h);
    free(max_h);

    return 0;
}
