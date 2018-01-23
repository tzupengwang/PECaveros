// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef long double D;
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
#define eps 1e-6
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
ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 2020
#define X FI
#define Y SE
typedef pair<D,D> Pt;
typedef pair<Pt,Pt> Ln;
typedef pair<Pt,Pt> Seg;
const D PI = acos( -1.0 );
const D PI2 = 2.0 * acos( -1.0 );
inline void Scan( Pt& tp ){ tp.X = getint(); tp.Y = getint(); }
inline void Print( const Pt& tp ){ printf( "(%.3f,%.3f)\n" , (double)tp.X , (double)tp.Y ); }
inline Pt operator+( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
inline Pt operator*( const Pt& p1 , const D& tk ){
  return MP( p1.X * tk , p1.Y * tk );
}
inline Pt operator/( const Pt& p1 , const D& tk ){
  return MP( p1.X / tk , p1.Y / tk );
}
inline D operator%( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline D operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
inline D Deg( const Pt& tp ){ return atan2( tp.Y, tp.X ); }
inline D norm2( const Pt& tp ){ return tp % tp; }
inline D norm( const Pt& tp ){ return sqrt( norm2( tp ) ); }
D onSeg( const Ln& tl , const Pt& tp ){
  Pt dlt = tl.SE - tl.FI;
  D tvl1 = tp % dlt - tl.FI % dlt;
  D tvl2 = dlt % dlt;
  if( equal( tvl1 - tvl2 , 0.0 ) ) return 0.5;
  return tvl1 / ( tvl1 - tvl2 );
}
D dist( const Ln& tl , const Pt& tp ){
  D k = onSeg( tl , tp );
  if( k > -eps && k < 1.0 + eps )
    return norm( tp - ( tl.FI + ( tl.SE - tl.FI ) * k ) );
  return min( norm( tp - tl.FI ) ,
              norm( tp - tl.SE ) );
}
int n , d;
Pt p[ N ];
void build(){

}
bool can[ N ][ N ];
bool deg_in( D ndeg , D ldeg , D rdeg ){
  for( int i = -1 ; i <= 1 ; i ++ ){
    D tdeg = ndeg + (D)i * PI2;
    if( tdeg > ldeg - eps &&
        tdeg < rdeg + eps )
      return true;
  }
  return false;
}
void update( D& ldeg , D& rdeg , D tldeg , D trdeg ){
  for( int i = -1 ; i <= 1 ; i ++ ){
    D ttldeg = tldeg + (D)i * PI2;
    D ttrdeg = trdeg + (D)i * PI2;
    D nl = max( ldeg , ttldeg );
    D nr = min( rdeg , ttrdeg );
    if( nl - eps < nr ){
      ldeg = nl;
      rdeg = nr;
      return;
    }
  }
  ldeg = PI2;
  rdeg = 0;
}
D dis( const Ln& tl , const Pt& tp ){
  if( equal( tl.FI.X , tl.SE.X ) )
    return fabs( tp.X - tl.FI.X );
  D slp = ( tl.SE.Y - tl.FI.Y ) /
          ( tl.SE.X - tl.FI.X );
  D c = tl.FI.Y - tl.FI.X * slp;
  return fabs( tp.Y - slp * tp.X - c ) /
          norm( MP( 1.0 , slp ) );
}
bool good( int i1 , int i2 ){
  Pt p1 = p[ i1 ] , p2 = p[ i2 ];
  int _s = min( i1 , i2 );
  int _t = max( i1 , i2 );
  for( int i = _s + 1 ; i < _t ; i ++ )
    if( ( p[ i ] - p1 ) % ( p2 - p1 ) > 0.0 ){
      if( dis( MP( p1 , p2 ) , p[ i ] ) > (D)d + eps )
        return false;
    }else if( norm( p[ i ] - p1 ) > (D)d + eps )
      return false;
  return true;
}
void cal( int now ){
  // for( int nxt = now + 1 ; nxt <= n ; nxt ++ ){
    // bool flag = true;
    // Ln tl = MP( p[ now ] , p[ nxt ] );
    // for( int j = now + 1 ; j < nxt ; j ++ ){
      // printf( "%d %d : %d %.3f\n" , now , nxt , j , (double)dist( tl , p[ j ] ) );
      // if( dist( tl , p[ j ] ) > (D)d + eps ){
        // flag = false; break;
      // }
    // }
    // if( flag ) can[ now ][ nxt ] = true;
  // }
  // return;
/**/
  int nxt = now + 1;
  can[ now ][ nxt ] = true;
  D deg = Deg( p[ nxt ] - p[ now ] );
  D ldeg = -2.0 * PI2 , rdeg = 2.0 * PI2;
  int midx = nxt;
  // if( now == 1 ) Print( p[ nxt ] - p[ now ] );
  if( norm2( p[ nxt ] - p[ now ] ) > (D)d * (D)d + eps ){
    D dlt = asin( (D)d / norm( p[ nxt ] - p[ now ] ) );
    ldeg = deg - dlt;
    rdeg = deg + dlt;
  }
  for( nxt = now + 2 ; nxt <= n ; nxt ++ ){
    // if( now == 1 ) Print( MP( ldeg , rdeg ) );
    bool flag = true;
    if( n > 500 ){
      if( norm2( p[ nxt ] - p[ now ] ) + eps < norm2( p[ midx ] - p[ now ] ) ){
        for( int pre = now + 1 ; pre < nxt ; pre ++ )
          if( norm2( p[ nxt ] - p[ now ] ) + eps <
              norm2( p[ pre ] - p[ now ] ) &&
              norm2( p[ nxt ] - p[ pre ] ) > (D)d * (D)d + eps ){
            flag = false; break;
          }
      }
    }else{
      if( !good( now , nxt ) ||
          !good( nxt , now ) ) flag = false;
    }
    if( norm2( p[ nxt ] - p[ now ] ) > norm2( p[ midx ] - p[ now ] ) + eps ) midx = nxt;
    deg = Deg( p[ nxt ] - p[ now ] );
    if( flag && deg_in( deg , ldeg , rdeg ) )
      can[ now ][ nxt ] = true;
    if( norm2( p[ nxt ] - p[ now ] ) > (D)d * (D)d + eps ){
      D dlt = asin( (D)d / norm( p[ nxt ] - p[ now ] ) );
      update( ldeg , rdeg , deg - dlt , deg + dlt );
    }
    if( ldeg > rdeg + eps ) break;
  }
}
void init(){
  n = getint();
  d = getint();
  for( int i = 1 ; i <= n ; i ++ )
    Scan( p[ i ] );
  for( int i = 1 ; i < n ; i ++ )
    cal( i );
  // for( int i = 1 ; i <= n ; i ++ )
    // for( int j  = i+ 1 ; j <= n ; j ++ )
      // if( can[ i ][ j ] )
        // printf( "can %d %d\n" , i , j );
}
int dp[ N ];
void solve(){
  dp[ 1 ] = 1;
  for( int i = 2 ; i <= n ; i ++ ){
    dp[ i ] = i;
    for( int j = 1 ; j < i ; j ++ )
      if( can[ j ][ i ] )
        dp[ i ] = min( dp[ i ] , dp[ j ] + 1 );
  }
  printf( "%d\n" , dp[ n ] );
}
int main(){
  freopen( "kingdom.in" , "r" , stdin );
  freopen( "kingdom.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
