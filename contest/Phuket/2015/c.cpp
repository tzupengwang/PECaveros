#include <bits/stdc++.h>
using namespace std;
int getint(){
  int x = 0; char ctmp = getchar();
  while( ctmp < '0' || ctmp > '9' ) ctmp = getchar();
  while( ctmp >= '0' && ctmp <= '9' ){
    x = x * 10 + ctmp - '0';
    ctmp = getchar();
  }
  return x;
}
#define N 101010
struct KeyHasher {
	size_t operator()(const pair<int,int>& k) const {
		return k.first + (size_t)k.second*100000;
	}
};
unordered_map< pair<int,int> , int , KeyHasher > M;
int n , m , q;
vector< pair< int , int > > e[ N ];
void init(){
  M.clear();
  n = getint();
  m = getint();
  q = getint();
  for( int i = 0 ; i < m ; i ++ ){
    int ai , bi , ci;
    ai = getint();
    bi = getint();
    ci = getint();
    if( ai > bi ) swap( ai , bi );
    if( M.count( { ai , bi } ) == 0 ||
        ci < M[ { ai , bi } ] )
      M[ { ai , bi } ] = ci;
  }
  for( int i = 1 ; i <= n ; i ++ )
    e[ i ].clear();
  for( auto it = M.begin() ; it != M.end() ; it ++ ){
    e[ it->first.first ].push_back( { it->first.second , it->second } );
    e[ it->first.second ].push_back( { it->first.first , it->second } );
  }
}
#define K 20
vector< pair<int,int> > other;
int p[ N ][ K ] , dd[ N ] , dep[ N ];
inline int lca( int ui , int vi ){
  if( dep[ ui ] > dep[ vi ] ) swap( ui , vi );
  int dlt = dep[ vi ] - dep[ ui ];
  for( int i = 0 ; i < K ; i ++ )
    if( ( dlt >> i ) & 1 )
      vi = p[ vi ][ i ];
  if( ui == vi ) return ui;
  for( int i = K - 1 ; i >= 0 ; i -- )
    if( p[ ui ][ i ] != p[ vi ][ i ] ){
      ui = p[ ui ][ i ];
      vi = p[ vi ][ i ];
    }
  return p[ ui ][ 0 ];
}
void go( int now , int prt , int tdep , int pc ){
  dep[ now ] = tdep;
  p[ now ][ 0 ] = prt;
  dd[ now ] = pc;
  for( auto i : e[ now ] ){
    int son = i.first;
    int cst = i.second;
    if( son == prt ) continue;
    if( dep[ son ] ){
      if( now <= son )
        other.push_back( { now , son } );
      else
        other.push_back( { son , now } );
      continue;
    }
    go( son , now , tdep + 1 , pc + cst );
  }
}
int sp[ 111 ][ 111 ];
int dist( int uu , int vv ){
  int lc = lca( uu , vv );
  return dd[ uu ] + dd[ vv ] - dd[ lc ] - dd[ lc ];
}
void find_sp(){
  for( size_t i = 0 ; i < other.size() ; i ++ )
    for( size_t j = 0 ; j < other.size() ; j ++ ){
      int w1 = M[ other[ i ] ];
      int w2 = M[ other[ j ] ];
      int dst = dist( other[ i ].first , other[ j ].first );
      dst = min( dst , dist( other[ i ].first , other[ j ].second ) + w2 );
      dst = min( dst , dist( other[ i ].second , other[ j ].first ) + w1 );
      dst = min( dst , dist( other[ i ].second , other[ j ].second ) + w1 + w2 );
      sp[ i ][ j ] = dst;
    }
  for( size_t k = 0 ; k < other.size() ; k ++ )
    for( size_t i = 0 ; i < other.size() ; i ++ )
      for( size_t j = 0 ; j < other.size() ; j ++ )
        sp[ i ][ j ] = min( sp[ i ][ j ],
                            sp[ i ][ k ] + sp[ k ][ j ] );
}
int _cs;
int quo[ 111 ] , qvo[ 111 ];
void solve(){
  other.clear();
  for( int i = 1 ; i <= n ; i ++ )
    dep[ i ] = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( dep[ i ] == 0 )
      go( i , i , 1 , 0 );
  for( int i = 1 ; i < K ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      p[ j ][ i ] = p[ p[ j ][ i - 1 ] ][ i - 1 ];
  sort( other.begin() , other.end() );
  other.resize( unique( other.begin() , other.end() ) - other.begin() );
  random_shuffle( other.begin() , other.end() );
//#define MAGIC 30lu
  //other.resize( min( other.size() , MAGIC ) );
  find_sp();
  printf( "Case %d:\n" , ++ _cs );
  while( q -- ){
    int qu , qv;
    qu = getint();
    qv = getint();
    int ql = lca( qu , qv );
    int ans = dd[ qu ] + dd[ qv ] - dd[ ql ] - dd[ ql ];
    for( size_t i = 0 ; i < other.size() ; i ++ ){
      quo[ i ] = min( dist( qu , other[ i ].first ) ,
                      dist( qu , other[ i ].second ) + M[ other[ i ] ] );
      qvo[ i ] = min( dist( qv , other[ i ].first ) ,
                      dist( qv , other[ i ].second ) + M[ other[ i ] ] );
    }
    for( size_t i = 0 ; i < other.size() ; i ++ ){
      if( quo[ i ] >= ans ) break;
      for( size_t j = 0 ; j < other.size() ; j ++ ){
        int tans = quo[ i ] + qvo[ j ] +
                   sp[ i ][ j ];
        ans = min( ans , tans );
      }
    }
    //for( size_t i = 0 ; i < other.size() ; i ++ ){
      //if( vst[ qu ] != vst[ other[ i ] ] ) continue;
      //if( vst[ qv ] != vst[ other[ i ] ] ) continue;
      //ans = min( ans , sp[ i ][ qu ] + sp[ i ][ qv ] );
    //}
    printf( "%d\n" , ans );
  }
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
