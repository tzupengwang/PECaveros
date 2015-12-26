#include<bits/stdc++.h>
using namespace std ;

typedef long long ll ;
typedef pair< int , int > ii ;

int n , m ;
int n2 , m2 ;
ll ans ;
bool vis[ 50 ][ 50 ] ;
priority_queue< ii > pq ;

bool in( int a , int b , int c ) {
  return a >= b && a < c ;
}

int dp[ 55 ][ 55 ] ;
void cal( int h , int w ) {
  int ret = 0 ;
  int bd = max( h , w ) / 2 ;
  for ( int l = 1 ; l <= bd ; l ++ ) {
    for ( int r = l ; r <= bd ; r ++ ) {
      if ( l + r > min( h , w ) ) continue ;
      memset( vis , 0 , sizeof vis ) ;
      while ( !pq.empty() ) pq.pop() ;
      pq.push( ii( 0 , 0 ) ) ;
      vis[ 0 ][ 0 ] = true ;
      int cnt = 0 ;
      while ( !pq.empty() ) {
        ii nw = pq.top() ; pq.pop() ;
        cnt ++ ;
        int x = nw.first , y = nw.second ;
        if ( in( x + l , 0 , h ) && in( y + r , 0 , w ) && !vis[ x + l ][ y + r ] ) vis[ x + l ][ y + r ] = true , pq.push( ii( x + l , y + r ) ) ;
        if ( in( x - l , 0 , h ) && in( y + r , 0 , w ) && !vis[ x - l ][ y + r ] ) vis[ x - l ][ y + r ] = true , pq.push( ii( x - l , y + r ) ) ;
        if ( in( x + l , 0 , h ) && in( y - r , 0 , w ) && !vis[ x + l ][ y - r ] ) vis[ x + l ][ y - r ] = true , pq.push( ii( x + l , y - r ) ) ;
        if ( in( x - l , 0 , h ) && in( y - r , 0 , w ) && !vis[ x - l ][ y - r ] ) vis[ x - l ][ y - r ] = true , pq.push( ii( x - l , y - r ) ) ;
        if ( in( x + r , 0 , h ) && in( y + l , 0 , w ) && !vis[ x + r ][ y + l ] ) vis[ x + r ][ y + l ] = true , pq.push( ii( x + r , y + l ) ) ;
        if ( in( x - r , 0 , h ) && in( y + l , 0 , w ) && !vis[ x - r ][ y + l ] ) vis[ x - r ][ y + l ] = true , pq.push( ii( x - r , y + l ) ) ;
        if ( in( x + r , 0 , h ) && in( y - l , 0 , w ) && !vis[ x + r ][ y - l ] ) vis[ x + r ][ y - l ] = true , pq.push( ii( x + r , y - l ) ) ;
        if ( in( x - r , 0 , h ) && in( y - l , 0 , w ) && !vis[ x - r ][ y - l ] ) vis[ x - r ][ y - l ] = true , pq.push( ii( x - r , y - l ) ) ;
      }
      if ( cnt == h * w ) {
        ret ++ ;
        //if ( h == 19 && w == 9 ) printf( "%d %d\n" , l , r ) ;
      }
    }
  }
  dp[ h ][ w ] = ret ;
  //printf( "%d %d %d\n" , h , w , ret ) ;
}

int main() {
  for ( int h = 1 ; h <= 30 ; h ++ ) {
    for ( int w = 1 ; w <= 25 ; w ++ ) {
      cal( h , w ) ;
    }
  }
  for ( int i = 1 ; i <= 30 ; i ++ ) {
    printf( "%2d:  " , i ) ;
    for ( int j = 1 ; j <= 25 ; j ++ ) {
      printf( "%2d%c" , dp[ i ][ j ] , " \n"[ j == 25 ] ) ;
    }
  }
  /*
  int T ; scanf( "%d" ,&T ) ;
  while ( T -- ) {
    ans = 0;
    scanf( "%d%d" , &n , &m ) ;
    n2 = n / 2 , m2 = m / 2 ;
    for ( int i = 1 ; i <= n2 ; i ++ ) {
      for ( int j = i + 1 ; j <= m2 ; j ++ ) {
        if ( __gcd( i + j , j - i ) == 1 ) ans ++ ;
      }
    }
    printf( "%lld\n" , ans ) ;
  }

  */
  return 0 ;
}
