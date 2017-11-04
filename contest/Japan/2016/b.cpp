#include <bits/stdc++.h>
using namespace std;
#define N 111
int a[ N ][ N ] , bs[ N ];
int cal( int vl ){
  int code = 0;
  for( int i = 4 ; i >= 0 ; i -- ){
    int cur = ( vl / bs[ i ] ) % 10;
    code = a[ code ][ cur ];
  }
  return code;
}
int main(){
  bs[ 0 ] = 1;
  for( int i = 1 ; i < 10 ; i ++ )
    bs[ i ] = bs[ i - 1 ] * 10;
  for( int i = 0 ; i < 10 ; i ++ )
    for( int j = 0 ; j < 10 ; j ++ )
      cin >> a[ i ][ j ];
  int ans = 0;
  for( int i = 0 ; i < 10000 ; i ++ ){
    int code = 0;
    for( int j = 3 ; j >= 0 ; j -- ){
      int cur = ( i / bs[ j ] ) % 10;
      code = a[ code ][ cur ];
    }
    int result = i * 10 + code;
    bool ok = true;
    for( int j = 0 ; j < 5 ; j ++ ){
      int vl = ( result / bs[ j ] ) % 10;
      int res = result - vl * bs[ j ];
      for( int k = 0 ; k < 10 ; k ++ ){
        if( k == vl ) continue;
        int now = res + k * bs[ j ];
        if( cal( now ) == 0 )
          ok = false;
      }
    }
    for( int j = 0 ; j < 4 ; j ++ ){
      int vl1 = ( result / bs[ j ]     ) % 10;
      int vl2 = ( result / bs[ j + 1 ] ) % 10;
      int res = result - vl1 * bs[ j ]
                       - vl2 * bs[ j + 1 ];
      res += vl2 * bs[ j ] +
             vl1 * bs[ j + 1 ];
      if( res == result ) continue;
      if( cal( res ) == 0 )
        ok = false;
    }
    if( not ok )
      ans ++;
  }
  cout << ans << endl;
}
