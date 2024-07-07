#include <stdio.h>
#include <stdlib.h>

void main(){
                char c1,c2;
                char space;

                scanf("%c%c%c",&c1,&space,&c2);
                int var = (int)c2 - (int)c1;
                int ans = abs(var);
                printf("%d",ans);
}