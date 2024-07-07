#include <stdio.h>

int main(){
        float a;
        float b;
        float h;
        printf("a: ");
        scanf("%f",&a);

        printf("b: ");
        scanf("%f",&b);

        printf("h: ");
        scanf("%f",&h);

        float area = 0.5*(a+b)*h;
        printf("Area is %.1f",area);
        return 0;
}