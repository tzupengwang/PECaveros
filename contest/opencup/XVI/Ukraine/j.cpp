#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL infll = 1000000000000000000LL;
inline LL mul( LL a , LL b ){
  if( a > infll / b ) return infll;
  return a * b;
}
LL mypow( LL a , LL b ){
  if( b == 0 ) return 1;
  LL ret = mypow( mul( a , a ) , b >> 1 );
  if( b & 1 ) ret = mul( ret , a );
  return ret;
}
LL n , kk;
vector<LL> v;
vector<LL> shrink( vector<LL>& vv ){
  sort( vv.begin() , vv.end() );
  vv.resize( unique( vv.begin() , vv.end() ) - vv.begin() );
  vector<LL> rv;
  for( int i = 0 ; i < kk ; i ++ ){
    bool ok = true;
    for( int j = 0 ; j < i and ok ; j ++ )
      if( vv[ i ] % vv[ j ] == 0 )
        ok = false;
    if( ok )
      rv.push_back( vv[ i ] );
  }
  return rv;
}
bool has[ 51 ];
void init(){
  scanf( "%lld%lld" , &n , &kk );
  //n = 1000000000;
  //kk = 42;
  v.clear();
  for( int i = 0 ; i < 51 ; i ++ )
    has[ i ] = false;
  for( int i = 0 ; i < kk ; i ++ ){
    LL x;
    scanf( "%lld" , &x );
    //x = 50 - i;
    v.push_back( x );
    has[ x ] = true;
  }
  v = shrink( v );
}
inline LL f( LL x , LL y ){
  if( x >= 60 ) return 0;
  if( x == 1 ) return y - 1;
  LL tmp = powl( y , 1. / x );
  for( LL i = tmp + 2 ; i >= 1 ; i -- )
    if( mypow( i , x ) <= y )
      return i - 1;
  assert( false );
  return 0;
}
inline LL lcm( LL a , LL b ){
  return ( a / __gcd( a , b ) ) * b;
}
int wt[ 62 ];
inline LL cnt( LL bdr ){
  if( has[ 1 ] ) return bdr;
  LL cc = 1;
  for( int i = 1 ; i < 60 ; i ++ )
    if( wt[ i ] )
      cc += wt[ i ] * f( i , bdr );
  return cc;
}
void solve(){
  for( int i = 0 ; i < 62 ; i ++ )
    wt[ i ] = 0;
  for( size_t i = 0 ; i < v.size() ; i ++ ){
    wt[ v[ i ] ] ++;
    for( size_t j = i + 1 ; j < v.size() ; j ++ ){
      int vl = lcm( v[ i ] , v[ j ] );
      if( vl < 60 ){
        wt[ vl ] --;
        for( size_t k = j + 1 ; k < v.size() ; k ++ ){
          int vl2 = lcm( vl , v[ k ] );
          if( vl2 < 60 )
            wt[ vl2 ] ++;
        }
      }
    }
  }
  LL bl = 1 , br = 100000000000000000LL , ba = br;
  while( bl <= br ){
    LL bmid = ( bl + br ) >> 1;
    LL cn = cnt( bmid );
    if( cn >= n ) ba = bmid , br = bmid - 1;
    else bl = bmid + 1;
  }
  printf( "%lld\n" , ba );
}
int main(){
  int _;
  scanf( "%d" , &_ );
  //_ = 987;
  while( _ -- ){
    init();
    solve();
  }
}
