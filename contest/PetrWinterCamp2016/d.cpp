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
#define N 100010
void build(){

}
ll n , a[ N ] , b[ N ] , st[ N << 2 ] , tag[ N << 2 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
void build_st( int no , int l , int r ){
  if( l == r ){
    st[ no ] = l / 2;
    return;
  }
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid + 1 , r );
  st[ no ] = min( st[ L( no ) ] , st[ R( no ) ] );
}
void push( int no , int l , int r ){
  if( tag[ no ] != 0 && l < r ){
    tag[ L( no ) ] += tag[ no ];
    st[ L( no ) ] += tag[ no ];
    tag[ R( no ) ] += tag[ no ];
    st[ R( no ) ] += tag[ no ];
  }
  tag[ no ] = 0;
}
void modify( int no , int l , int r , int ql , int qr ){
  if( qr < l || ql > r ) return;
  if( ql <= l && r <= qr ){
    tag[ no ] --;
    st[ no ] --;
    return;
  }
  push( no , l , r );
  modify( L( no ) , l , mid , ql , qr );
  modify( R( no ) , mid + 1 , r , ql , qr );
  st[ no ] = min( st[ L( no ) ] , st[ R( no ) ] );
}
ll query( int no , int l , int r , int ql , int qr ){
  if( l > qr || r < ql ) return n;
  if( ql <= l && r <= qr ) return st[ no ];
  push( no , l , r );
  return min( query( L( no ) , l , mid , ql , qr ) ,
              query( R( no ) , mid + 1 , r , ql , qr ) );
}
vector<PLL> v;
bool cmp( PLL p1 , PLL p2 ){
  if( p1.FI != p2.FI )
    return p1.FI < p2.FI;
  return p1.SE > p2.SE;
}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ )
    a[ i ] = getint();
  for( int i = 0 ; i < n ; i ++ )
    b[ i ] = getint();
  for( int i = 0 ; i < n ; i ++ )
    v.PB( MP( a[ i ] , b[ i ] ) );
  sort( ALL( v ) );
  reverse( ALL( v ) );
  build_st( 1 , 1 , n );
}
priority_queue<PLL> heap;
void solve(){
  for( size_t i = 0 ; i < v.size() ; i ++ )
    heap.push( MP( v[ i ].SE , i + 1 ) );
  ll ans = 0;
  while( heap.size() ){
    PLL tp = heap.top(); heap.pop();
    if( query( 1 , 1 , n , tp.SE , n ) == 0 ) continue;
    // printf( "%lld %lld\n" , tp.SE , query( 1 , 1 , n , tp.SE , n ) );
    ans += tp.FI;
    modify( 1 , 1 , n , tp.SE , n );
  }
  cout << ans << endl;
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
