#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 3030
int n , m , k;
vector< pair<int,LL> > v[ N ];
vector<int> cand;
void init(){
  scanf( "%d%d%d" , &n , &m , &k );
  for( int i = 0 ; i < m ; i ++ ){
    int ui , vi , ci;
    scanf( "%d%d%d" , &ui , &vi , &ci );
    v[ ui ].push_back( {vi, ci} );
    v[ vi ].push_back( {ui, ci} );
    cand.push_back( ci );
  }
  sort( cand.begin() , cand.end() );
  cand.resize( unique( cand.begin() , cand.end() ) - cand.begin() );
}
int vst[ N ] , stmp;
LL sp( LL x ){
typedef pair<LL,int> dat;
  priority_queue<dat, vector<dat>, greater<dat> > heap;
  heap.push( {0, 1} );
  ++ stmp;
  while( heap.size() ){
    LL nd; int who;
    tie(nd, who) = heap.top(); heap.pop();
    if( who == n ) return nd;
    if( vst[ who ] == stmp ) continue;
    vst[ who ] = stmp;
    for( auto e : v[ who ] ){
      if( vst[ e.first ] == stmp )
        continue;
      heap.push( {nd + max(0LL, e.second - x), e.first} );
    }
  }
  assert( false );
  return -1;
}
void solve(){
  LL ans = sp( 0 );
  for( int g : cand )
    ans = min( ans , sp( g ) + (LL)g * k );
  printf( "%lld\n" , ans );
}
int main(){
  init();
  solve();
}
