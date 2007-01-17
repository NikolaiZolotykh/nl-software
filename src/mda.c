#include <memory.h>

#include "nl.h"

/* 
 *  �.�.����襢
 *  �.�.�������  2005, 2006, 2007
 */

/*
 *  ������祭��:
 * 
 *  n        - ���冷� ������ A
 *  nz       - �᫮ ���㫥��� ����⮢ ������ A ���(����) ���������
 *  R        - �����������쭠� �������� ������ A
 *  L        - �����������쭠� �������� ������ A
 *  (IR, JR) - ���筮� �।�⠢����� ������ R
 *  (IL, JL) - ���筮� �।�⠢����� ������ L
 *  P        - ����⠭���� 㧫��
 *  IP       - ���⭠� ����⠭���� (IP[P[i]] = i � ������� P[IP[i]] = i)
 *  D        - �⥯��� 㧫��
 *  M        - ��⪨ 㧫��
 *  L        - ᯨ᮪ ���⨦���� 㧫��
 *  MR       - ᯨ᪨ ᫨��� 㧫��
 * 
 */

/*
 *  ����樨 � 2-��祩
 */

size_t heap_pos(size_t i, size_t n)
{
  return n - 1 - i;
}

/* �����頥� த�⥫� ��� i-�� 㧫� 2-��� */
size_t heap_parent(size_t i, size_t n)
{
  i = heap_pos(i, n);
  return heap_pos((i - 1)/2, n);
}

/* �����頥� ������襣� �� ������ ��⮬�� ��� i-�� 㧫� 2-��� */
size_t heap_child(size_t i, size_t h, size_t n)
{
  i = 2*heap_pos(i, n) + 1;
  return (n - 1 >= i + h)? n - 1 - i: n;
}

/* ������ �ᯫ��� i-�� 㧫� 2-��� */
size_t heap_up(size_t i, size_t n, size_t *D, size_t *P, size_t *IP)
{
  size_t p = P[i], deg = D[i], parent;
  while(i < n - 1)
  {
    parent = heap_parent(i, n);
    if(D[parent] <= deg) break;
    D[i] = D[parent];
    P[i] = P[parent];
    IP[P[i]] = i;
    i = parent;
  }
  P[i] = p; D[i] = deg; IP[P[i]] = i;
  return i;
}

/* �����頥� ��⮬�� � ����襩 �⥯���� ��� i-�� 㧫� 2-��� */
size_t heap_min_child(size_t i, size_t h, size_t n, size_t *D)
{
  size_t c = heap_child(i, h, n);
  if((c == h) || (c == n)) return c;
  return (D[c] <= D[c - 1])? c: c - 1;
}

/* ������ ����㦥��� i-�� 㧫� 2-��� */
size_t heap_down(size_t i, size_t h, size_t n, size_t *D, size_t *P, size_t *IP)
{
  size_t p = P[i], deg = D[i], child = heap_min_child(i, h, n, D);
  while((child != n) && (D[child] < deg))
  {
    D[i] = D[child];
    P[i] = P[child];
    IP[P[i]] = i;
    i = child;
    child = heap_min_child(i, h, n, D);
  }
  D[i] = deg;  P[i] = p;  IP[p] = i;
  return i;
}

/* �������� i-�� 㧫� �������쭮� �⥯��� �� 2-��� */
size_t heap_del_min(size_t i, size_t h, size_t n, size_t *D, size_t *P, size_t *IP)
{
  size_t t;
  t = D[h]; D[h] = D[i]; D[i] = t;
  t = P[h]; P[h] = P[i]; P[i] = t;
  IP[P[h]] = h; IP[P[i]] = i;
  return heap_down(i, h + 1, n, D, P, IP);
}

/* ��������� �⥯��� i-�� 㧫� 2-��� */
size_t heap_change(size_t i, size_t deg, size_t h, size_t n, size_t *D, size_t *P,
  size_t *IP)
{
  if(deg == D[i]) return i;
  if(deg < D[i])
  {
    D[i] = deg;
    return heap_up(i, n, D, P, IP);
  }
  else
  {
    D[i] = deg;
    return heap_down(i, h, n, D, P, IP);
  }
}

/* 
  ����஢���� ���ﭨ� 2-��� 
  0 - ��� � ���浪�
  1 - ����襭 ��祮�ࠧ�� ���冷�
  2 - ����襭� ������� ���ᨢ�
*/
int heap_test(size_t h, size_t n, size_t *D, size_t *P, size_t *IP)
{
  size_t i;
  for(i = h; i < n - 1; i++)
  {
    if(D[i] < D[heap_parent(i, n)]) return 1;
    if(P[IP[i]] != i) return 2;
  }
  if(P[IP[n - 1]] != n - 1) return 2;
  return 0;
}

/* ������ ����㦥��� i-�� 㧫� 2-��� */
size_t heap_down_m(size_t i, size_t h, size_t n, size_t *D)
{
  size_t deg = D[i], child = heap_min_child(i, h, n, D);
  while((child != n) && (D[child] < deg))
  {
    D[i] = D[child];
    i = child;
    child = heap_min_child(i, h, n, D);
  }
  D[i] = deg;
  return i;
}

/* ����஢�� ���ᨢ� I[h, n - 1] � ������� 2-��� */
void heap_sort(size_t h, size_t n, size_t *I)
{
  size_t i, t;
  /* ���稢���� */
  for(i = h + 1; i < n; i++) heap_down_m(i, h, n, I);
  /* �����⥫쭠� ���஢�� */
  for(i = h; i < n - 1; i++)
  {
    t = I[i];
    I[i] = I[n - 1];
    I[n - 1] = t;
    heap_down_m(n - 1, i + 1, n, I);
  }
}

/* 
   ������ ���� ����� a � ���ᨢ� I[h, n - 1]
   �᫨ ����� a ������, � �����頥��� 㪠��⥫� �� ����
   ���� �����頥��� NULL
*/
size_t* binary_search(size_t a, size_t h, size_t n, size_t *I)
{
  size_t p;
  if(h == n) return NULL;
  if(I[h] == a) return &I[h];
  if(I[--n] == a) return &I[n];
  while(n - h > 1)
  {
    p = (h + n)/2;
    if(I[p] == a) return &I[p];
    if(I[p] < a) h = p; else n = p;
  }
  return NULL;
}


/*
 *  ��������� MDA
 */

void mda_create(size_t n, size_t nz, size_t **IA, size_t **JA, size_t **D,
  size_t **P, size_t **IP, size_t **M, size_t **L)
{
  *IA = nl_xvector_create(n + 1);
  *JA = nl_xvector_create(2*nz);
  *D = nl_xvector_create(n);
  *P = nl_xvector_create(n);
  *IP = nl_xvector_create(n);
  *M = nl_xvector_create(n);
  *L = nl_xvector_create(n);
}

void mda_free(size_t *IA, size_t *JA, size_t *D, size_t *P, size_t *IP,
  size_t *M, size_t *L)
{
  nl_xvector_free(IA);
  nl_xvector_free(JA);
  nl_xvector_free(D);
  nl_xvector_free(P);
  nl_xvector_free(IP);
  nl_xvector_free(M);
  nl_xvector_free(L);
}


void mda_init(size_t n, size_t *IA, size_t *D, size_t *P, size_t *IP)
{
  size_t i;
  for(i = 0; i < n; i++)
  {
    D[i] = IA[i + 1] - IA[i];
    P[i] = IP[i] = i;
  }
}

void mda_convert( size_t n, size_t *IS, size_t *JS, size_t *IA, size_t *JA,
  size_t *D, size_t *P, size_t *IP)
{
  size_t i, j, k = 0, t = 0;
  memset(IA, 0, (n + 1)*sizeof(size_t));
  for(i = 0; i < n; i++)
  {
    t += k;
    for(j = IS[i]; j < IS[i + 1]; j++)
    {
      JA[t++] = JS[j];
      IA[JS[j]]++;
    }
    k = IA[i + 1];
    IA[i + 1] = t;
    D[i] = IA[i + 1] - IA[i];
    P[i] = IP[i] = i;
  }

  k = 0;
  for(i = 0; i < n - 1; i++)
  {
    for(j = k; j - k < IS[i + 1] - IS[i]; j++)
    {
      t = IA[JA[j]]++;
      JA[t] = i;
    }
    k = IA[i + 1];
    IA[i + 1] = j;
    heap_down(i + 1, 0, n, D, P, IP);
  }
}

/* 
   node - 㧥� �������쭮� �⥯��� 
   �㭪�� ��室�� ��� ���⨦���� ������⢮ R
   �ந�������� ᫨ﭨ� node � ᬥ���� �᪫�祭��� �㯥�㧫��
   �ந�������� �।���⥫쭠� 㯠����� ᫨⮣� �㯥�㧫�
*/
size_t mda_reach(size_t node, size_t h, size_t m, size_t n, size_t *IA,
  size_t *JA, size_t *M, size_t *L, size_t *IP)
{
  size_t i, j, l, r = n;
  L[node] = node;
  M[node] = m;
  /* ����ᥭ�� � R 㧫��, ᬥ���� � node */
  for(j = IA[node]; (j < IA[node + 1]) && (IP[i = JA[j]] > h); j++)
  {
    M[i] = m;
    L[i] = r;
    r = i;
  }
  /* ᫨ﭨ� node � ᬥ���� � ��� �㯥�㧫�� */
  for( ; (j < IA[node + 1]) && ((i = JA[j]) != n); j++)
  {
    l = L[node];
    L[node] = L[i];
    L[i] = l;
  }
  /* ����ᥭ�� � R 㧫��, ᬥ���� � ᫨�묨 �㯥�㧫��� */
  /* �।���⥫쭠� 㯠����� �㯥�㧫� node */
  for(l = L[node]; l != node; l = L[l])
  {
    M[l] = m;
    for(j = IA[l]; (j < IA[l + 1]) && ((i = JA[j]) != l) && (IP[i] >= h); j++)
    {
      if(M[i] == m)  /* 㤠�塞 �������騥�� ��뫪� */
      {
        JA[j] = node;
        continue;
      }
      M[i] = m;
      L[i] = r;
      r = i;
    }
  }
  /* ���⨦���� ������⢮ R ����஥�� */
  return r;
}

/* 
  r - 㧥� ���⨦����� ������⢠ R
  �㭪�� �����頥� ���-�� 㧫��, ���⨦���� �� r
  � �� �室��� � ���⨦���� ������⢮ R
*/
size_t mda_degree(size_t r, size_t h, size_t m, size_t mm, size_t n,
  size_t *IA, size_t *JA, size_t *M, size_t *L, size_t *IP)
{
  size_t i, j, k, t, l, f, d0, d = 0;
  /* ��室 ᬥ���� 㧫�� */
  for(j = IA[r]; (j < IA[r + 1]) && (IP[i = JA[j]] >= h); j++)
  {
    if(M[i] == m) continue;
    M[i] = mm;
    d++;
  }
  /* ��室 ᬥ���� �㯥�㧫�� */
  for( ; (j < IA[r + 1]) && ((i = JA[j]) != n); j++)
  {
    if(M[i] == m) continue;
    l = i;
    d0 = d;
    f = 0;
    do
    {
      for(k = IA[l]; (k < IA[l + 1]) && ((t = JA[k]) != l) && (IP[t] > h); k++)
      {
        if(M[t] == m) continue;
        f = 1;
        if(M[t] == mm) continue;
        M[t] = mm;
        d++;
      }
      l = L[l];
    }
    while(l != i);
    /* �᫨ �㯥�㧥� ᮤ�ন� 㦥 �ன����� ��뫪�, � 㤠�塞 ��� */
    if(d == d0) JA[j] = r;
    /* �᫨ �㯥�㧥� ��뫠���� ⮫쪮 �� 㧫� �� R,   
       � ����砥� ���, �⮡� ����� ��� �� ��室��� */
    if(f == 0) M[i] = m;
  }
  return d;
}

/*  
  ��室 ���⨦����� ������⢠ R
  ��ࠧ��稬� � node 㧫� �᪫������
  ��� ��⠫��� 㧫�� ��।������� ���� �⥯���
*/
size_t mda_process( size_t r, size_t node, size_t h, size_t m, size_t n,
  size_t *IA, size_t *JA, size_t *M, size_t *L, size_t *D, size_t *P, size_t *IP)
{
  size_t d, t, dnode = D[h], c = 0, mm = m;
  for(; r != n; r = t)
  {
    d = mda_degree(r, h, m, ++mm, n, IA, JA, M, L, IP);
    t = L[r];
    if(d)
    {
      L[r] = d;
      continue;
    }
    heap_del_min(IP[r], ++c + h, n, D, P, IP);
    D[h + c] = dnode - c;
    JA[IA[r]] = node;
    if(IA[r + 1] - IA[r] > 1) JA[IA[r] + 1] = n;
  }
  return h + c + 1;
}

/* 
  ���������� �⥯���� ���᪫�祭��� 㧫�� ���⨦����� ������⢠ R
  㯠����� �㯥�㧫� node 
*/
size_t mda_update( size_t node, size_t h, size_t hh, size_t n, size_t *IA,
  size_t *JA, size_t *L, size_t *D, size_t *P, size_t *IP)
{
  size_t i, j, k, l, t, r = n, d = D[h] - hh + h;
  /* 㯠����� 㧫� node */
  for(k = j = IA[node]; (j < IA[node + 1]) && (IP[i = JA[j]] > h); j++)
  {
    if(IP[i] < hh) continue;
    if(k < j)
    {
      JA[k] = i;
      JA[j] = node;
    }
    k++;
    heap_change(IP[i], d + L[i], hh, n, D, P, IP);
    L[i] = r;
    r = i;
  }
  /* 㯠����� �㯥�㧫��, ᬥ���� � node */
  for(t = node, l = L[node]; l != node; l = L[t])
  {
    for(k = j = IA[l]; (j < IA[l + 1]) && ((i = JA[j]) != l) && (IP[i] >= h); j++)
    {
      if(IP[i] < hh) continue;
      if(k < j)
      {
        JA[k] = i;
        JA[j] = l;
      }
      k++;
      heap_change(IP[i], d + L[i], hh, n, D, P, IP);
      L[i] = r;
      r = i;
    }
    if(k == IA[l]) L[t] = L[l]; else t = l;
  }
  return r;
}

/* 㯠����� ���᪫�祭��� 㧫�� ���⨦����� ������⢠ R */
void mda_pack( size_t node, size_t r, size_t m, size_t n, size_t *IA, size_t *JA,
  size_t *M, size_t *L)
{
  size_t i, j, k;
  for( ; r != n; r = L[r])
  {
    for(k = j = IA[r]; (j < IA[r + 1]) && ((i = JA[j]) != n); j++)
    {
      if(M[i] == m) continue;
      if(k < j) JA[k] = i;
      k++;
    }
    JA[k] = node;
    if(k + 1 < j) JA[k + 1] = n;
  }
}

size_t mda_iterate( size_t h, size_t m, size_t n, size_t *IA, size_t *JA,
  size_t *P, size_t *IP, size_t *D, size_t *M, size_t *L)
{
  size_t node = P[n - 1], hh, r;
  heap_del_min(n - 1, h, n, D, P, IP);
  m++;
  r = mda_reach(node, h, m, n, IA, JA, M, L, IP);
  hh = mda_process(r, node, h, m, n, IA, JA, M, L, D, P, IP);
  r = mda_update(node, h, hh, n, IA, JA, L, D, P, IP);
  mda_pack(node, r, m, n, IA, JA, M, L);
  return hh;
}

size_t mda_order(size_t n, size_t *IA, size_t *JA, size_t *M, size_t *L,
  size_t *D, size_t *P, size_t *IP)
{
  size_t node, r, hh, h = 0, size = 0, m = 0;
  memset(M, 0, n*sizeof(size_t));
  while(h < n)
  {
    node = P[n - 1];
    heap_del_min(n - 1, h, n, D, P, IP);
    r = mda_reach(node, h, ++m, n, IA, JA, M, L, IP);
    hh = mda_process(r, node, h, m, n, IA, JA, M, L, D, P, IP);
    r = mda_update(node, h, hh, n, IA, JA, L, D, P, IP);
    mda_pack(node, r, m, n, IA, JA, M, L);
    m += D[h];
    size += (2*D[h] + h - hh + 1)*(hh - h)/2;
    h = hh;
  }
  return size;
}

/* ������ ����檮�� */

void mda_chol_symb(size_t n, size_t unz, size_t *IS, size_t *JS, size_t *IU,
  size_t *JU, size_t *M, size_t *L, size_t *D, size_t *IP)
{
  size_t i, j, k, l, t, min;

  /* ��ନ஢���� IU */

  IU[0] = 0;

  for(i = 0; i < n; i++) 
    IU[i + 1] = IU[i] + D[i];

  /* ����⠭���� ��ப � �⮫�殢 */

  for(i = 0; i < n; i++)
  {
    for(j = IS[i]; j < IS[i + 1]; j++)
    {
      k = JS[j];
      JU[IU[NL_MIN(IP[i], IP[k])]] = NL_MAX(IP[i], IP[k]);
      IU[NL_MIN(IP[i], IP[k])]++;
    }
  }

  for(i = 0; i < n; i++) 
    L[i] = n;

  /* ��������᪮� ࠧ������� */

  for(i = t = 0; i < n; i++)
  {
    M[i] = ++unz;
    min = n;
    for(j = t; j < IU[i]; j++)
    {
      k = JU[j];
      M[k] = unz;
      if (k < min) min = k;
    }
    IU[i] = t;
    t = j;
    for (l = L[i]; l != n; l = L[l])
    {
      for (j = IU[l]; j < IU[l + 1]; j++)
      {
        k = JU[j];
        if (M[k] == unz) continue;
        M[k] = unz;
        if (k < min) min = k;
        JU[t++] = k;
      }
    }
    if (min == n) continue;
    l = L[min];
    L[min] = i;
    L[i] = l;
  }

}


void mda_chol_num(size_t n, size_t *IS, size_t *JS, size_t *IU, size_t *JU,
  size_t *P, double *SN, double *SD, double *UN, double *UD, size_t *xwork)
{
  size_t i, j, k, l, t, imin, imax, *p, *M, *L;
  double m;

  M = xwork;
  L = xwork + n;

  memcpy(M, IU, n*sizeof(size_t));
  for(i = 0; i < n; i++) 
    L[i] = n;

  for(i = 0; i < n; i++)
  {
    /* ���樠������ i-� ��ப� ������ U 
       ᮮ⢥�����騬� ���祭�ﬨ �� ������ S */

printf("%d-� �����:\n", i);
sp_print_list(IU, JU, UN, n, n, NULL, NULL);
nl_dvector_print(UD, n, NULL);

    UD[i] = SD[P[i]];

    for (k = IU[i]; k < IU[i + 1]; k++)
    {
      j = JU[k];
      imin = NL_MIN(P[i], P[j]);
      imax = NL_MAX(P[i], P[j]);

      if (binary_search(imax, IS[imin], IS[imin + 1], JS)) 
         UD[j] = SD[imax];
      else
         UD[j] = 0;
    }

    for (l = L[i]; l != n; l = t)
    {
      for (j = M[l], m = UN[j]*UD[l]; j < IU[l + 1]; j++)
      {
        k = JU[j];
        UD[k] -= m*UN[j];
      }
      UN[M[l]] = m;
printf("UN[M[l]] = %d\n", m);
      t = L[l];
      if (++M[l] == IU[l + 1]) continue;
      k = JU[M[l]];
      L[l] = L[k];
      L[k] = l;
    }

    UD[i] = 1/UD[i];
    if (IU[i] == IU[i + 1]) continue;
    k = JU[IU[i]];
    t = L[k];
    L[k] = i;
    L[i] = t;
    for (j = IU[i]; j < IU[i + 1]; j++)
    {
      k = JU[j];
      UN[j] = UD[k];
    }
  }
printf("��室\n");
sp_print_list(IU, JU, UN, n, n, NULL, NULL);
nl_dvector_print(UD, n, NULL);
}







void mda_chol_solve(size_t n, size_t *IU, size_t *JU, size_t *P, double *UN,
  double *UD, double *b, double *x)
{
  size_t i, k, j;

  memcpy(x, b, n*sizeof(double));

  /* ��אַ� 室 */

  for(i = j = 0; i < n; i++)
  {
    while(j < IU[i + 1])
    {
      k = JU[j];
      x[P[k]] -= UN[j]*x[P[i]];
      j++;
    }
    x[P[i]] *= UD[i];
  }

  /* ����� 室 */

  for(i = n - 1, j = IU[n]; i > 0; i--)
  {
    while(j >= IU[i - 1] + 1)
    {
      k = JU[j - 1];
      x[P[i - 1]] -= UN[j - 1]*x[P[k]];
      j--;
    }
  }
}

