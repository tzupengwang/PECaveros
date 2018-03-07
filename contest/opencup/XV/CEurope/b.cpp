#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 202020
int p[ N ];
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  p[ f( x ) ] = f( y );
}
int n , s , m;
bool ter[ N ];
vector< pair<int,LL> > v[ N ];
void init(){
  scanf( "%d%d%d" , &n , &s , &m );
  while( s -- ){
    int xi; scanf( "%d" , &xi );
    ter[ xi ] = true; 
  }
  while( m -- ){
    int ui , vi , di;
    scanf( "%d%d%d" , &ui , &vi , &di );
    v[ ui ].push_back( {vi, di} );
    v[ vi ].push_back( {ui, di} );
  }
}
LL dst[ N ];
int fr[ N ];
bool vst[ N ];
vector< pair<LL,pair<int,int>> > g;
void build_edge( int xi , int yi , LL di ){
  if( xi == yi ) return;
  //fprintf( stderr , "%d %d %lld\n" , xi , yi , di );
  g.push_back( { di , {xi , yi} } );
}
void pre_solve(){
typedef pair<LL,pair<int,int>> dat;
  priority_queue<dat, vector<dat>, greater<dat>> heap;
  for( int i = 1 ; i <= n ; i ++ )
    if( ter[ i ] )
      heap.push( {0, {i, i}} );
  while( heap.size() ){
    dat td = heap.top(); heap.pop();
    LL nd = td.first;
    int now = td.second.first;
    int from = td.second.second;
    if( vst[ now ] ){
      build_edge( fr[ now ] , from , nd + dst[ now ] );
      continue;
    }
    vst[ now ] = true;
    dst[ now ] = nd;
    fr[ now ] = from;
    for( auto e : v[ now ] )
      heap.push( { nd + e.second , {e.first, from} } );
  }
}
int q , x[ N ] , y[ N ] , vv[ N ];
bool ok[ N ];
void solve(){
  scanf( "%d" , &q );
  for( int i = 0 ; i < q ; i ++ )
    scanf( "%d%d%d" , &x[ i ] , &y[ i ] , &vv[ i ] );
  pre_solve();
  sort( g.begin() , g.end() );
  vector< pair<LL, int> > qry;
  for( int i = 0 ; i < q ; i ++ )
    qry.push_back( { vv[ i ] , i } );
  sort( qry.begin() , qry.end() );
  size_t ptr = 0;
  for( int i = 1 ; i <= n ; i ++ )
    p[ i ] = i;
  for( auto ii : qry ){
    while( ptr < g.size() and g[ ptr ].first <= ii.first ){
      uni( g[ ptr ].second.first ,
           g[ ptr ].second.second );
      ptr ++;
    }
    ok[ ii.second ] = (f( x[ ii.second ] ) ==
                       f( y[ ii.second ] ));
  }
  for( int i = 0 ; i < q ; i ++ )
    puts( ok[ i ] ? "TAK" : "NIE" );
}
int main(){
  init();
  solve();
}
