#include <bits/stdc++.h>
using namespace std;
#define N 100
#define PB push_back
inline int getint(){
  int x;
  scanf( "%d" , &x );
  return x;
}
int n , m , a[ N ][ N ];
int tag[ 2020202 ] , stp , vl[ 2020202 ];
inline void init(){
  n = getint(); m = getint();
  for( int i = 0 ; i < n ; i ++ ){
    for( int j = 0 ; j < m ; j ++ )
      a[ i ][ j ] = getint();
  }
}
set< vector<int> > S;
void go( int x ){
  vector<int> vv; stp ++;
  vv.PB( 1 );
  tag[ 1 ] = stp;
  vl[ 1 ] = a[ x ][ 0 ];
  for( int i = 1 ; i < m ; i ++ ){
    int now = 1;
    while( tag[ now ] == stp ){
      if( a[ x ][ i ] > vl[ now ] )
        now = now * 2 + 1;
      else now = now * 2;
    }
    vv.PB( now );
    tag[ now ] = stp;
    vl[ now ] = a[ x ][ i ];
  }
  sort( vv.begin() , vv.end() );
  S.insert( vv );
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    go( i );
  printf( "%d\n" , (int)S.size() );
}
int main(){
  init();
  solve();
}
