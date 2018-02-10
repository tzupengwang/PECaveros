#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
struct BccVertex {
  int n , nScc , step , dfn[ N ] , low[ N ];
  vector<int> E[ N ] , sccv[ N ];
  int top , stk[ N ];
  void init( int _n ){
    n = _n;
    nScc = step = 0;
    for( int i = 0 ; i <= n ; i ++ )
      E[ i ].clear();
  }
  void add_edge( int ui , int vi ){
    E[ ui ].push_back( vi );
    E[ vi ].push_back( ui );
  }
  void DFS( int u , int f ){
    dfn[ u ] = low[ u ] = step ++;
    stk[ top ++ ] = u;
    for( auto v : E[ u ] ){
      if( v == f ) continue;
      if( dfn[ v ] == -1 ){
        DFS( v , u );
        low[ u ] = min( low[ u ] , low[ v ] );
        if( low[ v ] >= dfn[ u ] ){
          int z;
          sccv[ nScc ].clear();
          do{
            z = stk[ -- top ];
            sccv[ nScc ].push_back( z );
          }while( z != v );
          sccv[ nScc ].push_back( u );
          nScc ++;
        }
      }else{
        low[ u ] = min( low[ u ] , dfn[ v ] );
      }
    }
  }
  vector< vector<int> > solve( int root ){
    vector< vector<int> > res;
    for( int i = 0 ; i <= n ; i ++ )
      dfn[ i ] = low[ i ] = -1;
    DFS( root , root );
    for( int i = 0 ; i < nScc ; i ++ )
      res.push_back( sccv[ i ] );
    return res;
  }
} graph;


int m , tag[ N ] , p[ N ] , sz[ N ] , stmp;
vector<int> v[ N ];
bool is_c[ N ];
int cand[ N ] , ct;
int til;
void add( int xi ){
  assert( xi < N );
  if( tag[ xi ] == stmp ) return;
  cand[ ct ++ ] = xi;
  tag[ xi ] = stmp;
  p[ xi ] = xi;
  sz[ xi ] = 1;
  v[ xi ].clear();
  is_c[ xi ] = false;
  til = max( til , xi );
}
int root;
void init(){
  ct = til = 0;
  ++ stmp;
  while( m -- ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    add( ui );
    add( vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
    root = ui;
  }
  graph.init( til );
  for( int i = 1 ; i <= til ; i ++ )
    for( int j : v[ i ] )
      graph.add_edge( i , j );
}
int stmp2 , dep[ N ] , low[ N ] , vst[ N ];
void go( int now , int prt ){
  vst[ now ] = stmp;
  dep[ now ] = low[ now ] = ++ stmp2;
  int cntc = 0;
  bool is_cri = false;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    if( vst[ son ] == stmp ){
      low[ now ] = min( low[ now ] , dep[ son ] );
    }else{
      go( son , now );
      cntc ++;
      low[ now ] = min( low[ now ] , low[ son ] );
      if( low[ son ] >= dep[ now ] )
        is_cri = true;
    }
  }
  if( now == prt ){
    if( cntc > 1 )
      is_c[ now ] = true;
  }else{
    if( is_cri )
      is_c[ now ] = true;
  }
}
int _cs;
void solve(){
  stmp2 = 0;
  go( root , root );
  LL ac = 0 , way = 1;
  vector< vector<int> > res = graph.solve( root );
  for( auto i : res ){
    int deg = 0;
    for( auto j : i ){
      if( is_c[ j ] )
        deg ++;
    }
    if( deg == 1 ){
      ac ++;
      way *= (i.size() - deg);
    }
  }
  if( res.size() == 1u ){
    ac = 2;
    way = (LL)res[ 0 ].size() * (res[ 0 ].size() - 1) / 2;
  }
  printf( "Case %d: %lld %lld\n" , ++ _cs , ac , way );
}
int main(){
  while( scanf( "%d" , &m ) == 1 and m ){
    init();
    solve();
  }
}
