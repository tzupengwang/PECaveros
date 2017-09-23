#include <bits/stdc++.h>
using namespace std;
#define N 404040
typedef long long LL;
int ans[ N ];
#define K 20
int root;
struct Tree{
  int n , tag;
  vector< pair<int,int> > g[ N ];
  void init( int _n , int _tag ){
    n = _n;
    for( int i = 1 ; i <= n ; i ++ )
      g[ i ].clear();
  }
  void add_edge( int ui , int vi , int id ){
    g[ ui ].push_back( { vi , id } );
  }
  int prt[ K ][ N ] , ss[ N ] , dep[ N ];
  bool vst[ N ];
  void dfs( int now , int p ){
    for( auto i : g[ now ] ){
      if( prt[ 0 ][ i.first ] != now )
        continue;
      dfs( i.first , now );
      ans[ i.second ] += ss[ i.first ];
      ss[ now ] += ss[ i.first ];
    }
  }
  void go( int now , int p , int tdep ){
    vst[ now ] = true;
    prt[ 0 ][ now ] = p;
    dep[ now ] = tdep;
    for( auto i : g[ now ] )
      if( not vst[ i.first ] )
        go( i.first , now , tdep + 1 );
  }
  int lca( int x , int y ){
    if( dep[ x ] > dep[ y ] ) swap( x , y );
    int dlt = dep[ y ] - dep[ x ];
    while( dlt ){
      int bt = __lg( dlt );
      y = prt[ bt ][ y ];
      dlt ^= (1 << bt);
    }
    if( x == y ) return x;
    for( int i = K - 1 ; i >= 0 ; i -- )
      if( prt[ i ][ x ] != prt[ i ][ y ] ){
        x = prt[ i ][ x ];
        y = prt[ i ][ y ];
      }
    return prt[ 0 ][ x ];
  }
  int part( int y , int up ){
    while( up ){
      int bt = __lg( up );
      y = prt[ bt ][ y ];
      up ^= (1 << bt);
    }
    return y;
  }
  bool is_a( int x , int y ){
    return lca( x , y ) == x;
  }
  void build(){
    for( int i = 1 ; i <= n ; i ++ ){
      vst[ i ] = false;
      ss[ i ] = 0;
      if( tag )
        reverse( g[ i ].begin() , g[ i ].end() );
      random_shuffle( g[ i ].begin() , g[ i ].end() );
    }
    queue<int> Q;
    Q.push( root );
    go( root , root , 0 );
    for( int i = 1 ; i < K ; i ++ )
      for( int j = 1 ; j <= n ; j ++ )
        prt[ i ][ j ] = prt[ i - 1 ][ prt[ i - 1 ][ j ] ];
  }
} g , rg;
int a , b , m , s[ N ] , t[ N ];
void init(){
  scanf( "%d%d%d" , &a , &b , &m );
  for( int i = 1 ; i <= a ; i ++ )
    scanf( "%d" , &s[ i ] );
  for( int i = 1 ; i <= b ; i ++ )
    scanf( "%d" , &t[ i ] );
  root = rand() % a + 1;
  g.init( a + b , 0 );
  rg.init( a + b , 1 );
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
vector< tuple<int,int,int> > cand;
void solve(){
  int c = accumulate( s + 1 , s + a + 1 , 0 );
  int iter = 1;
  for( int i = 1 ; i <= a ; i ++ ){
    while( s[ i ] ){
      while( t[ iter ] == 0 ) iter ++;
      int cc = min( t[ iter ] , s[ i ] );
      cand.push_back( make_tuple( i , a + iter , cc ) );
      t[ iter ] -= cc;
      s[ i ] -= cc;
    }
  }
  for( auto i : cand ){
    int ss = get<0>( i );
    int tt = get<1>( i );
    int ff = get<2>( i );
    if( g.is_a( ss , tt ) ){
      g.ss[ tt ] += ff;
      g.ss[ ss ] -= ff;
    }else if( rg.is_a( tt , ss ) ){
      rg.ss[ ss ] += ff;
      rg.ss[ tt ] -= ff;
    }else{
      rg.ss[ root ] -= ff;
      g.ss[ root ] -= ff;
      rg.ss[ ss ] += ff;
      g.ss[ tt ] += ff;
    }
  }
  g.dfs( root , root );
  rg.dfs( root , root );
  for( int i = 1 ; i <= m ; i ++ )
    assert( ans[ i ] <= c );
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
