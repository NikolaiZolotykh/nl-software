#include <stdio.h>
#include <math.h>
#include "nl.h"

/*
  ������������� ������� �� ������ @quad.h@
  ���������� ������������� ���������
  $\int_0^1 \sqrt{x} dx$
  ���������� ������� �������--��������
*/

double fun(double x)
{
  return sqrt(x);
}


int main()
{
   double q;
   int rc, nfunevals;

   q = quad_lk47(&fun, 0, 1, 1e-6, 10000, &rc, &nfunevals);

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

   return 0;
}

