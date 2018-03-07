#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 303030
int p[ N ];
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  p[ f( x ) ] = f( y );
}
int n , m , a[ N ] , b[ N ] , d[ N ] , lca[ N ];
vector<int> v[ N ];
vector< pair<int,int> > q[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ ){
    v[ i ].clear();
    q[ i ].clear();
  }
  for( int i = 1 ; i < n ; i ++ ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
    v[ vi ].push_back( ui );
  }
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d%d" , &a[ i ] , &b[ i ] , &d[ i ] );
    q[ a[ i ] ].push_back( {b[ i ] , i} );
    q[ b[ i ] ].push_back( {a[ i ] , i} );
  }
}
bool vst[ N ];
int dep[ N ];
void go( int now , int prt , int tdep ){
  vst[ now ] = true;
  dep[ now ] = tdep;
  for( auto i : q[ now ] ){
    if( !vst[ i.first ] ) continue;
    lca[ i.second ] = f( i.first );
  }
  for( auto son : v[ now ] ){
    if( son == prt ) continue;
    go( son , now , tdep + 1 );
    uni( son , now );
  }
}
bool okay( int root ){
  for( int i = 1 ; i <= n ; i ++ ){
    p[ i ] = i;
    vst[ i ] = false;
  }
  go( root , root , 0 );
  for( int i = 0 ; i < m ; i ++ )
    if( dep[ a[ i ] ] + dep[ b[ i ] ] > d[ i ] )
      return false;
  return true;
}
int gogo( int now , int prt , int tar , int dd , int tdep ){
  if( now == tar ){
    if( dd == tdep ) return now;
    return -1;
  }
  for( int son : v[ now ] ){
    if( son == prt ) continue;
    int ret = gogo( son , now , tar , dd , tdep + 1 );
    if( ret == -2 ) continue;
    if( ret > 0 ) return ret;
    if( ret == -1 ){
      if( dd == tdep )
        return now;
      return -1;
    }
  }
  return -2;
}
void solve(){
  if( okay( 1 ) ){
    printf( "TAK %d\n" , 1 );
    return;
  }
  int who = 1 , mst = 0;
  for( int i = 0 ; i < m ; i ++ ){
    int l = lca[ i ];
    int cd = dep[ a[ i ] ] + dep[ b[ i ] ] - 2 * dep[ l ];
    int x = (d[ i ] - cd) >> 1;
    int goal_dep = max( dep[ l ] - x , 0 );
    if( goal_dep > mst ){
      mst = goal_dep;
      who = l;
    }
  }
  int nroot = gogo( 1 , 1 , who , mst , 0 );
  if( okay( nroot ) ){
    printf( "TAK %d\n" , nroot );
    return;
  }
  puts( "NIE" );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
