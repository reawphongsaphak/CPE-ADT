#include <stdio.h>

void intToroman(int num);

int main(){
  int n = 0, num = 0;
  scanf("%d",&n);
  for(int i = 0; i < n; i++){
    scanf("%d",&num);
    intToroman(num);
  }
  return 0;
}

void intToroman(int num){
  
  char *thou[4] = {"", "M", "MM", "MMM"};
  char *hund[10] = {"", "C", "CC", "CCC", "CD" , "D", "DC", "DCC", "DCCC", "CM"};
  char *tens[10] = {"", "X", "XX", "XXX", "XL" , "L", "LX", "LXX", "LXXX", "XC"};
  char *digit[10] = {"", "I", "II", "III", "IV" , "V", "VI", "VII", "VIII", "IX"};

  int thou_i, hund_i, tens_i, digit_i;
  thou_i = num / 1000;

  num -= thou_i*1000;
  hund_i = num / 100;

  num -= hund_i*100;
  tens_i = num / 10;
  
  num -= tens_i*10;
  digit_i = num;
  
  printf("%s",thou[thou_i]);
  printf("%s",hund[hund_i]);
  printf("%s",tens[tens_i]);
  printf("%s\n",digit[digit_i]);

}