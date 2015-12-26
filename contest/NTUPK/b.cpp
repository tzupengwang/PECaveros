#include <bits/stdc++.h>
using namespace std;
#define K 30
#define N 101010
typedef long long ll;
int n , a[ N ] , psum[ N ][ K ];
int bit( int ta , int tk ){ return ( ta >> tk ) & 1; }
int Sum( int tk , int tl , int tr ){
  int ttt = psum[ tr ][ tk ];
  if( tl ) ttt -= psum[ tl - 1 ][ tk ];
  return ttt;
}
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &a[ i ] );
  sort( a , a + n );
  for( int i = 0 ; i < K ; i ++ ){
    psum[ 0 ][ i ] = bit( a[ 0 ] , i );
    for( int j = 1 ; j < n ; j ++ )
      psum[ j ][ i ] = psum[ j ][ i ] + bit( a[ j ] , i );
  }
}
ll DP( int k , int l , int r ){
  if( k < 0 ) return 0;
  if( l >= r ) return 0;
  int bl = l , br = r , bmid = -1 , ba = -1;
  while( bl <= br ){
    bmid = ( bl + br ) >> 1;
    if( bit( a[ bmid ] , k ) ) ba = bmid , br = bmid - 1;
    else bl = bmid + 1;
  }
  ll tans = 0;
  if( ba == -1 )
    tans = DP( k - 1 , l , r );
  else{
    tans = DP( k - 1 , l , ba - 1 );
    tans += DP( k - 1 , ba , r );
  }
  if( ba != -1 && l < ba && ba <= r ){
  printf( "==== %d %d %d %d\n" , k , l , r , ba );
    int lft = ba - l;
    int rgt = r - ba + 1;
    ll mn = 1000000000;
    if( lft < rgt ){
      for( int i = l ; i < ba ; i ++ ){
        ll ttans = 0;
        int nl = ba , nr = r;
        for( int j = K - 1 ; j >= 0 ; j -- ){
          int now = bit( a[ i ] , j );
          int xl = nl , xr = nr , xmid = nl , xa = -1;
          while( xl <= xr ){
            xmid = ( xl + xr ) >> 1;
            if( bit( xmid , j ) == 1 ) xa = xmid , xr = xmid - 1;
            else xl = xmid + 1;
          }
          if( now == 1 ){
            if( xa == -1 ) ttans |= ( 1 << j );
            else nl = xa;
          }else{
            if( xa == nl ) ttans |= ( 1 << j );
            else if( xa != -1 ) nr = xa - 1;
          }
        }
        mn = min( mn , ttans );
      }
    }else{
      for( int i = ba ; i <= r ; i ++ ){
        ll ttans = 0;
        int nl = l , nr = ba - 1;
        for( int j = K - 1 ; j >= 0 ; j -- ){
          int now = bit( a[ i ] , j );
          int xl = nl , xr = nr , xmid = nl , xa = -1;
          while( xl <= xr ){
            xmid = ( xl + xr ) >> 1;
            if( bit( xmid , j ) == 1 ) xa = xmid , xr = xmid - 1;
            else xl = xmid + 1;
          }
          if( now == 1 ){
            if( xa == -1 ) ttans |= ( 1 << j );
            else nl = xa;
          }else{
            if( xa == nl ) ttans |= ( 1 << j );
            else if( xa != -1 ) nr = xa - 1;
          }
          printf( "adddd %d %d %d\n" , j , nl , nr );
        }
        mn = min( mn , ttans );
      }
    }
    printf( "add %lld\n" , mn );
    tans += mn;
  }
  return tans;
}
void solve(){
  printf( "%lld\n" , DP( 29 , 0 , n - 1 ) );
}
int main(){
  init();
  solve();
}
