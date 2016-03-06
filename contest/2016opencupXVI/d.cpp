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
int __ = 1 , _cs;
/*********default*********/
#define N 101010
#define K 20
ll cnt[ N ] , two[ K ];
void build(){
  cnt[ 1 ] = 0;
  ll nxt = 2 , tmp = 0;
  for( ll i = 2 ; i < N ; i ++ ){
    cnt[ i ] = tmp;
    if( i == nxt ){
      nxt <<= 1;
      tmp ++;
    }
  }
  two[ 0 ] = 1;
  for( ll i = 1 ; i < K ; i ++ )
    two[ i ] = two[ i - 1 ] << 1;
}
ll n , w , f[ N ] , st[ K ][ N + N ];
void init(){
  n = getint();
  w = getint();
  for( int i = 0 ; i < n ; i ++ ){
    f[ i ] = getint();
    st[ 0 ][ i ] = f[ i ];
  }
  for( int i = 1 ; i < K ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      st[ i ][ j ] = max( st[ i - 1 ][ j ] , st[ i - 1 ][ j + two[ i - 1 ] ] );
}
bool okay( int tl ){
  ll sum = 0;
  for( int i = 0 ; i < n ; i += tl ){
    int l = i , r = min( (int)n - 1 , i + tl - 1 );
    int tk = cnt[ r - l + 1 ];
    ll tmp = max( st[ tk ][ l ] , st[ tk ][ r - two[ tk ] + 1 ] );
    sum += tmp + 1;
  }
  return sum - 1 <= w;
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    if( okay( i ) ){
      cout << i << endl;
      exit( 0 );
    }
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
