#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N (1 << 15)
char buf[ N ];
int slots;
string eff;
vector<string> rnk[ 6 ];
void init(){
  cin >> slots >> eff;
  for( int i = 0 ; i < 6 ; i ++ ){
    rnk[ i ].clear();
    string tmp = "";
    for( int j = 0 ; j < 20 ; j ++ ){
      cin >> tmp;
      rnk[ i ].push_back( tmp );
    }
  }
}
int cs;
size_t mxsz;
bool gg( int y ){
  set<string> advanced;
  int x = slots - y;
  for( size_t i = 0 ; i < mxsz and x > 0 ; i ++ )
    for( int j = 0 ; j < 5 and x > 0 ; j ++ ){
      if( i >= rnk[ j ].size() ) continue;
      auto it = advanced.find( rnk[ j ][ i ] );
      if( it != advanced.end() ) continue;
      x --;
      advanced.insert( rnk[ j ][ i ] );
    }
  for( auto i : rnk[ 5 ] ){
    if( y <= 0 ) break;
    auto it = advanced.find( i );
    if( it != advanced.end() ) continue;
    y --;
    advanced.insert( i );
  }
  return advanced.find( eff ) == advanced.end();
}
void solve(){
  mxsz = 0;
  for( int i = 0 ; i < 5 ; i ++ )
    mxsz = max( mxsz , rnk[ i ].size() );
  printf( "Case #%d: " , ++ cs );
  for( int i = 0 ; i <= slots ; i ++ )
    if( gg( i ) ){
      printf( "%d\n" , i );
      return;
    }
  puts( "ADVANCED!" );
}
int main(){
  int t;
  cin >> t;
  while( t -- ){
    init();
    solve();
  }
}
