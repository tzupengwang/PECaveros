#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 303030
int n , m;
vector< pair<int,int> > v[ N ] , rv[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ ){
    v[ i ].clear();
    rv[ i ].clear();
  }
  while( m -- ){
    int ui , vi , wi;
    scanf( "%d%d%d" , &ui , &vi , &wi );
    v[ ui ].push_back( { vi , wi } );
    rv[ vi ].push_back( { ui , -wi } );
  }
}
int vst[ N ] , vst2[ N ] , stmp , at[ N ];
LL sum[ N ] , psum[ N ] , cand;
bool in[ N ];
void go( int now , int dep , LL tsum , int tpsum ){
  vst2[ now ] = stmp;
  sum[ dep ] = tsum;
  psum[ dep ] = tpsum;
  at[ now ] = dep;
  in[ now ] = true;
  for( auto e : v[ now ] ){
    if( vst2[ e.first ] == stmp ){
      if( not in[ e.first ] ) continue;
      LL dlt = tsum - sum[ at[ e.first ] ] + e.second;
      int pdlt = tpsum - psum[ at[ e.first ] ] + 1;
      if( pdlt and dlt % pdlt == 0 )
        cand = dlt / pdlt;
      continue;
    }
    go( e.first , dep + 1 , tsum + e.second , tpsum + 1 );
  }
  for( auto e : rv[ now ] ){
    if( vst2[ e.first ] == stmp ){
      if( not in[ e.first ] ) continue;
      LL dlt = tsum - sum[ at[ e.first ] ] + e.second;
      int pdlt = tpsum - psum[ at[ e.first ] ] - 1;
      if( pdlt and dlt % pdlt == 0 )
        cand = dlt / pdlt;
      continue;
    }
    go( e.first , dep + 1 , tsum + e.second , tpsum - 1 );
  }
  in[ now ] = false;
}
LL phi[ N ];
void go3( int now , LL cur_x ){
  phi[ now ] = cur_x;
  vst[ now ] = stmp;
  for( auto e : v[ now ] ){
    // cand = e.second + phi(now) - phi(he)
    // phi(he) = e.second - cand + phi(now)
    if( vst[ e.first ] ) continue;
    go3( e.first , e.second - cand + phi[ now ] );
  }
  for( auto e : rv[ now ] ){
    // cand = -e.second + phi(he) - phi(now)
    // phi(he) = cand + e.second + phi(now)
    if( vst[ e.first ] ) continue;
    go3( e.first , cand + e.second + phi[ now ] );
  }
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    vst[ i ] = vst2[ i ] = 0;
  ++ stmp;
  cand = 0;
  for( int i = 1 ; i <= n and cand == 0 ; i ++ ){
    if( vst2[ i ] == stmp ) continue;
    go( i , 0 , 0 , 0 );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    if( vst[ i ] == stmp ) continue;
    go3( i , 0 );
  }
  bool ok = true;
  for( int i = 1 ; i <= n and ok ; i ++ )
    for( auto e : v[ i ] )
      if( e.second + phi[ i ] - phi[ e.first ] != cand )
        ok = false;
  if( not ok )
    puts( "NO" );
  else{
    puts( "YES" );
    for( int i = 1 ; i <= n ; i ++ )
      printf( "%lld%c" , phi[ i ] , " \n"[ i == n ] );
  }
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
