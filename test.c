//. O(n)
#include <stdio.h>
#include <stdlib.h>

int find_max(int size, int money);
int solve(int money, int size);
void show(int* arr, int size);

int* arr;

int main(){
    int n_snack = 0, p_snack = 0, money = 0, ans = 0;
    scanf("%d", &n_snack);
    arr = (int*)malloc(sizeof(int) * (n_snack + 1));
    for (int i = 0; i < n_snack; i++){
        scanf("%d", &p_snack);
        arr[i] = p_snack;
    }
    scanf("%d", &money);
    ans = solve(money, n_snack);
    printf("%d\n", ans);

    free(arr);
    return 0;
}

//* O(size)
int find_max(int size, int money) {
    int res = -1; 
    int var = -1; 
    for (int i = 0; i < size; i++) {
        if (arr[i] <= money && arr[i] > res) {
            res = arr[i];
            var = i;
        }
    }
    if (var != -1) {
        arr[var] = 0;
    }
    return res;
}

//* O(size)
void show(int* arr, int size){
    for (int i = 0; i < size; i++){
        printf("%d", arr[i]);
    }
}

//* O(size)
int solve(int money, int size){
    int max = 0, count = 0;
    max = find_max(size, money);

    while (max <= money){
        if (money / max > 0){
            count += (money / max);
            money = money - max * (money / max);
        }
        max = find_max(size, money);
        if (max == -1 || max == 0){ break;}
    }
    return count;
}

