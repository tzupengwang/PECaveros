#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
int n , clr[ N ] , cp[ N ];
vector< pair<int,int> > v[ N ];
bool blk[ N ];
int sz[ N ] , cen , censz;
void gogo( int now , int prt ){
  sz[ now ] = 1;
  for( auto e : v[ now ] ){
    if( e.first == prt or blk[ e.first ] )
      continue;
    gogo( e.first , now );
    sz[ now ] += sz[ e.first ];
  }
}
void gogo2( int now , int prt , int psz ){
  int tsz = psz;
  for( auto e : v[ now ] ){
    if( e.first == prt or blk[ e.first ] )
      continue;
    gogo2( e.first , now , psz + sz[ now ] - sz[ e.first ] );
    tsz = max( tsz , sz[ e.first ] );
  }
  if( tsz < censz ){
    cen = now;
    censz = tsz;
  }
}
void go( int now , int prt ){
  gogo( now , now );
  cen = now; censz = sz[ now ];
  gogo2( now , now , 0 );
  int cur_cen = cen;
  cp[ cur_cen ] = prt;
  //printf( "%d %d\n" , cur_cen , prt );
  blk[ cur_cen ] = true;
  for( auto e : v[ cur_cen ] ){
    if( blk[ e.first ] ) continue;
    go( e.first , cur_cen );
  }
}
#define lgN 18
int p[ lgN ][ N ] , dep[ N ];
LL dst[ N ];
void go2( int now , int prt , int tdep , LL tdst ){
  dep[ now ] = tdep;
  dst[ now ] = tdst;
  p[ 0 ][ now ] = prt;
  for( auto e : v[ now ] ){
    if( e.first == prt ) continue;
    go2( e.first , now , tdep + 1 , tdst + e.second );
  }
}
inline int lca( int ui , int vi ){
  if( dep[ ui ] > dep[ vi ] ) swap( ui , vi );
  int dlt = dep[ vi ] - dep[ ui ];
  while( dlt ){
    int bt = __lg( dlt & (-dlt) );
    vi = p[ bt ][ vi ];
    dlt ^= (1 << bt);
  }
  if( ui == vi ) return ui;
  for( int i = lgN - 1 ; i >= 0 ; i -- )
    if( p[ i ][ ui ] != p[ i ][ vi ] ){
      ui = p[ i ][ ui ];
      vi = p[ i ][ vi ];
    }
  return p[ 0 ][ ui ];
}
inline LL dist( int ui , int vi ){
  int lcaa = lca( ui , vi );
  return dst[ ui ] + dst[ vi ] - (dst[lcaa] << 1);
}
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi , wi;
    scanf( "%d%d%d" , &ui , &vi , &wi );
    v[ ui ].push_back( { vi , wi } );
    v[ vi ].push_back( { ui , wi } );
  }
  go( 1 , 0 );
  go2( 1 , 1 , 0 , 0 );
  for( int j = 1 ; j < lgN ; j ++ )
    for( int i = 1 ; i <= n ; i ++ )
      p[ j ][ i ] = p[ j - 1 ][ p[ j - 1 ][ i ] ];
}
deque< tuple<int,int,int> > dq[ N ];
#define T(X) get<0>(X)
#define D(X) get<1>(X)
#define C(X) get<2>(X)
int stmp;
void add( int qv , LL dd , int tclr ){
  ++ stmp;
  int now = qv;
  while( now ){
    LL td = dd - dist( now , qv );
    if( td >= 0 ){
      while( dq[ now ].size() and
             D( dq[ now ][ 0 ] ) <= td )
        dq[ now ].pop_front();
      dq[ now ].push_front( make_tuple( stmp , td , tclr ) );
    }
    now = cp[ now ];
  }
}
int query( int qv ){
  int ret = 0 , cur = 0 , now = qv;
  while( now ){
    int bl = 0 , br = (int)dq[ now ].size() - 1 , ba = -1;
    while( bl <= br ){
      int bmid = (bl + br) >> 1;
      if( D( dq[ now ][ bmid ] ) >= dist( now , qv ) )
        ba = bmid , br = bmid - 1;
      else
        bl = bmid + 1;
    }
    if( ba != -1 ){
      int tclr = C( dq[ now ][ ba ] );
      int ttms = T( dq[ now ][ ba ] );
      if( ttms > cur ){
        cur = ttms;
        ret = tclr;
      }
    }
    now = cp[ now ];
  }
  return ret;
}
void solve(){
  int q; scanf( "%d" , &q ); while( q -- ){
    int cmd; scanf( "%d" , &cmd );
    if( cmd == 1 ){
      int qv , d , c;
      scanf( "%d%d%d" , &qv , &d , &c );
      add( qv , d , c );
    }else{
      int qv;
      scanf( "%d" , &qv );
      printf( "%d\n" , query( qv ) );
    }
  }
}
int main(){
  init();
  solve();
}
