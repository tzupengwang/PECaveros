#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5+10;

int n , p[ MAXN ] , q[ MAXN ];
bool is_leaf_p[ MAXN ] , is_leaf_q[ MAXN ];
int depp[ MAXN ] , depq[ MAXN ];

int main() {
  ios_base::sync_with_stdio( 0 );cin.tie( 0 );
  cin >> n;
  for ( int i = 1 ; i <= n ; i++ ) cin >> p[ i ];
  for ( int i = 1 ; i <= n ; i++ ) cin >> q[ i ];
  fill ( is_leaf_p , is_leaf_p+n+1 , 1 );
  fill ( is_leaf_q , is_leaf_q+n+1 , 1 );
  for ( int i = 1 ; i <= n ; i++ ) is_leaf_p[ p[ i ] ] = 0;
  for ( int i = 1 ; i <= n ; i++ ) is_leaf_q[ q[ i ] ] = 0;
  for ( int i = n ; i >= 1 ; i-- ) depp[ i ] = depp[ p[ i ] ] + 1;
  for ( int i = n ; i >= 1 ; i-- ) depq[ i ] = depq[ q[ i ] ] + 1;
  int ans = 0 , cnt = 0;
  for ( int i = 1 ; i <= n ; i++ ) if ( is_leaf_p[ i ] ) {
    int cur = i;
    if ( !is_leaf_q[ cur ] ) {
      cnt += depp[ cur ];
      ans += depp[ cur ] - 1;
      continue;
    }
    while ( cur && p[ cur ] == q[ cur ] ) cur = p[ cur ]; 
    //cout << "  " << i << " " << cur << endl;
    if ( cur == 0 ) cnt++;
    else {
      cnt += depp[ cur ];
      ans += depp[ cur ] - 1;
    }
  }
  int cnt2 = 0;
  for ( int i = 1 ; i <= n ; i++ ) if ( is_leaf_q[ i ] ) cnt2++;
  //cout << ans << " " << cnt << " " << cnt2 << endl;
  ans += abs( cnt - cnt2 );
  cout << ans << endl;
}
