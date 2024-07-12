#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check(char* text, char* sub, int len_text, int len_sub, int err);

int main (){
    int text_l = 0, sub_l = 0, err = 0;
    char* text;
    char* sub;

    scanf("%d %d %d", &text_l, &sub_l, &err);
    text = (char *)malloc(sizeof(char) * (text_l + 1));
    sub = (char *)malloc(sizeof(char) * (sub_l + 1));
    scanf("%s", text);
    scanf("%s", sub);
    check(text, sub, text_l, sub_l, err);

    return 0;
}

void check(char* text, char* sub, int len_text, int len_sub, int err){
    char* check = (char *)malloc(sizeof(char) * (len_sub + 1));
    
    if (err == 0){
        for (int i = 0; i <= len_text; i++){

            for (int j = 0; j < len_sub; j++){
                check[j] = text[i+j];
                if (check[j] != sub[j] || i+j >= len_text) {
                    printf("%c", text[i]);
                    break;
                }

                if (j == len_sub -1 ){
                    printf("[");

                    for (int k = 0; k < len_sub; k++){
                        printf("%c", text[i+k]);
                    }
                    printf("]");
                    i += len_sub-1;
                }
            }
        }
    }

    else{
        for (int i = 0; i <= len_text; i++){
            int count_err = 0;
            char* clone_text = strdup(text);

            for (int j = 0; j < len_sub; j++){
                check[j] = text[i+j];
                if (check[j] != sub[j]) {
                    clone_text[i+j] = '?';
                    count_err++;
                }
                
                if (count_err > err || i+j >= len_text){
                    printf("%c", text[i]);
                    break;
                }

                if (j == len_sub -1 && count_err <= err && i+j < len_text){
                    printf("[");

                    for (int k = 0; k < len_sub; k++){
                        printf("%c", clone_text[i+k]);
                    }
                    printf("]");
                    i += len_sub - 1;
                }

            }
        }        
    }
}