/*
  ������ ������������� ������� �� ������ @optim.h@ 
  ����������� <<������>>-����������:
  $f(x_1, x_2) = (x_2 - x_1^2)^2 + (1 - x_1)^2$
  ��������-������� �������-����   
*/

#include <stdio.h>
#include <math.h>
#include "nl.h"

double fun(double *x)
{

  double tmp1, tmp2;

  tmp1 = x[1] - x[0]*x[0];
  tmp2 = 1 - x[0];

  return tmp1*tmp1 + tmp2*tmp2;
}

int main(void)
{
  size_t n;
  double *x0, *x, *f, *work;
  double f0;
  double ftol, xtol;
  int maxfun, maxiter, rc, nfun, niter;

  n = 2;

  x0 = nl_dvector_create(n);
  x = nl_dmatrix_create(n + 1, n);
  f = nl_dvector_create(n + 1);
  work = nl_dvector_create(4*n);

  x0[0] = -1.2;
  x0[1] = 1;
  ftol = 1.0e-6;
  xtol = 1.0e-6;
  maxfun = 200;
  maxiter = 50;

  rc = optim_nelder_mead(fun, n, 0, x0, &f0, x, f, ftol, xtol, maxfun, maxiter, 
    &nfun, &niter, work);

  if (rc == -1)
  {
    printf("\n����� �������� ��� ���������� ����������� �������� �������\n");
    printf("��������� ����������� ����������!\n" );
  }
  else
    printf("\n�������� ����������\n");

  printf("\n���������� ����������� �������� �������: %d\n", nfun);
  printf("����� �������� (���������� ����������� ����������): %d\n",niter);

  printf("\n����������� ����� ��������:\n");
  nl_dvector_print(x0, n, "  %12.6e");

  printf("\n������� ���������� ���������:\n");
  nl_dmatrix_print(x, n + 1, n, "  %12.6e");

  printf("\n�������� ������� � ��������:\n");
  nl_dvector_print(f, n + 1, "  %12.6e");
  
  nl_dvector_free(x0);
  nl_dmatrix_free(x);
  nl_dvector_free(f);
  nl_dvector_free(work);

  return 1;
}
