#include <bits/stdc++.h>
using namespace std;
#define N 12
typedef long long LL;
int n , c[ N ] , e[ N ];
LL dp[ N ][ 1 << N ];
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    cin >> c[ i ];
  for( int i = 0 ; i < n ; i ++ )
    cin >> e[ i ];
  dp[ 0 ][ 0 ] = 1;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < (1 << n) ; j ++ ){
      if( dp[ i ][ j ] == 0 ) continue;
      for( int k = 0 ; k < n ; k ++ ){
        if( (j >> k) & 1 ) continue;
        if( c[ k ] > e[ i ] ) continue;
        int nxtj = j | (1 << k);
        dp[ i + 1 ][ nxtj ] += dp[ i ][ j ];
      }
    }
  cout << dp[ n ][ (1 << n) - 1 ] << endl;
}
