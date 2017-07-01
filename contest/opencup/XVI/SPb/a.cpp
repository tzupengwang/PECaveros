#include <bits/stdc++.h>
using namespace std;
#define N 1111
typedef long long LL;
typedef pair<LL, LL> PII;
LL n , x[ N ] , y[ N ];
void init(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    cin >> x[ i ] >> y[ i ];
  }
}
LL d[ N ];
PII nor(LL a, LL b) {
  if ( b < 0 ) {
    a = -a;
    b = -b;
  }
  LL g = __gcd(abs(a), b);
  a /= g;
  b /= g;
  return PII{a, b};
}
void solve(){

  for ( int i = 0 ; i < n ; i ++ )
    d[ i ] = x[ i ] * x[ i ] + y[ i ] * y[ i ];

  set< PII > ans;
  for ( int i = 0 ; i < n ; i ++ )
    for ( int j = 0 ; j < i ; j ++ ) {
      LL dd = d[ i ] - d[ j ];
      LL dx = x[ i ] - x[ j ];
      if ( dx != 0 ) {
        ans.insert(nor(dd, dx));
      } else if ( dd == 0 ) {
        cout << 0 << endl;
      }
    }
  cout << ans.size() + 1 << endl;
}
int main(){
  init();
  solve();
}
