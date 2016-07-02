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
#define N 111
void build(){

}
const LD inf = 1e20;
inline void scan( Pt& tp ){
  tp.X = getint();
  tp.Y = getint();
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
inline Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
inline LD operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline Pt operator&( const Pt& p1 , const Pt& p2 ){
  return { max( p1.X , p2.X ) , min( p1.Y , p2.Y ) };
}
inline LD norm( const Pt& tp ){
  return sqrtl( tp * tp );
}
int n , m;
map< string , int > name;
string sname[ N ];
Pt pos[ N ];
Pt range[ N ][ N ];
bool got[ N ] , shoot[ N ];
int ind[ N ];
inline void find_ans(){
  vector<int> ans;
  for( int i = 0 ; i < n ; i ++ ){
    got[ i ] = 0;
    ind[ i ] = 0;
  }
  for( int i = 0 ; i < n ; i ++ ) if( shoot[ i ] )
    for( int j = 0 ; j < n ; j ++ ) if( shoot[ j ] )
      if( range[ i ][ j ].X > eps )
        ind[ j ] ++;
  queue<int> Q;
  for( int i = 0 ; i < n ; i ++ )
    if( shoot[ i ] && ind[ i ] == 0 ){
      Q.push( i );
      got[ i ] = true;
    }
  while( Q.size() ){
    if( (int)Q.size() > 1 ){
      puts( "UNKNOWN" );
      return;
    }
    int tn = Q.front(); Q.pop();
    ans.push_back( tn );
    for( int i = 0 ; i < n ; i ++ )
      if( shoot[ i ] && !got[ i ] && range[ tn ][ i ].X > 0 ){
        ind[ i ] --;
        if( ind[ i ] == 0 ){
          got[ i ] = true;
          Q.push( i );
        }
      }
  }
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%s%c" , sname[ ans[ i ] ].c_str() , " \n"[ i + 1 == ans.size() ] );
}
void init(){
  n = getint(); m = getint();
  name.clear();
  for( int i = 0 ; i < n ; i ++ ){
    cin >> sname[ i ];
    shoot[ i ] = false;
    name[ sname[ i ] ] = i;
    scan( pos[ i ] );
  }
  for( int i = 0 ; i < n ; i ++ ){
    for( int j = 0 ; j < n ; j ++ )
      range[ i ][ j ] = { -inf , inf };
    range[ i ][ i ] = { 0 , 0 };
  }
  while( m -- ){
    string ss[ 6 ];
    for( int i = 0 ; i < 6 ; i ++ )
      cin >> ss[ i ];
    int ai = name[ ss[ 0 ] ];
    int bi = name[ ss[ 2 ] ];
    int ci = name[ ss[ 5 ] ];
    shoot[ bi ] = shoot[ ci ] = true;
    LD dab = norm( pos[ ai ] - pos[ bi ] );
    LD dac = norm( pos[ ai ] - pos[ ci ] );
    range[ bi ][ ci ] = range[ bi ][ ci ] & MP( dab - dac , +inf );
    range[ ci ][ bi ] = range[ ci ][ bi ] & MP( -inf , dac - dab );
  }
}
void solve(){
  for( int k = 0 ; k < n ; k ++ ) if( shoot[ k ] )
    for( int i = 0 ; i < n ; i ++ ) if( shoot[ i ] )
      for( int j = 0 ; j < n ; j ++ ) if( shoot[ j ] )
        range[ i ][ j ] = range[ i ][ j ] & ( range[ i ][ k ] + range[ k ][ j ] );
  for( int i = 0 ; i < n ; i ++ ) if( shoot[ i ] )
    for( int j = 0 ; j < n ; j ++ ) if( shoot[ j ] )
      if( range[ i ][ j ].X > range[ i ][ j ].Y ){
        puts( "IMPOSSIBLE" );
        return;
      }
  for( int i = 0 ; i < n ; i ++ ) if( shoot[ i ] )
    for( int j = 0 ; j < n ; j ++ ) if( shoot[ j ] )
      if( range[ i ][ j ].X < -eps &&
          range[ i ][ j ].Y > eps ){
        puts( "UNKNOWN" );
        return;
      }
  find_ans();
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
