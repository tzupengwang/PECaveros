#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double ld;
int n , k;
ld ans;
ld cal( int p ){
  if( ((1 << n) - k - (1 << p) + 2) <= 0 )
    return 0;
  double ret = 1. , up = (1 << n) - k , dn = (1 << n) - 1;
  for( int _ = 0 ; _ < (1 << p) - 1 ; _ ++ ){
    ret *= up;
    ret /= dn;
    up -= 1;
    dn -= 1;
  }
  return ret;
}
int main(){
  cin >> n >> k;
  for( int p = 0 ; p < n ; p ++ )
    ans += cal( p );
  cout << fixed << setprecision( 12 ) << ans << endl;
}
