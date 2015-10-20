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
inline ll randll()
{
  return  ( (ll)rand() << 30 ) + ( rand() << 15 ) + rand();
} 
inline ll mult(ll a, ll b, ll n)
{//(a*b)%n
  ll res = 0ll;
  a %= n, b %= n;
  while(b)
  {
    if(b&1) res = ( res + a ) % n;
    a = ( a + a ) % n;
    b >>= 1ll;
  }
  return res;
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
bool millerRabin(long long n,int s=100) {
    // iterate s times of witness on n
    // return 1 if prime, 0 otherwise
    if(n<2) return 0;
    if(!(n&1)) return n==2;
    long long u=n-1;
    int t=0;
    // n-1 = u*2^t
    while(u&1) {
        u>>=1;
        t++;
    }
    while(s--) {
        long long a=randll()%(n-1)+1;
        if(witness(a,n,u,t)) return 0;
    }
    return 1;
}
 
inline bool isPr(ll n)
{
  return millerRabin( n , 1000 );
}
#define K 1000010
ll n;
bool p[ K ];
void build(){
  for( ll i = 2 ; i < K ; i ++ ) if( !p[ i ] )
    for( ll j = K / i ; j >= i ; j -- )
      p[ i * j ] = true;
}
ll ans = 1;
void init(){
  n = getint();
}
void solve(){
  for( ll i = 2 ; i < K && i <= n ; i ++ ) if( !p[ i ] )
    if( n % i == 0 ){
      ll tcnt = 0;
      while( n % i == 0 )
        tcnt ++, n /= i;
      ans *= ( tcnt + 1ll );
    }
  if( n != 1 ){
    ll tmp = sqrt( n );
    if( isPr( n ) ) ans *= 2ll;
    else if( tmp * tmp == n ) ans *= 3ll;
    else ans *= 4ll;
  }
  printf( "%lld\n" , ans );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
