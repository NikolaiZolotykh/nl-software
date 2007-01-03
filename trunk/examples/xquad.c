#include <stdio.h>
#include <math.h>
#include "nl.h"

/*
  ������������� ������� �� ������ @quad.h@
  ���������� ������������� ���������
  $\int_0^1 \sqrt{x} dx$
  ����������� �������� ��������, �������-��������, ������--��������
*/

double fun(double x)
{
  return sqrt(x);
}

void print_results(double q, int rc, int nfunevals)
{
   switch (rc)
   {
      case 0:
         printf("�������� ����������\n");
         break;
      case -1:
         printf("��������� ������� �� �������� �������� �����\n");
         printf("��������� �������� �� ����� ���� ����������\n");
         break;
      case -2:
         printf("���������� ���������� �������� ��������������� �������\n");
         printf("��������� ����������� ����������\n");
         break;
   }

   printf("�������� ���������: %14.12f\n", q);
   printf("���������� ��������� � �������: %d\n", nfunevals);
}


int main()
{
   double q;
   int rc, nfunevals;

   printf ("\n����� ��������:\n");
   q = quad_simpson(&fun, 0, 1, 1e-6, 10000, &rc, &nfunevals);
   print_results(q, rc, nfunevals);

   printf ("\n����� �������-�������� 4,7:\n");
   q = quad_lk47(&fun, 0, 1, 1e-6, 10000, &rc, &nfunevals);
   print_results(q, rc, nfunevals);

   printf ("\n����� ������-�������� 7,15:\n");
   q = quad_gk715(&fun, 0, 1, 1e-6, 10000, &rc, &nfunevals);
   print_results(q, rc, nfunevals);

   return 0;
}

