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
void build(){

}
inline Pt operator+( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
inline Pt operator/( const Pt& tp , const D& tk ){
  return MP( tp.X / tk , tp.Y / tk );
}
inline D operator%( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline D norm( const Pt& tp ){
  return sqrt( tp % tp );
}
void scan( Pt& tp ){
  tp.X = getint();
  tp.Y = getint();
}
const D pi = acos( -1.0 );
Pt p1 , p2 , o;
D r;
void init(){
  scan( p1 );
  scan( p2 );
  scan( o );
  r = getint();
}
// D ang1 , ang2 , dist1 , dist2;
D Dlt( D deg1 , D deg2 ){
  D bst = fabs( deg1 - deg2 );
  bst = min( bst , fabs( deg1 + 2.0 * pi - deg2 ) );
  bst = min( bst , fabs( deg1 - 2.0 * pi - deg2 ) );
  return bst;
}
D dist( Pt tp1 , Pt tp2 , Pt tp3 ){
  if( equal( tp1.X , tp2.X ) )
    return fabs( tp3.X - tp1.X );
  else{
    D slp = ( tp2.Y - tp1.Y ) / ( tp2.X - tp1.X );
    D c = tp1.Y - slp * tp1.X;
    // y - slp x - c = 0;
    D dst = ( tp3.Y - slp * tp3.X - c ) /
            sqrt( slp * slp + 1 );
    return fabs( dst );
  }
}
bool touch( Pt tp1 , Pt tp2 , Pt tp3 ){
  return ( ( tp2 - tp1 ) % ( tp3 - tp1 ) ) > eps &&
         ( ( tp1 - tp2 ) % ( tp3 - tp2 ) ) > eps;
  Pt dlt = tp2 - tp1;
  D k = ( ( tp3 % dlt ) - ( tp1 % dlt ) ) / ( dlt % dlt );
  return k > eps && k < 1.0 - eps;
}
#define KK 0.87
D g( const Pt &tp ){
  if( norm( tp - o ) < r - eps ) return 1e20;
  return norm( tp - o ) +
         norm( tp - p1 ) +
         norm( tp - p2 ) - r;
}
inline D solve2(){
  Pt tans = ( p1 + p2 ) / 2.0;
  D dlt = 100000.0 , ans = g( tans );
  for( int i = 0 ; i < 1000 ; i ++ ){
    Pt bans = tans;
    for( int j = 0 ; j < 5000 ; j ++ ){
      Pt tmp = MP( tans.X + dlt * cos( 2.0 * pi * j / 1000.0 ) ,
                   tans.Y + dlt * sin( 2.0 * pi * j / 1000.0 ) );
      D ttt = g( tmp );
      if( ttt < ans ){
        ans = ttt;
        bans = tmp;
      }
    }
    tans = bans;
    dlt *= KK;
  }
  return ans;
}
D cal(){
  if( dist( p1 , p2 , o ) < r - eps &&
      touch( p1 , p2 , o ) ){
    Pt dp1 = p1 - o;
    Pt dp2 = p2 - o;
    D d1 = norm( dp1 );
    D d2 = norm( dp2 );
    D ans = sqrt( d1 * d1 - r * r ) +
            sqrt( d2 * d2 - r * r );
    D ang1 = acos( r / d1 );
    D ang2 = acos( r / d2 );
    D sa1 = atan2( dp1.Y , dp1.X );
    D sa2 = atan2( dp2.Y , dp2.X );
    D bst = Dlt( sa1 + ang1 , sa2 + ang2 );
    bst = min( bst , Dlt( sa1 + ang1 , sa2 - ang2 ) );
    bst = min( bst , Dlt( sa1 - ang1 , sa2 + ang2 ) );
    bst = min( bst , Dlt( sa1 - ang1 , sa2 - ang2 ) );
    ans += bst * r;
    return ans;
  }else{
    D ans = solve2();
    return ans;
  }
}
void solve(){
  D ans = cal();
  printf( "%.12f\n" , ans );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
