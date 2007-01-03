#include <stdio.h>
#include <math.h>
#include "nl.h"

/*
  ������ ������������� ������� �� ������ @roots.h@ 
  ������ ���������
  $x^3 - 2x - 5 = 0$
*/

double fun(double x)
{
  return x*(x*x - 2) - 5;
}


int main()
{
  double x;

  x = roots_zero(&fun, 2, 3, 1e-6); 

  printf("������:  %f  \n", x);
  printf("�������� �������:  %e  \n", (*fun)(x));

  return 0;
}