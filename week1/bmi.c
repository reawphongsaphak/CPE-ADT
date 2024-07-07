#include <stdio.h>

void main(){
    int w,h;
    float bmi;
    int catagory;

    scanf("%d %d",&w, &h);
    bmi = w*10000.0/(h*h);

    if (bmi < 18.6){
    catagory = 1;}
    else if (bmi < 25){
    catagory = 2;}
    else if (bmi<30){
    catagory = 3;}
    else {
    catagory = 4;}

    switch (catagory){
        case 1:
            printf("BMI: %.4f and you are underweight",bmi);
            break;
        case 2:
            printf("BMI: %.4f and you are healthy",bmi);
            break;
        case 3:
            printf("BMI: %.4f and you are overweight",bmi);
            break;
        case 4:
            printf("BMI: %.4f and you are obese",bmi);
            break;} 
}