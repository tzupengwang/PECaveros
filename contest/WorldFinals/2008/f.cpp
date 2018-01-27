#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n , _cs;
LL cal(){
  if( n == 4 ) return 1;
  else if( n <= 3 or n % 2 ) return 0;
  else{
    LL k = (n - 4) / 2;
    return (k + k + 4) * (k + 3) * (k + 2) * (k + 1) / 24;
  }
}
int main(){
  while( cin >> n and n ){
    printf( "Case %lld: %lld\n" , ++ _cs , cal() );
  }
}
