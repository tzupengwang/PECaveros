#include <bits/stdc++.h>
using namespace std;
#define N 111
int num[ 10 ];
inline int OR( vector<int> v ){
  int ret = 0;
  for( int x : v ) ret |= ( 1 << x );
  return ret;
}
void build(){
  num[ 0 ] = OR( { 0 , 1 , 2 , 4 , 5 , 6 } );
  num[ 1 ] = OR( { 2 , 5 } );
  num[ 2 ] = OR( { 0 , 2 , 3 , 4 , 6 } );
  num[ 3 ] = OR( { 0 , 2 , 3 , 5 , 6 } );
  num[ 4 ] = OR( { 1 , 2 , 3 , 5 } );
  num[ 5 ] = OR( { 0 , 1 , 3 , 5 , 6 } );
  num[ 6 ] = OR( { 0 , 1 , 3 , 4 , 5 , 6 } );
  num[ 7 ] = OR( { 0 , 2 , 5 } );
  num[ 8 ] = OR( { 0 , 1 , 2 , 3 , 4 , 5 , 6 } );
  num[ 9 ] = OR( { 0 , 1 , 2 , 3 , 5 , 6 } );
}
int n , bt[ N ][ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= 9 ; i ++ )
    for( int j = 1 ; j <= n + ( 1 - i % 2 ) ; j ++ )
      scanf( "%d" , &bt[ i ][ j ] );
}
bool dp[ N ][ 1 << 4 ][ 2 ];
bool gt[ N ][ 1 << 4 ][ 2 ];
int   a[ N ][ 1 << 4 ][ 2 ];
int   b[ N ][ 1 << 4 ][ 2 ];
int   c[ N ][ 1 << 4 ][ 2 ];
int  fx[ N ][ 1 << 4 ][ 2 ];
int  fm[ N ][ 1 << 4 ][ 2 ];
inline int bit( int xn , int ii ){
  if( ii % 3 == 0 ) return bt[ ii / 3 * 2 + 1 ][ xn ];
  return bt[ ii / 3 * 2 + 2 ][ xn + ii % 3 - 1 ];
}
int bvl[ N ];
bool DP( int nn , int xmsk , int mr ){
  if( gt[ nn ][ xmsk ][ mr ] )
    return dp[ nn ][ xmsk ][ mr ];
  gt[ nn ][ xmsk ][ mr ] = true;
  if( nn == 0 ){
    if( mr > 0 ) return dp[ nn ][ xmsk ][ mr ] = false;
    int tmp = 0;
    if( ( xmsk >> 0 ) & 1 ) tmp |= ( 1 << 1 );
    if( ( xmsk >> 1 ) & 1 ) tmp |= ( 1 << 4 );
    if( ( xmsk >> 2 ) & 1 ) tmp |= ( 1 << 7 );
    if( ( xmsk >> 3 ) & 1 ) tmp |= ( 1 << 10 );
    int res = bvl[ 1 ] & (~tmp);
    for( int i = 1 ; i < 11 ; i += 3 )
      if( ( res >> i ) & 1 )
         return dp[ nn ][ xmsk ][ mr ] = false;
    return dp[ nn ][ xmsk ][ mr ] = true;
  }
  int ta = ( bvl[ nn ] >> 0 ) & ( ( 1 << 7 ) - 1 );
  int tb = ( bvl[ nn ] >> 3 ) & ( ( 1 << 7 ) - 1 );
  int tc = ( bvl[ nn ] >> 6 ) & ( ( 1 << 7 ) - 1 );
  int ga = 0 , gb = 0 , gc = 0;
  if( ( xmsk >> 0 ) & 1 )
    ga |= ( 1 << 2 );
  if( ( xmsk >> 1 ) & 1 )
    ga |= ( 1 << 5 ), gb |= ( 1 << 2 );
  if( ( xmsk >> 2 ) & 1 )
    gb |= ( 1 << 5 ), gc |= ( 1 << 2 );
  if( ( xmsk >> 3 ) & 1 )
    gc |= ( 1 << 5 );
  for( int aa = 0 ; aa < 10 ; aa ++ )
    for( int bb = 0 ; bb < 10 ; bb ++ ){
      if( ( num[ aa ] & ta ) != num[ aa ] ) continue;
      if( ( num[ bb ] & tb ) != num[ bb ] ) continue;
      int cc = ( aa + bb + mr ) % 10;
      int car = ( aa + bb + mr ) / 10;
      if( ( num[ cc ] & tc ) != num[ cc ] ) continue;
      int resa = ta & ( ~( num[ aa ] | ga ) );
      int resb = tb & ( ~( num[ bb ] | gb ) );
      int resc = tc & ( ~( num[ cc ] | gc ) );
      int res = ( ( resa << 0 ) | ( ( 1 << 13 ) - 1 - ( ( ( 1 << 7 ) - 1 ) << 0 ) ) ) &
                ( ( resb << 3 ) | ( ( 1 << 13 ) - 1 - ( ( ( 1 << 7 ) - 1 ) << 3 ) ) ) &
                ( ( resc << 6 ) | ( ( 1 << 13 ) - 1 - ( ( ( 1 << 7 ) - 1 ) << 6 ) ) );
      bool okay = true;
      int nmsk = 0;
      for( int i = 0 ; i < 13 ; i ++ ){
        if( i % 3 == 1 ){
          if( ( ( res >> i ) & 1 ) == 0 )
            nmsk |= ( 1 << ( i / 3 ) );
        }else if( ( res >> i ) & 1 ){
          okay = false;
          break;
        }
      }
      if( !okay ) continue;
      if( DP( nn - 1 , nmsk , car ) ){
        //printf( "%d %d %d %d %d %d\n" , res , resa , resb , resc , res , nmsk );
        dp[ nn ][ xmsk ][ mr ] = true;
        a[ nn ][ xmsk ][ mr ] = aa;
        b[ nn ][ xmsk ][ mr ] = bb;
        c[ nn ][ xmsk ][ mr ] = cc;
        fx[ nn ][ xmsk ][ mr ] = nmsk;
        fm[ nn ][ xmsk ][ mr ] = car;
        return true;
      }
    }
  return false;
}
string a1 = "" , a2 = "" , a3 = "";
void go( int nn , int xmsk , int mr ){
  if( nn == 0 ) return;
  go( nn - 1 , fx[ nn ][ xmsk ][ mr ] , fm[ nn ][ xmsk ][ mr ] );
  a1 += (char)( '0' + a[ nn ][ xmsk ][ mr ] );
  a2 += (char)( '0' + b[ nn ][ xmsk ][ mr ] );
  a3 += (char)( '0' + c[ nn ][ xmsk ][ mr ] );
}
void find_ans(){
  go( n , 0 , 0 );
  printf( "%s\n%s\n%s\n" , a1.c_str() , a2.c_str() , a3.c_str() );
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 0 ; j < 13 ; j ++ )
      if( bit( i , j ) )
        bvl[ i ] |= ( 1 << j );
  if( !DP( n , 0 , 0 ) ){
    puts( "NO" );
  }else{
    find_ans();
  }
}
int main(){
  freopen( "digital.in" , "r" , stdin );
  freopen( "digital.out" , "w" , stdout );
  build();
  init();
  solve();
}
