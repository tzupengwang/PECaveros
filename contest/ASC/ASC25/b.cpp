// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
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
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pt operator/( const Pt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
void scan( Pt& tp ){
  tp.X = getint();
  tp.Y = getint();
}
void print( const Pt& tp ){
  printf( "%.6f %.6f\n" , tp.X , tp.Y );
}
#define N 11
int n;
Pt p[ N ];
void build(){

}
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scan( p[ i ] );
}
Pt ans;
vector< Circle > vv;
vector<Pt> interCircle( Pt o1 , D r1 , Pt o2 , D r2 ){
  D d2 = ( o1 - o2 ) * ( o1 - o2 );
  D d = sqrt(d2);
  if( d < eps ){
    if( equal( r1 , r2 ) )
      return {o1 + make_pair( r1 , 0.0 )};
    return {};
  }
	if( d > r1 + r2 + eps ) return {};
  if( d < fabs( r1 - r2 ) ) return {};
  if( equal( d , fabs( r1 - r2 ) ) ){
    if( r1 < r2 ){
      swap( o1 , o2 );
      swap( r1 , r2 );
    }
    Pt dlt = o2 - o1;
    dlt = dlt * ( r2 / norm( o2 - o1 ) );
    return { o2 + dlt };
  }
  if( equal( d , r1 + r2 ) ){
    Pt dlt = o2 - o1;
    dlt = dlt * ( r1 / ( r1 + r2 ) );
    return { o1 + dlt };
  }
  Pt u = (o1+o2)*0.5 + (o1-o2)*((r2*r2-r1*r1)/(2*d2));
  D A = sqrt((r1+r2+d)*(r1-r2+d)*(r1+r2-d)*(-r1+r2+d));
  Pt v = Pt( o1.Y-o2.Y , -o1.X + o2.X ) * A / (2*d2);
  return {u+v, u-v};
}
const D pi = acos( -1.0 );
vector< Pt > cand;
inline D cal( Pt tp ){
  for( int i = 1 ; i <= n ; i ++ ){
    // printf( "%.6f\n" , norm( tp - p[ i ] ) );
    if( norm( tp - p[ i ] ) < 1.0 - eps )
      return -1;
  }
  D tang = 2.0 * pi;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = i + 1 ; j <= n ; j ++ ){
      Pt dlt1 = p[ i ] - tp;
      Pt dlt2 = p[ j ] - tp;
      D vl = ( dlt1 * dlt2 ) / norm( dlt1 ) / norm( dlt2 );
      if( equal( vl , +1 ) ) vl = +1.0 - eps;
      if( equal( vl , -1 ) ) vl = -1.0 + eps;
      D nang = acos( vl );
      // printf( "   %.6f\n" , vl );
      // printf( "%.6f\n" , nang );
      tang = min( tang , nang );
    }
  return tang;
}
inline bool okay( D theta ){
  vv.clear();
  cand.clear();
  for( int i = 1 ; i <= n ; i ++ )
    vv.push_back( { p[ i ] , 1 } );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = i + 1 ; j <= n ; j ++ ){
      Pt dlt = p[ j ] - p[ i ];
      D dst = norm( p[ i ] - p[ j ] );
      D r = sqrt( dst * dst / ( 2.0 * ( 1 - cos( 2.0 * theta ) ) ) );
      D yy = sqrt( r * r - dst * dst / 4 );
      Pt far = perp( dlt );
      far = far * ( yy / dst );
      Pt mid = ( p[ i ] + p[ j ] ) * 0.5;
      Pt o1 = mid + far , o2 = mid - far;
      vv.push_back( { o1 , r } );
      vv.push_back( { o2 , r } );
    }
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    for( size_t j = i + 1 ; j < vv.size() ; j ++ ){
      vector<Pt> tcand = interCircle( vv[ i ].O , vv[ i ].R ,
                                      vv[ j ].O , vv[ j ].R );
      for( auto it : tcand ){
        if( it.X != it.X ) continue;
        if( it.Y != it.Y ) continue;
        cand.push_back( it );
      }
    }
  for( auto tp : cand ){
    D ang = cal( tp );
    // print( tp );
    // printf( "%.12f\n" , ang );
    if( ang < theta - eps ) continue;
    ans = tp;
    return true;
  }
  return false;
}
void solve(){
  D bl = 0.0 , br = acos( -1.0 );
  for( int i = 0 ; i < 20 ; i ++ ){
    D bmid = ( bl + br ) * 0.5;
    if( okay( bmid ) ) bl = bmid;
    else br = bmid;
  }
  // printf( "%.9f\n" , cal( { -22.511460, -28.297960 } ) );
  // printf( "%.6f %.6f\n" , bl , br );
  printf( "%.9f %.9f\n" , ans.X , ans.Y );
}
int main(){
  freopen( "astronomy.in" , "r" , stdin );
  freopen( "astronomy.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
