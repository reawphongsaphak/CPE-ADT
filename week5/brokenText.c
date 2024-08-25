#include <stdio.h>
#include <string.h>

void solve(char text[], char ans[]);

int main(){
    char text[100000 + 1];
    char ans[100000 + 1];
    scanf("%[^\n]%*c", text);
    solve(text, ans);
    return 0;
}

void solve(char text[], char ans[]){
    int i = 0, len = 0;
    int cursor = 0;
    while (text[i] != '\0'){
        if (text[i] == '<'){
            cursor = 0;
        }
        else if (text[i] == '>'){
            cursor = len;
        }
        else{
            for (int j = len; j > cursor; j--) {
                ans[j] = ans[j-1];
            }
            // Insert the new character at the current cursor position
            ans[cursor] = text[i];
            cursor++;
            len++;
        }
        i++;
    }
    printf("%s\n",ans);
    return;
}