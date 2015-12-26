#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define K 20
typedef long long ll;
ll dp[ K ][ 10 ][ 3 ] , tsum[ K ];
// 0 <<<<<
// 1 =====
// 2 >>>>>
void build(){
  for( int i = 0 ; i < 10 ; i ++ )
    dp[ 0 ][ i ][ 1 ] = 1;
  for( int i = 1 ; i < K ; i ++ )
    for( int j = 0 ; j < 10 ; j ++ )
      for( int k = 0 ; k < 3 ; k ++ ){
        if( dp[ i - 1 ][ j ][ k ] == 0 ) continue;
        int vl = dp[ i - 1 ][ j ][ k ];
        for( int nxt = 0 ; nxt < 10 ; nxt ++ ){
          if( k == 0 ){
            if( nxt <= j )
              dp[ i ][ nxt ][ k ] += vl;
          }else if( k == 1 ){
            if( nxt == j ){
              dp[ i ][ nxt ][ k ] += vl;
            }else if( nxt < j ){
              dp[ i ][ nxt ][ 0 ] += vl;
            }else if( nxt > j ){
              dp[ i ][ nxt ][ 2 ] += vl;
            }
          }else if( k == 2 ){
            if( nxt >= j )
              dp[ i ][ nxt ][ k ] += vl;
          }
        }
      }
  for( int i = 0 ; i < K ; i ++ )
    for( int j = 1 ; j < 10 ; j ++ )
      for( int k = 0 ; k < 3 ; k ++ )
        tsum[ i ] += dp[ i ][ j ][ k ];
//  for( int i = 0 ; i < 3 ; i ++ )
//    for( int j = 0 ; j < 10 ; j ++ )
//      for( int k = 0 ; k < 3 ; k ++ )
//        printf( "%d %d %d : %lld\n" , i , j , k , dp[ i ][ j ][ k ] );
//  exit( 0 );
}
int bt[ K ] , by;
ll tans;
// 0 <<<<
// 1 ====
// 2 >>>>
void DFS( int now , int ty , int pre , bool flag ){
  //printf( "===== %d %d %d\n" , now , ty , pre );
  if( now == -1 ){
    tans ++;
    return;
  }
  if( ty == 0 ){
    for( int i = pre ; i < bt[ now ] ; i ++ )
      if( now == 0 ) tans ++;
      else{
        tans += dp[ now ][ i ][ 0 ];
        tans += dp[ now ][ i ][ 1 ];
      }
  }else if( ty == 2 ){
    for( int i = min( pre , bt[ now ] - 1 ) ; i >= 0 ; i -- )
      if( now == 0 ) tans ++;
      else{
        tans += dp[ now ][ i ][ 2 ];
        tans += dp[ now ][ i ][ 1 ];
      }
  }else if( !flag ){
    for( int i = 0 ; i < bt[ now ] ; i ++ ){
      if( now == 0 ) tans ++;
      else{
        if( i >= pre ) tans += dp[ now ][ i ][ 0 ];
        if( i <= pre ) tans += dp[ now ][ i ][ 2 ];
        tans += dp[ now ][ i ][ 1 ];
      }
    }
  }
// 0 <<<<
// 1 ====
// 2 >>>>
  if( ty == 0 ){
    if( bt[ now ] >= pre )
      DFS( now - 1 , ty , bt[ now ] , false );
  }else if( ty == 2 ){
    if( bt[ now ] <= pre )
      DFS( now - 1 , ty , bt[ now ] , false );
  }else{
    if( bt[ now ] == pre )
      DFS( now - 1 , 1 , bt[ now ] , false );
    else if( bt[ now ] < pre )
      DFS( now - 1 , 2 , bt[ now ] , false );
    else
      DFS( now - 1 , 0 , bt[ now ] , false );
  }
}
ll query( ll tx ){
  if( tx == 0 ) return 0;
  ll tmp = tx; by = 0;
  while( tmp ){
    bt[ by ++ ] = tmp % 10;
    tmp /= 10;
  }
  tans = 0;
  DFS( by - 1 , 1 , bt[ by - 1 ] , true );
  for( int i = 1 ; i < bt[ by - 1 ] ; i ++ )
    for( int k = 0 ; k < 3 ; k ++ )
      tans += dp[ by - 1 ][ i ][ k ];
  for( int i = by - 2 ; i >= 0 ; i -- )
    tans += tsum[ i ];
//  if( by > 1 ){
//    for( int i = 0 ; i < 10 ; i ++ )
//      for( int j = 0 ; j < 3 ; j ++ )
//        tans += dp[ by - 2 ][ i ][ j ];
//  }
//  printf( "============== %lld %lld\n" , tx , tans );
  return tans;
}
int main(){
  build();
  int _; scanf( "%d" , &_ );
  while( _ -- ){
    ll ql , qr;
    scanf( "%lld%lld" , &ql , &qr );
    printf( "%lld\n" , query( qr ) - query( ql - 1 ) );
  }
}
