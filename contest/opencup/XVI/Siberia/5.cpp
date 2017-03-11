#include <bits/stdc++.h>
using namespace std;
#define N 55
#define M 222
const int mod = 1000000007;
typedef long long LL;
int add( int a , int b , int m ){
  a += b;
  return a >= m ? a - m : a;
}
int sub( int a , int b , int m ){
  a -= b;
  return a < 0 ? a + m : a;
}
int mul( LL a , LL b , LL m ){
  a *= b;
  return a >= m ? a % m : a;
}
int n , m , p;
void init(){
  scanf( "%d%d%d" , &n , &m , &p );
}
int dp1[ N ][ M ] , dp2[ N ][ M ];
void solve(){
  for( int i = 0 ; i < m ; i ++ ){
    int tlen = 0 , ti = i;
    if( i == 0 ) tlen = 1;
    while( ti ){
      tlen ++;
      ti /= 10;
    }
    dp1[ tlen ][ i ] ++;
  }
  for( int len = 1 ; len <= n ; len ++ )
    for( int j = 0 ; j < m ; j ++ ){
      if( len > 1 ){
        dp1[ len ][ j ] = add( dp1[ len ][ j ] , dp1[ len - 2 ][ j ] , mod );
        dp1[ len ][ j ] = add( dp1[ len ][ j ] , dp2[ len - 2 ][ j ] , mod );
      }
      for( int pos = 2 ; pos < len ; pos ++ )
        for( int pj = 0 ; pj < m ; pj ++ ){
          { // +
            int nj = sub( j , pj , m );
            int lhs = add( dp2[ pos - 1 ][ pj ] , dp1[ pos - 1 ][ pj ] , mod );
            int ret = mul( lhs , dp1[ len - pos ][ nj ] , mod );
            dp2[ len ][ j ] = add( dp2[ len ][ j ] , ret , mod );
          }
          { // -
            int nj = sub( pj , j , m );
            int lhs = add( dp2[ pos - 1 ][ pj ] , dp1[ pos - 1 ][ pj ] , mod );
            int ret = mul( lhs , dp1[ len - pos ][ nj ] , mod );
            dp2[ len ][ j ] = add( dp2[ len ][ j ] , ret , mod );
          }
        }
    }
  printf( "%d\n" , add( dp2[ n ][ p ] , dp1[ n ][ p ] , mod ) );
}
int main(){
#ifndef LOCAL
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  init();
  solve();
}
