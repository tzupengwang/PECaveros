#include <bits/stdc++.h>
using namespace std;
#define N 202020
typedef long long LL;
int n , q;
LL x[ N ] , y[ N ] , ax , ay , bx , by;
void init(){
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld%lld" , &x[ i ] , &y[ i ] );
  scanf( "%lld%lld" , &ax , &ay );
  scanf( "%lld%lld" , &bx , &by );
}
int _cs;
LL sqr( LL xx ){ return xx * xx; }
int cal( const vector<LL>& vv , LL tar ){
  tar *= tar;
  int bl = 1 , br = (int)vv.size() , ba = 0;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( vv[ bmid - 1 ] <= tar )
      ba = bmid , bl = bmid + 1;
    else
      br = bmid - 1;
  }
  return ba;
}
void solve(){
  scanf( "%d" , &q );
  vector< LL > v1 , v2;
  for( int i = 0 ; i < n ; i ++ ){
    v1.push_back( sqr( ax - x[ i ] ) + sqr( ay - y[ i ] ) );
    v2.push_back( sqr( bx - x[ i ] ) + sqr( by - y[ i ] ) );
  }
  sort( v1.begin() , v1.end() );
  sort( v2.begin() , v2.end() );
  printf( "Case %d:\n" , ++ _cs );
  while( q -- ){
    LL r1 , r2; scanf( "%lld%lld" , &r1 , &r2 );
    int got = 0;
    got += cal( v1 , r1 );
    got += cal( v2 , r2 );
    printf( "%d\n" , max( 0 , n - got ) );
  }
}
int main(){
  while( scanf( "%d" , &n ) == 1 && n ){
    init();
    solve();
  }
}
