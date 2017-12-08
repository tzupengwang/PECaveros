#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n;
int ans;
int highbit( LL x ){
  int ret = 0;
  if( x & 0xFFFFFFFF00000000LL ) x >>= 32 , ret += 32;
  if( x & 0x00000000FFFF0000LL ) x >>= 16 , ret += 16;
  if( x & 0x000000000000FF00LL ) x >>=  8 , ret +=  8;
  if( x & 0x00000000000000F0LL ) x >>=  4 , ret +=  4;
  if( x & 0x000000000000000CLL ) x >>=  2 , ret +=  2;
  if( x & 0x0000000000000002LL ) x >>=  1 , ret +=  1;
  return ret;
}
LL cnt[ 64 ][ 64 ];
int main(){
  for( LL i = 1 ; i <= 2000000000 ; i ++ )
    if( i * i <= 1000000000000000000LL )
      cnt[ highbit( i * i ) ][ __builtin_popcountll( i * i ) ] ++;
  for( int i = 0 ; i < 64 ; i ++ )
    for( int j = 0 ; j < 64 ; j ++ )
      if( cnt[ i ][ j ] )
        printf( "cnt[%d][%d]=%lld;\n" , i , j , cnt[ i ][ j ] );
  return 0;
  cin >> n;
  int bt = __builtin_popcountll(n);
  LL K = 1;
  while (K <= n) K <<= 1;
  LL K2 = K;
  K >>= 1;

  LL bl = 1 , br = 2000000000 , ba = 0;
  while( bl <= br ){
    LL bmid = (bl + br) >> 1;
    if( bmid * bmid < K )
      bl = bmid + 1;
    else
      ba = bmid, br = bmid - 1;
  }
  //cout << ba << endl;
  K2 = min(K2, (LL)1e18 + 1);
  while( true ){
    LL ba2 = ba * ba;
    if( ba2 >= K2 ) break;
    if( __builtin_popcountll( ba2 ) == bt )
      ans ++;
    ba ++;
  }
  cout << ans << endl;
}
