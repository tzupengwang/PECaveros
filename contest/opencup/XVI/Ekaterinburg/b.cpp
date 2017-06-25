#include <bits/stdc++.h>
using namespace std;
set<int> S;
int n , a;
int main(){
  cin >> n; while( n -- ){
    cin >> a;
    for( long long i = 1 ; i * i <= a ; i ++ )
      if( a % i == 0 ){
        S.insert( i );
        S.insert( a / i );
      }
  }
  int ans = 1;
  while( S.count( ans ) )
    ans ++;
  cout << ans << endl;
}
