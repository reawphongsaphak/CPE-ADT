#include <stdio.h>

int isPerfect(int n);

int main() {
    int n = 0, max = 0;
    scanf("%d", &n);
    
    if (n == 2){
        printf("1");
        return 0;
    }
    for (int i = 0;i < n; i++){
        if (isPerfect(i)){
            max = i;
        }
    }

    printf("%d", max);
    return 0;
}

int isPerfect(int n) {
    int sum = 0;
    
    for (int i = 1; i <= n/2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }
    
    if (sum == n) {
        return 1;
    } else {
        return 0;
    }
}