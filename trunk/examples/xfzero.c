/*
  ������ ������������� ������� �� ������ @.h@ 
  ������ ���������
  $x^3 - 2x - 5 = 0$
*/

#include <stdio.h>
#include <math.h>
#include "nl.h"

/**
  ������� ��������� � ����� �����������.
  ������������ ��������������� ����� ������� ������� (��������),
  ������� � �������� ������������ ������������.

  - ����:
	- @func@ - ��������� �� ������� ����������� ������ ����� ��������� \f$f(x)=0\f$
	- $a$ - ����� ����� ��������� ���������
	- $b$ - ������ ����� ��������� ���������
	- $tol$ - �������� ����� ��������� ���������������� ��������� ����������

  - �����:
	- ������� ���������� ��������� �������.

  ��� �������� ��������������, ��� �� ������ ������� \f$[a, b]\f$
  ������� \f$f(x)\f$ ����� ������ �����. ������ ��������� ������ � �������� �������
  �� ������ \f$4\cdot \varepsilon_{\rm M} \cdot |x| + tol\f$,
  ��� \f$\varepsilon_{\rm M}\f$ - �������� ��������.

  ������� �������� ��������� ������������� ��������� zeroin �� ����� [FMM].
*/

double fzero(double (*func)(double), double a, double b, double tol) 
{

  double eps, tol1, c, d, e, fa, fb, fc, p, q, r, s, xm;

  /* ���������� ��������� ������� */

  eps = 1.0;

  do
  {
    eps = eps/2;
    tol1 = 1.0 + eps;
  }
  while (tol1 > 1.0);

  /* ��������� ������������� */

  fa = (*func)(a);
  fb = (*func)(b);
  c = a;
  fc = fa;
  d = b - a;
  e = d;

  /* �������� ���� */

  while(1)
  {

    if (fabs(fc) < fabs(fb))
    {
      a = b;
      b = c;
      c = a;
      fa = fb;
      fb = fc;
      fc = fa;
    }

     /* �������� ���������� */

     tol1 = 2.0*eps*fabs(b) + 0.5*tol;
     xm = .5*(c - b);
     if (fabs(xm) <= tol1 || fb == 0.0) 
  	break;
   
     if (fabs(e) < tol1 || fabs(fa) < fabs(fb))
     {
          /* �������� */

          d = xm;
          e = d;
     }
     else 
     {
        if (a != c)
        {
          /* �������� ������������ ������������ */

          q = fa/fc;
          r = fb/fc;
          s = fb/fa;
          p = s*(2.0*xm*q*(q - r) - (b - a)*(r - 1.0));
          q = (q - 1.0)*(r - 1.0)*(s - 1.0);
        }
        else
        {
          /* �������� ������������ (����� �������) */

          s = fb/fa;
          p = 2.0*xm*s;
          q = 1.0 - s;
        }
        
        /* ������� ����� */

        if (p > 0.0) 
          q = -q;
        p = fabs(p);

        /* ��������� �� ������������? */

        if (2*p < 3*xm*q - fabs(tol1*q) && p < fabs(0.5*e*q))
        {
          e = d;
          d = p/q;
        }
        else
        {
          /* ���-���� �������� */

          d = xm;
          e = d;
        }
     }

     /* ���������� �������� */

     a = b;
     fa = fb;

     if (fabs(d) > tol1) 
       b = b + d;
     else
       if (xm >= 0)
         b = b + tol1;
       else
         b = b - tol1;

     fb = (*func)(b);

     if (fb*(fc/fabs(fc)) > 0.0)
     {
       c = a;
       fc = fa;
       d = b - a;
       e = d;
     }

  }
    
  return b;

}

double func(double x)
{
  return x*(x*x - 2) - 5;
}


int main()
{
  double x;

  x = fzero(&func, 2, 3, 1e-6); 

  printf("������:  %f  \n", x);

  return 0;
}