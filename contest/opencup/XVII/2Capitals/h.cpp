#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 222
const int mod = 1000000007;
typedef long long LL;
int add( int a , int b ){
  a += b;
  return a >= mod ? a - mod : a;
}
int sub( int a , int b ){
  a -= b;
  return a <  0   ? a + mod : a;
}
int mul( LL a , LL b ){
  a *= b;
  return a >= mod ? a % mod : a;
}
int n , m , k , C[ N ][ N ];
bitset<101> b[ N + N ] , rb[ N + N ];
void init(){
  cin >> n >> m >> k;
  for( int i = 0 ; i < m ; i ++ ){
    int sz; cin >> sz; while( sz -- ){
      int x; cin >> x;
      b[ i ][ x ] = 1;
    }
    for( int j = 1 ; j <= n ; j ++ )
      b[ m + i ][ j ] = !b[ i ][ j ];
  }
  for( int i = 0 ; i < m + m ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      rb[ i ][ j ] = !b[ i ][ j ];
  for( int i = 0 ; i < N ; i ++ )
    C[ i ][ 0 ] = C[ i ][ i ] = 1;
  for( int i = 2 ; i < N ; i ++ )
    for( int j = 1 ; j < i ; j ++ )
      C[ i ][ j ] = add( C[ i - 1 ][ j ] , C[ i - 1 ][ j - 1 ] );
}
int ans;
void go( int now , int cnt , bitset<101> in , bitset<101> out ){
  if( (int)in.count() < k or (int)out.count() < k )
    return;
  if( now == m + m ){
    if( cnt == 0 ) return;
    if( cnt & 1 )
      ans = add( ans , mul( C[ in.count() ][ k ],
                            C[ out.count() ][ k ] ) );
    else
      ans = sub( ans , mul( C[ in.count() ][ k ],
                            C[ out.count() ][ k ] ) );
    return;
  }
  go( now + 1 , cnt , in , out );
  go( now + 1 , 1 + cnt , in & b[ now ] , out & rb[ now ] );
}
void solve(){
  bitset<101> bb;
  for( int i = 1 ; i <= n ; i ++ )
    bb[ i ] = 1;
  go( 0 , 0 , bb , bb );
  cout << ans << endl;
}
int main(){
  init();
  solve();
}
