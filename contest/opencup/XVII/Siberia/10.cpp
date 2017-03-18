#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long llu ;
const LL INF  = 1000000000000LL;
int n ;
#define N 35

char s[ 2 ][ N ] ;
char mp[ 10 ][ 10 ] ;

void init(){
  scanf( "%d%s%s" , &n , s[ 0 ] , s[ 1 ] );
  for( int i = 0 ; i < 8 ; i ++ )
    scanf( "%s" , mp[ i ] ) ;
}

inline llu enc( int x , int y ) {
  return 1LLU << ( x * 8 + y ) ;
}

inline bool isb( char x ) {
  return x == '.' || x == 'B' || x == 'T' ;
}
inline bool isb( int x , int y , llu msk ) {
  return mp[ x ][ y ] == '.' || ( mp[ x ][ y ] == 'B' && ( msk & enc( x , y ) ) ) || mp[ x ][ y ] == 'T' ;
}

llu pre[ N ][ 10 ][ 10 ] ;

void move( int x , int y , char S , int &nx , int &ny , llu msk = 0 ) {
  int tx = x , ty = y ;
  nx = x , ny = y ;
  if ( S == 'u' ) tx -- ;
  else if ( S == 'd' ) tx ++ ;
  else if ( S == 'r' ) ty ++ ;
  else if ( S == 'l' ) ty -- ;
  else return ;
  if ( tx < 0 || tx >= 8 || ty < 0 || ty >= 8 || !isb( tx , ty , msk ) );
  else nx = tx , ny = ty ;
}

void shoot( int x , int y , char S , int &nx , int &ny , llu msk ) {
  int tx = x , ty = y ;
  int dx = 0 , dy = 0 ;
  nx = ny = -1 ;
  if ( S == 'U' ) dx -- ;
  else if ( S == 'D' ) dx ++ ;
  else if ( S == 'R' ) dy ++ ;
  else if ( S == 'L' ) dy -- ;
  else return ;

  while ( true ) {
    tx += dx , ty += dy ;
    if ( tx < 0 || tx >= 8 || ty < 0 || ty >= 8 || mp[ tx ][ ty ] == 'A' )
      return ;
    else if ( mp[ tx ][ ty ] == 'B' && ( (~msk) & enc( tx , ty ) ) ) {
      nx = tx , ny = ty ;
      return ;
    }
  }
}
llu shoot2( int x , int y , char S ) {
  int tx = x , ty = y ;
  int dx = 0 , dy = 0 ;
  if ( S == 'U' ) dx -- ;
  else if ( S == 'D' ) dx ++ ;
  else if ( S == 'R' ) dy ++ ;
  else if ( S == 'L' ) dy -- ;
  else return 0LLU ;

  llu msk = enc( tx , ty ) ;
  while ( true ) {
    tx += dx , ty += dy ;
    if ( tx < 0 || tx >= 8 || ty < 0 || ty >= 8 || mp[ tx ][ ty ] == 'A' )
      return msk ;
    msk |= enc( tx , ty ) ;
  }
}

void ppp() {
  for ( int i = 0 ; i < 8 ; i ++ ) {
    for ( int j = 0 ; j < 8 ; j ++ ) {
      if ( isb( mp[ i ][ j ] ) ) {
        pre[ n ][ i ][ j ] = enc( i , j ) ;
      }
    }
  }
  for ( int k = n - 1 ; k >= 0 ; k -- )
    for ( int i = 0 ; i < 8 ; i ++ )
      for ( int j = 0 ; j < 8 ; j ++ )
        if ( isb( mp[ i ][ j ] ) ) {
          pre[ k ][ i ][ j ] = 0LLU ;
          int nx , ny ;
          llu mk = shoot2( i , j , s[ 0 ][ k ] ) ;
          move( i , j , s[ 0 ][ k ] , nx , ny , ~0LLU ) ;
          pre[ k ][ i ][ j ] |= pre[ k + 1 ][ nx ][ ny ] ;
          move( i , j , s[ 0 ][ k ] , nx , ny , 0LLU ) ;
          pre[ k ][ i ][ j ] |= pre[ k + 1 ][ nx ][ ny ] ;

          mk = shoot2( i , j , s[ 1 ][ k ] ) ;
          move( i , j , s[ 1 ][ k ] , nx , ny , ~0LLU ) ;
          pre[ k ][ i ][ j ] |= pre[ k + 1 ][ nx ][ ny ] ;
          move( i , j , s[ 1 ][ k ] , nx , ny , 0LLU ) ;
          pre[ k ][ i ][ j ] |= pre[ k + 1 ][ nx ][ ny ] ;

          pre[ k ][ i ][ j ] |= enc( i , j ) ;
        }
}

map< llu , llu > dp[ N ][ 8 ][ 8 ] ;

void solve(){
  ppp() ;
  int stx = 0 , sty = 0 ;
  {
    for ( int i = 0 ; i < 8 ; i ++ )
      for ( int j = 0 ; j < 8 ; j ++ )
        if ( mp[ i ][ j ] == 'T' ) {
          stx = i , sty = j ;
          break ;
        }
  }
  dp[ 0 ][ stx ][ sty ][ 0 ] = 1 ;
  for ( int k = 0 ; k < n ; k ++ ) {
    for ( int i = 0 ; i < 8 ; i ++ ) {
      for ( int j = 0 ; j < 8 ; j ++ ) {
        for ( auto tt : dp[ k ][ i ][ j ] ) {
          llu msk = tt.first , pos = tt.second , nmsk ;
          for ( int pp = 0 ; pp < 2 ; pp ++ ) {
            int nx , ny , tx , ty ;
            move( i , j , s[ pp ][ k ] , nx , ny , msk ) ;
            shoot( i , j , s[ pp ][ k ] , tx , ty , msk ) ;

            nmsk = msk ;
            if ( tx != -1 ) nmsk |= enc( tx , ty ) ;
            dp[ k + 1 ][ nx ][ ny ][ nmsk & pre[ k + 1 ][ nx ][ ny ] ] += pos ;
          }
        }
      }
    }
  }
  llu denom = ( 1llu << n ) ;
  for ( int i = 0 ; i < 8 ; i ++ ) {
    for ( int j = 0 ; j < 8 ; j ++ ) {
      llu ans = 0 ;
      for ( auto tt : dp[ n ][ i ][ j ] )
        ans += tt.second ;
      llu ta = ans , tb = denom , tc = __gcd( ta , tb ) ;
      ta /= tc ;
      tb /= tc ;
      printf( "%llu/%llu%c" , ta , tb , " \n"[ j == 7 ] ) ;
    }
  }
}

int main(){
  init();
  solve();
}
