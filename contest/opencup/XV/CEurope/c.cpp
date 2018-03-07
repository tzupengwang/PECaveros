#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
#define M 16
const LL inf = 10000000000000000LL;
int n , m , di , v[ M ];
LL dp[ 1 << M ] , dp2[ 1 << M ];
void upd(){
  for( int i = 0 ; i < (1 << m) ; i ++ )
    dp2[ i ] = dp[ i ];
  for( int i = 0 ; i < (1 << m) ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      if( (i >>j) & 1 ) continue;
      dp2[ i | (1 << j) ] = min( dp2[ i | (1 << j) ] ,
                                 dp2[ i ] + v[ j ] );
    }
  for( int i = 0 ; i < (1 << m) ; i ++ )
    dp[ i ] = min( dp[ i ] ,
                   dp2[ i ] + di );
}
int main(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i < (1 << m) ; i ++ )
    dp[ i ] = inf;
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &di );
    for( int j = 0 ; j < m ; j ++ )
      scanf( "%d" , &v[ j ] );
    upd();
  }
  printf( "%lld\n" , dp[ (1 << m) - 1 ] );
}
