#include <bits/stdc++.h>
using namespace std;
#define N 111
int n ;
typedef pair< int , int > ii ;

ii add( ii x , ii y ) {
  return ii( x.first + y.first , x.second + y.second ) ;
}

int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  scanf( "%d" , &n );
  vector< ii > a , b ;
  if ( n % 2 == 1 ) {
    a.push_back( ii( -20 , 21 ) ) ;
    a.push_back( ii( 0 , 0 ) ) ;
    b.push_back( ii( 4 , 3 ) ) ;
    n -= 3 ;
    int rd = 0 ;
    while ( n ) {
      if ( rd ) {
        a.push_back( add( a.back() , ii( 4 , -3 ) ) ) ;
        b.push_back( add( b.back() , ii( 4 , -3 ) ) ) ;
      } else {
        a.push_back( add( a.back() , ii( 3 , -4 ) ) ) ;
        b.push_back( add( b.back() , ii( 3 , -4 ) ) ) ;
      }
      rd = 1 - rd ;
      n -= 2 ;
    }
  } else {
    a.push_back( ii( 0 , 0 ) ) ;
    b.push_back( ii( 3 , 4 ) ) ;
    n -= 2 ;
    int rd = 1 ;
    while ( n ) {
      if ( rd ) {
        a.push_back( add( a.back() , ii( 4 , -3 ) ) ) ;
        b.push_back( add( b.back() , ii( 4 , -3 ) ) ) ;
      } else {
        a.push_back( add( a.back() , ii( 4 , 3 ) ) ) ;
        b.push_back( add( b.back() , ii( 4 , 3 ) ) ) ;
      }
      rd = 1 - rd ;
      n -= 2 ;
    }
  }
  reverse( b.begin() , b.end() ) ;
  for ( ii x : a ) {
    printf( "%d %d\n" , x.first , x.second ) ;
  }
  for ( ii x : b ) {
    printf( "%d %d\n" , x.first , x.second ) ;
  }
}

