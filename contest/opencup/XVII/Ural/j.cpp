#include <bits/stdc++.h>
using namespace std;
#define N 111
typedef pair< int , int > ii ;

int n , m , s ;
int a[ 100 ] , b[ 100 ] , c[ 100 ] , d[ 100 ] ;
char ed[ 2005 ][ 2005 ] ;
int ser( char x ) {
  if ( 'a' <= x && x <= 'z' ) return x - 'a' ;
  else return x - 'A' + 26 ;
}

priority_queue< ii , vector< ii > , greater< ii > > pq ;
int ds[ 2005 ] ;
int dp[ 2005 ][ 100 ] ;

int nt( int t , int tp ) {
  int rem = t % c[ tp ] ;
  if ( dp[ rem ][ tp ] != -1 ) return t + dp[ rem ][ tp ] ;
  int need = ( a[ tp ] * t + b[ tp ] ) % c[ tp ] + d[ tp ] ;
  int cand1 = need ;
  if ( a[ tp ] == 0 ) {
    dp[ rem ][ tp ] = need ;
    return t + cand1 ;
  }
  for ( int i = 1 ; ; i ++ ) {
    if ( i >= cand1 ) break ;
    int tneed = ( a[ tp ] * ( t + i ) + b[ tp ] ) % c[ tp ] + d[ tp ] ;
    if ( tneed + i < cand1 ) cand1 = tneed + i ;
  }
  dp[ rem ][ tp ] = cand1 ;
  return t + cand1 ;
}

void process() {
  memset( ds , -1 , sizeof ds ) ;
  memset( dp , -1 , sizeof dp ) ;
  pq.push( ii( s , 1 ) ) ;
  while ( !pq.empty() ) {
    ii pr = pq.top() ; pq.pop() ;
    int t = pr.first , now = pr.second ;
    if ( ds[ now ] != -1 ) continue ;
    ds[ now ] = t ;

    for ( int nxt = 1 ; nxt <= n ; nxt ++ ) if ( ed[ now ][ nxt ] != '.' && ds[ nxt ] == -1 ) {
      int nnt = nt( t , ser( ed[ now ][ nxt ] ) ) ;
      pq.push( ii( nnt , nxt ) ) ;
    }
  }
  if ( ds[ n ] == -1 ) puts( "-1" ) ;
  else printf( "%d\n" , ds[ n ] - s ) ;
}

int main(){
  //freopen( "input.txt" , "r" , stdin );
  //freopen( "output.txt" , "w" , stdout );
  scanf( "%d%d%d" , &n , &m , &s );
  for ( int i = 0 ; i < m ; i ++ ) {
    char bf[ 10 ] ;
    scanf( "%s" , bf ) ;
    int id = ser( bf[ 0 ] ) ;
    scanf( "%d%d%d%d" , &a[ id ] , &b[ id ] , &c[ id ] , &d[ id ] ) ;
    a[ id ] %= c[ id ] ;
    b[ id ] %= c[ id ] ;
  }
  for ( int i = 1 ; i <= n ; i ++ )
    scanf( "%s" , ed[ i ] + 1 ) ;

  process() ;
}


