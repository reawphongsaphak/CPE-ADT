#include <stdio.h>

void rebound(int n, int m, int x, int y, int d);
int dir(int n, int m, int x, int y, int d);
void show(int n, int m);


int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
int map[100][100] = {0}; // Assuming maximum size for the map

int main() {
    int n, m, x, y, d;
    scanf("%d %d %d %d %d", &n, &m, &x, &y, &d);
    if(n == 1 && m == 1){
        printf("1");
        return 0;
    }
    rebound(n, m, x, y, d);
    return 0;
}

void rebound(int n, int m, int x, int y, int d){
    int count = 0;
    int o_count = 0;
    int count_ = 0;
    int st_d = d;
    int st_x = x;
    int st_y = y;

    for (int i = 0; i < 1000; i++){
        // show(n, m);
        // printf("d before : %d\n", d);
        d = dir(n, m, x, y, d);

        // printf("x : %d , y : %d\n", x, y);
        // printf("d : %d\n", d);
        // printf("count : %d\n", count);
        // printf("\n");
        if (x == st_x && y == st_y && d == st_d && count > 0){
            break;
        }

        x += dx[d];
        y += dy[d];

        if (map[x][y] != 1){
            map[x][y] = 1;
            count ++;
        }
    }
    printf("%d", count);

}


int dir(int n, int m, int x, int y, int d){
    int nx = x + dx[d];
    int ny = y + dy[d];
    //* check if ball out if grid
    if ((nx < 0) || (nx >= n) || (ny < 0) || (ny >= m)){
        //* hit cornor
        if ((x == 0 && y == 0) || (x == 0 && y == m-1) || (x == n-1 && y == 0) || (x == n-1 && y == m-1)){
            return (d + 4) % 8;
        }
        else{
            //* hit top side
            if (nx < 0){
                if (d == 0) { return 4;}
                else if (d == 1) { return 3;}
                else if (d == 7) { return 5;}
            }
            //* hit bottom side
            else if (nx >= n){
                if (d == 3) { return 1;}
                else if (d == 4) { return 0;}
                else if (d == 5) { return 7;}
            }
            //* hit left side
            else if (ny < 0){
                if (d == 5) { return 3;}
                else if (d == 6) { return 2;}
                else if (d == 7) { return 1;}
            }
            //* hit right side
            else if (ny >= m){
                if (d == 1) { return 7;}
                else if (d == 2) { return 6;}
                else if (d == 3) { return 5;}
            }
        }
    }
    return d;
}


void show(int n, int m){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
}
