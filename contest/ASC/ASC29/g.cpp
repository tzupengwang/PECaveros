#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 404040
typedef long long LL;
int ans[ N ];
#define K 20
int root;
struct SegT{
  pair<int,int> st[ N ] , tg[ N ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
  vector<size_t> sp;
  vector< pair< pair<int,int>*,  pair<int,int> > > rc;
  void init( int no , int l , int r ){
    st[ no ] = { 0 , 0 };
    tg[ no ] = { 0 , 0 };
    if( l == r ) return;
    init( L( no ) , l , mid );
    init( R( no ) , mid + 1 , r );
  }
  void assign( pair<int,int> *x , pair<int,int> v ){
    rc.push_back( { x , *x } );
    *x = v;
  }
  void push( int no , int l , int r ){
    if( tg[ no ].first == 0 ) return;
    if( tg[ no ] > tg[ L( no ) ] )
      assign( &tg[ L( no ) ] , tg[ no ] );
    if( tg[ no ] > tg[ R( no ) ] )
      assign( &tg[ R( no ) ] , tg[ no ] );
    if( tg[ no ] > st[ L( no ) ] )
      assign( &st[ L( no ) ] , tg[ no ] );
    if( tg[ no ] > st[ R( no ) ] )
      assign( &st[ R( no ) ] , tg[ no ] );
    assign( &tg[ no ] , { 0 , 0 } );
  }
  void modify( int no , int l , int r , int ql , int qr , pair<int,int> v ){
    if( r < ql or l > qr ) return;
    if( ql <= l and r <= qr ){
      if( v > tg[ no ] )
        assign( &tg[ no ] , v );
      if( v > st[ no ] )
        assign( &st[ no ] , v );
      return;
    }
    push( no , l , r );
    modify( L( no ) , l , mid , ql , qr , v );
    modify( R( no ) , mid + 1 , r , ql , qr , v );
  }
  pair<int,int> query( int no , int l , int r , int p ){
    if( l == r ) return st[ no ];
    push( no , l , r );
    if( p <= mid ) return query( L( no ) , l , mid , p );
    return query( R( no ) , mid + 1 , r , p );
  }
  void save(){
    sp.push_back(rc.size());
  }
  void undo(){
    while(rc.size()>sp.back()){
      *rc.back().first = rc.back().second;
      rc.pop_back();
    }
    sp.pop_back();
  }
} seg;
struct Tree{
  int n;
  vector< pair<int,int> > g[ N ] , son[ N ];
  void init( int _n ){
    n = _n;
    for( int i = 1 ; i <= n ; i ++ ){
      g[ i ].clear();
      son[ i ].clear();
    }
  }
  void add_edge( int ui , int vi , int id ){
    g[ ui ].push_back( { vi , id } );
  }
  int ss[ N ] , dep[ N ] , prt[ N ];
  bool vst[ N ];
  void dfs( int now , int p ){
    for( auto i : son[ now ] ){
      if( prt[ i.first ] != now )
        continue;
      dfs( i.first , now );
      ans[ i.second ] += ss[ i.first ];
      ss[ now ] += ss[ i.first ];
    }
  }
  int in[ N ] , out[ N ] , stmp;
  void go( int now , int p , int tdep ){
    in[ now ] = ++ stmp;
    vst[ now ] = true;
    prt[ now ] = p;
    dep[ now ] = tdep;
    for( auto i : g[ now ] )
      if( not vst[ i.first ] ){
        son[ now ].push_back( i );
        go( i.first , now , tdep + 1 );
      }
    out[ now ] = stmp;
  }
  void build(){
    for( int i = 1 ; i <= n ; i ++ ){
      vst[ i ] = false;
      ss[ i ] = 0;
    }
    stmp = 0;
    go( root , root , 1 );
  }
} g , rg;
int a , b , m , s[ N ] , t[ N ];
void init(){
  scanf( "%d%d%d" , &a , &b , &m );
  for( int i = 1 ; i <= a ; i ++ )
    scanf( "%d" , &s[ i ] );
  for( int i = 1 ; i <= b ; i ++ )
    scanf( "%d" , &t[ i ] );
  root = 1;
  g.init( a + b );
  rg.init( a + b );
  for( int i = 1 ; i <= m ; i ++ ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    if( ui < 0 ) ui = - ui;
    else ui += a;
    if( vi < 0 ) vi = - vi;
    else vi += a;
    g.add_edge( ui , vi , i );
    rg.add_edge( vi , ui , i );
  }
  g.build();
  rg.build();
}
vector< pair<int,int> > cand[ N ];
void gogo( int now , int prt ){
  seg.save();
  seg.modify( 1 , 1 , a + b ,
              rg.in[ now ] , rg.out[ now ] , { rg.dep[ now ] , now } );
  for( auto qq : cand[ now ] ){
    int who = seg.query( 1 , 1 , a + b , rg.in[ qq.first ] ).second;
    assert( who > 0 );
    g.ss[ now ] += qq.second;
    g.ss[ who ] -= qq.second;
    rg.ss[ qq.first ] += qq.second;
    rg.ss[ who ] -= qq.second;
  }
  for( auto son : g.son[ now ] )
    gogo( son.first , now );
  seg.undo();
}
void solve(){
  int iter = 1;
  for( int i = 1 ; i <= a ; i ++ ){
    while( s[ i ] ){
      while( t[ iter ] == 0 ) iter ++;
      int cc = min( t[ iter ] , s[ i ] );
      cand[ a + iter ].push_back( { i , cc } );
      t[ iter ] -= cc;
      s[ i ] -= cc;
    }
  }
  seg.init( 1 , 1 , a + b );
  gogo( root , root );
  g.dfs( root , root );
  rg.dfs( root , root );
  //for( int i = 1 ; i <= m ; i ++ )
    //assert( ans[ i ] <= c );
  puts( "YES" );
  for( int i = 1 ; i <= m ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i == m ] );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "transport.in" , "r" , stdin );
  freopen( "transport.out" , "w" , stdout );
#endif
  srand( 514514 );
  init();
  solve();
}
