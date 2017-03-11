#include <bits/stdc++.h>
using namespace std;
#define N 222
int n , m;
vector<int> v[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    int ki; scanf( "%d" , &ki ); while( ki -- ){
      int ai; scanf( "%d" , &ai );
      v[ ai ].push_back( i );
      v[ i ].push_back( ai );
    }
  }
}
int ba , bb , clr[ N ];
bool flg;
void go( int now , int nclr ){
  if( not flg ) return;
  clr[ now ] = nclr;
  for( int x : v[ now ] ){
    if( x == ba or x == bb )
      continue;
    if( clr[ x ] ){
      if( nclr == clr[ x ] ){
        flg = false;
        return;
      }
    }else{
      go( x , 3 - nclr );
      if( not flg ) return;
    }
  }
}
inline bool okay( int ai , int bi ){
  ba = ai; bb = bi; flg = true;
  for( int i = 1 ; i <= n ; i ++ )
    clr[ i ] = 0;
  for( int i = 1 ; i <= n and flg ; i ++ )
    if( clr[ i ] == 0 and i != ai and i != bi )
      go( i , 1 );
  return flg;
}
void solve(){
  bool ok = false;
  for( int i = 1 ; i <= n and not ok ; i ++ )
    for( int j = i + 1 ; j <= n and not ok ; j ++ )
      ok = okay( i , j );
  puts( ok ? "Hurrah!" : "Fired." );
}
int main(){
#ifndef LOCAL
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  init();
  solve();
}
