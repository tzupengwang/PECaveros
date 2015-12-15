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
#define N 222
class Matrix{
 public:
  int n;
  D a[ N ][ N ];
  Matrix(){}
  void gauss(){
    for( int i = 0 ; i < n ; i ++ ){
      int pvt = i;
      while( pvt < n && equal( a[ pvt ][ i ] , 0 ) ) pvt ++;
      if( i != pvt ){
        for( int j = 0 ; j <= n + 1 ; j ++ )
          swap( a[ i ][ j ] , a[ pvt ][ j ] );
      }
      D ii = a[ i ][ i ];
      for( int j = 0 ; j <= n + 1 ; j ++ )
        a[ i ][ j ] = a[ i ][ j ] / ii;
      for( int j = 0 ; j < n ; j ++ ){
        if( i == j ) continue;
        D dlt = a[ j ][ i ];
        for( int k = 0 ; k <= n + 1 ; k ++ )
          a[ j ][ k ] = a[ j ][ k ] - a[ i ][ k ] * dlt;
      }
    }
  }
};
int n , cst[ N ] , num[ N ];
int a[ N ][ N ];
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ) cst[ i ] = getint();
  for( int i = 0 ; i < n - 1 ; i ++ ) num[ i ] = getint();
  for( int i = 0 ; i < n - 1 ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      a[ i ][ j ] = getint();
}
Matrix tk;
D x[ N ];
void solve(){
  tk.n = n - 1;
  for( int i = 0 ; i < n - 1 ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      tk.a[ i ][ j ] = a[ i ][ j ];
  for( int j = 0 ; j < n - 1 ; j ++ )
    tk.a[ j ][ n ] = num[ j ];
  tk.gauss();
  ll ans = -1;
  for( ll xn = 0 ; xn <= 1000000 ; xn ++ ){
    bool flag = true;
    x[ n - 1 ] = xn;
    for( int i = 0 ; i < n - 1 ; i ++ ){
      x[ i ] = tk.a[ i ][ n ] - (D)xn * tk.a[ i ][ n - 1 ];
      ll tmp = round( x[ i ] );
      if( !equal( tmp , x[ i ] ) || tmp < 0 ){
        flag = false;
        break;
      }
      x[ i ] = tmp;
    }
    if( !flag ) continue;
    ll tans = 0;
    for( int i = 0 ; i < n ; i ++ )
      tans += cst[ i ] * x[ i ];
    ans = max( ans , tans );
  }
  printf( "%lld\n" , ans );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
