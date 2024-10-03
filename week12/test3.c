#include <stdio.h>
#include <stdlib.h>

int lower_bound(float *tail, int length, float key) {
    int left = 0, right = length;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (tail[mid] >= key)
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}

void solve (float *arr, int *price, int n) {
    int i, sum = 0, maxLength = 0;

    // tail array stores the end elements of each length of increasing subsequences
    float *tail = (float *)malloc(sizeof(float) * n);
    int *indexes = (int *)malloc(sizeof(int) * n);
    
    for (i = 0; i < n; i++) {
        // Get the position in tail for arr[i] using binary search
        int pos = lower_bound(tail, maxLength, arr[i]);
        
        // If the position is at the end, we have found a new longer subsequence
        if (pos == maxLength)
            maxLength++;
        
        // Update tail and index arrays
        tail[pos] = arr[i];
        indexes[i] = pos + 1;  // Store the length of the subsequence ending at arr[i]
    }

    // Now we calculate the sum of prices based on the longest increasing subsequence
    int max = 0;
    for (i = 0; i < n; i++) {
        if (i < n - 1 && indexes[i] == indexes[i + 1]) {
            printf("0 ");
            continue;
        }
        if (max < indexes[i]) {
            printf("1 ");
            max = indexes[i];
            sum += price[i];
        } else {
            printf("0 ");
        }
    }

    printf("\n%d\n", sum);

    free(tail);
    free(indexes);
}

int main(){
    int n, p, w;
    scanf("%d", &n);
    float *arr = (float *)malloc(sizeof(float) * n);
    int *price = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &p, &w);
        arr[i] = (float)w / (float)p;
        price[i] = p;
    }

    solve(arr, price, n);

    free(arr);
    free(price);

    return 0;
}
