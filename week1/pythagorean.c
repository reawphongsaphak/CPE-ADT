#include <stdio.h>

void main(){
                int m, n, s1, s2, hy;
                char space;

                scanf("%d%c%d",&m,&space,&n);
                s1 = (m*m) - (n*n);
                s2 = 2*m*n;
                hy = (m*m) + (n*n);
                printf("%d %d %d",s1,s2,hy);
}