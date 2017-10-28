#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1000010
int n , m , lb[ N ];
LL bit[ N ];
void reset(){
  for( int i = 0 ; i < N ; i ++ )
    bit[ i ] = 0;
}
inline void modify( int p , LL v ){
  for( int i = p ; i < N ; i += lb[ i ] )
    bit[ i ] = max( bit[ i ] , v );
}
inline LL query( int p ){
  LL ret = 0;
  for( int i = p ; i ; i -= lb[ i ] )
    ret = max( ret , bit[ i ] );
  return ret;
}
void build(){
  for( int i = 0 ; i < N ; i ++ )
    lb[ i ] = i & (-i);
}
vector< pair<pair<int,int>,int> > vv;
void init(){
  scanf( "%d%d" , &n , &m );
  vv.clear();
  while( m -- ){
    int dump , l , r , v;
    scanf( "%d%d%d%d" , &dump , &l , &r , &v );
    vv.push_back( { { r + 1 , l + 1 } , v } );
  }
}
int _cs;
void solve(){
  sort( vv.begin() , vv.end() );
  reset();
  LL ans = 0;
  for( auto i : vv ){
    LL tmp = query( i.first.second ) + i.second;
    ans = max( ans , tmp );
    modify( i.first.first , tmp );
  }
  printf( "Case #%d: %lld\n" , ++ _cs , ans );
}
int main(){
  build();
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
