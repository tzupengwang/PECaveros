#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL n , f[ N ] , p[ N ] , m[ N ] , s[ N ];
vector< pair<int,int> > v[ N ];
LL ans;
bool vst[ N ];
int ind[ N ] , v2[ N ];
void go( int now ){
  while( now ){
    vst[ now ] = true;
    if( v2[ now ] == 0 ) return;

    ans += m[ now ] - p[ v2[ now ] ];

    now = v2[ now ];
  }
}

void go2( int now ){
  vector< pair<int,int> > cyc;
  LL sum = 0 , bst = 0;
  while( not vst[ now ] ){
    vst[ now ] = true;
    cyc.push_back( { now , m[ now ] - p[ v2[ now ] ] } );
    sum += m[ now ] - p[ v2[ now ] ];
    now = v2[ now ];
  }
  if( cyc.size() == 1u ){
    ans += sum;
    return;
  }
  for( size_t i = 0 ; i < cyc.size() ; i ++ ){
    int tnow = cyc[ i ].first;
    LL tans = sum - cyc[ i ].second;
    
    if( v[ tnow ].size() > 1u and
        v[ tnow ][ 1 ].first < m[ tnow ] )
      tans += m[ tnow ] - v[ tnow ][ 1 ].first;

    bst = max( bst , tans );

  }
  ans += bst;
}

int main(){
  scanf( "%lld" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%lld%lld%lld%lld" , &f[ i ] , &p[ i ] , &m[ i ] , &s[ i ] );
    v[ f[ i ] ].push_back( { p[ i ] , i } );
  }
  for( int i = 1 ; i <= n ; i ++ )
    sort( v[ i ].begin() , v[ i ].end() );
  for( int i = 1 ; i <= n ; i ++ ){
    if( not v[ i ].empty() and v[ i ][ 0 ].first < m[ i ] ){
      ans += (m[ i ] - v[ i ][ 0 ].first) * (s[ i ] - 1);
      v2[ i ] = v[ i ][ 0 ].second;
      ind[ v[ i ][ 0 ].second ] ++;
    }
  }
  for( int i = 1 ; i <= n ; i ++ )
    if( not vst[ i ] and ind[ i ] == 0 )
      go( i );

  for( int i = 1 ; i <= n ; i ++ )
    if( not vst[ i ] )
      go2( i );

  cout << ans << endl;
}
