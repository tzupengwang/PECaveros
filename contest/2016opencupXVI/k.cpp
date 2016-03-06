// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
#define int long long
typedef pair<LL,LL> PII;
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
#define N 1021
typedef pair<PII,PII> Ln;
inline PII operator+( const PII& p1 , const PII& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
inline PII operator-( const PII& p1 , const PII& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
inline int operator^( const PII& p1 , const PII& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
inline int operator%( const PII& p1 , const PII& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline bool operator==( const PII& p1 , const PII& p2 ){
  return p1.X == p2.X && p1.Y == p2.Y;
}
inline int norm( const PII& tp ){
  return tp % tp;
}
inline bool interPt( PII p1 , PII p2 , PII q1 , PII q2 ){
	int f1 = ( p2 - p1 ) ^ ( q1 - p1 ); // cross
	int f2 = ( p2 - p1 ) ^ ( p1 - q2 ); // cross
	int f = f1 + f2;
	if( f == 0 ){
    if( ( ( q1 - p1 ) ^ ( q2 - p1 ) ) == 0 &&
        ( ( q1 - p2 ) ^ ( q2 - p2 ) ) == 0 ){
      return ( q1 - p1 ) % ( q2 - p1 ) < 0 ||
             ( q1 - p2 ) % ( q2 - p2 ) < 0 ||
             ( p1 - q1 ) % ( p2 - q1 ) < 0 ||
             ( p1 - q2 ) % ( p2 - q2 ) < 0;
    }
    return false;
  }
  if( ( ( q1 - p1 ) ^ ( p2 - p1 ) ) *
      ( ( q2 - p1 ) ^ ( p2 - p1 ) ) < 0 &&
      ( ( p1 - q1 ) ^ ( q2 - q1 ) ) *
      ( ( p2 - q1 ) ^ ( q2 - q1 ) ) < 0 )
    return true;
  return false;
}
inline void scan( PII& tp ){
  tp.X = getint();
  tp.Y = getint();
}
inline void scan( Ln& tl ){
  scan( tl.FI );
  scan( tl.SE );
}
int n , p[ N ] , sz;
int find_p( int x ){
  return x == p[ x ] ? x : p[ x ] = find_p( p[ x ] );
}
void Union( int x , int y ){
  x = find_p( x );
  y = find_p( y );
  if( x == y ) return;
  p[ x ] = y; sz --;
}
void build(){

}
Ln v[ N ];
bool cmp( Ln l1 , Ln l2 ){
  return norm( l1.FI - l1.SE ) > norm( l2.FI - l2.SE );
}
map<PII,int> M;
vector<PII> upt;
vector< tuple<int,Ln,int,int> > e;
inline void add_pt( const PII& tp , int id ){
  if( M.count( tp ) ) return;
  upt.PB( tp );
  M[ tp ] = id;
}
inline void add( const PII& p1 , const PII& p2 ){
  if( M[ p1 ] == M[ p2 ] ) return;
  e.PB( MT( norm( p1 - p2 ) , MP( p1 , p2 ) , M[ p1 ] , M[ p2 ] ) );
}
void init(){
  sz = n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    scan( v[ i ] );
    p[ i ] = i;
    add_pt( v[ i ].FI , i );
    add_pt( v[ i ].SE , i );
  }
  sort( v , v + n , cmp );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ )
      if( v[ i ].FI == v[ j ].FI ||
          v[ i ].FI == v[ j ].SE ||
          v[ i ].SE == v[ j ].FI ||
          v[ i ].SE == v[ j ].SE )
        Union( i , j );
  for( size_t i = 0 ; i < upt.size() ; i ++ )
    for( size_t j = i + 1 ; j < upt.size() ; j ++ )
      add( upt[ i ] , upt[ j ] );
  sort( ALL( e ) );
}
bool okay( const Ln& tl ){
  for( int i = 0 ; i < n ; i ++ )
    if( interPt( tl.FI , tl.SE , v[ i ].FI , v[ i ].SE ) )
      return false;
  return true;
}
void solve(){
  LD ans = 0.0;
  for( size_t i = 0 ; i < e.size() && sz > 1 ; i ++ ){
    if( find_p( get<2>( e[ i ] ) ) !=
        find_p( get<3>( e[ i ] ) ) ){
      if( okay( get<1>( e[ i ] ) ) ){
        ans += sqrt( get<0>( e[ i ] ) );
        Union( get<2>( e[ i ] ) , get<3>( e[ i ] ) );
      }
    }
  }
  printf( "%.12f\n" , (D)ans );
}
signed main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
