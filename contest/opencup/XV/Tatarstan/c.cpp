#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000009;
inline int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
inline int mul( LL a , int b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
#define N 333
int DP[ N ][ N ];
int dp[ N ][ N ][ 3 ];
char encode( int x ){
  if( x < 10 ) return x + '0';
  x -= 10;
  if( x < 26 ) return x + 'a';
  x -= 26;
  if( x < 26 ) return x + 'A';
  x -= 26;
  return "!?"[x];
}
int main(){
  dp[ 2 ][ 0 ][ 0 ] = 1;
  DP[ 2 ][ 0 ] = 1;
  dp[ 3 ][ 1 ][ 0 ] = 1;
  dp[ 3 ][ 0 ][ 1 ] = 1;
  DP[ 3 ][ 1 ] = 1;
  for( int i = 4 ; i <= 300 ; i ++ ){
    for( int ii = 2 ; ii < i ; ii ++ )
      for( int jj = 0 ; jj < ii ; jj ++ )
        for( int k = 0 ; k < 3 ; k ++ ){
          if( dp[ ii ][ jj ][ k ] == 0 ) continue;
          int sz = i - ii + 1;
          for( int nj = 0 ; nj <= sz - 2 ; nj ++ ){
            if( DP[ sz ][ nj ] == 0 ) continue;
            dp[ i ][ jj + nj ][ min(k + 1, 2) ] = add(
              dp[ i ][ jj + nj ][ min(k + 1, 2) ] ,
              mul( dp[ ii ][ jj ][ k ] , DP[ sz ][ nj ] ) );
          }
        }
    for( int j = 0 ; j < i ; j ++ ){
      DP[ i ][ j ] = add( DP[ i ][ j ] , dp[ i ][ j ][ 2 ] );
      DP[ i ][ j + 1 ] = add( DP[ i ][ j + 1 ] , dp[ i ][ j ][ 1 ] );
    }
    {
      int sz = i;
      for( int jj = 0 ; jj <= sz - 2 ; jj ++ )
        dp[ i ][ jj ][ 0 ] = DP[ sz ][ jj ];
    }
  }
  printf( "string s=\"" );
  for( int i = 3 ; i <= 300 ; i ++ )
    for( int j = 0 ; j <= i - 2 ; j ++ ){
      for( int k = 0 , vl = DP[ i ][ j ] ; k < 5 ; k ++ , vl >>= 6 )
        putchar( encode( vl & 63 ) );
    }
  printf( "\";\n" );
      //if( DP[ i ][ j ] )
        //printf( "DP[%d][%d]=%d;\n" , i , j , DP[ i ][ j ] );
  //int qn , qk;
  //cin >> qn >> qk;
  //cout << DP[ qn ][ qk ] << endl;
}
