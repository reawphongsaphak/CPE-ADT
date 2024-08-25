#include <stdio.h>
#include <stdlib.h>

int main(){
    char c1,c2
    scanf("%c %c",&c1,&c2);
    int var = (int)c2 - (int)c1;
    int ans = abs(var);
    printf("%d\n",ans);
    return 0;
}