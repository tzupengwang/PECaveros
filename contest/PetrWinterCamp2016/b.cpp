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
ll BIT[ N ] , lb[ N ];
void build(){
  for( ll i = 1 ; i < N ; i ++ )
    lb[ i ] = i & (-i);
}
ll n , x[ N ] , y[ N ] , liy[ N ];
vector<ll> li;
void modify( ll _x ){
  for( ll i = _x ; i <= n ; i += lb[ i ] )
    BIT[ i ] ++;
}
ll query( ll _x ){
  ll sum = 0;
  for( ll i = _x ; i ; i -= lb[ i ] )
    sum += BIT[ i ];
  return sum;
}
void init(){
  n = getint();
  for( ll i = 0 ; i < n ; i ++ ){
    x[ i ] = getint();
    y[ i ] = getint();
    li.PB( y[ i ] );
  }
  sort( ALL( li ) );
  li.resize( unique( ALL( li ) ) - li.begin() );
  for( ll i = 0 ; i < n ; i ++ )
    liy[ i ] = lower_bound( ALL( li ) , y[ i ] ) - li.begin() + 1;
}
ll cal( LD rad ){
  vector< pair<LD,ll> > v;
  LD a = sinl( rad ) , b = cosl( rad );
  for( ll i = 0 ; i <= n ; i ++ ) BIT[ i ] = 0;
  for( ll i = 0 ; i < n ; i ++ )
    v.PB( MP( a * x[ i ] - b * y[ i ] , liy[ i ] ) );
  sort( ALL( v ) );
  ll cnt = 0;
  for( ll i = 0 ; i < n ; i ++ ){
    cnt += query( v[ i ].SE );
    modify( v[ i ].SE );
  }
  return cnt;
}
void solve(){
  ll all = n * ( n - 1 ) / 2;
  if( all % 2 ){
    ll hf = all / 2 + 1;
    LD l = 0.0 , r = acosl( -1.0 ) , mid;
    for( int i = 0 ; i < 70 ; i ++ ){
      mid = ( l + r ) * 0.5;
      ll tmp = cal( mid );
      // printf( "%.12f %lld\n" , (D)mid , tmp  );
      if( tmp < hf ) l = mid;
      else r = mid;
    }
    printf( "%.12f\n" , (D)( ( l + r ) * 0.5 ));
  }else{
    ll hf = all / 2;
    LD l1 = 0.0 , r1 = acosl( -1.0 ) , mid1;
    for( int i = 0 ; i < 70 ; i ++ ){
      mid1 = ( l1 + r1 ) * 0.5;
      ll tmp = cal( mid1 );
      if( tmp < hf ) l1 = mid1;
      else r1 = mid1;
    }
    LD l2 = 0.0 , r2 = acosl( -1.0 ) , mid2;
    for( int i = 0 ; i < 70 ; i ++ ){
      mid2 = ( l2 + r2 ) * 0.5;
      ll tmp = cal( mid2 );
      if( tmp < hf + 1 ) l2 = mid2;
      else r2 = mid2;
    }
    printf( "%.12f\n" , (D)( ( mid1 + mid2 ) * 0.5 ) );
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
