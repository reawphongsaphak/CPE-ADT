#include <stdio.h>

void rebound(int n, int m, int x, int y, int d);

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
    int direction = d;
    int st_x = x;
    int st_y = y;
    int count = 0;
    int count_ = 0;

    while (1) {
        if (x == st_x && y == st_y && d == direction && count != 0) {
            break;
        }
        // Adjust direction if out of bounds 
        if (x + dx[direction] < 0 || x + dx[direction] >= n || y + dy[direction] < 0 || y + dy[direction] >= m) {
            //* hit the cornor
            if ( (x == 0 && y == 0) || (x == 0 && y == m-1) || (x == n-1 && y == 0) || (x == n-1 && y == m-1)) {
                direction = (direction + 4) % 8;
            }
            else{
                if (direction == 0 || direction == 2 || direction == 4 || direction == 6){
                    direction = (direction + 4) % 8;
                }
                else if (x + dx[direction] < 0){
                    if (direction == 1){ direction = 3;}
                    if (direction == 7) { direction = 5;}
                }
                else if (x + dx[direction] >= n){
                    if (direction == 3){ direction = 1;}
                    if (direction == 5) { direction = 7;}
                }
                else if (y + dy[direction] < 0){
                    if (direction == 7){ direction = 1;}
                    if (direction == 5) { direction = 3;}
                }
                else if (y + dy[direction] >= m){
                    if (direction == 1){ direction = 7;}
                    if (direction == 3) { direction = 5;}
                }
            }
        }
        x += dx[direction];
        y += dy[direction];
        // printf("\n");
        // printf("x : %d, y : %d\n", x, y);
        // printf("count : %d\n", count);
        // printf("direction : %d\n", direction);
        if (x + dx[direction] < 0 || x + dx[direction] >= n || y + dy[direction] < 0 || y + dy[direction] >= m) {
            //* hit the cornor
            if ( (x == 0 && y == 0) || (x == 0 && y == m-1) || (x == n-1 && y == 0) || (x == n-1 && y == m-1)) {
                direction = (direction + 4) % 8;
            }
            else{
                if (direction == 0 || direction == 2 || direction == 4 || direction == 6){
                    direction = (direction + 4) % 8;
                }
                else if (x + dx[direction] < 0){
                    if (direction == 1){ direction = 3;}
                    if (direction == 7) { direction = 5;}
                }
                else if (x + dx[direction] >= n){
                    if (direction == 3){ direction = 1;}
                    if (direction == 5) { direction = 7;}
                }
                else if (y + dy[direction] < 0){
                    if (direction == 7){ direction = 1;}
                    if (direction == 5) { direction = 3;}
                }
                else if (y + dy[direction] >= m){
                    if (direction == 1){ direction = 7;}
                    if (direction == 3) { direction = 5;}
                }
            }
        }

        if (map[x][y] != 1) {
            map[x][y] = 1;
            count++;
        }

        // if (count_ >= 20){
        //     break;
        // }
        // if(count == 15){
        //     count_++;
        // }
        // Check if we returned to the starting position with the same direction
        if (x == st_x && y == st_y && d == direction) {
            break;
        }
    }

    printf("%d\n", count);
}

