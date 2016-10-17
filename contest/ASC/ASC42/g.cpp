#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , d[ N ];
vector< int > e[ N ];
vector< pair<int,int> > v;
void init(){
  for( int i = 1 ; i <= n ; i ++ )
    e[ i ].clear();
  v.clear();
  for( int i = 1;  i <= n ; i ++ ){
    scanf( "%d" , &d[ i ] );
    v.push_back( { d[ i ] , i } );
  }
  sort( v.begin() , v.end() );
  int m; scanf( "%d" , &m ); while( m -- ){
    int tu , tv; scanf( "%d%d" , &tu , &tv );
    e[ tv ].push_back( tu );
  }
}
int vst[ N ] , st;
int ans[ N ] , at;
void go( int now ){
  if( vst[ now ] == st ) return;
  vst[ now ] = st;
  for( int x : e[ now ] )
    go( x );
  ans[ at ++ ] = now;
}
bool okay( int x ){
  at = 0; st ++;
  for( int i = 0 ; i < n ; i ++ ){
    if( vst[ v[ i ].second ] == st ) continue;
    go( v[ i ].second );
    if( at > v[ i ].first + x ) return false;
  }
  return true;
}
void solve(){
  int l = 0 , r = n , aa = n;
  while( l <= r ){
    int mid = ( l + r ) >> 1;
    if( okay( mid ) ) aa = mid , r = mid - 1;
    else l = mid + 1;
  }
  okay( aa );
  printf( "%d\n" , aa );
  for( int i = 0 ; i < n ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == n ] );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "grand.in" , "r" , stdin );
  freopen( "grand.out" , "w" , stdout );
#endif
  while( scanf( "%d" , &n ) == 1 && n ){
    init();
    solve();
  }
}
