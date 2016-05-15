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
#define N 101010
ll n , x[ N ] , y[ N ] , st;
int p[ N ];
int find_p( int _x ){
  return _x == p[ _x ] ? _x : p[ _x ] = find_p( p[ _x ] );
}
void Union( int tx , int ty ){
  tx = find_p( tx );
  ty = find_p( ty );
  if( tx == ty ) return;
  p[ tx ] = ty;
  st --;
}
void build(){

}
vector< PLL > v;
inline ll dist( int xi , int yi ){
  return abs( x[ xi ] - x[ yi ] ) +
         abs( y[ xi ] - y[ yi ] );
}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    x[ i ] = getint();
    y[ i ] = getint();
    v.PB( { y[ i ] , i } );
  }
  sort( ALL( v ) );
}
inline bool okay( ll tx ){
  st = n;
  for( int i = 0 ; i < n ; i ++ ) p[ i ]= i;
  ll bsts = -INF16 , bstm = -INF16;
  int ids = -1 , idm = -1;
  for( int l = 0 , r = 0 ; l < n ; l = r ){
    while( r < n && v[ r ].FI == v[ l ].FI ) r ++;
    for( int i = l ; i < r ; i ++ ){
      if( bsts == -INF16 || x[ v[ i ].SE ] + y[ v[ i ].SE ] < bsts ) 
        bsts = x[ v[ i ].SE ] + y[ v[ i ].SE ] , ids = v[ i ].SE;
      if( bstm == -INF16 || x[ v[ i ].SE ] - y[ v[ i ].SE ] > bstm ) 
        bstm = x[ v[ i ].SE ] - y[ v[ i ].SE ] , idm = v[ i ].SE;
    }
    for( int i = l ; i < r ; i ++ ){
      if( dist( v[ i ].SE , ids ) >= tx )
        Union( v[ i ].SE , ids );
      if( dist( v[ i ].SE , idm ) >= tx )
        Union( v[ i ].SE , idm );
    }
  }
  bsts = -INF16 , bstm = -INF16;
  ids = -1 , idm = -1;
  for( int r = n - 1 , l = n - 1 ; r >= 0 ; r = l ){
    while( l >= 0 && v[ r ].FI == v[ l ].FI ) l --;
    for( int i = r ; i > l ; i -- ){
      if( bsts == -INF16 || x[ v[ i ].SE ] + y[ v[ i ].SE ] > bsts ) 
        bsts = x[ v[ i ].SE ] + y[ v[ i ].SE ] , ids = v[ i ].SE;
      if( bstm == -INF16 || x[ v[ i ].SE ] - y[ v[ i ].SE ] < bstm ) 
        bstm = x[ v[ i ].SE ] - y[ v[ i ].SE ] , idm = v[ i ].SE;
    }
    for( int i = r ; i > l ; i -- ){
      if( dist( v[ i ].SE , ids ) >= tx )
        Union( v[ i ].SE , ids );
      if( dist( v[ i ].SE , idm ) >= tx )
        Union( v[ i ].SE , idm );
    }
  }
  return st == 1;
}
void solve(){
  ll bl = 0 , br = 2000000000 , mid , ans = 0;
  while( bl <= br ){
    mid = ( bl + br ) >> 1;
    if( okay( mid ) ) ans = mid , bl = mid + 1;
    else br = mid - 1;
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
