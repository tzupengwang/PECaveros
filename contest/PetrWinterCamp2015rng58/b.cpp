//by tzupengwang™
#include<bits/stdc++.h>
using namespace std;

#define FO(it,c) for (__typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
typedef long long ll;
typedef pair<int,int> ii;

const ll mod = 1000000007LL ;
int n ;
char ss[ 55 ][ 25 ] ;
int s[ 55 ][ 25 ] ;
int maxi ;

void init() {
  scanf( "%d" , &n ) ;
  for ( int i = 0 ; i < n ; i ++ ) {
    scanf( "%s" , ss[ i ] ) ;
    maxi = max( maxi , (int)strlen( ss[ i ] ) ) ;
  }
  for ( int i = 0 ; i < n ; i ++ ) {
    int k = strlen( ss[ i ] ) ;
    for ( int j = 0 ; j < k ; j ++ ) {
      if ( ss[ i ][ j ] != '?' ) s[ i ][ j ] = ss[ i ][ j ] - 'a' + 1 ;
      else s[ i ][ j ] = 27 ;
    }
    for ( int j = k ; j < maxi ; j ++ ) s[ i ][ j ] = 0 ;
  }
}

void add( ll &a , ll b ) {
  a = ( a + b ) % mod ;
}

ll dp[ 55 ][ 55 ][ 30 ][ 30 ] ;

ll DP( int l , int r , int j , int bnd ) {
  if ( dp[ l ][ r ][ j ][ bnd ] != -1 ) return dp[ l ][ r ][ j ][ bnd ] ;

  if ( l == r ) {
    if ( s[ l ][ j ] == 0 ) return dp[ l ][ r ][ j ][ bnd ] = 1 ;
    else if ( s[ l ][ j ] == 27 ) return dp[ l ][ r ][ j ][ bnd ] = DP( l , r , j + 1 , 1 ) * ( 27 - bnd ) % mod ;
    else if ( s[ l ][ j ] >= bnd ) return dp[ l ][ r ][ j ][ bnd ] = DP( l , r , j + 1 , 1 ) ;
    else return dp[ l ][ r ][ j ][ bnd ] = 0 ;
  }

  for ( int i = l + 1 ; i <= r ; i ++ ) if ( s[ i ][ j ] == 0 ) {
    return dp[ l ][ r ][ j ][ bnd ] = 0LL ;
  }
  if ( s[ l ][ j ] == 0 ) return dp[ l ][ r ][ j ][ bnd ] = DP( l + 1 , r , j , bnd ) ;
  for ( int i = l ; i <= r ; i ++ ) if ( s[ i ][ j ] != 27 && s[ i ][ j ] < bnd ) {
    return dp[ l ][ r ][ j ][ bnd ] = 0LL ;
  }

  dp[ l ][ r ][ j ][ bnd ] = 0 ;
  int ip = l ;
  while ( ip <= r ) {
    if ( ip < r && bnd < 26 ) {
      if ( s[ ip ][ j ] == 27 || s[ ip ][ j ] == bnd ) {
        add( dp[ l ][ r ][ j ][ bnd ] , DP( l , ip , j + 1 , 1 ) * DP( ip + 1 , r , j , bnd + 1 ) % mod ) ;
      } else break ;
    } else if ( ip == r ) {
      if ( s[ ip ][ j ] == 27 || s[ ip ][ j ] == bnd ) {
        add( dp[ l ][ r ][ j ][ bnd ] , DP( l , ip , j + 1 , 1 ) ) ;
      } else break ;
    }
    ip ++ ;
  }
  if ( bnd < 26 ) add( dp[ l ][ r ][ j ][ bnd ] , DP( l , r , j , bnd + 1 ) ) ;
  return dp[ l ][ r ][ j ][ bnd ] ;
}

void process() {
  memset( dp , -1 , sizeof dp ) ;
  cout << DP( 0 , n - 1 , 0 , 1 ) << endl ;
}

int main() {
  init() ;
  process() ;
  return 0 ;
}

