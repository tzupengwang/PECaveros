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
void build(){

}
ll m , n , l;
void init(){
  m = getint();
  n = getint();
  l = getint();
}
vector<ll> fac;
void factor(){
  fac.clear();
  for( ll i = 1 ; i <= l / i ; i ++ )
    if( l % i == 0 ){
      fac.PB( i );
      fac.PB( l / i );
    }
  sort( ALL( fac ) );
  fac.resize( unique( ALL( fac ) ) - fac.begin() );
}
bool okay( ll tl , ll tk ){
  if( l % ( tl * tk ) != 0 ) return false;
  ll div = l / ( tl * tk );
  ll ta = div - ( tl - 1 ) * n - ( tk - 1 );
  if( ta < 0 ) return false;
  if( ta % 2 ) return false;
  ta >>= 1;
  return ( ta % n ) + ( tk - 1 ) < n &&
         ( ta / n ) + ( tl - 1 ) < m;
}
void solve(){
  l *= 2ll;
  factor();
  ll ans = -1;
  int _sz = (int)fac.size();
  for( int i = 0 ; i < _sz ; i ++ )
    for( int j = 0 ; j < _sz ; j ++ ){
      if( fac[ i ] * fac[ j ] > ( l / 2 ) ) break;
      if( ans != -1 && fac[ i ] * fac[ j ] >= ans ) break;
      if( okay( fac[ i ] , fac[ j ] ) ){
        if( ans == -1 || fac[ i ] * fac[ j ] < ans )
          ans = fac[ i ] * fac[ j ];
      }
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
