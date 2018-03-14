#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 201010
int n , m , ui[ N ] , vi[ N ];
vector<int> v[ N ] , rv[ N ];
bool vst[ N ] , vst2[ N ];
set< pair<int,int> > taken;
void init(){
  scanf( "%d%d" , &n , &m );
  taken.clear();
  for( int i = 1 ; i <= n ; i ++ ){
    v[ i ].clear();
    rv[ i ].clear();
    vst[ i ] = false;
    vst2[ i ] = false;
  }
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d" , &ui[ i ] , &vi[ i ] );
    v[ ui[ i ] ].push_back( vi[ i ] );
    rv[ vi[ i ] ].push_back( ui[ i ] );
  }
}
void go( int now , int prt ){
  if( now != prt )
    taken.insert( {prt, now} );
  vst[ now ] = true;
  for( int son : v[ now ] ){
    if( vst[ son ] ) continue;
    go( son , now );
  }
}
void go2( int now , int prt ){
  if( now != prt )
    taken.insert( {now, prt} );
  vst2[ now ] = true;
  for( int son : rv[ now ] ){
    if( vst2[ son ] ) continue;
    go2( son , now );
  }
}
bool ok[ N ];
void solve(){
  go( 1 , 1 );
  go2( 1 , 1 );
  int cnt = 0;
  for( int i = 0 ; i < m ; i ++ ){
    ok[ i ] = taken.find( {ui[ i ] , vi[ i ]} ) != taken.end();
    if( ok[ i ] )
      cnt ++;
  }
  for( int i = 0 ; i < m ; i ++ ){
    if( ok[ i ] ) continue;
    if( cnt < n + n ){
      cnt ++;
      continue;
    }
    printf( "%d %d\n" , ui[ i ] , vi[ i ] );
  }
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
