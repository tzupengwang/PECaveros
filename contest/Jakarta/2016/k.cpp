#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 32768
typedef long long LL;
const int mod = 1000000007;
const int MAXN = N+10;
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub( int a , int b ){
  a -= b;
  return a < 0 ? a + mod : a;
}
int mpow( int a , int b ){
  if( !b ) return 1;
  int ret = mpow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
inline int inv( int x ) {
  return mpow( x , mod-2 );
}
inline void xor_fwt( int x[ MAXN ] , int n , bool tinv=0 ) {
  for( int d = 1 ; d < n ; d <<= 1 ) {
    int d2 = d<<1;
    for( int s = 0 ; s < n ; s += d2 ) {
      for( int i = s , j = s+d ; i < s+d ; i++, j++ ){
        int ta = x[ i ] , tb = x[ j ];
        x[ i ] = add(ta, tb);
        x[ j ] = sub(ta, tb);
      }
    }
  }
  if( tinv )
    for( int i = 0 ; i < n ; i++ ) {
      x[i] = mul(x[i], inv(n));
    }
}
inline void or_fwt( int x[ MAXN ] , int n , bool tinv=0 ) {
  for( int d = 1 ; d < n ; d <<= 1 ) {
    int d2 = d<<1;
    for( int s = 0 ; s < n ; s += d2 ) {
      for( int i = s , j = s+d ; i < s+d ; i++, j++ ){
        int ta = x[ i ] , tb = x[ j ];
        if (not tinv) {
          x[ i ] = ta;
          x[ j ] = add(ta, tb);
        } else {
          x[ i ] = ta;
          x[ j ] = sub(tb, ta);
        }
      }
    }
  }
  if( tinv )
    for( int i = 0 ; i < n ; i++ ) {
      x[i] = mul(x[i], inv(n));
    }
}

int tA[MAXN], tB[MAXN];

void OR(int C[MAXN], int A[MAXN], int B[MAXN], int n) {
  fill(C, C+n, 0);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      C[i|j] = add(C[i|j], mul(A[i], B[j]));
    }
  return;
  for (int i = 0; i < n; ++i) {
    tA[i] = A[i];
    tB[i] = B[i];
  }
  or_fwt(tA, n, 0);
  or_fwt(tB, n, 0);
  for (int i = 0; i < n; ++i) {
    C[i] = mul(tA[i], tB[i]);
  }
  or_fwt(C, n, 1);
}

void XOR(int C[MAXN], int A[MAXN], int B[MAXN], int n) {
  fill(C, C+n, 0);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      C[i^j] = add(C[i^j], mul(A[i], B[j]));
    }
  return;
  for (int i = 0; i < n; ++i) {
    tA[i] = A[i];
    tB[i] = B[i];
  }
  xor_fwt(tA, n, 0);
  xor_fwt(tB, n, 0);
  for (int i = 0; i < n; ++i) {
    C[i] = mul(tA[i], tB[i]);
  }
  xor_fwt(C, n, 1);
}

void f(int C[MAXN], int A[MAXN], int B[MAXN], int n) {
  static int C1[MAXN], C2[MAXN], D[MAXN];
  //for (int U = 0; U < n; ++U) {
    //for (int S = 0; S < n; ++S) if ((S^U) == (S|U))
      //C[S|U] = add(C[S|U], mul(A[S], B[U]));
  //}
  //return;
  OR(C1, A, B, n);
  XOR(C2, A, B, n);
  for (int s = 0; s < n; ++s) {
    D[s] = C2[s];
    printf("S %d %d %d\n", s, C1[s], C2[s]);
  }
  for (int i = 1; i < n; i <<= 1) {
    for (int s = 0; s < n; ++s) if (s&i)
      D[s] = add(D[s], D[s^i]);
  }
  for (int s = 0; s < n; ++s) {
    C[s] = add(sub(C1[s], D[s]), C2[s]);
  }
}

#define K 3
int fac[ K ] , iv[ K ];
void build(){
  fac[ 0 ] = iv[ 0 ] = 1;
  for( int i = 1 ; i < K ; i ++ ){
    fac[ i ] = mul( fac[ i - 1 ] , i );
    iv[ i ] = mpow( fac[ i ] , mod - 2 );
  }
}
int n , a[ N ] , cnt[ N ] , _cs;
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%d" , &a[ i ] );
    cnt[ a[ i ] ] ++;
  }
}
int dp[ N ];
void solve(){
  dp[0] = 1;
  for (int i = 1; i < N; ++i) {
    int lb = (i&-i);
    int R = (i^lb);
    dp[i] = 0;

    for (int cmb = R; cmb; cmb = (cmb-1) & R) {
      dp[i] = add(dp[i], mul(cnt[cmb|lb], dp[R^cmb]));
    }
    dp[i] = add(dp[i], mul(cnt[lb], dp[R]));
  }

  int ans = 0;
  for (int i = 1; i < N; ++i) ans = add(ans, dp[i]);
  ans = sub(ans, n);
  printf( "Case #%d: %d\n" , ++ _cs , ans );
  for( int i = 0 ; i < n ; i ++ )
    cnt[ a[ i ] ] = 0;
}
int main(){
  //build();
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
