#include <bits/stdc++.h>
using namespace std;
#define N 1021
int n , m , cnt[ N ];
char c[ N ][ N ] , v[ N ];
int which(){
  int tt = 0 , tx = 0;
  for( int i = 0 ; i < n ; i ++ )
    if( v[ i ] == 'X' )
      tt ++ , tx = i;
  if( tt == 0 || tt > 1 ) return n;
  return tx;
}
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%s" , c[ i ] );
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%s" , v );
    cnt[ which() ] ++;
  }
}
bool cmp( pair<int,int> p1 , pair<int,int> p2 ){
  if( p1.first != p2.first )
    return p1.first > p2.first;
  return p1.second < p2.second;
}
void solve(){
  vector< pair<int,int> > vv;
  for( int i = 0 ; i < n ; i ++ )
    vv.push_back( { cnt[ i ] , i } );
  sort( vv.begin() , vv.end() , cmp );
  for( int i = 0 ; i < n ; i ++ ){
    int kk = ( ( vv[ i ].first * 10000 + ( m / 2 ) ) / m );
    int l = kk / 100 , r = kk % 100;
    printf( "%s %d.%02d%%\n" , c[ vv[ i ].second ] , l , r );
  }
  int kk = ( ( cnt[ n ] * 10000 + ( m / 2 ) ) / m );
  int l = kk / 100 , r = kk % 100;
  printf( "Invalid %d.%02d%%\n" , l , r );
}
int main(){
  freopen( "bad.in" , "r" , stdin );
  freopen( "bad.out" , "w" , stdout );
  init();
  solve();
}
