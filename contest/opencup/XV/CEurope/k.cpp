#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 202020
int n , x[ N ] , y[ N ];
vector< pair<int,int> > e[ N ] , vv;
bool vst[ N ];
typedef pair<LL,LL> dat;
priority_queue<dat, vector<dat>, greater<dat>> heap;
int main(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d%d" , &x[ i ] , &y[ i ] );
  {
    for( int i = 1 ; i <= n ; i ++ )
      vv.push_back( {x[ i ] , i} );
    sort( vv.begin() , vv.end() );
    for( size_t i = 0 ; i + 1 < vv.size() ; i ++ ){
      int dlt = vv[ i + 1 ].first - vv[ i ].first;
      e[ vv[ i ].second ].push_back( {vv[ i + 1 ].second, dlt} );
      e[ vv[ i + 1 ].second ].push_back( {vv[ i ].second, dlt} );
    }
  }
  {
    vv.clear();
    for( int i = 1 ; i <= n ; i ++ )
      vv.push_back( {y[ i ] , i} );
    sort( vv.begin() , vv.end() );
    for( size_t i = 0 ; i + 1 < vv.size() ; i ++ ){
      int dlt = vv[ i + 1 ].first - vv[ i ].first;
      e[ vv[ i ].second ].push_back( {vv[ i + 1 ].second, dlt} );
      e[ vv[ i + 1 ].second ].push_back( {vv[ i ].second, dlt} );
    }
  }
  heap.push( {0, 1} );
  while( heap.size() ){
    auto tp = heap.top(); heap.pop();
    LL nd = tp.first;
    int now = tp.second;
    if( vst[ now ] ) continue;
    vst[ now ] = true;
    if( now == n ){
      printf( "%lld\n" , nd );
      exit(0);
    }
    for( auto ee : e[ now ] ){
      if( vst[ ee.first ] ) continue;
      heap.push( {nd + ee.second, ee.first} );
    }
  }
}
