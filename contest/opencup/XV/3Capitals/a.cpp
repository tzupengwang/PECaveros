#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n;
inline LL rev( LL x ){
  LL ret = 0;
  for( int i = 0 ; i < 32 ; i ++ )
    ret = (ret << 1) | ((x >> i) & 1);
  return ret;
}
int main(){
  cin >> n;
  LL msk = (1LL << 16) - 1;
  if( (n >> 16) )
    cout << ( (n & msk) + (rev(n) & msk) + 1 ) << endl;
  else
    cout << n << endl;
}
