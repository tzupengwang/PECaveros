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
#define N 111
class Matrix{
public:
  ll a[ N ][ N ] , n;
  Matrix(){}
  Matrix( int _n ) : n( _n ) {
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= n ; j ++ )
        a[ i ][ j ] = 0;
  }
  Matrix operator*( const Matrix& m1 ) const{
    Matrix tmp( n );
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        for( int k = 0 ; k < n ; k ++ )
          tmp.a[ i ][ j ] = add( tmp.a[ i ][ j ] ,
                                 mul( a[ i ][ k ] ,
                                      m1.a[ k ][ j ] , mod9 ) , mod9 );
    return tmp;
  }
  Matrix operator^( ll tk ) const{
    Matrix A( n ) , I( n );
    for( int i = 0 ; i < n ; i ++ )
      I.a[ i ][ i ] = 1;
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < n ; j ++ )
        A.a[ i ][ j ] = a[ i ][ j ];
    while( tk ){
      if( tk & 1 ) I = I * A;
      A = A * A; tk >>= 1;
    }
    return I;
  }
};
ll n , m , c[ 10 ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  for( int i = 1 ; i <= m ; i ++ )
    c[ i ] = getint();
  c[ 0 ] = 1 ;
}
Matrix A , B[ 12 ];
ll x[ N ];
inline int enc( int i , int j ) {
  return i*(m+1)+j;
}
inline PII dec( int xx ) {
  return PII( xx/(m+1) , xx%(m+1) );
}
void solve(){
  for( int k = 0 ; k <= m ; k ++ ){
    B[ k ] = Matrix( enc( m , m ) );
    for( int i = 0 ; i < enc( m , k ) ; i ++ )
      B[ k ].a[ i ][ i ] = 1;
    int is = m;
    int id = k;
    int i = enc( m , k );
    for ( int j = 0 ; j < enc( m , k ) ; j ++ ) {
      int js , jd;tie( js , jd ) = dec( j );
      // j -> i
      if( is == js ) {
        int tk = id-jd;
        B[ k ].a[ i ][ j ] = c[ tk ];
      } else {
        int tk = is-js;
        if( tk+id == jd )
          B[ k ].a[ i ][ j ] = c[ tk ];
      }
      if ( id == 0 && jd == 0 && is == js + 1 ) {
        // A.a[ i ][ j ] += c[ 2 ] ;
        B[ 0 ].a[ i ][ j ] = add( B[ 0 ].a[ i ][ j ] , c[ 2 ] , mod9 ) ;
      }
    }
  }
  B[ m+1 ] = Matrix( enc( m , m ) );
  for( int i = 0 ; i < enc( m-1 , m ) ; i++ )
    B[ m+1 ].a[ i ][ i+m+1 ] = 1;
  A = B[ 0 ];
  for( int i = 1 ; i <= m+1 ; i++ )
    A = B[ i ] * A;
  A = A ^ n;
  ll ans = 0ll;
  for( int i = 0 ; i < enc( m , m ) ; i++ )
    ans = add( ans , A.a[ 0 ][ i ] , mod9 );
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
