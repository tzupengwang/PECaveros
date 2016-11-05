#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10000001
const LL mod = 1000000007;
LL mypow( LL a , LL b ){
  if( b == 0 ) return 1;
  LL ret = mypow( a * a , b >> 1 );
  if( b & 1ll ) ret *= a;
  return ret;
}
LL mypowmod( LL a , LL b ){
  if( b == 0 ) return 1;
  LL ret = mypow( ( a * a ) % mod , b >> 1 );
  if( b & 1ll ) ret = ( ret * a ) % mod;
  return ret;
}
LL ps[ N ];
bool isp[ N ];
void build(){
  for( int i = 1 ; i < N ; i ++ ) ps[ i ] = 1;
  for( int i = 2 ; i < N ; i ++ ) if( !isp[ i ] ){
    ps[ i ] = i;
    for( int j = N / i ; j >= i ; j -- )
      isp[ i * j ] = true;
  }
  for( int i = 2 ; i < N ; i ++ )
    ps[ i ] = ( ps[ i ] * ps[ i - 1 ] ) % mod;
}
LL n;
int _cs;
void solve(){
  vector< pair<LL,LL> > vv;
  for( int i = 2 ; i <= 60 ; i ++ ){
    LL cand = powl( n , 1.0 / i ) , ya = 1;
    LL bst = powl( 1e17 , 1.0 / i );
    for( LL j = max( 1ll , cand - 10 ) ; j <= min( bst , cand + 1 ) ; j ++ ){
      LL tmp = mypow( j , i );
      if( tmp <= n )
        ya = j;
    }
    if( ya == 1 ) break;
    //if( vv.size() && ya == vv.back().first )
      //vv.pop_back();
    vv.push_back( { ya , i } );
  }
  LL ans = 1;
  if( vv.size() ){
    int pre = 1;
    for( auto i : vv ){
      int mr = i.second - pre;
      ans = ( ans * ps[ i.first ] ) % mod;
      //ans = ( ans * mypowmod( ps[ i.first ] , mr ) ) % mod;
      pre = i.second;
    }
  }
  printf( "Case %d: %lld\n" , ++ _cs , ans );
}
int t;
int main(){
  build();
  scanf( "%d" , &t ); while( t -- ){
    scanf( "%lld" , &n );
    solve();
  }
}
