#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mod = 1000000007;
#define N 50010
inline LL add( LL ui , LL vi ){
  ui += vi;
  return ui >= mod ? ui - mod : ui;
}
inline LL mul( LL ui , LL vi ){
  ui *= vi;
  return ui >= mod ? ui % mod : ui;
}
LL mypow( LL a , LL b ){
  if( b == 0 ) return 1;
  LL ret = mypow( mul( a , a ), b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
LL fac[ N ] , inv[ N ];
void build(){
  fac[ 0 ] = inv[ 0 ] = 1;
  for( LL i = 1 ; i < N ; i ++ ){
    fac[ i ] = mul( fac[ i - 1 ] , i );
    inv[ i ] = mypow( fac[ i ] , mod - 2 );
  }
}
inline LL C( LL a , LL b ){
  if( b > a || a < 0 ) return 0;
  return mul( fac[ a ] , mul( inv[ b ] , inv[ a - b ] ) );
}
LL n , k , a[ N ];
void init(){
  scanf( "%lld%lld" , &n , &k );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &a[ i ] );
  sort( a , a + n );
  reverse( a , a + n );
}
LL dp[ 2 ][ 1111 ];
vector< pair<LL,LL> > vv;
int _cs;
void go_dp(){
  for( int i = 0 ; i <= k ; i ++ )
    dp[ 0 ][ i ] = 0;
  dp[ 0 ][ 0 ] = 1;
  LL rest = n;
  for( size_t i = 0 ; i + 1 < vv.size() ; i ++ ){
    int pre = ((int)i) & 1 , now = 1 - pre;
    for( int j = 0 ; j <= k ; j ++ )
      dp[ now ][ j ] = 0;
    for( int u = 0 ; u <= vv[ i ].second ; u ++ ){
      LL ret = C( rest - u - 1 , vv[ i ].second - u );
      if( ret == 0 ) continue;
      for( int j = 0 ; j <= k ; j ++ ){
        if( dp[ pre ][ j ] == 0 ) continue;
        int to = j + vv[ i ].second - u;
        if( to > k ) continue;
        dp[ now ][ to ] = add( dp[ now ][ to ] , 
                               mul( dp[ pre ][ j ] , ret ) );
      }
    }
    rest -= vv[ i ].second;
    //for( int j = 0 ; j <= k ; j ++ )
      //printf( "%lld " , dp[ now ][ j ] );
    //puts( "" );
  }
  int _sz = (int)vv.size() - 1;
  printf( "Case %d: %lld\n" , ++ _cs , dp[ _sz & 1 ][ k ] );
}
void solve(){
  vv.clear();
  LL pre = -1 , pc = 0;
  for( int i = 0 ; i < n ; i ++ ){
    if( a[ i ] != pre ){
      if( pc )
        vv.push_back( { pre , pc } );
      pre = a[ i ]; pc = 1;
    }else pc ++;
  }
  if( pc ) vv.push_back( { pre , pc } );
  go_dp();
}
int main(){
  build();
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
