#include <bits/stdc++.h>
using namespace std;
#define N 11
typedef long long LL;
vector< int > pre[ N ];
void build(){
  for( int i = 0 ; i < N ; i ++ ){
    pre[ i ].resize( N );
    for( int j = 0 ; j < N ; j ++ )
      pre[ i ][ j ] = 0;
  }
  pre[ 0 ][ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ )
    for( int j = 0 ; j + 1 < N ; j ++ ){
      pre[ i ][ j ] += pre[ i - 1 ][ j ];
      if( j )
        pre[ i ][ j ] -= pre[ i - 1 ][ j - 1 ];
    }
}
//LL ans[ N ] = { 0 , 1 , 2 , 5 , 14 };
LL ans[ N ] = { 1 , 1 , 2 , 5 , 14 , 43 , 140 , 474 , 1648 , 5839 };
vector< pair<int,int> > vv;
map< vector< int > , LL > cnt;
int now , all , hf , id[ N ][ N ];
vector< int > kk;
vector< int > poly( int i , int j ){
  vector< int > u( now + 1 , 0 );
  for( int k = 0 ; k < N ; k ++ )
    if( pre[ j ][ k ] && i + k <= now )
      u[ i + k ] += pre[ j ][ k ];
  return u;
}
void cal(){
  vector< int > res( now + 1 , 0 );
  for( int i = 0 ; i < hf ; i ++ ){
    if( kk[ i ] == 0 ) continue;
    vector< int > tmp = poly( vv[ i ].first , vv[ i ].second );
    for( int j = 0 ; j <= now ; j ++ )
      res[ j ] += tmp[ j ];
  }
  cnt[ res ] ++;
}
void cal2(){
  vector< int > res( now + 1 , 0 );
  for( int i = 0 ; i < all - hf ; i ++ ){
    if( kk[ i ] == 0 ) continue;
    vector< int > tmp = poly( vv[ i + hf ].first , vv[ i + hf ].second );
    for( int j = 0 ; j <= now ; j ++ )
      res[ j ] += tmp[ j ];
  }
  vector< int > need( now + 1 , 0 );
  for( int i = 0 ; i <= now ; i ++ )
    need[ i ] = ( i == 0 ? 1 : 0 ) - res[ i ];
  //for( int i = 0 ; i <= now ; i ++ )
    //printf( "%d " , res[ i ] );
  //puts( "" );
  //for( int i = 0 ; i <= now ; i ++ )
    //printf( "%d " , need[ i ] );
  //puts( "" );
  //printf( "%d\n" , cnt[ need ] );
  //puts( "" );
  ans[ now ] += cnt[ need ];
}
void go( int tnow ){
  if( tnow == hf ){
    cal();
    return;
  }
  for( int i = 0 ; i < 2 ; i ++ ){
    kk[ tnow ] = i;
    go( tnow + 1 );
  }
}
void go2( int tnow ){
  if( tnow == all ){
    cal2();
    return;
  }
  for( int i = 0 ; i < 2 ; i ++ ){
    kk[ tnow - hf ] = i;
    go2( tnow + 1 );
  }
}
inline LL find_ans( int x ){
  now = x;
  vv.clear();
  cnt.clear();
  for( int i = 0 ; i <= x ; i ++ )
    for( int j = 0 ; j + i <= x ; j ++ )
      vv.push_back( { i , j } );
  all = (int)vv.size();
  hf = all / 2;
  kk.resize( hf );
  go( 0 );
  kk.resize( all - hf );
  go2( hf );
  for( int i = 0 ; i < x ; i ++ )
    ans[ now ] -= ans[ i ];
  return ans[ now ];
}
int main(){
  //build();
  //for( int i = 1 ; i < 10 ; i ++ ){
    //ans[ i ] = 0;
    //ans[ i ] = find_ans( i );
    //printf( "%d %lld\n" , i , ans[ i ] );
  //}
#ifdef ONLINE_JUDGE
  freopen( "immetric.in" , "r" , stdin );
  freopen( "immetric.out" , "w" , stdout );
#endif
  for( int i = 1 , x ;  ; i ++ ){
    scanf( "%d" , &x );
    if( x == 0 ) break;
    printf( "Case #%d: %lld\n" , i , ans[ x ] );
  }
}
