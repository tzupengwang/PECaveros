#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
const LL inf = 1e16;
int n , m , res[ N ] , fr[ N ];
LL dp[ N ] , bl[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &res[ i ] );
  for( int i = n ; i >= 1 ; i -- ){
    if( res[ i ] )
      dp[ i ] = 0 , fr[ i ] = i;
    else{
      if( i * 2 + 1 <= n and dp[ i * 2 + 1 ] < dp[ i * 2 ] ){
        dp[ i ] = dp[ i * 2 + 1 ] + 1;
        fr[ i ] = fr[ i * 2 + 1 ];
      }else if( i * 2 <= n ){
        dp[ i ] = dp[ i * 2 ] + 1;
        fr[ i ] = fr[ i * 2 ];
      }else{
        dp[ i ] = inf;
        fr[ i ] = -1;
      }
    }
  }
}
int cur;
LL ans;
int cost( int who , int dlt ){
  int new_bl = bl[ who ] + dlt;
  if( abs( new_bl ) > abs( bl[ who ] ) ) return 1;
  return -1;
}
void climb_up( int now , int lca , int dlt ){
  for( int i = now ; ; i >>= 1 ){
    if( res[ i ] ){
      dp[ i ] = 0 , fr[ i ] = i;
      if( i > lca )
        bl[ i ] += dlt;
    }else{
      if( i > lca )
        bl[ i ] += dlt;
      if( i * 2 + 1 <= n and
          dp[ i * 2 + 1 ] + cost( i * 2 + 1 , -1 ) <
          dp[ i * 2     ] + cost( i * 2     , -1 ) ){
        dp[ i ] = dp[ i * 2 + 1 ] + cost( i * 2 + 1 , -1 );
        fr[ i ] = fr[ i * 2 + 1 ];
      }else if( i * 2 <= n ){
        dp[ i ] = dp[ i * 2 ] + cost( i * 2 , -1 );
        fr[ i ] = fr[ i * 2 ];
      }else{
        dp[ i ] = inf;
        fr[ i ] = -1;
      }
    }
    if( i == 1 ) break;
  }
}
void go(){
  LL bst = inf; int take_fr = -1 , lca = -1;
  for( int prt = cur , cst = 0 ; prt ; prt >>= 1 ){
    if( cst + dp[ prt ] < bst ){
      bst = cst + dp[ prt ];
      take_fr = fr[ prt ];
      lca = prt;
    }
    cst += cost( prt , +1 );
  }
  assert( take_fr != -1 );
  ans += bst;
  res[ take_fr ] --;
  climb_up( cur     , lca , +1 );
  climb_up( take_fr , lca , -1 );
}
void solve(){
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d" , &cur );
    go();
    printf( "%lld%c" , ans , " \n"[ i + 1 == m ] );
  }
}
int main(){
#ifndef LOCAL
  freopen( "mole.in" , "r" , stdin );
  freopen( "mole.out" , "w" , stdout );
#endif
  init();
  solve();
}
