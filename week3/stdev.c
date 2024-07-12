#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double findSD(int* ls, int n){
    double sum = 0;
    double avg = 0;
    double sigma = 0;
    double temp = 1/(double)n;
    double ans = 0;

    for (int i = 0; i < n; i++){
        sum += ls[i];
    }
    avg = sum/n;
    sum = 0;

    for (int i = 0; i < n; i++){
        sum += pow((ls[i]-avg),2);
        // printf("%lf\n", sum);
    }
    ans = sqrt(temp*sum);
    // printf("%lf\n",temp);
    return ans;
}

int main(){
    int n, i;
    double sigma;
    int* nums;
    
    scanf("%d", &n);
    nums = (int* )malloc(sizeof(int) * n);
    for (i = 0; i < n; i++){
        scanf("%d", nums+i);
    }
    sigma = findSD(nums, n);
    printf("%.2f", sigma);
    return 0;
}