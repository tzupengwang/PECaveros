// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef pair<LD,LD> Pt;
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
#define eps 1e-9
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
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = ( _tmp * _tmp ) % _mod;
  if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
  return _tmp;
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
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 303030
int n , m;
D r , c[ N ] , x[ N ];
void build(){

}
int gl[ N ] , gr[ N ];
void init(){
  n = getint(); m = getint();
  scanf( "%lf" , &r );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%lf" , &c[ i ] );
  for( int i = 1 ; i <= m ; i ++ )
    scanf( "%lf" , &x[ i ] );
  for( int i = 1 ; i <= m ; i ++ ){
// 1 ... hf
// hf + 1 ... n
    int bl = 1 , br = n , bm , hf = 0;
    while( bl <= br ){
      bm = ( bl + br ) >> 1;
      if( c[ bm ] < x[ i ] ) hf = bm , bl = bm + 1;
      else br = bm - 1;
    }
    bl = 1, br = hf, gl[ i ] = hf + 1;
    while( bl <= br ){
      bm = ( bl + br ) >> 1;
      D dlt = x[ i ] - c[ bm ];
      if( 1.0 + dlt * dlt < r * r + eps ) gl[ i ] = bm , br = bm - 1;
      else bl = bm + 1;
    }
    bl = hf + 1, br = n, gr[ i ] = hf;
    while( bl <= br ){
      bm = ( bl + br ) >> 1;
      D dlt = c[ bm ] - x[ i ];
      if( 1.0 + dlt * dlt < r * r + eps ) gr[ i ] = bm , bl = bm + 1;
      else br = bm - 1;
    }
  }
}
void solve(){
  D ans = 0, pos = c[ 1 ];
  for( int il = 1 , ir = 1 ; il <= m ; il = ir ){
    int tl = gl[ il ];
    int tr = gr[ il ];
    while( ir <= m && 
        max( tl , gl[ ir ] ) <=
        min( tr , gr[ ir ] ) ){
      tl = max( tl , gl[ ir ] );
      tr = min( tr , gr[ ir ] );
      ir ++;
    }
    if( fabs( pos - c[ tl ] ) < fabs( pos - c[ tr ] ) ){
      ans += fabs( pos - c[ tl ] );
      pos = c[ tl ];
    }else{
      ans += fabs( pos - c[ tr ] );
      pos = c[ tr ];
    }
  }
  printf( "%.1f\n" , ans );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
