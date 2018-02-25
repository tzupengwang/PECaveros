#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 400010;
struct DominatorTree{
#define REP(i,s,e) for(int i=(s);i<=(e);i++)
#define REPD(i,s,e) for(int i=(s);i>=(e);i--)
  int n , m , s;
  vector< int > g[ MAXN ] , pred[ MAXN ];
  vector< int > cov[ MAXN ];
  int dfn[ MAXN ] , nfd[ MAXN ] , ts;
  int par[ MAXN ];
  int sdom[ MAXN ] , idom[ MAXN ];
  int mom[ MAXN ] , mn[ MAXN ];
  inline bool cmp( int u , int v )
  { return dfn[ u ] < dfn[ v ]; }
  int eval( int u ){
    if( mom[ u ] == u ) return u;
    int res = eval( mom[ u ] );
    if(cmp( sdom[ mn[ mom[ u ] ] ] , sdom[ mn[ u ] ] ))
      mn[ u ] = mn[ mom[ u ] ];
    return mom[ u ] = res;
  }
  void init( int _n , int _m , int _s ){
    ts = 0; n = _n; m = _m; s = _s;
    REP( i, 1, n ) g[ i ].clear(), pred[ i ].clear();
  }
  void addEdge( int u , int v ){
    //printf( "Add Edge %d->%d\n" , u , v );
    g[ u ].push_back( v );
    pred[ v ].push_back( u );
  }
  void dfs( int u ){
    ts++;
    dfn[ u ] = ts;
    nfd[ ts ] = u;
    for( int v : g[ u ] ) if( dfn[ v ] == 0 ){
      par[ v ] = u;
      dfs( v );
    }
  }
  void build(){
    REP( i , 1 , n ){
      dfn[ i ] = nfd[ i ] = 0;
      cov[ i ].clear();
      mom[ i ] = mn[ i ] = sdom[ i ] = i;
    }
    dfs( s );
    REPD( i , n , 2 ){
      int u = nfd[ i ];
      if( u == 0 ) continue ;
      for( int v : pred[ u ] ) if( dfn[ v ] ){
        eval( v );
        if( cmp( sdom[ mn[ v ] ] , sdom[ u ] ) )
          sdom[ u ] = sdom[ mn[ v ] ];
      }
      cov[ sdom[ u ] ].push_back( u );
      mom[ u ] = par[ u ];
      for( int w : cov[ par[ u ] ] ){
        eval( w );
        if( cmp( sdom[ mn[ w ] ] , par[ u ] ) )
          idom[ w ] = mn[ w ];
        else idom[ w ] = par[ u ];
      }
      cov[ par[ u ] ].clear();
    }
    REP( i , 2 , n ){
      int u = nfd[ i ];
      if( u == 0 ) continue ;
      if( idom[ u ] != sdom[ u ] )
        idom[ u ] = idom[ idom[ u ] ];
    }
  }
} domT;
#define N 402020
int n , m;
vector< pair<int,int> > v[ N ];
int ui[ N ] , vi[ N ] , di[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d%d" , &ui[ i ] , &vi[ i ] , &di[ i ] );
    v[ ui[ i ] ].push_back( { vi[ i ] , di[ i ] } );
    v[ vi[ i ] ].push_back( { ui[ i ] , di[ i ] } );
  }
}
LL dst[ N ];
bool vst[ N ];
void sp(){
  priority_queue< pair<LL,int> ,
          vector< pair<LL,int> > ,
         greater< pair<LL,int> > > heap;
  heap.push( { 0 , 1 } );
  while( heap.size() ){
    pair<LL,int> tp = heap.top(); heap.pop();
    LL cd = tp.first;
    int who = tp.second;
    if( vst[ who ] ) continue;
    vst[ who ] = true;
    dst[ who ] = cd;
    //cerr << who << " " << cd << endl;
    for( auto e : v[ who ] ){
      if( vst[ e.first ] ) continue;
      heap.push( { cd + e.second , e.first } );
    }
  }
}
pair< pair<int,int> , int > who[ N ];
vector<int> son[ N ];
map< pair< pair<int,int> , int > , int> ans;
int gogo( int now ){
  int ret = 0;
  for( int ss : son[ now ] )
    ret += gogo( ss );
  if( now <= n ) return ret + 1;
  ans[ who[ now ] ] = ret;
  return ret;
}
void solve(){
  sp();
  domT.init( n + m , 0 , 1 );
  int eid = n;
  for( int i = 1 ; i <= n ; i ++ )
    for( auto e : v[ i ] )
      if( dst[ i ] + e.second == dst[ e.first ] ){
        ++ eid;
        who[ eid ] = { { i , e.first } , e.second };
        domT.addEdge( i , eid );
        domT.addEdge( eid , e.first );
      }
  domT.build();
  for( int i = 1 ; i <= eid ; i ++ ){
    son[ domT.idom[ i ] ].push_back( i );
    //printf( "%d -> %d\n" , domT.idom[ i ] , i );
  }
  gogo( 1 );
  for( int i = 0 ; i < m ; i ++ ){
    int cans = max( ans[ { { ui[ i ] , vi[ i ] } , di[ i ] } ] ,
                    ans[ { { vi[ i ] , ui[ i ] } , di[ i ] } ] );
    printf( "%d\n" , cans );
  }
}
int main(){
  init();
  solve();
}
