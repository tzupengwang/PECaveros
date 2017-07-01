#include <bits/stdc++.h>
using namespace std;
#define MAX 100010
struct P{
  int d;
  bitset<MAX> b;
  P(){
    d = 0;
    b.reset();
  }
  void init(){
    scanf( "%d" , &d );
    b.reset();
    for( int i = 0 ; i <= d ; i ++ ){
      int x; scanf( "%d" , &x );
      if( x ) b[ i ] = 1;
    }
  }
  void print(){
    printf( "%d" , d );
    for( int i = 0 ; i <= d ; i ++ )
      printf( " %d" , b[ i ] ? 1 : 0 );
    puts( "" );
  }
  void add( const P& he , int dlt ){
    b ^= ( he.b << dlt );
    d = max( d , he.d + dlt );
    while( d > 0 and !b[ d ] ) d --;
  }
};
void solve(){
  P a , b;
  a.init();
  b.init();
  //a.print();
  //b.print();
  vector<int> vv;
  while( b.d != 0 or b.b[ 0 ] ){
    if( a.d < b.d ){
      vv.push_back( -1 );
      swap( a , b );
    }else{
      int dlt = a.d - b.d;
      a.add( b , dlt );
      vv.push_back( dlt );
      swap( a , b );
      vv.push_back( -1 );
    }
  }
  P x , y;
  x.d = 0;
  x.b[ 0 ] = 1;
  y.d = 0;
  y.b[ 0 ] = 1;
  reverse( vv.begin() , vv.end() );
  for( auto i : vv ){
    if( i == -1 ) swap( x , y );
    else y.add( x , i );
  }
  x.print();
  y.print();
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- )
    solve();
}
