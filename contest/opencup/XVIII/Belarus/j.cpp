#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define K 32
LL n , f[ K ];
int main(){
  f[ 1 ] = 1;
  for( LL i = 2 ; i < K ; i ++ )
    f[ i ] = f[ i - 1 ] + f[ i - 2 ];
  //cerr << f[ K - 1 ] << endl;
  cin >> n;
  LL ax = 0 , ay = n;
  for( LL x = 0 ; x <= n ; x ++ )
    for( LL i = 0 ; i + 1 < K and x * f[ i ] <= n ; i ++ ){
      LL res = n - x * f[ i ];
      if( res % f[ i + 1 ] ) continue;
      LL y = res / f[ i + 1 ];
      if( x + y < ax + ay )
        ax = x , ay = y;
    }
  cout << ax << " " << ay << endl;
}
