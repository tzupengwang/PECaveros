/*
Lucas’ Theorem:
	For non-negative integer n,m and prime P,
	C(m,n) mod P = C(m/M,n/M) * C(m%M,n%M) mod P
	= mult_i ( C(m_i,n_i) )
	where m_i is the i-th digit of m in base P.

Pick’s Theorem
  A = i + b/2 - 1

Kirchhoff's theorem
  A_{ii} = deg(i), A_{ij} = (i,j) \in E ? -1 : 0
  Deleting any one row, one column, and cal the det(A)
*/
