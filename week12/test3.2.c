#include <stdio.h>
#include <stdlib.h>

typedef struct sushi_t {
    int price;
    int weight;
    float value;
    int idx;
} sushi_t;

//* ================  sort function =================
void merge(int *arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    char L[n1], R[n2];  // Use char instead of int

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
// l is for left index and r is right index of the
void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
    return;
}

//* ================  solve function =================

void add()

int main() {
    int n, price, weight;
    scanf("%d", &n);
    sushi_t *sushi = (sushi_t*)malloc(sizeof(sushi_t) * n);
    for (int i = 0; i < n; i++){
        scanf("%d %d", &price, &weight);
        
    }
    
    return 0;
}