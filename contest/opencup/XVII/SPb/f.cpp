#include <bits/stdc++.h>
using namespace std;
#define N 404040
typedef long long LL;

int n ;
void init(){
  scanf( "%d" , &n );
}

void print( int x ) {
  if ( x == 1 ) printf( "1" ) ;
  else if ( x == 2 ) printf( "11" ) ;
  else if ( x == 3 ) printf( "111" ) ;
  else if ( x % 2 == 0 ) {
    printf( "[" ) ;
    print( x / 2 ) ;
    printf( "]" ) ;
  } else {
    printf( "[" ) ;
    print( x / 2 ) ;
    printf( "]1" ) ;
  }
}

void solve(){
  print( n ) ;
  printf( "\n" ) ;
}
int main(){
  init();
  solve();
}
