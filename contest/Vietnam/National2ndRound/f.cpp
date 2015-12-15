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
#define N 101010
int n;
char c[ N ];
void build(){

}
vector< PII > v;
int trans( char ctmp ){
  if( ctmp == 'N' ) return 0;
  if( ctmp == 'W' ) return 1;
  if( ctmp == 'S' ) return 2;
  if( ctmp == 'E' ) return 3;
  return -1;
}
int dx[]={0,-1,0,1};
int dy[]={1,0,-1,0};
int minx , miny;
int maxx , maxy;
void init(){
  v.clear();
  scanf( "%s" , c + 1 );
  n = strlen( c + 1 );
  int nx = 0, ny = 0;
  minx = miny = maxx = maxy = 0;
  v.PB( MP( nx , ny ) );
  for( int i = 1 ; i <= n ; i ++ ){
    nx += dx[ trans( c[ i ] ) ];
    ny += dy[ trans( c[ i ] ) ];
    v.PB( MP( nx , ny ) );
    minx = min( minx , nx );
    maxx = max( maxx , nx );
    miny = min( miny , ny );
    maxy = max( maxy , ny );
  }
}
vector< string > ans;
void Xmin(){
  int seg = 1;
  vector<int> tmp;
  for( int i = 0 ; i <= n ; i ++ )
    if( v[ i ].X == minx )
      tmp.PB( v[ i ].Y );
  sort( ALL( tmp ) );
  for( int i = 1 ; i < (int)tmp.size() ; i ++ )
    if( abs( tmp[ i ] - tmp[ i - 1 ] ) > 1 )
      seg ++;
  if( seg > 1 ) return;

}
void solve(){
  ans.clear();
  Xmin();
  Xmax();
  Ymin();
  Ymax();
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
