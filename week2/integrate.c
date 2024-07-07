#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double cal_area(double d, double h1, double h2);
double graph_h(double A, double B, double x);

int main(){
    double a, b, A, B, d, ans = 0.0;
    int  n;

    scanf("%lf %lf %lf %lf %d", &a, &b, &A, &B, &n);
    d = (b - a) / n;

    for (int i = 0; i < n; i++){
        double x1 = a +  i * d;
        double x2 = a +  (i + 1) * d;

        double h1 = graph_h(A, B, x1);
        double h2 = graph_h(A, B, x2);
        double area = (double)cal_area(d, h1, h2);

        ans += area;
    }
    printf("%.5lf\n", ans);

    return 0;
}

double cal_area(double d, double h1, double h2){
    return 0.5 * d * ( h1 + h2);
}

double graph_h(double A, double B, double x){
    return A * sin( (M_PI*x) / B);
}