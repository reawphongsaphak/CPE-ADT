#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct sushi{
    int price;
    int weight;
    int number;
    float value;
}sushi_t;

void set_sushi(sushi_t *plate, int price_t, int weight_t, int id){
    plate[id].price = price_t;
    plate[id].weight = weight_t;
    plate[id].value = (float)weight_t/price_t;
    plate[id].number = id;
}

void binary_search(sushi_t *plate, int n, int *p, int *m, int *l) {
    for (int i = 0; i < n; i++) {
        int lo = 1;
        int hi = *l + 1;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (plate[m[mid]].value > plate[i].value)
                hi = mid;
            else
                lo = mid + 1;
        }
        int l_ = lo;

        p[i] = m[l_ - 1];
        m[l_] = i;

        if (l_ > *l) {
            *l = l_;
        }
    }
}

void find_sushi(sushi_t *plate, int n) {
    int *p = (int *)malloc(n * sizeof(int));
    int *m = (int *)malloc((n + 1) * sizeof(int));
    m[0] = -1;
    int l = 0; 
    binary_search(plate, n, p, m, &l);

    sushi_t *s = (sushi_t *)malloc(l * sizeof(sushi_t));
    int k = m[l];
    for (int j = l - 1; j >= 0; j--) {
        s[j] = plate[k];
        k = p[k];
    }
    
    char *sel = (char *)malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n + 1; i++)
        sel[i] = '0';

    for (int i = 0; i < l; i++)
        sel[s[i].number] = '1';

    for (int i = 0; i < n; i++) {
        printf("%c ", sel[i]);
    }
    printf("\n");

    int total_price = 0;
    for (int i = 0; i < l; i++)
        total_price += s[i].price;
    printf("%d\n", total_price);

    free(p);
    free(m);
    free(s);
    free(sel);
}

int main(void){
    int n, price, weight;
    scanf("%d", &n);
    sushi_t *plate = (sushi_t *)malloc(n * sizeof(sushi_t));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &price, &weight);
        set_sushi(plate, price, weight, i);
    }
    find_sushi(plate, n);
    
    free(plate);
}
