#include <stdio.h> 

void Pascal(int n);
unsigned long long fac(int n);

int main() 
{ 
    int n = 0; 
    scanf("%d", &n);
    Pascal(n); 
    return 0; 
}

void Pascal(int n) {
    for (int i = 0; i < n; i++) {
        // Adjust the number of spaces for better formatting
        for (int k = 0; k < n - i - 1; k++) {
            printf("   ");
        }

        for (int j = 0; j <= i; j++) {
            printf("%6llu", fac(i) / (fac(j) * fac(i - j)));
        }
        printf("\n");
    }
}

unsigned long long fac(int n) {
    unsigned long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}