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
#define eps 1e-9
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
D mypow( D _a , ll _x ){
  if( _x == 0 ) return 1.0;
  D _tmp = mypow( _a , _x / 2 );
  _tmp = _tmp * _tmp;
  if( _x & 1 ) _tmp = _tmp * _a;
  return _tmp;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 9
class poly{
public:
  vector<D> _v;
  int _odr;
  poly(){}
  poly( int _n ){
    _odr = _n;
    _v.resize( _odr + 1 );
    for( int i = 0 ; i <= _odr ; i ++ )
      _v[ i ] = 0.0;
  }
  void resize( int _n ){
    _odr = _n;
    _v.resize( _odr + 1 );
    for( int i = 0 ; i <= _odr ; i ++ )
      _v[ i ] = 0.0;
  }
  D f( D _x ) const{
    D ret = 0.0;
    for( int i = 0 ; i <= _odr ; i ++ )
      ret += _v[ i ] * mypow( _x , i );
    return ret;
  }
  poly integral() const{
    poly _tmp( _odr + 1 );
    for( int i = 0 ; i <= _odr ; i ++ )
      _tmp._v[ i + 1 ] = _v[ i ] / ( (D)(i + 1) );
    return _tmp;
  }
  poly operator*( const poly& p2 ) const{
    poly _tmp( _odr + p2._odr );
    for( int i = 0 ; i <= _odr ; i ++ )
      for( int j = 0 ; j <= p2._odr ; j ++ )
        _tmp._v[ i + j ] += _v[ i ] * p2._v[ j ];
    return _tmp;
  }
  void print() const{
    for( int i = _odr ; i >= 0 ; i -- )
      printf( "%.2f%c" , (double)_v[ i ] , " \n"[ i == 0 ] );
  }
};
int odr , a , b , n , x;
void build(){

}
poly cur;
void init(){
  odr = getint();
  cur.resize( odr );
  for( int i = odr ; i >= 0 ; i -- )
    cur._v[ i ] = getint();
  a = getint();
  b = getint();
  n = getint();
  x = getint();
}
D ntan( D nr , D nx ){
  D ang = 2.0 * acos( -1.0 ) / nx;
  D area = 0.5 * nr * nr * sin( ang ) * nx;
  return area;
}
D myabs( D tx ){
  if( tx < 0.0 ) tx = -tx;
  return tx;
}
void solve(){
  poly cur2 = cur * cur;
  // cur.print();
  // cur2.print();
  cur2 = cur2.integral();
  // cur2.print();
  D ans1 = acos( -1.0 ) * ( cur2.f( b ) - cur2.f( a ) );
  D ans2 = 0.0;
  for( int i = 0 ; i < x ; i ++ ){
    D nx1 = a + (D)i * ( (D)( b - a ) / (D)x );
    D nx2 = nx1 + ( (D)( b - a ) / (D)x );
    D nr1 = cur.f( nx1 );
    D nr2 = cur.f( nx2 );
    D upa = ntan( nr1 , n );
    D upb = ntan( nr2 , n );
    if( upa < upb ){
      swap( upa , upb );
      swap( nr1 , nr2 );
      swap( nx1 , nx2 );
    }
    if( equal( nr1 , nr2 ) ){
      ans2 += ( upa ) * (D)( (D)( b - a ) / (D)x );
    }else{
      D nx3 = nx2 + ( nx2 - nx1 ) * nr2 / ( nr1 - nr2 );
      D vol = ( upa * myabs( nx1 - nx3 ) ) / 3.0 -
              ( upb * myabs( nx2 - nx3 ) ) / 3.0;
      // D vol = ( upa * nr1 - upb * nr2 ) / 3.0;
      ans2 += vol;
    }
  }
  // printf( "%.8f %.8f\n" , (double)ans1 , (double)ans2 );
  printf( "Case %d: %.4f\n" , ++ cs , (double)( myabs( ans1 - ans2 ) / ans1 ) * 100.0 );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
