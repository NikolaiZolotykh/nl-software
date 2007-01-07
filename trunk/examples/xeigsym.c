/*
  ������������ �������� ����������� ��������.
  $QR$-��������.
*/

#include "nl.h"

int main()
{
    size_t n = 5;
    size_t rc;
    double *A, *d, *e;

    A = nl_dmatrix_create(n, n);
    d = nl_dvector_create(n);
    e = nl_dvector_create(n);
    
    A[0]  = 11;
    A[5]  = 10; A[6]  = 14; 
    A[10] = 18; A[11] = 41; A[12] = 17; 
    A[15] = 11; A[16] = 12; A[17] = 23; A[18] = 11; 
    A[20] = 21; A[21] = 13; A[22] = 23; A[23] = 17; A[24] = 17; 
    
    printf("\n������� A (������ ����������� �����):\n");
    nl_dmatrix_print(A, n, n, NULL);

    eig_tridiag_reduction(A, n, 1, d, e);

    printf("\n���������������� ���\n");
    printf("���������:\n");
    nl_dvector_print(d, n, NULL);

    printf("\n������������ = ������������:\n");
    nl_dvector_print(e, n, NULL);

    printf("\n������� �������� Q:\n");
    nl_dmatrix_print(A, n, n, NULL);

    eig_tridiag(d, e, n, 1, A, &rc);

    printf("\n����������� �����:\n");
    nl_dvector_print(d, n, NULL);

    printf("\n����������� �������:\n");
    nl_dmatrix_print(A, n, n, NULL);

    nl_dmatrix_free(A);
    nl_dvector_free(d);
    nl_dvector_free(e);
    
    return 0;
}
