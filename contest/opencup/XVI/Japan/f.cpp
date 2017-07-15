#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 222
#define P 1021
int n , m , p;
vector< pair< int , pair<int,int> > > v[ N ];
#define T first
#define D second.first
#define V second.second
void init(){
  cin >> n >> m >> p;
  while( m -- ){
    int si , ti , di , vi;
    cin >> si >> ti >> di >> vi;
    v[ si ].push_back( { ti , { di , vi } } );
    v[ ti ].push_back( { si , { di , vi } } );
  }
}
LL bst[ N ][ P ];
double ans , mx[ N ];
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 0 ; j <= p ; j ++ )
      bst[ i ][ j ] = -1e9;
  bst[ 1 ][ 0 ] = 0;
  for( int j = 0 ; j <= p ; j ++ )
    for( int i = 1 ; i <= n ; i ++ ){
      if( bst[ i ][ j ] < 0 ) continue;
      for( auto e : v[ i ] ){
        if( j + e.D > p ) continue;
        bst[ e.T ][ j + e.D ] = max( bst[ e.T ][ j + e.D ] ,
                                     bst[ i ][ j ] + e.V );
      }
    }
  for( int i = 1 ; i <= n ; i ++ )
    for( auto e : v[ i ] )
      mx[ i ] = max( mx[ i ] , (double)e.V / e.D );
  ans = 0.0;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 0 ; j + j <= p ; j ++ ){
      if( bst[ i ][ j ] < 0 ) continue;
      ans = max( ans , bst[ i ][ j ] * 2. + mx[ i ] * ( p - j - j  ) );
    }
  printf( "%.9f\n" , ans );
}
int main(){
  init();
  solve();
}
