#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 303030
int n , tp[ N ] , d[ N ];
vector< pair<int,int> > v[ N ];
void init(){
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d%d" , &tp[ i ] , &d[ i ] );
    v[ i ].clear();
  }
  for( int i = 1 ; i < n ; i ++ ){
    int xi , yi , zi;
    scanf( "%d%d%d" , &xi , &yi , &zi );
    v[ xi ].push_back( { yi , zi } );
    v[ yi ].push_back( { xi , zi } );
  }
}
int dp[ N ][ 2 ];
bool ok[ N ][ 2 ];
void go( int now , int prt ){
  ok[ now ][ 0 ] = true;
  ok[ now ][ 1 ] = false;
  if( tp[ now ] == 0 ){
    dp[ now ][ 0 ] = d[ now ];
    dp[ now ][ 1 ] = d[ now ];
  }else{
    dp[ now ][ 0 ] = -d[ now ];
    dp[ now ][ 1 ] = -d[ now ];
  }
  bool tok[ 2 ];
  int tdp[ 2 ];
  for( auto e : v[ now ] ){
    if( e.first == prt ) continue;
    go( e.first , now );
    for( int i = 0 ; i < 2 ; i ++ ){
      tok[ i ] = ok[ now ][ i ];
      tdp[ i ] = dp[ now ][ i ];
      ok[ now ][ i ] = false;
    }
    for( int ii = 0 ; ii < 2 ; ii ++ ){
      if( not tok[ ii ] ) continue;
      for( int i = 0 ; i < 2 ; i ++ ){
        if( not ok[ e.first ][ i ] ) continue;
        int nxti = max( i , ii );
        if( dp[ e.first ][ i ] < 0 ){
          if( -dp[ e.first ][ i ] <= e.second ){
            int nxtdp = tdp[ ii ] + dp[ e.first ][ i ];
            if( not ok[ now ][ nxti ] or
                nxtdp > dp[ now ][ nxti ] ){
              ok[ now ][ nxti ] = true;
              dp[ now ][ nxti ] = nxtdp;
            }
          }
        }else{
          {
            int send = min( dp[ e.first ][ i ] , e.second );
            int nxtdp = tdp[ ii ] + send;
            if( not ok[ now ][ nxti ] or
                nxtdp > dp[ now ][ nxti ] ){
              ok[ now ][ nxti ] = true;
              dp[ now ][ nxti ] = nxtdp;
            }
          }
          {
            if( not ok[ now ][ 1 ] or
                tdp[ ii ] > dp[ now ][ 1 ] ){
              ok[ now ][ 1 ] = true;
              dp[ now ][ 1 ] = tdp[ ii ];  
            }
          }
        }
      }
    }
  }
}
void solve(){
  go( 1 , 1 );
  puts( ( ok[ 1 ][ 1 ] and dp[ 1 ][ 1 ] >= 0 ) or
        ( ok[ 1 ][ 0 ] and dp[ 1 ][ 0 ] >= 0 ) ? "1" : "0" );
}
int main(){
  while( scanf( "%d" , &n ) == 1 ){
    init();
    solve();
  }
}
