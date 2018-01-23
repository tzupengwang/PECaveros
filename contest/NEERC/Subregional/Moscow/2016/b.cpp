#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL l , r , w;
int main(){
  cin >> l >> r >> w;
  LL gg = __gcd( r , w );
  LL k = ( r - 1 ) / gg * gg;
  while( k > r - 1 ) k -= gg;
  if( k > l - w )
    cout << "DEADLOCK" << endl;
  else
    cout << "OK" << endl;
}
