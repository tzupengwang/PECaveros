#include <bits/stdc++.h>
using namespace std;
#define N 1021
int n , k;
vector<int> v[ N ];
void init(){
  cin >> n >> k;
  for( int i = 1 ; i <= n ; i ++ )
    v[ i ].clear();
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi;
    cin >> ui >> vi;
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
}
int go( int now , int prt ){
  vector<int> vv;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    vv.push_back( go( son , now ) );
  }
  sort( vv.begin() , vv.end() );
  reverse( vv.begin() , vv.end() );
  int ret = 1;
  if( (int)vv.size() >= k ){
    for( int i = 0 ; i < k ; i ++ )
      ret += vv[ i ];
  }
  return ret;
}
int cs;
void solve(){
  printf( "Case %d: %d\n" , ++ cs , go( 1 , 1 ) );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
