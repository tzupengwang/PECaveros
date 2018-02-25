#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define K 18
#define N 101010
int BIT[ N + N ];
int lb( int x ){
  return x & (-x);
}
void modify( int x , int d ){
  for( int i = x ; i < N + N ; i += lb( i ) )
    BIT[ i ] += d;
}
int query( int x ){
  int ret = 0;
  for( int i = x ; i ; i -= lb( i ) )
    ret += BIT[ i ];
  return ret;
}
int n , m;
vector<int> v[ N ];
vector< pair<int,int> > pth;
int p[ K ][ N ] , dep[ N ] , in[ N ] , out[ N ] , stmp;
void go( int now , int prt , int tdep ){
  dep[ now ] = tdep;
  in[ now ] = ++ stmp;
  p[ 0 ][ now ] = prt;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    go( son , now , tdep + 1 );
  }
  out[ now ] = ++ stmp;
}
int lca( int ui , int vi ){
  if( dep[ ui ] > dep[ vi ] ) swap( ui , vi );
  int dlt = dep[ vi ] - dep[ ui ];
  while( dlt ){
    int bt = __lg( dlt & (-dlt) );
    vi = p[ bt ][ vi ];
    dlt ^= (1 << bt);
  }
  if( ui == vi ) return ui;
  for( int i = K - 1 ; i >= 0 ; i -- )
    if( p[ i ][ ui ] != p[ i ][ vi ] ){
      ui = p[ i ][ ui ];
      vi = p[ i ][ vi ];
    }
  return p[ 0 ][ ui ];
}
vector< int > wt[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
  scanf( "%d" , &m );
  while( m -- ){
    int ai , bi;
    scanf( "%d%d" , &ai , &bi );
    if( ai > bi ) swap( ai , bi );
    pth.push_back( { ai , bi } );
  }
  sort( pth.begin() , pth.end() );
  pth.resize( unique( pth.begin() , pth.end() ) - pth.begin() );
  go( 1 , 1 , 0 );
  for( int j = 1 ; j < K ; j ++ )
    for( int i = 1 ; i <= n ; i ++ )
      p[ j ][ i ] = p[ j - 1 ][ p[ j - 1 ][ i ] ];
  for( size_t i = 0 ; i < pth.size() ; i ++ ){
    int ui = pth[ i ].first;
    int vi = pth[ i ].second;
    wt[ lca( ui , vi ) ].push_back( i );
  }
}
int tk[ N ];
void go2( int now , int prt ){
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    go2( son , now );
  }
  bool pt = false;
  for( auto i : wt[ now ] ){
    int ui = pth[ i ].first;
    int vi = pth[ i ].second;
    int gt = query( in[ ui ] ) + query( in[ vi ] );
    if( gt ) continue;
    pt = true;
  }
  if( pt ){
    tk[ now ] = 1;
    modify( in[ now ] , +1 );
    modify( out[ now ] , -1 );
  }
}
void solve(){
  go2( 1 , 1 );
  vector<int> ans;
  for( int i = 1 ; i <= n ; i ++ )
    if( tk[ i ] )
      ans.push_back( i );
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
int main(){
  init();
  solve();
}
