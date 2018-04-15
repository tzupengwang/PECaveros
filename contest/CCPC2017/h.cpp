#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 12
int n , m;
int c[ N ][ 4 ] , ct[ N ];
int d[ N ][ 4 ] , dt[ N ];
void init(){
  cin >> n >> m;
  vector<int> id;
  for( int i = 0 ; i < n ; i ++ ){
    cin >> ct[ i ];
    for( int j = 0 ; j < ct[ i ] ; j ++ ){
      cin >> c[ i ][ j ];
      id.push_back( c[ i ][ j ] );
    }
  }
  for( int i = 0 ; i < m ; i ++ ){
    cin >> dt[ i ];
    for( int j = 0 ; j < dt[ i ] ; j ++ ){
      cin >> d[ i ][ j ];
      id.push_back( d[ i ][ j ] );
    }
  }
  sort( id.begin() , id.end() );
  id.resize( unique( id.begin() , id.end() ) - id.begin() );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < ct[ i ] ; j ++ )
      c[ i ][ j ] = lower_bound( id.begin() , id.end() , c[ i ][ j ] ) - id.begin();
  for( int i = 0 ; i < m ; i ++ )
    for( int j = 0 ; j < dt[ i ] ; j ++ )
      d[ i ][ j ] = lower_bound( id.begin() , id.end() , d[ i ][ j ] ) - id.begin();
}
LL nd[ N ] , can[ N ];
bool ok[ 1 << N ][ N ];
int dp[ N ][ 1 << N ];
int gt[ N ][ 1 << N ] , stmp;
int DP( int nn , int msk ){
  if( nn < 0 ) return 0;
  if( gt[ nn ][ msk ] == stmp ) return dp[ nn ][ msk ];
  gt[ nn ][ msk ] = stmp;
  dp[ nn ][ msk ] = 0;
  int ret = DP( nn - 1 , msk );
  for( int smsk = msk ; smsk ; smsk = (smsk - 1) & msk )
    if( ok[ smsk ][ nn ] )
      ret = max( ret , 1 + DP( nn - 1 , msk ^ smsk ) );
  return dp[ nn ][ msk ] = ret;
}
int cs;
void solve(){
  for( int i = 0 ; i < n ; i ++ ){
    nd[ i ] = 0;
    for( int j = 0 ; j < ct[ i ] ; j ++ )
      nd[ i ] |= (1LL << c[ i ][ j ]);
  }
  for( int i = 0 ; i < m ; i ++ ){
    can[ i ] = 0;
    for( int j = 0 ; j < dt[ i ] ; j ++ )
      can[ i ] |= (1LL << d[ i ][ j ]);
  }
  for( int i = 1 ; i < (1 << m) ; i ++ ){
    LL all = 0;
    for( int j = 0 ; j < m ; j ++ )
      if( (i >> j) & 1 )
        all |=  can[ j ];
    for( int j = 0 ; j < n ; j ++ ){
      if( (all & nd[ j ]) == nd[ j ] )
        ok[ i ][ j ] = true;
      else
        ok[ i ][ j ] = false;
    }
  }
  ++ stmp;
  printf( "Case #%d: %d\n" , ++ cs , DP( n - 1 , (1 << m) - 1 ) );
}
int main(){
  int t; cin >> t; while( t -- ){
    init();
    solve();
  }
}
