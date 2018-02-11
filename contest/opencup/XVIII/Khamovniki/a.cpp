#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
int n , s , ord[ N ] , tot , nc , sc;
int nor[ N ] , spe[ N ];
int dp[ N ][ 1 << 10 ] , bt[ 1 << 10 ] , lst[ N ];
bool gt[ N ][ 1 << 10 ];
int DP( int now , int msk ){
  if( now == tot ){
    assert( msk == (((1 << (n + n)) - 1)) );
    return 0;
  }
  if( gt[ now ][ msk ] ) return dp[ now ][ msk ];
  int bst = 0; bool gg = false;
  if( ((msk >> (ord[ now ] - 1)) & 1) == 0 ){
    int ret = DP( now + 1 , msk | (1 << (ord[ now ] - 1)) );
    if( ord[ now ] <= n ) ret += spe[ bt[ msk ] ];
    else ret -= spe[ bt[ msk ] ];
    if( !gg ){
      gg = true;
      bst = ret;
    }else if( ord[ now ] <= n and ret > bst )
      bst = ret;
    else if( ord[ now ] > n and ret < bst )
      bst = ret;
  }
  if( now == lst[ ord[ now ] ] and
      ((msk >> (ord[ now ] - 1)) & 1) == 0 );
  else{
    int ret = DP( now + 1 , msk );
    int pre = now - bt[ msk ];
    if( ord[ now ] <= n ) ret += nor[ pre ];
    else ret -= nor[ pre ];
    if( !gg ){
      gg = true;
      bst = ret;
    }else if( ord[ now ] <= n and ret > bst )
      bst = ret;
    else if( ord[ now ] > n and ret < bst )
      bst = ret;
  }
  assert( gg );
  gt[ now ][ msk ] = true;
  //printf( "%d %d %d\n" , now , msk , bst );
  return dp[ now ][ msk ] = bst;
}
int main(){
  for( int i = 1 ; i < (1 << 10) ; i ++ )
    bt[ i ] = bt[ i >> 1 ] + (i & 1);
  scanf( "%d%d" , &n , &s );
  tot = (n + n) * (s + 1);
  for( int i = 0 ; i < tot ; i ++ ){
    scanf( "%d" , &ord[ i ] );
    lst[ ord[ i ] ] = i;
  }
  //cerr << tot << endl;
  {
    scanf( "%d" , &nc );
    for( int i = 0 ; i < nc ; i ++ )
      scanf( "%d" , &nor[ i ] );
    sort( nor , nor + nc );
    reverse( nor , nor + nc );
  }
  {
    scanf( "%d" , &sc );
    for( int i = 0 ; i < sc ; i ++ )
      scanf( "%d" , &spe[ i ] );
    sort( spe , spe + sc );
    reverse( spe , spe + sc );
  }
  printf( "%d\n" , DP( 0 , 0 ) );
}
