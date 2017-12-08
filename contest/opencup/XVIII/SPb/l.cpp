#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 60
LL n , a[ N ];
map<LL,LL> cnt;
LL cal(){
  if( n == 1 ) return 0;
  int hf = n / 2 , nhf = n - hf;
  {
    LL vl = 0;
    for( int i = 0 ; i < hf ; i ++ )
      vl ^= a[ i ];
    for( int i = 0 ; i < (1 << hf) ; i ++ ){
      LL tvl = 0;
      for( int j = 0 ; j < hf ; j ++ )
        if( (i >> j) & 1 )
          tvl ^= a[ j ];
      LL tmp = tvl ^ (tvl ^ vl);
      cnt[ tmp ] ++;
    }
  }
  LL ans = 0;
  {
    LL vl = 0;
    for( int i = 0 ; i < nhf ; i ++ )
      vl ^= a[ hf + i ];
    for( int i = 0 ; i < (1 << nhf) ; i ++ ){
      LL tvl = 0;
      for( int j = 0 ; j < nhf ; j ++ )
        if( (i >> j) & 1 )
          tvl ^= a[ hf + j ];
      LL tmp = tvl ^ (tvl ^ vl);
      ans += cnt[ tmp ];
    }
  }
  LL tmp = 0;
  for( int i = 0 ; i < n ; i ++ )
    tmp ^= a[ i ];
  if( tmp == 0 ) ans -= 2;
  return ans;
}
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    cin >> a[ i ];
  cout << cal() << endl;
}
