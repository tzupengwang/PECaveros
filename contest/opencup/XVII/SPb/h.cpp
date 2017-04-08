#include <bits/stdc++.h>
using namespace std;
#define N 1021
int n , m , k;
vector<int> g[ N ];
void init(){
  scanf( "%d%d%d" , &n , &m , &k );
  while( m -- ){
    int ai , bi;
    scanf( "%d%d" , &ai , &bi );
    g[ ai ].push_back( bi );
    g[ bi ].push_back( ai );
  }
}
int who[ N ] , tag[ N ] , stmp , clr[ N ];
bool kk;
void go( int now , int prt , int dep ){
  tag[ now ] = stmp;
  clr[ now ] = dep + 1;
  who[ dep ] = now;
  if( dep == k ){
    printf( "path " );
    for( int i = 0 ; i <= dep ; i ++ )
      printf( "%d%c" , who[ i ] , " \n"[ i == dep ] );
    kk = true;
    return;
  }
  for( int son : g[ now ] ){
    if( son == prt ) continue;
    if( tag[ son ] == stmp ) continue;
    go( son , now , dep + 1 );
    if( kk ) return;
  }
}
void solve(){
  ++ stmp;
  kk = false;
  for( int i = 1 ; i <= n ; i ++ )
    if( tag[ i ] != stmp ){
      go( i , i , 0 );
      if( kk ) return;
    }
  printf( "coloring " );
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , clr[ i ] , " \n"[ i == n ] );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
    for( int i = 1 ; i <= n ; i ++ )
      g[ i ].clear();
  }
}
