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
#define N 505050
inline ll operator%( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline ll operator^( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
int n , m , qa[ N ] , qb[ N ];
vector<PLL> u , v;
map<PLL,ll> ans;
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    qa[ i ] = getint();
    qb[ i ] = getint();
    u.PB( MP( qa[ i ] , qb[ i ] ) );
  }
  sort( ALL( u ) );
  u.resize( unique( ALL( u ) ) - u.begin() );
  m = getint();
  for( int i = 0 ; i < m ; i ++ ){
    int tx = getint();
    int ty = getint();
    v.PB( MP( tx , ty ) );
  }
  sort( ALL( v ) );
  int sz = 1;
  for( int i = 1 ; i < m ; i ++ )
    if( v[ i ].SE < v[ sz - 1 ].SE )
      v[ sz ++ ] = v[ i ];
  v.resize( sz );
  m = sz;
}
bool cmp( PLL p1 , PLL p2 ){
  return ( p1 ^ p2 ) < 0;
}
void cal( int ql , int qr , int al , int ar ){
  if( ql > qr ) return;
  int bst = -1 , mid = ( ql + qr ) >> 1;
  ll nans = 3000000000000000000ll;
  for( int i = al ; i <= ar ; i ++ ){
    ll tans = u[ mid ] % v[ i ];
    if( tans < nans ){
      nans = tans;
      bst = i;
    }
  }
  // printf( "%d %d %d %d %d %d %lld\n" , mid , ql , qr , al , ar , bst , nans );
  ans[ u[ mid ] ] = nans;
  cal( ql , mid - 1 , bst , ar );
  cal( mid + 1 , qr , al , bst );
}
void solve(){
  sort( ALL( u ) , cmp );
  cal( 0 , (int)u.size() - 1 , 0 , m - 1 );
  for( int i = 0 ; i < n ; i ++ )
    printf( "%lld%c" , ans[ MP( qa[ i ] , qb[ i ] ) ] , " \n"[ i == n - 1 ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
