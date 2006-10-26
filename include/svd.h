#ifndef __SVD_H__
#define __SVD_H__

/**
  \file
  ����������� ����������.

  ���� �������� �������, �������� � ������������ ����������� ���������� �������.

  C���������� ����������� ������������� ������� \f$A\f$ ������� \f$m\times n\f$, \f$m \ge n\f$
  ���������� �� ������������� \f$A = U S V^{\rm T}\f$, ���
    - \f$U\f$ - ������� ������� \f$m \times n\f$ � ������������������ ���������,
    - \f$V\f$ - ������������� ������� ������� \f$n \times n\f$,
    - \f$S\f$ - ������������ \f$n \times n\f$ ������� � ���������������� ������������� ����������,
          ����������� ������������ �������.

  ��������� ������������� ������������ ����� � ������������ ����
  ������������ ����� ��������������� ���������� �������. ����� \f$r\f$ ���������
  ����������� ����� ��������� ���� �������. ��� ����������� �� ����������
  ������ ������� ����������� ����� ����� ���� �������� ���������, �������
  ����������� ����������� ����� ���������� ��������������� � ������
  ����������� ����������.

  ����������� ���������� ������������ ��� ���������� ����������� �������������
  ������������� ������� \f$Ax = b\f$.
  ������ x ���������� �������������� ������� \f$Ax=b\f$, ���� �� ��� �����������
  ������� \f$\|Ax-b\|_2\f$. ������������� \f$x\f$ ���������� ����������, ���� �����
  ���� ������������� ��� ����� ����������� �����. ��� ����� ������� ����������
  ������������� �����������.

  ����� \f$S={\rm diag}(\sigma_1,\dots,\sigma_r,0,\dots,0)\f$,
  \f$U=(U_1, U_2)\f$, \f$V=(V_1, V_2)\f$, ��� \f$U_1\f$, \f$V_1\f$ ����� �� \f$r\f$ �������� ������.
  ���������� ������������� ����� �����
  �� ������� \f$x = V_1 S_1^{-1} U_1^{\rm T} b\f$.
*/

/*
  ���������:

  C���������� ����������� ������������ ������������� ������������ ������� \f$A\f$ 
  ������� \f$m \times n\f$ ���������� �� ������������� \f$A = USV^{\rm T}\f$, ���
    - \f$U\f$ - ������������� ������� ������� \f$m \times m\f$,
    - \f$V\f$ - ������������� ������� ������� \f$n \times n\f$,
    - \f$S\f$ - ������������ \f$m \times n\f$ ������� � ���������������� ������������� ����������,
          ����������� ������������ �������.

  ���� m > n, �� ��-�� ������� ��������� ����� ������� S � ������� U
  ������� � (n + 1)-�� �� m-�� ����� ���� ������ ��� ������������
  �����������, ��� ������� U ����� ������������� (�.�. �� �������
  ���������� ����������������� �������). � ���������� ������������
  ����������� ������������� ������������ ����������, � ������� �����������
  � �������� ������ ������ n �������� ������� U.

*/

/**
  \example xsvd.c
*/

/**
  ����������� ���������� �������.

  ������� ������� ����������� ���������� \f$A = U\cdot S\cdot V^{\rm T}\f$ ������������ 
  ������� A ������� \f$m\times n\f$, \f$m \ge n\f$.

  - ����:  
     - \f$A\f$  - ������������� ������� ������� \f$m \times n\f$
     - \f$m\f$  - ����� ����� ������� \f$A\f$
     - \f$n\f$  - ����� �������� ������� \f$A\f$
     - \f$matu\f$ - ����� \f$1\f$, ���� ��������� ����� ������� \f$U\f$: ����� \f$0\f$, ���� �� ���������
     - \f$matv\f$ - ����� \f$1\f$, ���� ��������� ����� ������� \f$V\f$: ����� \f$0\f$, ���� �� ���������

  - �����: 
     - \f$A\f$ - �� ����������
     - \f$w\f$ - ������ ����� n, ���������� ����������� ����� ������� \f$A\f$. �����,
           ������ (�� �� �����������), ����������� �� ��������.
           � ������ ������ ����������� �����, ������� �� ��������
           \f$ierr\f$, \f$ierr+1\f$, \f$\dots\f$, \f$n - 1\f$, ����������.
     - \f$U\f$ - ������������� ������� ������� \f$m \times n\f$. � ������ ������ ������� �������
           \f$U\f$, ������� �� �������� \f$ierr\f$, \f$ierr+1\f$, \f$\dots\f$, \f$n - 1\f$, ���������.
     - \f$V\f$ - ���������� ������� ������� \f$n\f$. � ������ ������ ������� �������
           \f$V\f$, ������� �� �������� \f$ierr\f$, \f$ierr+1\f$, \f$\dots\f$, \f$n - 1\f$, ���������.
     - ierr ��������������� ������
            - \f$0\f$ ��� ���������� ������
            - \f$k\f$, ���� \f$k\f$-� ����������� ����� �� ���� ���������� �� \f$30\f$ ��������

  �������� ������� �� ���� ������. �� ������ ����� ����������� �����������
  ������� \f$A\f$ ���������� � ����������������� ����. �� ������ ����� ���������
  \f$QR\f$-��������� ���������������� ������� ���������� � ������������� ���� \f$S\f$.

  ������� �������� ��������� ������������� ��������� svd �� ����� [FMM].

  ������������: 

  �������������� ������: O(n)
*/
extern void svd_decomp(double** A, size_t m, size_t n, double* w, int matu, double** U, int 
  matv, double** V, size_t *ierr);


/**
  �������������� ��������������� ����������� ����������� �����.

  ������� �������� ������� � ���� ����������� ����� ������� \f$A\f$, ����������� ��������
  #svd_decomp, � ������ ���������� ������������� ����������� \f$rel\_err\f$.
  ������� A ����� ������� \f$m\times n\f$, \f$m \ge n\f$.
  �������� \f$rel\_err\f$ ������ �������� ������ � �������� ������ (� ������� \f$A\f$).
  ���� ������ ��������������� ��� ������, �� ���������� ������ \f$rel\_err = 0\f$.
  � ���� ������ ������� ��������� �������� \f$rel\_err\f$, ���������� ������ ��� 
  ����������� � ����� ������� #svd_decomp, � ������, \f$\varepsilon\cdot n\f$,
  ��� \f$\varepsilon \approx 10^{16}\f$ - ���������� ����� \f$1\f$ � ��������� �� ��� ������
  � ���������� ������� ��������. ����������
  ����������� ��������, �� ������������� \f$rell\_err \cdot \sigma_{\max}\f$, ��� \f$\sigma_{\max}\f$ - 
  ������������ ����������� ��������.

  - ����:  
     - \f$w\f$ - ������ ����� n, ������������ �������� #svd_decomp. 
     - \f$n\f$ - ����� �������� ������� A
     - \f$rel\_err\f$ - ������������� �����������

  - �����: 
     - \f$w\f$ - ����������������� ����������� �����, ������ ����� \f$n\f$
*/
extern void svd_correct(double *w, size_t n, double rel_err);

/**
  ���������� ������������� ����� ��������������� �� ������
  ������������ ����������.

  ������� ��������� ������������ ����� ��������������� ������� \f$A\f$ �� ������ ���������� 
  �������� #svd_decomp ������������ ���������� \f$A = USV^{\rm T}\f$. 
  ������� A ����� ������� \f$m\times n\f$, \f$m \ge n\f$.
  ������������ ����� ���������������
  ����� ��������� ������������� ������������ �������� � ������������.
 
  - ����:  
     - \f$w\f$ - ������ ����� \f$n\f$, ������������ �������� #svd_decomp � ����������
           ����������� ����� ������� \f$A\f$
     - \f$n\f$ - ����� �������� ������� \f$A\f$

  - �����: ������� ���������� ������������ ����� ���������������

  ������������: 
*/
extern double svd_cond(double *w, size_t n);

/**
  ���������� ����������� ������������� ������� �������� ��������� 
  �� ������ ������������ ����������.

  ������� ������� ���������� ������������� ������� �������� ��������� \f$Ax = b\f$
  �� ������ ������������ �������� #svd_decomp ������������ ���������� \f$A = USV^{\rm T}\f$. 
  ������� A ����� ������� \f$m\times n\f$, \f$m \ge n\f$.
  ��� ���������� ������������� ������������ ������ ��������� ����������� ��������.
  ����� ������� ������� ������������� �������� ������� � ���� ����������� ��������
  (��������, � ������� ������� #svd_correct).

  - ����:  
     - \f$U\f$ - ������������� ������� ������� \f$m \times n\f$, ������������ �������� #svd_decomp. 
     - \f$V\f$ - ���������� ������� ������� \f$n\f$, ������������ �������� #svd_decomp. 
     - \f$w\f$ - ������ ����� \f$n\f$, ������������ �������� #svd_decomp. 
     - \f$m\f$ - ����� ����� ������� \f$A\f$
     - \f$n\f$ - ����� �������� ������� \f$A\f$
     - \f$b\f$ - ������ ����� ������� \f$Ax = b\f$, ������ ����� \f$m\f$

  - �����: 
     - \f$x\f$ - ��������� ���������� �������������, ������ ����� \f$n\f$

  ������������: 
*/
extern void svd_least_squares(double **U, double *w, double **V, size_t m, size_t n, double *b, double *x);

#endif