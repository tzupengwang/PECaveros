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
#define MX 1000000000000000000ll
#define N 101
vector<PLL> ans;
bool p[ N ];
inline void go( ll tp ){
  size_t asz = ans.size();
  for( size_t i = 0 ; i < asz ; i ++ ){
    ll ta = ans[ i ].FI , tn = ans[ i ].SE;
    if( MX / tp < ta ) break;
    for( ll j = 1 , tmp = tp ; ; j ++ ){
      ans.PB( MP( ta * tmp , tn * ( j + 1 ) ) );
      if( MX / tp < tmp ) break;
      tmp *= tp;
      if( MX / tmp < ta ) break;
    }
  }
  sort( ALL( ans ) );
  ll lg[ 3 ] , lgt = 0 , got = 0;
  for( size_t i = 0 ; i < ans.size() ; i ++ ){
    if( lgt < 2 || ans[ i ].SE >= lg[ 1 ] ){
      ans[ got ++ ] = ans[ i ];
      lg[ lgt ++ ] = ans[ i ].SE;
      for( int j = lgt - 2 ; j >= 0 ; j -- )
        if( lg[ j + 1 ] > lg[ j ] )
          swap( lg[ j + 1 ] , lg[ j ] );
      lgt = min( lgt , 2ll );
    }
  }
  ans.resize( got );
}
void build(){
  ans.PB( MP( 1 , 1 ) );
  for( int i = 2 ; i < N ; i ++ ) if( !p[ i ] ){
    size_t psz = ans.size();
    go( i );
    if( psz == ans.size() ) break;
    for( int j = i + i ; j < N ; j += i )
      p[ j ] = true;
  }
}
int n;
void init(){
  n = getint();
}
void solve(){
  if( n > (int)ans.size() ) puts( "-1" );
  else printf( "%lld\n" , ans[ n - 1 ].FI );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
