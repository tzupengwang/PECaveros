#include <bits/stdc++.h>
using namespace std;
#define N 514
int n , m;
vector<int> v[ N ];
void init(){
  cin >> n >> m;
  for( int i = 0 ; i < m ; i ++ ){
    int ui , vi;
    cin >> ui >> vi;
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
}
bool vst[ N ];
int cc;
void go( int now ){
  cc ++;
  vst[ now ] = true;
  for( int x : v[ now ] )
    if( not vst[ x ] )
      go( x );
}
bool gt[ N ][ N ][ 2 ];
bool dp[ N ][ N ][ 2 ];
bool win( int zer , int one , int left ){
  if( zer + one <= 1 ) return false;
  if( gt[ zer ][ one ][ left ] )
    return dp[ zer ][ one ][ left ];
  gt[ zer ][ one ][ left ] = true;
  bool good = false;
  if( zer >= 2 )
    if( not win( zer - 1 , one , !left ) )
      good = true;
  if( one >= 2 )
    if( not win( zer+1 , one - 2 , left ) )
      good = true;
  if( zer and one )
    if( not win( zer - 1 , one , !left ) )
      good = true;
  if( left )
    if( not win( zer , one , !left ) )
      good = true;
  return dp[ zer ][ one ][ left ] = good;
}
void solve(){
  int cnt[ 2 ] = {} , tmp = m % 2;
  for( int i = 1 ; i <= n ; i ++ ){
    if( vst[ i ] ) continue;
    cc = 0;
    go( i );
    cnt[ cc % 2 ] ++;
    int rr = cc * ( cc - 1 ) / 2;
    tmp = ( tmp + rr % 2 ) % 2;
  }
  puts( win( cnt[ 0 ] , cnt[ 1 ] , tmp ) ? "Andrew" : "Betty" );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "points.in" , "r" , stdin );
  freopen( "points.out" , "w" , stdout );
#endif
  init();
  solve();
}
