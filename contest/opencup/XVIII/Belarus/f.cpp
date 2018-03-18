#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 16
#define M 222
int n , m , x[ M ] , y[ M ];
LL fac[ N ] , dp[ 1 << N ];
bool ok[ 1 << N ];
int main(){
  fac[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ )
    fac[ i ] = fac[ i - 1 ] * i;
  cin >> n >> m;
  for( int i = 0 ; i < m ; i ++ ){
    cin >> x[ i ] >> y[ i ];
    x[ i ] --;
    y[ i ] --;
  }
  for( int i = 0 ; i < (1 << n) ; i ++ ){
    int vl = i;
    for( int j = 0 ; j < m ; j ++ )
      if( ((vl >> x[ j ]) & 1) == 1 and
          ((vl >> y[ j ]) & 1) == 0 ){
        vl ^= (1 << x[ j ]);
        vl ^= (1 << y[ j ]);
      }
    ok[ i ] = true;
    for( int j = 1 ; j < n ; j ++ )
      if( ((vl >> j) & 1) == 0 and
          ((vl >> (j - 1)) & 1) == 1 ){
        ok[ i ] = false;
        break;
      }
  }
  dp[ 0 ] = 1;
  for( int i = 1 ; i < (1 << n) ; i ++ ){
    if( not ok[ i ] ) continue;
    for( int j = 0 ; j < n ; j ++ )
      if( (i >> j) & 1 )
        dp[ i ] += dp[ i ^ (1 << j) ];
  }
  LL ans = fac[ n ] - dp[ (1 << n) - 1 ];
  printf( "%lld\n" , ans );
}
