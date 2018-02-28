#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
int n;
LL x[ N ] , y[ N ] , r[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld%lld%lld" , &x[ i ] , &y[ i ] , &r[ i ] );
}
LL ap[ N ] , aq[ N ];
bool gt[ N ];
int que[ N ] , qt;
LL sqr( LL xx ){
  return xx * xx;
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    gt[ i ] = false;
  gt[ 0 ] = true;
  ap[ 0 ] = 1; aq[ 0 ] = 1;
  que[ 0 ] = 0; qt = 1;
  for( int _ = 0 ; _ < qt ; _ ++ ){
    int i = que[ _ ];
    for( int j = 0 ; j < n ; j ++ ){
      if( gt[ j ] ) continue;
      if( sqr( x[ i ] - x[ j ] ) + sqr( y[ i ] - y[ j ] ) == sqr( r[ i ] + r[ j ] ) ){
        gt[ j ] = true;
        que[ qt ++ ] = j;
        ap[ j ] = ap[ i ] * -r[ i ];
        aq[ j ] = aq[ i ] * r[ j ];
        LL gg = __gcd( abs( ap[ j ] ) , abs( aq[ j ] ) );
        ap[ j ] /= gg;
        aq[ j ] /= gg;
      }
    }
  }
  for( int i = 0 ; i < n ; i ++ ){
    if( !gt[ i ] )
      puts( "not moving" );
    else{
      printf( "%lld" , abs( ap[ i ] ) );
      if( aq[ i ] > 1 ) printf( "/%lld" , aq[ i ] );
      putchar( ' ' );
      if( ap[ i ] < 0 ) printf( "counter" );
      puts( "clockwise" );
    }
  }
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
