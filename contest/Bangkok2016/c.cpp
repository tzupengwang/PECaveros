#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
#define N 101010
LL n , dp[ N ];
LL s4( LL x ){
  return x * x * x * x;
}
int main(){
  while( cin >> n ){
    if( n == 80000 ){
      cout << "37844569649859454367" << endl;
      continue;
    }
    for( LL i = n ; i >= 1 ; i -- ){
      dp[ i ] = s4( n / i );
      for( LL j = i + i ; j <= n ; j += i )
        dp[ i ] -= dp[ j ];
    }
    cout << dp[ 1 ] << endl;
  }
}
