#include <stdio.h>
#include <math.h>
#include "nl.h"

void fn(double *x, double *f)
{
  f[0] = x[1] - x[0]*x[0];
  f[1] = 1 - x[0];
}

void jc(double *x, double *J)
{
  J[0] = -2*x[0]; J[1] = 1;
  J[2] = -1;      J[3] = 0;
}

int main()
{
  size_t n, m;
  double *x0, *f, *work, *J, *A, *g;
  double f0;
  double ftol, xtol;
  int maxfunevals, maxiter, rc, niter, nfunevals, njacevals;

  n = 2;
  m = 2;

  x0 = nl_dvector_create(n);
  f = nl_dvector_create(m);
  J = nl_dmatrix_create(m, n);
  A = nl_dmatrix_create(n, n);
  g = nl_dvector_create(n);
  work = nl_dvector_create(2*n + m);

  x0[0] = -10;
  x0[1] = 6;
  ftol = 1.0e-6;
  xtol = 1.0e-6;
  maxfunevals = 200;
  maxiter = 50;

  rc = optim_levenberg_marquardt(
   fn,
   jc,
   n,
   m,
   x0, 
   ftol, 
   xtol, 
   maxfunevals, 
   maxiter, 
   &f0,
   f,
   &niter,
   &nfunevals,
   &njacevals,
   g,
   J,
   A,
   work);


  if (rc == 1 || rc == 2)
    printf("\n�ᯥ譮� �����襭��\n");
  else
  {
    printf("\n��᫮ ���権 ��� ������⢮ ���᫥���� ���祭�� �㭪樨\n");
    printf("�ॢ�ᨫ� ���ᨬ��쭮 �����⨬��!\n" );
  }

  printf("\n��᫮ ���権: %d\n",niter);
  printf("������⢮ ���᫥���� ���祭�� �㭪樨: %d\n", nfunevals);
  printf("������⢮ ���᫥���� ����� �����:     %d\n", njacevals);

  printf("\n��������� �窠 �����㬠:\n");
  nl_dvector_print(x0, n, "  %12.6e");

  printf("\n���祭�� �㭪樨: %e\n", f0);
  
  nl_dvector_free(x0);
  nl_dvector_free(work);

  return 1;
}







