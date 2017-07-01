#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
LL n , a[ N ] , b[ N ];
void init(){
  cin >> n;
  for( LL i = 0 ; i < n ; i ++ )
    cin >> a[ i ];
  for( LL i = 0 ; i < n ; i ++ )
    cin >> b[ i ];
}
const LL INF = 1e15;
LL dp[ N ][ 2 ];
void solve(){
  for( int i = 1 ; i < n ; i ++ )
    if( b[ i ] >= a[ i - 1 ] or
        a[ i ] <= b[ i - 1 ] ){
      puts( "-1" );
      return;
    }
  dp[ 0 ][ 0 ] = 0;
  dp[ 0 ][ 1 ] = a[ 0 ] - b[ 0 ];
  for( int i = 1 ; i < n ; i ++ ){
    dp[ i ][ 0 ] = dp[ i ][ 1 ] = INF;
    if( b[ i ] <= b[ i - 1 ] ) {
      dp[ i ][ 0 ] = min( dp[ i ][ 0 ] , dp[ i - 1 ][ 0 ] );
      dp[ i ][ 1 ] = min( dp[i][1] , dp[i-1][0] + a[i]-b[i] );
    }
    if( a[ i ] >= a[ i - 1 ] ) {
      dp[ i ][ 1 ] = min( dp[ i ][ 1 ] , dp[ i - 1 ][ 1 ] );
      dp[ i ][ 0 ] = min( dp[i][0] , dp[i-1][1] + a[i]-b[i] );
    }
  }
  LL ans = dp[ n - 1 ][ 0 ];
  //LL ans = min( dp[ n - 1 ][ 0 ] , dp[ n - 1 ][ 1 ] );
  if( ans >= INF ) ans = -1;
  cout << ans << endl;
  //cout << min( dp[ n - 1 ][ 0 ] , dp[ n - 1 ][ 1 ] ) << endl;
}
int main(){
  init();
  solve();
}
