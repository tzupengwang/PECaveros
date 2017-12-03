#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 100020
#define Q 30030
#define BIG 456
int BIT[ N + N ];
inline int lb( int x ){ return x & (-x); }
inline void modify( int x , int d ){
  for( int i = x ; i < N + N ; i += lb( i ) )
    BIT[ i ] += d;
}
inline int query( int x ){
  int ret = 0;
  for( int i = x ; i ; i -= lb( i ) )
    ret += BIT[ i ];
  return ret;
}
LL ans[ Q ];
int n , m , f[ N + N ] , cnt[ N ];
int al[ Q ] , ar[ Q ];
int bl[ Q ] , br[ Q ];
vector< pair< pair<int,int> , pair<int,int> > > qq[ N + N ];
vector<int> v[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &f[ i ] );
    v[ f[ i ] ].push_back( i );
    cnt[ f[ i ] ] ++;
  }
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d%d%d" , &al[ i ] , &ar[ i ] , &bl[ i ] , &br[ i ] );
    qq[ ar[ i ]     ].push_back( { { bl[ i ] , br[ i ] } ,
                                   { i , +1 } } );
    qq[ al[ i ] - 1 ].push_back( { { bl[ i ] , br[ i ] } ,
                                   { i , -1 } } );
  }
}
void solve(){
  for( int i = 0 ; i < N ; i ++ )
    if( cnt[ i ] >= BIG ){
      for( int j : v[ i ] )
        modify( j , +1 );
      for( int j = 0 ; j < m ; j ++ ){
        LL ql = query( ar[ j ] ) - query( al[ j ] - 1 );
        LL qr = query( br[ j ] ) - query( bl[ j ] - 1 );
        ans[ j ] += ql * qr;
      }
      for( int j : v[ i ] )
        modify( j , -1 );
    }
  for( int i = 1 ; i <= n ; i ++ ){
    if( cnt[ f[ i ] ] < BIG ){
      for( int j : v[ f[ i ] ] )
        modify( j , +1 );
    }
    for( auto qs : qq[ i ] ){
      int ql = qs.first.first;
      int qr = qs.first.second;
      int who = qs.second.first;
      int bns = qs.second.second;
      int ret = query( qr ) - query( ql - 1 );
      ans[ who ] += bns * ret;
    }
  }
  for( int i = 0 ; i < m ; i ++ )
    printf( "%lld\n" , ans[ i ] );
}
int main(){
  init();
  solve();
}
