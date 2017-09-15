#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n;
int main(){
  cin >> n;
  vector<int> per;
  for( int i = 1 ; i <= n ; i ++ )
    per.push_back( i );
  LL ans = 0;
  do{
    for( int j = 0 ; j < (1 << n) ; j ++ ){
      bool ok = true;
      for( int k = 0 ; k < n ; k ++ )
        if( ((j >> k) & 1) and per[ k ] == k + 1 ){
          ok = false;
          break;
        }
      if( ok ) ans ++;
    }
  }while( next_permutation( per.begin() , per.end() ) );
  cout << ans << endl;
}
