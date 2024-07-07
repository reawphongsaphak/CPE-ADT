#include <stdio.h>
#define feet 3.28084

void main() {
        int l;
        int w;
        double area;
        double time;
        printf("length(m.):");
        scanf("%d",&l);
        printf("width(m.):");
        scanf("%d",&w);
        area = l*w*feet*feet;
        time = area/2;
        printf("Use %0.5f seconds.",time);
}