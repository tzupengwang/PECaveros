#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 50505
int p[ N ] , sz[ N ];
void init_djs(){
  for( int i = 0 ; i < N ; i ++ ){
    p[ i ] = i;
    sz[ i ] = 1;
  }
}
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  x = f( x ); y = f( y );
  if( x == y ) return;
  p[ x ] = y;
  sz[ y ] += sz[ x ];
}
int n , m , wt[ N ];
vector<int> v[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  while( m -- ){
    int k; scanf( "%d" , &k );
    for( int i = 0 ; i < k ; i ++ )
      scanf( "%d" , &wt[ i ] );
    for( int i = 0 ; i + 1 < k ; i ++ ){
      v[ wt[ i ] ].push_back( wt[ i + 1 ] );
      v[ wt[ i + 1 ] ].push_back( wt[ i ] );
    }
  }
  for( int i = 1 ; i <= n ; i ++ ){
    sort( v[ i ].begin() , v[ i ].end() );
    v[ i ].resize( unique( v[ i ].begin() , v[ i ].end() ) - v[ i ].begin() );
  }
}
LL ans;
int dep[ N ] , low[ N ] , stmp;
vector< vector<int> > cyc;
int stk[ N ];
bool instk[ N ];
int go( int now , int prt , int tdep ){
  instk[ now ] = true;
  stk[ tdep ] = now;
  dep[ now ] = low[ now ] = ++ stmp;
  int ret = 1;
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    if( dep[ son ] ){
      if( not instk[ son ] )
        continue;
      vector<int> tc;
      for( int i = tdep ; ; i -- ){
        tc.push_back( stk[ i ] );
        if( stk[ i ] == son ) break;
      }
      cyc.push_back( tc );
      low[ now ] = min( low[ now ] , dep[ son ] );
    }else{
      int son_sz = go( son , now , tdep + 1 );
      if( low[ son ] > dep[ now ] ){
        ans += son_sz * (LL)( n - son_sz ) - 1;
        uni( now , son );
      }
      ret += son_sz;
      low[ now ] = min( low[ now ] , low[ son ] );
    }
  }
  instk[ now ] = false;
  return ret;
}
inline LL C2( LL x ){
  return x * (x - 1) / 2;
}
void solve(){
  init_djs();
  go( 1 , 1 , 0 );
  LL tot = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( i == f( i ) )
      tot += C2( sz[ f( i ) ] ) - (sz[ f( i ) ] - 1);
  for( auto cc : cyc ){
    LL cur = tot;
    int sumsz = 0;
    for( auto i : cc ){
      cur -= (C2( sz[ f( i ) ] ) - (sz[ f( i ) ] - 1) );
      sumsz += sz[ f( i ) ];
    }
    cur += C2( sumsz ) - sumsz;
    ans += cur * cc.size();
  }
  printf( "%lld\n" , ans );
}
int main(){
#ifndef EDDY
  freopen( "cactus.in" , "r" , stdin );
  freopen( "cactus.out" , "w" , stdout );
#endif
  init();
  solve();
}
