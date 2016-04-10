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
ll mymul( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 0ll;
  ll _tmp = mymul( _a , _x / 2 , _mod );
  _tmp = add( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = add( _tmp , _a , _mod );
  return _tmp;
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
// n < 4,759,123,141        3 :  2, 7, 61
// n < 1,122,004,669,633    4 :  2, 13, 23, 1662803
// n < 3,474,749,660,383          6 :  pirmes <= 13
// n < 2^64                       7 :
// 2, 325, 9375, 28178, 450775, 9780504, 1795265022
// Make sure testing integer is in range [2, n−2] if
// you want to use magic.
ll xx[]={2, 325, 9375, 28178, 450775, 9780504, 1795265022};
ll modit(ll x,ll mod) {
	if(x>=mod) x-=mod;
	//if(x<0) x+=mod;
	return x;
}
ll mult(ll x,ll y,ll mod) {
	ll s=0,m=x%mod;
	while(y) {
		if(y&1) s=modit(s+m,mod);
		y>>=1;
		m=modit(m+m,mod);
	}
	return s;
}
long long power(long long x,long long p,long long mod){
	long long s=1,m=x;
	while(p) {
		if(p&1) s=mult(s,m,mod);
		p>>=1;
		m=mult(m,m,mod);
	}
	return s;
}
bool witness(long long a,long long n,long long u,int t){
	long long x=power(a,u,n);
	for(int i=0;i<t;i++) {
		long long nx=mult(x,x,n);
		if(nx==1&&x!=1&&x!=n-1) return 1;
		x=nx;
	}
	return x!=1;
}
bool miller_rabin(long long n,int i){
	// iterate s times of witness on n
	// return 1 if prime, 0 otherwise
	if(n<2) return 0;
	if(!(n&1)) return n==2;
	long long u=n-1;
	int t=0;
	// n-1 = u*2^t
	while(!(u&1)) {
		u>>=1;
		t++;
	}
  ll a = xx[ i ];
  if(witness(a,n,u,t)) return 0;
	return 1;
}
ll f(ll x,ll mod) {
	return modit(mult(x,x,mod)+1,mod);
}
ll pollard_rho(ll n) {
	if(!(n&1)) return 2;
  while (true) {
    ll y=2, x=rand()%(n-1)+1, res=1;
    for (int sz=2; res==1; sz*=2) {
      for (int i=0; i<sz && res<=1; i++) {
        x = f(x, n);
        res = __gcd(abs(x-y), n);
      }
      y = x;
    }
    if (res!=0 && res!=n) return res;
  }
}
ll isp( ll n ){
  for( int i = 0 ; i < 7 ; i ++ )
    if( miller_rabin( n , i ) )
      return -1;
  return pollard_rho( n );
}
#define N 5555
PLL gcd( ll a , ll b , ll mi ){
	if( b == 0 ) return make_pair(1, 0);
	else{
		ll p = a / b;
		PLL q = gcd( b, a % b , mi );
		return make_pair( q.second , sub( q.first , mymul( q.second , p , mi ) , mi ) );
	}
}
ll n , m;
#define P 1000000
bool pp[ P + P ];
vector<ll> pset;
ll psz;
void build(){
  for( int i = 2 ; i < N ; i ++ ) if( !pp[ i ] ){
    pset.PB( i );
    for( int j = N / i ; j >= i ; j -- )
      pp[ i * j ] = true;
  }
  psz = (int)pset.size();
}
ll va[ N ] , vb[ N ] , ta[ N ] , tb[ N ];
vector<ll> fac;
void Div( ll u ){
  if( u == 1 ) return;
  ll div = isp( u );
  if( div == -1 ){
    fac.PB( u );
    return;
  }
  Div( div );
  Div( u / div );
}
void factor( ll u ){
  fac.clear();
  for( int i = 0 ; i < psz && pset[ i ] * pset[ i ] <= u ; i ++ )
    if( u % pset[ i ] == 0 ){
      fac.PB( pset[ i ] );
      while( u % pset[ i ] == 0 )
        u /= pset[ i ];
    }
  Div( u );
}
void init(){
  n = getint();
  m = getint();
  for( int i = 0 ; i < n ; i ++ )
    va[ i ] = getint();
  for( int j = 0 ; j < m ; j ++ )
    vb[ j ] = getint();
}
inline bool solve( ll mi ){
  for( int i = 0 ; i < n ; i ++ )
    ta[ i ] = va[ i ];
  for( int j = 0 ; j < m ; j ++ )
    tb[ j ] = vb[ j ];
  factor( mi );
  for( size_t i = 0 ; i < fac.size() ; i ++ ){
    ll cnt = 0;
    for( int j = 0 ; j < m ; j ++ )
      while( tb[ j ] % fac[ i ] == 0 ){
        cnt ++;
        tb[ j ] /= fac[ i ];
      }
    for( int j = 0 ; j < n && cnt > 0 ; j ++ )
      while( cnt > 0 && ta[ j ] % fac[ i ] == 0 ){
        cnt --;
        ta[ j ] /= fac[ i ];
      }
    if( cnt > 0 ) return false;
  }
  ll ans = 1;
  for( int i = 0 ; i < n ; i ++ )
    ans = mymul( ans , ta[ i ] , mi );
  for( int i = 0 ; i < m ; i ++ ){
    PLL tp = gcd( tb[ i ] % mi , mi , mi );
    ans = mymul( ans , tp.FI , mi );
  }
  printf( "%lld\n" , ans );
  return true;
}
void solve(){
  int k = getint(); while( k -- ){
    ll mi = getint();
    if( !solve( mi ) )
      puts( "DIVISION BY ZERO" );
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
