#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
int n , e;
vector<int> v;
void init(){
  scanf( "%d%d" , &n , &e );
  v.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &v[ i ] );
  sort( v.begin() , v.end() );
  v.resize( unique( v.begin() , v.end() ) - v.begin() );
}
bool ok[ 2020202 ];
int cal(){
  if( v.size() == 1u ) return ( v[ 0 ] - e % v[ 0 ] ) % v[ 0 ];
  int mx = v[ 0 ] * v[ 1 ] * 2;
  if( e >= mx ) return 0;
  for( int i = 0 ; i <= mx ; i ++ )
    ok[ i ] = false;
  ok[ 0 ] = true;
  for( int x : v )
    for( int i = x ; i <= mx ; i ++ )
      if( ok[ i - x ] )
        ok[ i ] = true;
  //bitset<mx> bt;
  //bt.reset();
  //bt[0] = 1;
  //for( int x : v )
    //bt |= (bt << x);
  for( int i = e ; i <= mx ; i ++ )
    if( ok[ i ] )
      return i - e;
  return mx - e;
}
int _cs;
void solve(){
  printf( "Case #%d: %d\n" , ++ _cs , cal() );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
