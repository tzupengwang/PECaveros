#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 302
const int mod = 1000000007;
inline int add( int ai , int bi ){
  ai += bi;
  return ai >= mod ? ai - mod : ai;
}
inline int mul( LL ai , int bi ){
  ai *= bi;
  return ai >= mod ? ai % mod : ai;
}
int n;
void mul( int a[ N ][ N ] , int b[ N ][ N ] , int c[ N ][ N ] ){ // to c
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ ){
      c[ i ][ j ] = 0;
      for( int k = 0 ; k < n ; k ++ )
        c[ i ][ j ] = add( c[ i ][ j ] ,
                           mul( a[ i ][ k ] , b[ k ][ j ] ) );
    }
}
bool is_zero( int c[ N ][ N ] ){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      if( c[ i ][ j ] )
        return false;
  return true;
}
int m[ 9 ][ N ][ N ];
int tmp[ 11 ][ N ][ N ];
int ans;
int main(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      scanf( "%d" , &m[ 0 ][ i ][ j ] );
  for( int i = 1 ; i < 9 ; i ++ )
    mul( m[ i - 1 ] , m[ i - 1 ] , m[ i ] );
  for( int i = 0 ; i < n ; i ++ )
    tmp[ 0 ][ i ][ i ] = 1;
  int lst = 0;
  for( int j = 8 ; j >= 0 ; j -- ){
    mul( tmp[ lst ] , m[ j ] , tmp[ lst + 1 ] );
    if( is_zero( tmp[ lst + 1 ] ) )
      continue;
    lst ++; ans |= (1 << j);
  }
  mul( tmp[ lst ] , m[ 0 ] , tmp[ lst + 1 ] );
  ans ++;
  if( is_zero( tmp[ lst + 1 ] ) )
    printf( "%d\n" , ans );
  else
    puts( "Infinity" );
}
