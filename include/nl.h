#ifndef __NL_H__
#define __NL_H__

#include "util.h"
#include "band.h"
#include "chol.h"
#include "lu.h"
#include "qr.h"
#include "qsort.h"
#include "sparse.h"
#include "iter.h"
#include "svd.h"
#include "gallery.h"
#include "eig.h"
#include "mda.h"
#include "optim.h"
#include "fft.h"
#include "conv.h"
#include "ode.h"
#include "quad.h"
#include "interp.h"
#include "roots.h"
#include "int.h"

#include "clapack/f2c.h"
//#include "clapack/blaswrap.h"
#include "clapack/cblas.h"
#include "clapack/clapack.h"

/**
  \file 
  ���� ���������� ��� ��������� ������������ ����� ����������.

  ��� ���������� ����� ��������� � �������������� ��������� ����������
  ���������� ���������� ������ ������ ������������ ����.
  ��� ������ (��������) ���������� ������������ ��������� (��� ������������)
  ����� ����������.

  ����� ���� �������� ����������� ��������
  NL_MIN(a, b), NL_MAX(a, b), NL_SIGN(a)  
 

  \todo
    �� ���� ������� �������������� ����� ������� malloc, create � �.�.
    ���������� � �������� ���������� ������� ������� ������� (-�������!).

  \todo
    �� ���� ������� � ��������� *a �������� �� ��������, � ����������, ����������� �� 
    ������� ������ ������ ����� (������� ��������).
*/

#define NL_MIN(a, b)  (((a) < (b))? (a):(b))
#define NL_MAX(a, b)  (((a) > (b))? (a):(b))
#define NL_SIGN(a)  (((a) > 0)? 1:(((a) < 0)? -1:0))



/*

  ����� ���� �������� �������� ��������� ���������, ������������ ������
  ����������.

  �������� �������� � ������ ���������� NL
static const char* nl_version =
#include "..\version"
;
*/

/**

\mainpage ���������� NL - Numerical Library

  - <a href="..\..\version">������ ����������</a>
  - <a href="..\..\change.log">������ ���������</a>

<p>
������ �������� �������� ���������� �� �������� 
������-����������������� ���������� ��������� ������� NL.
���������� ������������ ����� ����� �������, ���������� ��
����� C. � ��������� ����� �����������:

  - ������� ������ �������� �������������� ��������� 
    � ������� \f$LU-\f$, \f$QR-\f$ ���������� � ���������� ���������
  - ����������� ����������. ������ ���������� ���������.
  - ������ ������ ������� ��������� ������
  - �������� � ������������ ���������
  - ������ � ������������ ������ ������� ����������� ������
  - ������� �������������� �����
  - ������������ ���������
  - ������ �����������
  - ������ ���� ��� ������������ ���������������� ���������
  - ��������� ���������� �������� �������� ����� �� ���������
  - ���, �������� �� �������� � ������������ ����� ����� (long)

�������� ������� ���������� ��. � ������� <a href="files.html">�����</a>

������ 1.0.0 ���������� ��������������� � ������-����������������� �����������
"�������������� ����������" �������������� ���������������� ������������
��. �.�.������������ ��� ��������� ����� ���������� �������� ����� ����
����������� � ������-����������� �����.

(c) �.�.�������, <a href="http://www.uic.nnov.ru/~zny">�.�.�������</a>, �.�.�������,
2004, 2005, 2006, 2007, 2008



<h2> ����������� </h2>

�������� ����� ���������� ��������� � ����� src. ������������ ����� - �
����� include. ������� - � ����� examples. ��� �������� ����������
���������� �������������� � ������� ��� ����� �� ����� src. �����
������������ ����������� � ��������� ���� ����� ��������� ����������
���������� ���� include\\nl.h, ���������� ��������� ���� �������. ���
������ ��������� ��� ��������� ���� ����� ���������� ������ � �������
����������.

����� ����, ��� �������� ������������ �������� ��������� �����
makemsvc.bat, makebcc32.bat, makewatcom.bat � makegcc.bat. ��� ��������� ����� ���������� ��������
������������ MS Visual C++, Borland C++, Watcom C++ � gcc ��������������. � ���������� �� ����������
��������� ������������ ����� lib\\nl.lib, lib\\nl.bcc32.lib, lib\\nl.watcom.lib � lib\\nl.a 
� ������������� ��� ������� �� ����� examples. ������������ ���� ��������� ������ �����������
� �������������� ��������� ������������:
  - Microsoft Visual C++ 6.0,
  - Borland C++ 5.5,
  - Open Watcom C/C++/FORTRAN Version 1.1,
  - gcc 3.3.1 (cygwin special).




<h2> ���������� </h2>

[BelovZolotykh]
<i>����� �.�., ������� �.�.</i> ��������� ������ �������� �������. ������������ ���������. ������ ��������: ���-�� ��������� ���. ��-��, 2005.

[VoevodinKuznetsov]
<i>�������� �.�., �������� �.�.</i> ������� � ����������. �.: �����, 1984.

[GolubVanLoan]
<i>����� ��., ���� ��� �.</i> ��������� ����������. �.:  ���. 1999.

[Demmel]
<i>����������.</i> �������������� �������� �������. ������ � ����������. �.:  ���. 2001.

[KMN]
<i>������� �., ������ �., ��� �.</i> ��������� ������ � ����������� �����������. �.:  ���. 1999.

[Pissanezki]
<i>���������� �.</i> ���������� ����������� ������. �.: ���, 1988.

[FMM]
<i>������� ��.,  ��������� �., ������ �.</i> �������� ������ �������������� ����������. �.:  ���. 1980.

[Recipes]
<i>Press W.H., Teukolsky S.A., Vetterling W.T.,  Flannery B.P.</i> Numerical Recipes in C. The Art of Scientific Computing. 1992. 

[GG2000]
<i>Gander W., Gautschi  W.</i> Adaptive Quadrature - Revisited. BIT, Vol. 40, 2000. P. 84-101

*/


#endif
