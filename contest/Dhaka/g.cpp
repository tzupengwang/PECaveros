// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
  ll _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = ( _tmp * _tmp ) % _mod;
  if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
  return _tmp;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 2042
ll lvl[ N ] , c[ N ][ N ];
ll dp[ 4 ][ N ][ N ][ 4 ];
ll ans[ N ][ N ];
void build(){
  lvl[ 0 ] = 1;
  for( ll i = 1 ; i < N ; i ++ )
    lvl[ i ] = ( lvl[ i - 1 ] * i ) % mod7;
  for( ll i = 0 ; i < N ; i ++ ) c[ i ][ i ] = c[ i ][ 0 ] = 1ll;
  for( ll i = 2 ; i < N ; i ++ )
    for( ll j = 1 ; j < i ; j ++ ){
      c[ i ][ j ] = ( c[ i - 1 ][ j - 1 ] +
                      c[ i - 1 ][ j ] );
      if( c[ i ][ j ] >= mod7 ) c[ i ][ j ] -= mod7;
    }
// 0 1 2 3
// X < _ >
  for( ll i = 0 ; i < 4 ; i ++ )
    for( ll j = 0 ; j < 4 ; j ++ ){
      if( i == 2 && j == 1 ) continue;
      if( i == 3 && j == 2 ) continue;
      ll nmsk = 0;
      if( i == 3 || j == 2 ) nmsk += 2;
      if( j == 3 ) nmsk ++;
      ll msk2 = 0;
      if( i == 2 || j == 1 ) msk2 += 2;
      if( i == 1 ) msk2 ++;
      dp[ msk2 ][ 2 ][ ( i != 0 ) + ( j != 0 ) ][ nmsk ] ++;
    }
  for( ll i = 0 ; i < 4 ; i ++ )
    for( ll j = 2 ; j + 1 < N ; j ++ )
      for( ll k = 0 ; k <= j ; k ++ )
        for( ll msk = 0 ; msk < 4 ; msk ++ ){
          ll ppre = msk / 2;
          ll npre = msk % 2;
          for( ll nxt = 0 ; nxt < 4 ; nxt ++ ){
            if( nxt == 1 && ppre > 0 ) continue;
            if( nxt == 2 && npre > 0 ) continue;
            ll nxtk = k + ( nxt != 0 );
            int nxtmsk = 0;
            if( npre || nxt == 2 ) nxtmsk += 2;
            if( nxt == 3 ) nxtmsk ++;
            dp[ i ][ j + 1 ][ nxtk ][ nxtmsk ] += dp[ i ][ j ][ k ][ msk ];
            dp[ i ][ j + 1 ][ nxtk ][ nxtmsk ] %= mod7;
          }
          for( ll nxt = 0 ; nxt < 4 ; nxt ++ ){
            if( nxt == 1 && ppre > 0 ) continue;
            if( nxt == 2 && npre > 0 ) continue;
            if( nxt == 2 && ( i & 1 ) ) continue;
            if( nxt == 3 && ( i >= 2 ) ) continue;
            if( npre > 0 && ( i & 1 ) ) continue;
            ll nxtk = k + ( nxt != 0 );
            ans[ j + 1 ][ nxtk ] += ( dp[ i ][ j ][ k ][ msk ] * lvl[ ( j + 1 ) - nxtk ] ) % mod7;
            ans[ j + 1 ][ nxtk ] %= mod7;
          }
        }
}
int n , k;
void init(){
  n = getint();
  k = getint();
}
ll par[ N ];
void solve(){
  ll nans = ans[ n ][ k ];
  par[ k ] = 1;
  for( ll i = k + 1 ; i <= n ; i ++ ){
    ll tk = c[ i ][ k ];
    for( ll j = k + 1 ; j < i ; j ++ ){
      ll dk = ( c[ i ][ j ] * par[ j ] ) % mod7;
      tk = ( tk + dk + mod7 ) % mod7;
    }
    tk = 1 - tk;
    par[ i ] = ( tk + mod7 ) % mod7;
    ll dans = ( par[ i ] * ans[ n ][ i ] ) % mod7;
    nans = ( nans + dans ) % mod7;
  }
  printf( "Case %d: %lld\n" , ++ cs , nans );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
