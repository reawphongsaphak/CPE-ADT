#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

int min_coin(int n, int* p, int size);

int main() {
    int n_snack = 0, money = 0;
    int* p_snack;
    scanf("%d", &n_snack);

    p_snack = (int*)malloc(sizeof(int) * (n_snack + 1));

    for (int i = 0; i < n_snack; i++) {
        int temp = 0;
        scanf("%d", &temp);
        p_snack[i] = temp; 
    }
    scanf("%d", &money);

    int result = min_coin(money, p_snack, n_snack);
    printf("%d\n", result);
    
    free(p_snack);
    return 0;
}

int min_coin(int m, int* p, int size) {
    if (m == 0) {
        return 0;
    }
    int answer = INT_MAX;
    for (int i = 0; i < size; i++) {
        if (p[i] <= m) {
            int sub_result = min_coin(m - p[i], p, size);
            if (sub_result != INT_MAX) {
                answer = MIN(answer, sub_result + 1);
            }
        }
    }
    return answer;
}


