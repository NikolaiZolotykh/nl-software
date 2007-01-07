#include <stdio.h>
#include <math.h>
#include "nl.h"

/*
  ������ ������������� ������� �� ������ @optim.h@ 
  ������� ������� $x^3 - 2x - 5$ �� ������� $[0,1]$
*/

double fun(double x)
{
  return x*(x*x - 2) - 5;
}


int main()
{
  double x, fx;

  x = optim_min(&fun, 0, 1, 1e-6);
  fx = (*fun)(x); 

  printf("����� ��������:    %f\n", x);
  printf("�������� ��������: %f\n", fx);


  return 0;
}