#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef pair< int , int > ii ;

int sq[ 5000005 ] ;
struct T {
  bool ok ;
  int ti , tj , x , y ;
  void set( int a , int b , int c , int d ) {
    ok = true ;
    ti = a , tj = b , x = c , y = d ;
  }
} dp[ 1005 ][ 2005 ] ;

void process( int n , int m , vector< ii > &r ) {
  if ( m <= n || n + n < m ) return ;
  while ( m > n + 1 ) {
    r.emplace_back( 1 , 1 ) ;
    m -= 2 , n -= 1 ;
  }
  r.emplace_back( 1 , n ) ;
}

void solve( int n , int m ) {
  if ( n + n < m ) return ;
  if ( dp[ n ][ m ].ok ) return ;

  for ( int i = n - 1 ; i >= 0 ; i -- ) {
    for ( int j = min( i + i , m ) ; j >= 0 ; j -- ) if ( dp[ i ][ j ].ok ) {
      int tn = n - i , tm = m - j ;
      int tt = tm * tm - 4 * tn ;
      if ( tt < 0 || sq[ tt ] == -1 ) continue ;
      tt = sq[ tt ] ;
      if ( ( tt + tm ) % 2 == 1 ) continue ;
      dp[ n ][ m ].set( i , j , ( tt + tm ) / 2 , ( tm - tt ) / 2 ) ;
      //if ( n == 10 && m == 18 )
        //printf( "ss %d %d %d %d\n" , i , j , ( tt + tm ) / 2 , ( tm - tt ) / 2 ) ;
      return ;
    }
  }
}

void process() {
  int n , m ;
  scanf( "%d%d" , &n , &m ) ;

  if ( m % 2 == 1 ) {
    puts( "No" ) ;
    return ;
  }
  m /= 2 ;
  if ( !dp[ n ][ m ].ok ) {
    puts( "No" ) ;
    return ;
  }
  puts( "Yes" ) ;
  vector< ii > ans ;
  while ( n != 0 && m != 0 ) {
    ans.push_back( ii( dp[ n ][ m ].x , dp[ n ][ m ].y ) ) ;
    int xx = dp[ n ][ m ].ti ;
    int yy = dp[ n ][ m ].tj ;
    n = xx , m = yy ;
  }
  printf( "%d\n" , (int)ans.size() ) ;
  for ( ii x : ans ) {
    printf( "%d %d\n" , x.first , x.second ) ;
  }
}

int main(){
  //freopen( "input.txt" , "r" , stdin );
  //freopen( "output.txt" , "w" , stdout );

  for ( int i = 0 ; i <= 5000000 ; i ++ ) {
    sq[ i ] = -1 ;
  }
  for ( int i = 0 ; i <= 5000000 ; i ++ ) {
    if ( i * i > 5000000 ) break ;
    sq[ i * i ] = i ;
  }
  for ( int i = 0 ; i <= 1000 ; i ++ )
    for ( int j = 0 ; j <= 2000 ; j ++ )
      dp[ i ][ j ].ok = false ;

  for ( int i = 1 ; i <= 1000 ; i ++ ) {
    dp[ i ][ i + 1 ].set( 0 , 0 , 1 , i ) ;
  }
  for ( int i = 1 ; i <= 1000 ; i ++ ) {
    for ( int j = 1 ; j <= i + i ; j ++ ) {
      solve( i , j ) ;
    }
  }
  int n ;
  scanf( "%d" , &n );
  for ( int i = 0 ; i < n ; i ++ ) {
    process() ;
  }
}


