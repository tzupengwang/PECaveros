#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL l , r , q;
int main(){
  cin >> l >> r >> q;
  if( r < q )
    cout << "infinity\n";
  else{
    LL x = (r - r % q);
    LL tl = (l - l % q);
    if( tl < x )
      x = q;
    LL ans = 0;
    for( LL i = 1 ; i * i <= x ; i ++ ){
      if( x % i ) continue;
      ans ++;
      if( i * i < x )
        ans ++;
    }
    cout << ans << endl;
  }
}
