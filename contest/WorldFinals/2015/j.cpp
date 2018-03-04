#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
template<LL P, LL root, int MAXN>
struct NTT{
  static LL bigmod(LL a, LL b){
    LL res = 1;
    for( LL bs = a ; b ; b >>= 1 , bs = (bs * bs) % P ){
      if( b & 1 ) res = (res * bs) % P;
    }
    return res;
  }
  static LL inv( LL a , LL b ){
    if( a == 1 ) return 1;
    return (((LL)(a - inv(b % a, a)) * b + 1)/a) % b;
  }
  LL omega[MAXN + 1];
  NTT(){
    omega[0] = 1;
    LL r = bigmod(root, (P - 1) / MAXN);
    for( int i = 1 ; i <= MAXN ; i ++ )
      omega[ i ] = (omega[i - 1] * r) % P;
  }
  void tran(int n , LL a[], bool inv_ntt = false ){
    int basic = MAXN / n;
    int theta = basic;
    for( int m = n ; m >= 2 ; m >>= 1 ){
      int mh = m >> 1;
      for( int i = 0 ; i < mh ; i ++ ){
        LL w = omega[i * theta % MAXN];
        for( int j = i ; j < n ; j += m ){
          int k = j + mh;
          LL x = a[ j ] - a[ k ];
          if( x < 0 ) x += P;
          a[ j ] += a[ k ];
          if( a[ j ] > P ) a[ j ] -= P;
          a[ k ] = (w * x) % P;
        }
      }
      theta = (theta * 2) % MAXN;
    }
    {
      int i = 0;
      for( int j = 1 ; j < n - 1 ; j ++ ){
        for( int k = n >> 1 ; k > (i ^= k) ; k >>= 1);
        if( j < i ) swap(a[i], a[j]);
      }
    }
    if(inv_ntt){
      LL ni = inv(n, P);
      reverse(a + 1 , a + n);
      for( int i = 0 ; i < n ; i ++ )
        a[i] = (a[i] * ni) % P;
    }
  }
};
const LL P = 2013265921 , root = 31;
const int MAXN = 1048576;

NTT<P, root, MAXN> ntt;

#define N (1 << 20)
LL d[ N ];

void build(){
  for( int i = 1 ; i <= 500000 ; i ++ )
    for( int j = i ; j <= 500000 ; j += i )
      d[ j ] ++;
  ntt.tran( N , d );
  for( int i = 0 ; i < N ; i ++ )
    d[ i ] = (d[ i ] * d[ i ]) % P;
  ntt.tran( N , d , 1 );
}
int q;
int main(){
  build();
  scanf( "%d" , &q );
  while( q -- ){
    int lo , hi;
    scanf( "%d%d" , &lo , &hi );
    int ans = max_element( d + lo , d + hi + 1 ) - d;
    printf( "%d %lld\n" , ans , d[ ans ] );
  }
}
