// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<LD,LD> Pt;
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define X FI
#define Y SE
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-12
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
#ifndef ONLINE_JUDGE
#define debug(...) printf(__VA_ARGS__)
#else 
#define debug(...)
#endif
inline ll getint(){
  ll _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
inline ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
inline ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
inline ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = mul( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = mul( _tmp , _a , _mod );
  return _tmp;
}
ll mymul( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 0ll;
  ll _tmp = mymul( _a , _x / 2 , _mod );
  _tmp = add( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = add( _tmp , _a , _mod );
  return _tmp;
}
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 222
ll n , m;
ll a[ 4 ][ N ][ N ];
ll pr[] = {1097774749ll,1076767633ll,1000000007ll,1000000009ll};
void build(){

}
inline ll inv( ll x , ll p ){
  return mypow( x , p - 2 , p );
}
void init(){
  n = getint();
  m = getint();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ ){
      a[ 0 ][ i ][ j ] =
      a[ 1 ][ i ][ j ] =
      a[ 2 ][ i ][ j ] =
      a[ 3 ][ i ][ j ] = getint();
      for( int k = 0 ; k < 4 ; k ++ )
        a[ k ][ i ][ j ] = ( a[ k ][ i ][ j ] % pr[ k ] + pr[ k ] ) % pr[ k ];
    }
}
void solve(){
  ll ans = 0 , j = 1;
  for( int i = 1 ; i <= n ; i ++ ){
    int got = -1;
    while( got == -1 && j <= m ){
      for( int k = i ; k <= n ; k ++ )
        if( a[ 0 ][ k ][ j ] || a[ 1 ][ k ][ j ] ||
            a[ 2 ][ k ][ j ] || a[ 3 ][ k ][ j ] ){
          got = k; break;
        }
      if( got == -1 ) j ++;
    }
    if( got == -1 ) break;
    ans ++;
    for( int k = 1 ; k <= m ; k ++ )
      for( int u = 0 ; u < 4 ; u ++ )
        swap( a[ u ][ got ][ k ] , a[ u ][ i ][ k ] );
    for( int k = i + 1 ; k <= n ; k ++ ){
      LL dlt[ 4 ];
      for( int u = 0 ; u < 4 ; u ++ )
        dlt[ u ] = mul( a[ u ][ k ][ j ] , inv( a[ u ][ i ][ j ] , pr[ u ] ) , pr[ u ] );
      for( int u = 1 ; u <= m ; u ++ ){
        // a[ j ][ k ] -= a[ i ][ k ] * dlt;
        for( int l = 0 ; l < 4 ; l ++ )
          a[ l ][ k ][ u ] = sub( a[ l ][ k ][ u ] , mul( a[ l ][ i ][ u ] , dlt[ l ] , pr[ l ] ) , pr[ l ] );
      }
    }
  }
  cout << ans << endl;
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
