// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
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
class frac{
 public:
  ll up, dn;
  frac(){ up = 0; dn = 1; }
  frac( ll _up , ll _dn ){
    up = _up; dn = _dn;
    ll t = __gcd( up , dn );
    up /= t;
    dn /= t;
    if( dn < 0 ) dn *= -1, up *= -1;
  }
  frac operator+( const frac& t ) const{
    frac tmp( 0 , 1 );
    ll d = dn * t.dn / __gcd( dn , t.dn );
    ll u = up * ( d / dn ) + t.up * ( d / t.dn );
    frac _a( u , d );
    return _a;
  }
  frac operator-( const frac& t ) const{
    frac tmp( 0 , 1 );
    ll d = dn * t.dn / __gcd( dn , t.dn );
    ll u = up * ( d / dn ) - t.up * ( d / t.dn );
    frac _a( u , d );
    return _a;
  }
  frac operator*( const frac& t ) const{
    ll d = dn * t.dn;
    ll u = up * t.up;
    ll _ = __gcd( d , u );
    d /= _; u /= _;
    frac _a( u , d );
    return _a;
  }
  frac operator/( const frac& t ) const{
    ll d = dn * t.up;
    ll u = up * t.dn;
    ll _ = __gcd( d , u );
    d /= _; u /= _;
    frac _a( u , d );
    return _a;
  }
  bool operator==( const frac& t ) const{
    return up == t.up && dn == t.dn;
  }
  bool operator!=( const frac& t ) const{
    return up != t.up || dn != t.dn;
  }
  void print() const{
    printf( "%lld/%lld" , up , dn );
  }
};
#define N 514
string input[ N ];
int nidx;
int var[ N ];
int kind[ N ];
#define LAG 514514
// 514514 for lag
// 0 ~ 25 for a ~ z
// 100~900 for 1 ~ 9
vector<int> nxt[ N ];
void build(){

}
int pre[ N ];
void init(){
  pre[ 0 ] = 0;
  kind[ 0 ] = -1;
  while( getline( cin , input[ nidx + 1 ] ) ){
    int now = ++ nidx;
    int len = input[ now ].length();
    int ptr = 0;
    while( ptr < len && input[ now ][ ptr ] == ' ' ) ptr ++;
    int tmp = ptr / 4 + 1;
    nxt[ pre[ tmp - 1 ] ].PB( now );
    pre[ tmp ] = now;
    if( input[ now ][ ptr ] == 'l' )
      kind[ now ] = LAG;
    else{
      var[ now ] = ( input[ now ][ ptr + 4 ] - 'a' );
      while( ptr < len && input[ now ][ ptr ] != '(' ) ptr ++;
      ptr ++;
      if( input[ now ][ ptr ] >= '0' &&
          input[ now ][ ptr ] <= '9' )
        kind[ now ] = ( input[ now ][ ptr ] - '0' ) * 100;
      else
        kind[ now ] = ( input[ now ][ ptr ] - 'a' );
    }
  }
}
int ans , a[ 10 ];
int tag[ 26 ];
void go( int now ){
  if( kind[ now ] == LAG ){
    ans ++;
    return;
  }
  if( kind[ now ] >= 100 && kind[ now ] <= 900 ){
    for( int _ = 0 ; _ < kind[ now ] / 100 ; _ ++ ){
      tag[ var[ now ] ] = _;
      for( int j = 0 ; j < (int)nxt[ now ].size() ; j ++ )
        go( nxt[ now ][ j ] );
    }
  }else{
    for( int _ = 0 ; _ < tag[ kind[ now ] ] ; _ ++ ){
      tag[ var[ now ] ] = _;
      for( int j = 0 ; j < (int)nxt[ now ].size() ; j ++ )
        go( nxt[ now ][ j ] );
    }
  }
}
int sans[ N ];
frac mat[ 9 ][ 9 ];
void gauss(){
  for( int i = 0 ; i < 7 ; i ++ )
    for( int j = 6, k = 1 ; j >= 0 ; j -- , k *= i )
      mat[ i ][ j ] = frac( k , 1 );
  // for( int i = 0 ; i < 7 ; i ++ )
    // for( int j = 0 ; j < 8 ; j ++ ){
      // mat[ i ][ j ].print();
      // printf( "%c" , " \n"[ j == 7 ] );
    // }
  for( int i = 0 ; i < 7 ; i ++ ){
    int j = i;
    while( j < 7 && mat[ j ][ i ] == frac( 0 , 1 ) ) j ++;
    if( i != j ){
      for( int k = 0 ; k < 8 ; k ++ )
        swap( mat[ i ][ k ] , mat[ j ][ k ] );
    }
    frac inv = frac( 1 , 1 ) / mat[ i ][ i ];
    for( int k = i ; k < 8 ; k ++ )
      mat[ i ][ k ] = mat[ i ][ k ] * inv;
    for( int k = 0 ; k < 7 ; k ++ ){
      if( k == i ) continue;
      frac bns = mat[ k ][ i ] / mat[ i ][ i ];
      for( int l = i ; l < 8 ; l ++ )
        mat[ k ][ l ] = mat[ k ][ l ] - mat[ i ][ l ] * bns;
    }
  }
}
void cal( int now ){
  mat[ now ][ 7 ].print();
  if( 6 - now ){
    int pwr = 6 - now;
    while( pwr -- )
      printf( "*n" );
  }
}
void solve(){
  for( int i = 0 ; i < 7 ; i ++ ){
    ans = 0;
    tag[ 'n' - 'a' ] = i;
    for( int j = 0 ; j < (int)nxt[ 0 ].size() ; j ++ )
      go( nxt[ 0 ][ j ] );
    mat[ i ][ 7 ] = frac( ans , 1 );
    sans[ i ] = ans;
  }
  gauss();
  for( int i = 0 ; i < 7 ; i ++ ){
    if( i ) putchar( '+' );
    cal( i );
  }
  puts( "" );
}
int main(){
  freopen( "fygon.in" , "r" , stdin );
  freopen( "fygon.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
