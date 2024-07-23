#include <stdio.h> 

void Pascal(int n);

int main() 
{ 
    int n = 0;
    scanf("%d",&n);
    Pascal(n); 
    return 0; 
}

 void Pascal(int n){
     for (int line = 1; line <= n; line++) {
         for (int space = 1; space <= n - line; space++) {
             printf("   ");
         }

         int num = 1;
         for (int i = 1; i <= line; i++) {
             printf("%6d", num);
             num = num * (line - i) / i;
         }
         printf("\n");
     }
 }