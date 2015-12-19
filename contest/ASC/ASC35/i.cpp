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
#define eps 1e-7
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
#define N 111
typedef pair<D,D> PT;
typedef pair<PT,PT> LN;
int n;
void scan( PT& pt ){ scanf( "%lf%lf" , &pt.X , &pt.Y ); }
PT operator+( const PT& p1 , const PT& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
PT operator-( const PT& p1 , const PT& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
PT operator*( const PT& p1 , const D& tk ){
  return MP( p1.X * tk , p1.Y * tk );
}
PT operator/( const PT& p1 , const D& tk ){
  return MP( p1.X / tk , p1.Y / tk );
}
D operator^( const PT& p1 , const PT& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
D operator%( const PT& p1 , const PT& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
D norm( const PT& tp ){
  return sqrt( tp % tp );
}
PT normal( const PT& p1 ){
  return p1 / norm( p1 );
}
PT interPT(PT p1, PT p2, PT q1, PT q2){
	double f1 = (p2 - p1) ^ (q1 - p1); // cross
	double f2 = (p2 - p1) ^ (p1 - q2); // cross
	double f = (f1 + f2);
	if(fabs(f) < eps) return PT(nan(""), nan(""));
	return q1 * (f2 / f) + q2 * (f1 / f);
}
D dist( const LN& tl , const PT& tp ){
  PT dlt = tp - tl.FI;
  PT dltp = tl.SE - tl.FI;
  PT far = normal( MP( dltp.Y , -dltp.X ) );
  return fabs( dlt % far );
}
vector<PT> p;
vector<PT> p2;
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    PT tp; scan( tp );
    p.PB( tp );
  }
}
D ans;
void cal(){
  n = (int)p.size();
  p.PB( p[ 0 ] );
  p.PB( p[ 1 ] );
  p.PB( p[ 2 ] );
  // printf( "%d\n" , n );
  p2.clear();
  D mn = 1e30;
  for( int i = 1 ; i <= n ; i ++ ){
    // printf( "============ %.6f %.6f\n" , p[ i ].X , p[ i ].Y );
    PT v1 = normal( p[ i - 1 ] - p[ i ] );
    PT v2 = normal( p[ i + 1 ] - p[ i ] );
    PT fen = ( v1 + v2 );

    PT u1 = normal( p[ i ] - p[ i + 1 ] );
    PT u2 = normal( p[ i + 2 ] - p[ i + 1 ] );
    PT fan = ( u1 + u2 );

    PT jiou = interPT( p[ i ] , p[ i ] + fen ,
                       p[ i + 1 ] , p[ i + 1 ] + fan );
	  if( jiou == PT(nan(""), nan("")) ) continue;
    D gli = dist( MP( p[ i ] , p[ i + 1 ] ) , jiou );
    if( gli != gli ) continue;
    if( equal( gli , 0.0 ) ) continue;
    mn = min( gli , mn );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    PT v1 = normal( p[ i - 1 ] - p[ i ] );
    PT v2 = normal( p[ i + 1 ] - p[ i ] );
    PT fen = ( v1 + v2 );
    if( equal( norm( fen ) , 0.0 ) ){
      PT dlt = p[ i + 1 ] - p[ i - 1 ];
      fen = MP( dlt.Y , -dlt.X );
    }

    D ang = acos( fabs( fen % v1 ) / norm( fen ) );
    D ndist = mn / sin( ang );
    if( equal( sin( ang ) , 0.0 ) ){
      ndist = mn;
      // printf( "angle : %.12f\n" , ang );
    }
    // if( equal( norm( fen ) , 0.0 ) ) puts( "shit" );
    ans += ndist;

    PT np = p[ i ] + normal( fen ) * ndist;
    if( p2.size() && equal( np.X , p2.back().X ) &&
                     equal( np.Y , p2.back().Y ) ) continue;
    p2.PB( np );
    // printf( "%.12f %.12f\n" , np.X , np.Y );
  }
  // puts( "====" );
  p.clear();
  // int nn = 1;
  // for( int i = 1 ; i < (int)p2.size() ; i ++ )
    // if( !equal( p2[ i ].X , p2[ nn - 1 ].X ) ||
        // !equal( p2[ i ].Y , p2[ nn - 1 ].Y ) )
      // p2[ nn ++ ] = p2[ i ];
  // p2.resize( nn );
  // printf( "%dn" , nn );
  while( (int)p2.size() > 1 &&
         equal( p2.back().X , p2[ 0 ].X ) &&
         equal( p2.back().Y , p2[ 0 ].Y ) )
    p2.pop_back();
  p = p2;
}
void solve(){
  // for( int i = 0 ; i < 15 ; i ++ ) cal();
  while( p.size() > 2 ) cal();
  if( (int)p.size() == 2 ) ans += norm( p[ 0 ] - p[ 1 ] );
  printf( "%.12f\n" , ans );
}
int main(){
  freopen( "roof.in" , "r" , stdin );
  freopen( "roof.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
