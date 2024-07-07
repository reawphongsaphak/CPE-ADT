#include <stdio.h>

void show(int y, int m);
int isLeapYear(int y);

char *dOw[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
char *month[12] = {"January", "February", "March", "April", "May", "June", "July",
                    "August", "September", "October", "November", "December"};

int normal_year[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int leap_year[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int day = 0;
int space = 0;

int main() {
    int y = 1990, m = 1;
    printf("Enter year: ");
    scanf("%d", &y);
    printf("Enter month: ");
    scanf("%d", &m);
    show(y, m);
    return 0;
}

//. show date
void show(int y, int m) {
    printf("====================\n");
    printf("%s %d\n", month[m-1], y);
    for (int i = 0; i < 7; i++) {
        printf("%s ", dOw[i]);
    }
    printf("\n");

    for (int i = 1990; i < y; i++) {
        if (isLeapYear(i)) {
            day += 366;
        } else {
            day += 365;
        }
    }

    for (int i = 1; i < m; i++) {
        if (isLeapYear(y)) {
            day += leap_year[i-1];
        } else {
            day += normal_year[i-1];
        }
    }

    space = (day % 7)+1;

    for (int i = 0; i < space; i++){
        printf("    ");
    }


    if (isLeapYear(y)){
        for (int i = 1; i <= leap_year[m-1]; i++) {
            if ((i+space) % 7 == 0) {
                printf("%3d\n", i);
            } else {
                printf("%3d ", i);
            }
        }
    }
    else {
        for (int i = 1; i <= normal_year[m-1]; i++) {
            if ((i+space) % 7 == 0) {
                printf("%3d\n", i);
            } else {
                printf("%3d ", i);
            }
        }
    }
    printf("\n");
}

//.check is leap year
int isLeapYear(int y) {
    if (y % 4 == 0) {
        if (y % 100 == 0) {
            if (y % 400 == 0) {
                return 1; //* It is a leap year
            } else {
                return 0; //* It is not a leap year
            }
        } else {
            return 1; //* It is a leap year
        }
    } else {
        return 0; //* It is not a leap year
    }
}