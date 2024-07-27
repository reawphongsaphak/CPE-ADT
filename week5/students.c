#include <stdio.h>
#include <math.h>

typedef struct student {
    char name[30];
    int points;
    char grade;
} student_t;

void inputStudent(student_t students[], int n_students);
void showStudentGrade(student_t students[], int n);
void grading(student_t students[], int n);
char grader(int points, float avg, float sd);

int main(void) {
    student_t students[1000];
    int n;
    scanf("%d", &n);
    inputStudent(students, n);
    showStudentGrade(students, n);
    return 0;
}

void inputStudent(student_t students[], int n) {  //* n mean number of students
    for (int i = 0; i < n; i++){
        scanf("%s %d", students[i].name, &students[i].points);
    }
    grading(students, n);
}

void showStudentGrade(student_t students[], int n) {
    for (int i = 0; i < n; i++){
        printf("%s %c\n", students[i].name, students[i].grade);
    }
}

void grading(student_t students[], int n){ //* n mean number of students
    int sum = 0, s_square = 0;
    float avg = 0, sd = 0;

    
    for (int i = 0; i < n; i++){
        sum += students[i].points;
    }

    avg = sum / n;

    for (int i = 0; i < n; i++){
        s_square += pow((students[i].points - avg), 2);
    }

    sd = sqrt(s_square/(n-1));

    for (int i = 0; i < n; i++){
        students[i].grade = grader(students[i].points, avg, sd);
    }
}

char grader(int points, float avg, float sd){
    if (points >= (avg + (1.5 * sd))) {return 'A';}
    if ((points < (avg + (1.5 * sd))) && (points >= avg + sd)) {return 'B';}
    if ((points < (avg + sd)) && (points >= avg - sd)) {return 'C';}
    if ((points < avg - sd) && (points >= (avg - (1.5 * sd)))) {return 'D';}
    else {return 'F';}
}
