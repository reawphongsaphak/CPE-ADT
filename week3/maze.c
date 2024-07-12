#include <stdio.h>
#include <stdlib.h>

void show(char** map, int row);
int traverseMaze(char** map,int x, int y, int row);

int main(){
    int row = 0;
    int st_x = 0;
    int st_y = 0;

    scanf("%d", &row);
    getchar();
    
    char** map = (char**)malloc(sizeof(char*) * row);
    for (int i = 0; i < row; i++){
        map[i] = (char*)malloc(sizeof(char) * (row + 1));
    }
    for (int i = 0; i < row; i++){
        fgets(map[i], row + 1, stdin);
        map[i][row] = '\0'; 
        getchar();
    }
    for (int i = 0; i < row; i++){
        for (int j = 0; j < row; j++){
            if (map[i][j] == 'S'){
                st_x = i;
                st_y = j;
            }
        }
    }
    if (traverseMaze(map, st_x, st_y, row)){
        map[st_x][st_y] = 'S';
    }

    show(map, row);

    for (int i = 0; i < row; i++){
        free(map[i]);
    }
    free(map);
    return 0;
}

int traverseMaze(char** map,int x, int y, int row){
    if (x < 0 || y < 0 || x >= row || y >= row || map[x][y] == '#' || map[x][y] == '.') {
        return 0;
    }

    if (map[x][y] == 'G') { return 1; }

    char temp = map[x][y];
    map[x][y] = '.';

    if (traverseMaze(map, x + 1, y, row) || traverseMaze(map, x - 1, y, row) ||
        traverseMaze(map, x, y + 1, row) || traverseMaze(map, x, y - 1, row)) {
        return 1;
    }
    map[x][y] = temp;
    return 0;
}

void show(char** map, int row){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < row; j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}