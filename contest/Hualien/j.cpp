#include <bits/stdc++.h>
using namespace std;
#define N 22
typedef long long LL;
int n , m;
char buf[ 100 ];
inline LL read(){
  scanf( "%s" , buf );
  int at = 0;
  int len = strlen( buf );
  while( at < len and buf[ at ] != '.' ) at ++;
  if( at == len ) return 0;
  LL ret = 0;
  for( int i = 0 ; i < 18 ; i ++ ){
    ++ at;
    if( at < len )
      ret = ret * 10 + (buf[ at ] - '0');
    else
      ret = ret * 10;
  }
  return ret;
}
#define ONE 1000000000000000000LL
__int128 a[ N ] , b[ N ] , inf;
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    a[ i ] = read();
  scanf( "%d" , &m );
  for( int i = 0 ; i < m ; i ++ )
    b[ i ] = read();
}
__int128 ans , a2[ N ] , b2[ N ];
__int128 dp[ N ][ N ][ N ];
__int128 cost( __int128 x , __int128 y ){
  if( x > y ) swap( x , y );
  return min( y - x , x + ONE - y );
}
void gogo(){
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; j <= m ; j ++ )
      for( int k = 0 ; k <= min( n , m ) ; k ++ )
        dp[ i ][ j ][ k ] = inf;
  dp[ 1 ][ 1 ][ 1 ] = cost( a2[ 0 ] , b2[ 0 ] );
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; j <= m ; j ++ )
      for( int k = 0 ; k <= min( i , j ) ; k ++ ){
        if( dp[ i ][ j ][ k ] >= inf ) continue;
        if( i == n or j == m )
          ans = min( ans , dp[ i ][ j ][ k ] );
        if( i < n ){
          for( int jj = j ; jj < m ; jj ++ ){
            __int128 tc = cost( a2[ i ] , b2[ jj ] );
            dp[ i + 1 ][ jj + 1 ][ k + 1 ] =
              min( dp[ i + 1 ][ jj + 1 ][ k + 1 ] ,
                   dp[ i ][ j ][ k ] + tc ); 
          }
        }
        if( j < m ){
          for( int ii = i ; ii < n ; ii ++ ){
            __int128 tc = cost( a2[ ii ] , b2[ j ] );
            dp[ ii + 1 ][ j + 1 ][ k + 1 ] =
              min( dp[ ii + 1 ][ j + 1 ][ k + 1 ] ,
                   dp[ i ][ j ][ k ] + tc ); 
          }
        }
      }
}
void cal( int ii , int jj , __int128 cdlt ){
  __int128 goal = a[ ii ] + cdlt;
  __int128 dlt = goal - b[ jj ];
  for( int i = 0 ; i < n ; i ++ )
    a2[ i ] = a[ (ii + i) % n ];
  for( int j = 0 ; j < m ; j ++ ){
    __int128 tmp = b[ (jj + j) % m ] + dlt;
    while( tmp < 0 ) tmp += ONE;
    while( tmp >= ONE ) tmp -= ONE;
    b2[ j ] = tmp;
  }
  gogo();
}
__int128 ten[ 20 ];
void solve(){
  ans = inf;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ ){
      cal( i , j , 0 );
      cal( i , j , ONE / 2 );
    }
  printf( "%lld" , (long long)( ans / ONE ) );
  ans %= ONE;
  if( ans > 0 ){
    putchar( '.' );
    for( int i = 17 ; i >= 0 ; i -- ){
      printf( "%lld" , (long long)( ans / ten[ i ] ) );
      ans %= ten[ i ];
      if( ans == 0 ) break;
    }
  }
  puts( "" );
}
int main(){
  ten[ 0 ] = 1;
  for( int i = 1 ; i < 20 ; i ++ )
    ten[ i ] = ten[ i - 1 ] * 10;
  inf = ONE;
  inf *= N;
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
