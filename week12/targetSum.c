#include <stdio.h>
#include <stdlib.h>

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

//* ====================== solve function ====================
void targetSum(int *arr, int n, int p) {
    for (int i = 0; i < n-2; i++) {
        if (i > 0 && arr[i] == arr[i-1]) {
            continue;
        }
        int l = i + 1;
        int r = n - 1;
        while (l < r) {
            int sum = arr[i] + arr[l] + arr[r];

            if (sum == p) {
                printf("%d %d %d\n", arr[i], arr[l], arr[r]);
                while (l < r && arr[l] == arr[l + 1]) {
                    l++;
                }
                while (l < r && arr[r] == arr[r - 1]){
                    r--;
                }
                l++;
                r--;
            } else if (sum > p) {
                r--;
            } else {
                l++;
            }
        }
    }
}


//* ====================== main function =====================
int main(){
    int n, p, m;
    int *arr;
    scanf("%d %d", &n, &p);
    arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++){
        scanf("%d", &m);
        arr[i] = m;
    }
    mergeSort(arr, 0, n - 1);
    targetSum(arr, n, p);
    return 0;
}