#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define SZ(c) (int)(c).size()
#define ALL(c) (c).begin(), (c).end()
#define REP(i, s, e) for(int i = (s); i <= (e); i ++)
#define REPD(i, s, e) for(int i = (s); i >= (e); i --)
typedef pair<int,int> pii;
#define MAXN 101010
#define LOG 18
struct HLD{
  int n;
  vector<int> g[MAXN];
  int sz[MAXN], dep[MAXN];
  int ts, tid[MAXN], tdi[MAXN], tl[MAXN], tr[MAXN];
  int mom[MAXN][LOG], head[MAXN];
  void dfssz(int u, int p){
    dep[u] = dep[p] + 1;
    mom[u][0] = p;
    sz[u] = 1;
    head[u] = u;
    for(int& v:g[u]) if(v != p){
      dep[v] = dep[u] + 1;
      dfssz(v, u);
      sz[u] += sz[v];
    }
  }
  void dfshl(int u){
    ts ++;
    tid[u] = tl[u] = tr[u] = ts;
    tdi[tid[u]] = u;
    sort(ALL(g[u]),
         [&](int a, int b){return sz[a] > sz[b];});
    bool flag = 1;
    for(int& v:g[u]) if(v != mom[u][0]){
      if(flag) head[v] = head[u], flag = 0;
      dfshl(v);
      tr[u] = tr[v];
    }
  }
  inline int lca(int a , int b){
    if(dep[a] > dep[b]) swap(a,b);
    int diff = dep[b] - dep[a];
    REPD(k, LOG-1, 0) if(diff & (1 << k))
      b = mom[b][k];
    if(a == b) return a;
    REPD(k, LOG-1, 0) if(mom[a][k] != mom[b][k]){
      a=mom[a][k];
      b=mom[b][k];
    }
    return mom[a][0];
  }
  void init( int _n ){
    n = _n;
    REP( i , 1 , n ) g[ i ].clear();
  }
  void addEdge( int u , int v ){
    g[ u ].push_back( v );
    g[ v ].push_back( u );
  }
  void yutruli(){
    dfssz(1, 0);
    ts = 0;
    dfshl(1);
    REP(k, 1, LOG - 1) REP(i, 1, n)
      mom[i][k] = mom[mom[i][k-1]][k-1];
  }
  int dist( int u , int v ){
    return dep[ u ] + dep[ v ] - 2 * dep[ lca( u , v ) ];
  }
  vector< pii > getPath( int u , int v ){
    vector< pii > res;
    while( tid[ u ] < tid[ head[ v ] ] ){
      res.push_back( pii(tid[head[v]] , tid[ v ]) );
      v = mom[ head[ v ] ][ 0 ];
    }
    res.push_back( pii(tid[ u ] , tid[ v ]) );
    reverse( ALL( res ) );
    return res;
  }
} tree;
#define N 101010
int mn[ N << 2 ] , mx[ N << 2 ] , as[ N << 2 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
void push( int no , int l , int r ){
  if( !as[ no ] ) return;
  as[ L( no ) ] = mn[ L( no ) ] = mx[ L( no ) ] = as[ no ];
  as[ R( no ) ] = mn[ R( no ) ] = mx[ R( no ) ] = as[ no ];
  as[ no ] = 0;
}
void modify( int no , int l , int r , int ql , int qr , int vl ){
  if( r < ql or l > qr ) return;
  if( ql <= l and r <= qr ){
    as[ no ] = mn[ no ] = mx[ no ] = vl;
    return;
  }
  push( no , l , r );
  modify( L( no ) , l , mid , ql , qr , vl );
  modify( R( no ) , mid + 1 , r , ql , qr , vl );
  mn[ no ] = min( mn[ L( no ) ] , mn[ R( no ) ] );
  mx[ no ] = max( mx[ L( no ) ] , mx[ R( no ) ] );
}
pair<int,int> query( int no , int l , int r , int ql , int qr ){
  if( ql == l and r == qr ) return {mn[no], mx[no]};
  push( no , l , r );
  if( qr <= mid ) return query( L( no ) , l , mid , ql , qr );
  if( mid < ql  ) return query( R( no ) , mid + 1 , r , ql , qr );
  pair<int,int> retl = query( L( no ) , l , mid , ql , mid );
  pair<int,int> retr = query( R( no ) , mid + 1 , r , mid + 1 , qr );
  return {min(retl.first , retr.first ) ,
          max(retl.second, retr.second) };
}
int n , f , a[ N ] , b[ N ] , d[ N ];
void init(){
  scanf( "%d" , &n );
  scanf( "%d" , &f );
  tree.init( n );
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    tree.addEdge( ui , vi );
  }
  tree.yutruli();
  for( int i = 0 ; i < f ; i ++ ){
    scanf( "%d%d" , &a[ i ] , &b[ i ] );
    d[ i ] = tree.dist( a[ i ] , b[ i ] );
  }
}
int id[ N ];
void no(){
  puts( "No" );
  exit(0);
}
vector< pair<int,int> > vv[ 2 ];
void solve(){
  for( int i = 0 ; i < f ; i ++ )
    id[ i ] = i;
  sort( id , id + f , 
        [&]( int id1 , int id2 ){ return d[ id1 ] > d[ id2 ]; } );
  for( int _ = 0 ; _ < f ; _ ++ ){
    int i = id[ _ ];
    int tmn = -1 , tmx = -1;
    int x = tree.lca( a[ i ] , b[ i ] );
    vv[ 0 ] = tree.getPath( x , a[ i ] );
    vv[ 1 ] = tree.getPath( x , b[ i ] );
    for( int j = 0 ; j < 2 ; j ++ )
      for( auto pp : vv[ j ] ){
        int ql = pp.first;
        int qr = pp.second;
        pair<int,int> ret = query( 1 , 0 , n , ql , qr );
        if( tmn == -1 )
          tie( tmn , tmx ) = ret;
        else{
          tmn = min( tmn , ret.first );
          tmx = max( tmx , ret.second );
        }
        if( tmn != tmx ) no();
      }
    for( int j = 0 ; j < 2 ; j ++ )
      for( auto pp : vv[ j ] ){
        int ql = pp.first;
        int qr = pp.second;
        modify( 1 , 0 , n , ql , qr , _ + 1 );
      }
  }
  puts( "Yes" );
}
int main(){
  init();
  solve();
}
