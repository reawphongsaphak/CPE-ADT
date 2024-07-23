//. O(n^2)
#include <stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))

int estatePlanner(int w, int l, int shift);

int main() {
    int w = 0, l = 0, shift = 0;
    scanf("%d %d", &w, &l);
    int min = MIN(w,l);
    for (int i = 0; 1<<i <= min; i++){
        shift = i;
    }
    // printf("shift : %d\n", shift);
    printf("%d\n", estatePlanner(w, l, shift));
    return 0;
}

int estatePlanner(int w, int l, int shift){
    int n_w = w - (1 << shift), n_l = l - (1 << shift);
    if (shift < 0) {return 0;}
    if (w == 1) {return l;}
    if (l == 1) {return w;}
    if (n_w < 0 || n_l < 0){return estatePlanner(w, l, shift - 1);}
    else {
        return 1 + estatePlanner(n_w, l, shift) 
        + estatePlanner(w-n_w , n_l, shift);}
}