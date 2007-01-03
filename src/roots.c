#include <math.h>
#include <float.h>
#include "nl.h"

double roots_zero(double (*fun)(double), double a, double b, double abstol) 
{

  double eps, tol1, c, d, e, fa, fb, fc, p, q, r, s, xm;

  /* ��������� ������������� */

  eps = DBL_EPSILON;

  fa = (*fun)(a);
  fb = (*fun)(b);
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

     tol1 = 2.0*eps*fabs(b) + 0.5*abstol;
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

     fb = (*fun)(b);

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

