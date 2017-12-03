#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
LL n , ans;
int main(){
  cin >> n;
  LL bs = 1;
  for( LL i = 1 ; n > 0 ; i ++ ){
    LL tk = min( i , n );
    LL cst = tk * bs % mod;
    ans = (ans + cst) % mod;
    n -= tk;
    bs = (bs + bs) % mod;
  }
  cout << ans << endl;
}
