#include <stdio.h> 
#include <stdlib.h>

void swap(int *xp, int *yp);
int* sort(int* ls, int size);
void cntDup(int* ls, int n);

int main(){
    int* ptr;
    int n = 0, temp = 0;
    scanf("%d", &n);
    ptr = (int*)malloc(sizeof(int)*n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &temp);
        ptr[i] = temp;
    }
    ptr = sort(ptr, n);
    cntDup(ptr, n);
    return 0;
} 

void cntDup(int* ls, int n){
    int max_count = 0;
    int most_freq = ls[0];
    int count = 1;
    for (int i = 1; i < n; i++){
        if (ls[i] == ls[i-1]){
            count++;
        }
        else{
            if (count > max_count){
            max_count = count;
            most_freq = ls[i-1];
            }
            count = 1;
        }

    }
    if (count > max_count) {
        max_count = count;
        most_freq = ls[n - 1];
    }

    int curr_count = 1;
    for (int i = 1; i < n; i++){
        if (ls[i] == ls[i - 1]) {
            curr_count++;
        } 
        else {
            if (curr_count == max_count) {
                printf("%d ", ls[i - 1]);
            }
            curr_count = 1;
        }
    }
    if (curr_count == max_count) {
        printf("%d", ls[n - 1]);
    }
} 


void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int* sort(int* ls, int size) {
    int i, j;
    for (i = 0; i < size-1; i++) {
        for (j = 0; j < size-i-1; j++) {
            if (ls[j] > ls[j+1]) {
                swap(&ls[j], &ls[j+1]);
            }
        }
    }
    return ls;
}