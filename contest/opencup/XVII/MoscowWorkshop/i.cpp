#include <bits/stdc++.h>
using namespace std;
#define N 10000010
typedef unsigned int uint;
uint n , q , x0 , x1 , a , b , c;
uint next(){
  uint t = x0 * a + x1 * b + c;
  x0 = x1;
  x1 = t;
  return x0 >> 2;
}
uint g[ N ];
uint mn , idx;
uint ans;
void refind(){
  idx = 0;
  for( uint i = 1 ; i < n ; i ++ )
    if( g[ i ] < g[ idx ] )
      idx = i;
  mn = g[ idx ];
}
int main(){
  cin >> n >> q >> x0 >> x1 >> a >> b >> c;
  for( uint i = 0 ; i < n ; i ++ )
    g[ i ] = ( (uint)1 << 31 ) - 1;
  mn = g[ 0 ]; idx = 0;
  uint bs = 1;
  uint mul = 10099;
  for( uint _ = 0 ; _ < q ; _ ++ ){
    bs *= mul;
    uint i = next() % n;
    uint x = next();
    if( i == idx and x > g[ i ] ){
      g[ i ] = x;
      refind();
    }else{
      if( x < mn )
        mn = x , idx = i;
      g[ i ] = x;
    }
    ans += mn * bs;
  }
  cout << ans << endl;
}
