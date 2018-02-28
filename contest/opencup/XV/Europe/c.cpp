#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 2048
int n;
struct DJS{
  int p[ N ];
  int f( int x ){
    return x == p[ x ] ? p[ x ] : p[ x ] = f( p[ x ] );
  }
  void uni( int x , int y ){
    p[ f( x ) ] = f( y );
  }
} djs;
vector<int> v[ N ];
#define K 10
int pp[ K ][ N ] , dep[ N ];
int m , p[ N * N ] , q[ N * N ] , lca[ N * N ];
vector< pair<int,int> > qry[ N ];
int in[ N ] , out[ N ] , stmp;
bool vst[ N ];
inline int climb( int x , int d ){
  while( d ){
    int bt = __lg( d & (-d) );
    x = pp[ bt ][ x ];
    d ^= (1 << bt);
  }
  return x;
}
void go( int now , int prt , int tdep ){
  dep[ now ] = tdep;
  pp[ 0 ][ now ] = prt;
  vst[ now ] = true;
  in[ now ] = ++ stmp;
  for( auto qq : qry[ now ] ){
    if( not vst[ qq.first ] ) continue;
    lca[ qq.second ] = djs.f( qq.first );
  }
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    go( son , now , tdep + 1 );
    djs.uni( son , now );
  }
  out[ now ] = ++ stmp;
}
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    v[ i ].clear();
    qry[ i ].clear();
    vst[ i ] = false;
    djs.p[ i ] = i;
  }
  stmp = 0;
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
  scanf( "%d" , &m );
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d" , &p[ i ] , &q[ i ] );
    qry[ p[ i ] ].push_back( { q[ i ] , i } );
    qry[ q[ i ] ].push_back( { p[ i ] , i } );
  }
  go( 1 , 1 , 0 );
}
LL BIT[ 2 ][ N ] , lb[ N ];
void modify( int kd , int k , LL d ){
  for( int i = k ; i <= n + n ; i += lb[ i ] )
    BIT[ kd ][ i ] += d;
}
LL query( int kd , int k ){
  LL ret = 0;
  for( int i = k ; i ; i -= lb[ i ] )
    ret += BIT[ kd ][ i ];
  return ret;
}
LL dp[ N ];
vector<int> cand[ N ];
LL cdp[ 1 << 10 ] , id[ N ] , vv[ 1 << 10 ];
LL xdp[ 1 << 10 ];
int wt[ 1 << 10 ] , ct;
void DP( int now , int prt ){
  dp[ now ] = 0;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    DP( son , now );
    dp[ now ] += dp[ son ];
  }
  int _id = 0;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    id[ son ] = _id ++;
  }
  for( int i = 0 ; i < (1 << _id) ; i ++ ){
    xdp[ i ] = cdp[ i ] = vv[ i ] = 0;
    for( int son : v[ now ] ){
      if( son == prt ) continue;
      if( (i >> id[ son ]) & 1 )
        vv[ i ] += dp[ son ];
    }
  }
  ct = 0;
  for( int i : cand[ now ] ){
    int ui = p[ i ] , vi = q[ i ];
    if( vi == now ) swap( ui , vi );
    if( ui == now ){
      LL tdp = 0;
      tdp += query( 0 , in[ vi ] ) - query( 0 , in[ now ] - 1 );
      tdp += dp[ vi ] + 1;
      int vvi = climb( vi , dep[ vi ] - dep[ now ] - 1 );
      LL& to = xdp[ (1 << id[ vvi ]) ];
      if( tdp > to ){
        if( to == 0 )
          wt[ ct ++ ] = (1 << id[ vvi ]);
        to = tdp;
      }
    }else{
      LL tdp = 0;
      tdp += query( 0 , in[ ui ] ) - query( 0 , in[ now ] - 1 );
      tdp += query( 0 , in[ vi ] ) - query( 0 , in[ now ] - 1 );
      tdp += dp[ ui ] + dp[ vi ] + 1;
      int uui = climb( ui , dep[ ui ] - dep[ now ] - 1 );
      int vvi = climb( vi , dep[ vi ] - dep[ now ] - 1 );
      LL& to = xdp[ (1 << id[ uui ]) | (1 << id[ vvi ]) ];
      if( tdp > to ){
        if( to == 0 )
          wt[ ct ++ ] = (1 << id[ vvi ]) | (1 << id[ uui ]);
        to = tdp;
      }
    }
  }
  LL ya[ 11 ] = {};
  for( int i = 0 ; i < (1 << _id) ; i ++ ){
    for( int j = 0 ; j < ct ; j ++ ){
      if( i & wt[ j ] ) continue;
      cdp[ i | wt[ j ] ] = max( cdp[ i | wt[ j ] ] ,
                                  cdp[ i ] + xdp[ wt[ j ] ] );
    }
    dp[ now ] = max( dp[ now ] , cdp[ i ] + vv[ ((1 << _id) - 1) ^ i ] );
    for( int son : v[ now ] ){
      if( son == prt ) continue;
      if( (i >> id[ son ]) & 1 )
        continue;
      ya[ id[ son ] ] = max( ya[ id[ son ] ] ,
                             cdp[ i ] + vv[ ((1 << _id) - 1) ^ i ^ (1 << id[ son ]) ] );
    }
  }
  //printf( "%d dp %lld\n" , now , dp[ now ] );
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    modify( 0 ,  in[ son ] , + ya[ id[ son ] ] );
    modify( 0 , out[ son ] , - ya[ id[ son ] ] );
    //printf( "%d ya %lld\n" , son , ya[ id[ son ] ] );
  }
}
void solve(){
  for( int j = 1 ; j < K ; j ++ )
    for( int i = 1 ; i <= n ; i ++ )
      pp[ j ][ i ] = pp[ j - 1 ][ pp[ j - 1 ][ i ] ];
  for( int i = 1 ; i <= n ; i ++ )
    cand[ i ].clear();
  for( int i = 0 ; i < m ; i ++ )
    cand[ lca[ i ] ].push_back( i );
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = 0 ; j <= n + n ; j ++ )
      BIT[ i ][ j ] = 0;
  DP( 1 , 1 );
  printf( "%lld\n" , dp[ 1 ] );
}
int main(){
  for( int i = 1 ; i < N ; i ++ )
    lb[ i ] = i & (-i);
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
