#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
const int inv2 = (mod + 1) / 2;
#define N 5140
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
char c[ N ];
int n , ldp[ N ][ N ] , rdp[ N ][ N ] , fac[ N ] , ans[ N ];
inline int C2( int x ){
  return mul( x , x - 1 );
}
int main(){
  fac[ 0 ] = 1;
  for( int i = 1 ; i < N ; i ++ )
    fac[ i ] = mul( fac[ i - 1 ] , i );
  scanf( "%s" , c + 1 );
  n = strlen( c + 1 );
  if( n == 1 ){
    puts( "1" );
    return 0;
  }
  {
    if( c[ 1 ] == '>' )
      ldp[ 1 ][ 1 ] = 1;
    for( int i = 1 ; i < n ; i ++ )
      for( int j = 1 ; j <= i ; j ++ ){
        if( ldp[ i ][ j ] == 0 ) continue;
        if( c[ i + 1 ] == '<' ){
          ldp[ i + 1 ][ j ] = add( ldp[ i + 1 ][ j ] ,
                                   mul( ldp[ i ][ j ] , j ) );
          ldp[ i + 1 ][ j - 1 ] = add( ldp[ i + 1 ][ j - 1 ] ,
                                       mul( ldp[ i ][ j ] , C2( j ) ) );
        }else{
          ldp[ i + 1 ][ j + 1 ] = add( ldp[ i + 1 ][ j + 1 ],
                                       ldp[ i ][ j ] );
          ldp[ i + 1 ][ j ] = add( ldp[ i + 1 ][ j ] , 
                                   mul( ldp[ i ][ j ] , j ) );
        }
      }
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= n ; j ++ )
        ldp[ i ][ j ] = mul( ldp[ i ][ j ] , fac[ j ] );
  }
  {
    if( c[ n ] == '<' )
      rdp[ n ][ 1 ] = 1;
    for( int i = n ; i > 1 ; i -- )
      for( int j = 1 ; j <= n - i + 1 ; j ++ ){
        if( rdp[ i ][ j ] == 0 ) continue;
        if( c[ i - 1 ] == '>' ){
          rdp[ i - 1 ][ j ] = add( rdp[ i - 1 ][ j ] ,
                                   mul( rdp[ i ][ j ] , j ) );
          rdp[ i - 1 ][ j - 1 ] = add( rdp[ i - 1 ][ j - 1 ] ,
                                       mul( rdp[ i ][ j ] , C2( j ) ) );
        }else{
          rdp[ i - 1 ][ j + 1 ] = add( rdp[ i - 1 ][ j + 1 ],
                                       rdp[ i ][ j ] );
          rdp[ i - 1 ][ j ] = add( rdp[ i - 1 ][ j ] , 
                                   mul( rdp[ i ][ j ] , j ) );
        }
      }
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= n ; j ++ )
        rdp[ i ][ j ] = mul( rdp[ i ][ j ] , fac[ j ] );
  }
  ans[ 1 ] = rdp[ 2 ][ 1 ];
  ans[ n ] = ldp[ n - 1 ][ 1 ];
  for( int i = 2 ; i < n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ ){
      ans[ i ] = add( ans[ i ] , mul( mul( ldp[ i - 1 ][ j ] ,
                                           rdp[ i + 1 ][ j ] ) , 2 ) );
      ans[ i ] = add( ans[ i ] , mul( ldp[ i - 1 ][ j ],
                                      rdp[ i + 1 ][ j + 1 ] ) );
      ans[ i ] = add( ans[ i ] , mul( ldp[ i - 1 ][ j + 1 ],
                                      rdp[ i + 1 ][ j ] ) );
    }
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i == n ] );
}
