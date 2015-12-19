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
#define N 111
void build(){

}
ll n , m , p;
vector<ll> r , s;
void init(){
  n = getint();
  m = getint();
  p = getint();
  for( int i = 0 ; i < n ; i ++ ) s.PB( getint() );
  for( int i = 0 ; i < m ; i ++ ) r.PB( getint() );
  sort( ALL( s ) );
  sort( ALL( r ) );
}
multiset<ll> S;
typedef multiset<ll>::iterator si;
bool okay( ll tx ){
  S.clear();
  for( int i = 0 ; i < m ; i ++ ) S.insert( r[ i ] );
  for( int i = 0 ; i < n && S.size() ; i ++ ){
    ll nd = ( p / s[ i ] ) + ( p % s[ i ] != 0 );
    ll tk = tx - nd + 1;
    while( true ){
      si it = S.upper_bound( tk );
      if( it == S.begin() ) break;
      it --;
      ll tmp = *it;
      if( tmp <= tk ){
        S.erase( S.find( tmp ) );
        tk -= nd;
      }else break;
    }
  }
  return S.size() == 0;
}
void solve(){
  ll bl = 0 , br = 1000000000000000ll , bmid , bans = -1;
  while( bl <= br ){
    bmid = ( bl + br ) >> 1;
    if( okay( bmid ) ) bans = bmid , br = bmid - 1;
    else bl = bmid + 1;
  }
  cout << bans << endl;
}
int main(){
  freopen( "budget.in" , "r" , stdin );
  freopen( "budget.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
