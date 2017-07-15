#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
LL n , q , w[ N ] , s[ N ] , t[ N ];
vector<int> qq[ N ];
void init(){
  scanf( "%lld%lld" , &n , &q );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%lld" , &w[ i ] );
    w[ i ] += w[ i - 1 ];
  }
  for( int i = 0 ; i < q ; i ++ ){
    scanf( "%lld%lld" , &s[ i ] , &t[ i ] );
    s[ i ] ++;
    t[ i ] ++;
    qq[ s[ i ] ].push_back( i );
    qq[ t[ i ] ].push_back( i );
  }
}
LL dist( int i1 , int i2 ){
  if( i1 <= i2 ) return w[ i2 - 1 ] - w[ i1 - 1 ];
  return w[ n ] - w[ i1 - 1 ] + w[ i2 - 1 ];
}
LL cal(){
  LL ans1 = 0 , ans2 = 0;
  for( int i = 0 ; i < q ; i ++ ){
    ans1 += dist( s[ i ] , t[ i ] );
    ans2 += dist( t[ i ] , s[ i ] );
  }
  return min( ans1 , ans2 );
}
LL cst[ N ];
void solve(){
  LL ans = cal() , tans = 0;
  // 1 <-----> 1
  for( int i = 0 ; i < q ; i ++ ){
    if( s[ i ] == 1 or t[ i ] == 1 )
      cst[ i ] = min( dist( s[ i ] , t[ i ] ) , dist( t[ i ] , s[ i ] ) );
    else if( s[ i ] < t[ i ] )
      cst[ i ] = dist( s[ i ] , t[ i ] );
    else
      cst[ i ] = dist( t[ i ] , s[ i ] );
    tans += cst[ i ];
  }
  //cout << ans << endl;
  //cout << tans << endl;
  ans = min( ans , tans );
  for( int i = 1 ; i < n ; i ++ ){
    // i <-----> i
    for( int id : qq[ i ] ){
      tans -= cst[ id ];
      if( s[ id ] == i )
        cst[ id ] = dist( t[ id ] , s[ id ] );
      else
        cst[ id ] = dist( s[ id ] , t[ id ] );
      tans += cst[ id ];
    }
    for( int id : qq[ i + 1 ] ){
      tans -= cst[ id ];
      cst[ id ] = min( dist( s[ id ] , t[ id ] ) ,
                       dist( t[ id ] , s[ id ] ) );
      tans += cst[ id ];
    }
    printf( "%d\n" , i + 1 );
    for( int j = 0 ; j < q ; j ++ )
      printf( "%lld%c" , cst[ j ] , " \n"[ j + 1 == q ] );
    ans = min( ans , tans );
  }
  cout << ans << endl;
}
int main(){
  init();
  solve();
}
