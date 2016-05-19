// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef unsigned long long ll;
typedef unsigned long long LL;
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
void build(){

}
#define K 1000
ll a , b , len;
void init(){
  a = getint();
  b = getint();
  ll tb = b;
  while( tb ){
    len ++;
    tb /= 10;
  }
}
ll ans = 10;
inline bool okay( ll bs ){
  ll result = 0 , tmp = a , len2 = 0 , rr = 1;
  bool okay = true;
  while( tmp ){
    if( tmp % bs >= 10 ) okay = false;
    result = result + rr * ( tmp % bs );
    rr *= 10;
    tmp /= bs;
    len2 ++;
  }
  if( len2 < len ) return false;
  if( okay && result >= b )
    ans = max( ans , bs );
  return true;
}
inline void solve1(){
  for( ll bs = 10 ; ; bs ++ )
    if( !okay( bs ) )
      break;
  cout << ans << endl;
}
#define MX 1000000000000000001ll
inline ll test( ll rb ){
  ll lbs = 10 , rbs = MX , mbs , aa = 0;
  while( lbs <= rbs ){
    mbs = ( lbs + rbs ) >> 1;
    bool xx = true;
    ll tmp = rb , ob = 1 , res = 0;
    while( tmp && xx ){
      res += ob * ( tmp % 10 );
      if( res >= MX ) xx = false;
      if( MX / ob < tmp % 10 ) xx = false;
      tmp /= 10;
      if( tmp && MX / mbs < ob ) xx = false;
      ob *= mbs;
    }
    if( !xx || res > a ) rbs = mbs - 1;
    else if( res == a ){
      aa = mbs; break;
    }
    else lbs = mbs + 1;
  }
  // cout << lbs << " " << rbs << endl;
  ans = max( ans , aa );
  return lbs;
}
inline void solve2(){
  ll up = 0;
  for( ll rb = b ; rb < 100000 ; rb ++ )
    up = test( rb );
  for( ll bs = 10 ; bs <= up ; bs ++ )
    if( !okay( bs ) )
      break;
  cout << ans << endl;
}
void solve(){
  if( b >= K ) solve1();
  else solve2();
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
