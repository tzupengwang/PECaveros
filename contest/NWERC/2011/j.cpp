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
#define N 2048
#define M 60
void build(){

}
const D inf = 1e30;
int mcnt;
map< string , int > MM;
vector< tuple<int,int,int,int,int> > vv[ N ];
#define Des(X) get<0>(X)
#define Stt(X) get<1>(X)
#define Dur(X) get<2>(X)
#define Prb(X) get<3>(X)
#define Dly(X) get<4>(X)
inline void add( const string& _s ){
  if( MM.count( _s ) ) return;
  MM[ _s ] = mcnt;
  vv[ mcnt ++ ].clear();
}
char buf[ N ];
void init(){
  MM.clear(); mcnt = 0;
  string s , t;
  scanf( "%s" , buf ); s = string( buf );
  scanf( "%s" , buf ); t = string( buf );
  add( s ); add( t );
  int m = getint(); while( m -- ){
    scanf( "%s" , buf ); s = string( buf );
    scanf( "%s" , buf ); t = string( buf );
    add( s ); add( t );
    int sidx = MM[ s ];
    int tidx = MM[ t ];
    int st = getint();
    int du = getint();
    int pr = getint();
    int dl = getint();
    vv[ tidx ].push_back( MT( sidx , st , du , pr , dl ) );
  }
}
D dst[ N ][ M ];
bool got[ N ][ M ];
inline void Dijkstra(){
  for( int i = 0 ; i < mcnt ; i ++ )
    for( int j = 0 ; j < M ; j ++ ){
      dst[ i ][ j ] = inf;
      got[ i ][ j ] = false;
    }
typedef pair<D,PII> state;
  priority_queue< state , vector<state> , greater<state> > heap;
  for( int j = 0 ; j < M ; j ++ ){
    dst[ 1 ][ j ] = 0.0;
    heap.push( { 0.0 , { 1 , j } } );
  }
  while( heap.size() ){
    state tp = heap.top(); heap.pop();
    int tn = tp.SE.FI;
    int xm = tp.SE.SE;
    if( got[ tn ][ xm ] ) continue;
    got[ tn ][ xm ] = true;
    dst[ tn ][ xm ] = tp.FI;
    for( size_t _ = 0 ; _ < vv[ tn ].size() ; _ ++ ){
      int des = Des( vv[ tn ][ _ ] );
      int stt = Stt( vv[ tn ][ _ ] );
      int dur = Dur( vv[ tn ][ _ ] );
      int prb = Prb( vv[ tn ][ _ ] );
      int dly = Dly( vv[ tn ][ _ ] );
      D tans = 0.0;
      D ndly = 1.0 - (D)prb / 100.0;
      int nxt = ( stt + dur ) % M;
      tans += ndly * ( dur + dst[ tn ][ nxt ] );
      D dlyp = (D)prb / 100.0 / dly;
      for( int j = 1 ; j <= dly ; j ++ )
        tans += dlyp * ( dur + j + dst[ tn ][ ( nxt + j ) % M ] );
      for( int j = 0 ; j < M ; j ++ ){
        int wt = stt - j;
        if( wt < 0 ) wt += M;
        if( tans + wt < dst[ des ][ j ] ){
          dst[ des ][ j ] = tans + wt;
          heap.push( { dst[ des ][ j ] , { des , j } } );
        }
      }
    }
  }
}
void solve(){
  Dijkstra();
  D ans = inf;
  for( int j = 0 ; j < M ; j ++ )
    ans = min( ans , dst[ 0 ][ j ] );
  if( ans > 1e29 ) puts( "IMPOSSIBLE" );
  else printf( "%.12f\n" , ans );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
