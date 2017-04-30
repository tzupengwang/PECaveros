#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;
const int MAXM = 1e4+10;
const int LOG  = 22;

int n , MN , MX;
int M[ MAXN ] , C[ MAXN ];

inline bool chk( int m ) {
  static bitset<MAXM> dp;
  vector< int > vec{0};
  for ( int i = 1 ; i <= n ; i++ ) {
    int cnt = C[ i ] / m;
    int cur = 1;
    while( cnt ) {
      cur = min( cur , cnt );
      cnt -= cur;
      vec.push_back( cur*M[ i ] );
      cur <<= 1;
    }
  }
  dp.reset();
  dp[ 0 ] = 1; 
  for ( int i = 1 ; i < vec.size() ; i++ ) {
    if ( vec[ i ] > MX ) continue;
    dp = dp | ( dp << vec[ i ] );
  }
  for ( int x = MN ; x <= MX ; x++ ) if ( dp[ x ] ) return 1;
  return 0;
}

int main() {
#ifndef LOCAL
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  cin >> n >> MN >> MX;
  for ( int i = 1 ; i <= n ; i++ )
    cin >> M[ i ] >> C[ i ];
  int l = 1 , r = 1e6 , ans = 0;
  while ( l <= r ) {
    int mid = ( l+r ) / 2;
    if ( chk( mid ) ) {
      l = mid+1;
      ans = mid;
    } else r = mid-1;
  }
  cout << ans << endl;
}
