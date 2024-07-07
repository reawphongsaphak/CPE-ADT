#include <stdio.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884
#endif

float cal_area(float d, float h1, float h2);
float graph_h(float A, float B, float x);

int main(){
  float a, b, A, B, d, ans = 0.0;
  int  n;

  scanf("%f %f %f %f %d", &a, &b, &A, &B, &n);
  d = (b - a) / n;
  for (int i = 0; i < n; i++){

    float x1 = a +  i * d;
    float x2 = a +  (i + 1) * d;

    float h1 = graph_h(A, B, x1);
    float h2 = graph_h(A, B, x2);
    float area = (float)cal_area(d, h1, h2);

   // printf("area is : %.5lf\n",area);
   // printf("h1 is : %.5lf\n",h1);
   // printf("h2 is : %.5lf\n",h2);
    ans += area;
  }
  
  printf("%.5lf\n", ans);
  
  return 0;
}

float cal_area(float d, float h1, float h2){
  return 0.5 * d * ( h1 + h2);
}

float graph_h(float A, float B, float x){
  return A * sin( (M_PI*x) / B);
}