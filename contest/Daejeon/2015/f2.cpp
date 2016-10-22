#include <bits/stdc++.h>
using namespace std;
#define N 101010
#define MXN 101010
#define PB push_back
#define FZ(X) memset(X,0,sizeof X)
struct Scc{
  int n, nScc, vst[MXN], bln[MXN];
  vector<int> E[MXN], rE[MXN], vec;
  void init(int _n){
    n = _n;
    for (int i=0; i<=n; i++){
      E[i].clear();
      rE[i].clear();
    }
  }
  void add_edge(int u, int v){
    E[u].PB(v);
    rE[v].PB(u);
  }
  void DFS(int u){
    vst[u]=1;
    for (auto v : E[u])
      if (!vst[v]) DFS(v);
    vec.PB(u);
  }
  void rDFS(int u){
    vst[u] = 1;
    bln[u] = nScc;
    for (auto v : rE[u])
      if (!vst[v]) rDFS(v);
  }
  void solve(){
    nScc = 0;
    vec.clear();
    FZ(vst);
    for (int i=0; i<=n; i++)
      if (!vst[i]) DFS(i);
    reverse(vec.begin(),vec.end());
    FZ(vst);
    for (auto v : vec){
      if (!vst[v]){
        rDFS(v);
        nScc++;
      }
    }
  }
} scc;
int n , m;
vector< int > v[ N ] , ov[ N ];
set< pair<int,int> > S;
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i <= n ; i ++ ){
    v[ i ].clear();
    ov[ i ].clear();
  }
  S.clear();
  scc.init( n );
  for( int i = 0 ; i < m ; i ++ ){
    int ui , vi; scanf( "%d%d" , &ui , &vi );
    ov[ ui ].push_back( vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
    scc.add_edge( ui , vi );
    S.insert( { ui , vi } );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    ov[ 0 ].push_back( i );
    v[ 0 ].push_back( i );
    v[ i ].push_back( 0 );
  }
  scc.solve();
}
bool got;
int clr[ N ] , id[ N ] , cand;
vector< int > oo[ N ];
int sssk[ N ];
vector< int > candv;
void go( int now , int tclr , int ndep ){
  sssk[ ndep ] = now;
  clr[ now ] = tclr;
  for( int x : v[ now ] )
    if( scc.bln[ now ] == scc.bln[ x ] ){
      if( clr[ x ] ){
        if( clr[ x ] == clr[ now ] ){
          cand = 1;
          for( int i = ndep ; sssk[ i ] != x ; i -- )
            candv.push_back( sssk[ i ] );
          candv.push_back( x );
          return;
        }
      }else{
        go( x , 3 - tclr , ndep + 1 );
        if( candv.size() ) return;
      }
    }
}
int stk[ N ] , vst[ N ] , dep[ N ];
//void gogo( int now , int tdep ){
  //stk[ tdep ] = now;
  //dep[ now ] = tdep;
  //vst[ now ] = 1;
  //for( int x : v[ now ] ){
    //if( vst[ x ] ){
      //if( ( dep[ now ] - dep[ x ] ) % 2 == 0 ){
        //for( int i = dep[ x ] ; i <= dep[ now ] ; i ++ )
          //candv.push_back( i );
        //return;
      //}
      //continue;
    //}
    //gogo( x , tdep + 1 );
    //if( candv.size() ) return;
  //}
//}
vector< int > ans;
int ssk[ N ];
bool f , bye , gggt[ N ];
void gogogogo( int now , int tar , int tdep ){
  ssk[ tdep ] = now;
  gggt[ now ] = true;
  if( now == tar ){
    if( tdep % 2 == 0 ){
      puts( "1" );
      printf( "%d\n" , tdep + 1 );
      for( int i = 0 ; i <= tdep ; i ++ )
        printf( "%d\n" , ssk[ i ] );
      f = bye = true;
      return;
    }else{
      for( int i = 1 ; i < tdep ; i ++ )
        ans.push_back( ssk[ i ] );
      f = true;
      return;
    }
  }
  for( int u : ov[ now ] ){
    if( gggt[ u ] || scc.bln[ now ] != scc.bln[ u ] )
      continue;
    gogogogo( u , tar , tdep + 1 );
    if( f || bye ) return;
  }
}
void fixup( int ss , int tt ){
  if( S.count( { ss , tt } ) ) return;
  f = false;
  gogogogo( ss , tt , 0 );
}
int pre[ N ];
bool bb[ N ];
void shrink(){
  for( size_t i = 0 ; i < ans.size() ; i ++ ){
    pre[ ans[ i ] ] = -1;
    bb[ i ] = false;
  }
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    if( pre[ ans[ i ] ] != -1 ){
      int dlt = i - pre[ ans[ i ] ];
      if( dlt % 2 ){
        vector< int > tans;
        for( size_t j = pre[ ans[ i ] ] ; j < i ; j ++ )
          tans.push_back( ans[ j ] );
        ans = tans;
        return;
      }else{
        for( size_t j = pre[ ans[ i ] ] ; j < i ; j ++ ){
          pre[ ans[ j ] ] = -1;
          bb[ j ] = true;
        }
        pre[ ans[ i ] ] = i;
      }
    }else
      pre[ ans[ i ] ] = i;
  size_t ksz = 0;
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    if( !bb[ i ] )
      ans[ ksz ++ ] = ans[ i ];
  ans.resize( ksz );
}
void go( int id ){
  if( oo[ id ].empty() ) return;
  int rt = oo[ id ][ 0 ];
  candv.clear();
  cand = -1;
  go( rt , 1 , 0 );
  if( candv.empty() ) return;
  for( int x : oo[ id ] ){
    vst[ x ] = 0;
    gggt[ x ] = false;
  }
  bye = false;
  ans.clear();
  for( size_t i = 0 ; i < candv.size() ; i ++ ){
    ans.push_back( candv[ i ] );
    for( int x : oo[ id ] )
      gggt[ x ] = false;
    fixup( candv[ i ] , candv[ ( i + 1 ) % candv.size() ] );
    if( bye ){
      got = true;
      return;
    }
  }
  got = true;
  shrink();
  puts( "1" );
  printf( "%d\n" , (int)ans.size() );
  for( auto i : ans )
    printf( "%d\n" , i );
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ ){
    id[ i ] = scc.bln[ i ];
    oo[ scc.bln[ i ] ].push_back( i );
    clr[ i ] = 0;
  }
  got = false;
  for( int i = 0 ; i < scc.nScc && !got ; i ++ )
    go( i );
  if( !got ) puts( "-1" );
  for( int i = 0 ; i <= n ; i ++ )
    oo[ i ].clear();
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
