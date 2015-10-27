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
bool equal( D _x ,  D _y ){
    return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
const int L = 111;
const int BS = 100000000;
class BigInt{
public:
  int _vl[ L ] , _l , _sgn;
  BigInt(){
    for( int i = 0 ; i < L ; i ++ )
      _vl[ i ] = 0;
    _l = 0; _sgn = 1;
  }
  BigInt( ll x ){
    for( int i = 0 ; i < L ; i ++ )
      _vl[ i ] = 0;
    _l = 0; _sgn = 1;
    if( x < 0 ) _sgn = -1, x = -x;
    while( x ){
      _vl[ _l ++ ] = x % BS;
      x /= BS;
    }
  }
  void print() const{
    if( _l == 0 ) putchar( '0' );
    else{
      if( _sgn < 0 ) putchar( '-' );
      printf( "%d" , _vl[ _l - 1 ] );
      for( int i = _l - 2 ; i >= 0 ; i -- )
        printf( "%08d" , _vl[ i ] );
    }
  }
  void normalize(){
    for( int i = 0 ; i < _l ; i ++ ){
      _vl[ i + 1 ] += _vl[ i ] / BS;
      _vl[ i ] %= BS;
    }
    while( _l && _vl[ _l - 1 ] == 0 ) _l --;
    if( _l == 0 ) _sgn = 1;
  }
  BigInt operator-() const{
    BigInt _t = (*this);
    if( _l > 0 ) _t._sgn = -_t._sgn;
    return _t;
  }
  BigInt operator+( const BigInt& b ) const{
    if( _sgn < b._sgn ) return b - sign( 1 );
    if( _sgn > b._sgn ) return (*this) - b.sign( 1 );
    BigInt _t = *this;
    _t._l = max( _l , b._l ) + 2;
    for( int i = 0 ; i < _t._l ; i ++ )
      _t._vl[ i ] += b._vl[ i ];
    _t.normalize();
    return _t;
  }
  BigInt operator-( const BigInt& b ) const{
    if( cmp3( b ) >= 0 ){
      if( _sgn == -1 )
        return b.sign( 1 ) - sign( 1 );
      if( _sgn != b._sgn )
        return (*this) + b.sign( 1 );
      BigInt _t = *this;
      for( int i = 0 ; i < _l ; i ++ )
        _t._vl[ i ] -= b._vl[ i ];
      for( int i = 0 ; i < _l ; i ++ )
        if( _t._vl[ i ] < 0 )
          _t._vl[ i ] += BS,
          _t._vl[ i + 1 ] --;
      _t.normalize();
      return _t;
    }else{
      BigInt _t = b - (*this);
      _t._sgn = -1;
      return _t;
    }
  }
  int cmp3( const BigInt& b ) const{
    if( _sgn != b._sgn ) return ( _sgn > 0 ) - ( b._sgn > 0 );
    if( _l != b._l ) return ( ( _l > b._l ) - ( b._l > _l ) ) * _sgn;
    for( int i = _l - 1 ; i >= 0 ; i --  )
      if( _vl[ i ] != b._vl[ i ] ){
        return ( ( _vl[ i ] > b._vl[ i ] ) - 
                 ( b._vl[ i ] > _vl[ i ] ) ) * _sgn;
      }
    return 0;
  }
  BigInt sign( int _newSgn ) const{
    BigInt b = *this;
    b._sgn = _newSgn;
    return b;
  }
  BigInt mulsign( int _newSgn ) const{
    BigInt b = *this;
    b._sgn *= _newSgn;
    return b;
  }
  bool operator==( const BigInt& b ) const{ return cmp3( b ) == 0; }
  bool operator>( const BigInt& b ) const{ return cmp3( b ) > 0; }
  bool operator<( const BigInt& b ) const{ return cmp3( b ) < 0; }
};
#define N 110
int n;
vector<string> func[ N ];
void build(){
}
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    int k = getint();
    while( k -- ){
      string tmp; cin >> tmp;
      func[ i ].push_back( tmp );
    }
  }
}
BigInt dpx[ N ][ 4 ][ 5 ];
BigInt dpy[ N ][ 4 ][ 5 ];
int dpdir[ N ][ 4 ];
// 0 for + + 1 for + - 2 for - + 3 for - - 4 for shift
int sgnx[]={1,1,-1,-1};
int sgny[]={1,-1,1,-1};
bool dn[ N ][ 4 ];
bool on[ N ][ 4 ];
int dirx[]={1,0,-1,0};
int diry[]={0,-1,0,1};
BigInt ox[ N ][ 4 ];
BigInt oy[ N ][ 4 ];
// LEFT -- RIGHT ++
void find_ans(){
  BigInt ans;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 0 ; j < 4 ; j ++ )
      for( int k = 0 ; k < 5 ; k ++ ){
        BigInt tx = dpx[ i ][ j ][ k ] + ox[ i ][ j ];
        BigInt ty = dpy[ i ][ j ][ k ] + oy[ i ][ j ];
        tx = tx.sign( 1 );
        ty = ty.sign( 1 );
        if( tx + ty > ans )
          ans = tx + ty;
      }
  ans.print();
  puts( "" );
}
void DP( int no , BigInt x , BigInt y , int dir ){
  if( dn[ no ][ dir ] ) return;
  if( on[ no ][ dir ] ){
    if( x == ox[ no ][ dir ] && y == oy[ no ][ dir ] ){
      find_ans();
      exit( 0 );
    }else{
      puts( "Infinity" );
      exit( 0 );
    }
  }
  on[ no ][ dir ] = true;
  ox[ no ][ dir ] = x;
  oy[ no ][ dir ] = y;
  int odir = dir;
  for( int i = 0 ; i < (int)func[ no ].size() ; i ++ ){
    if( func[ no ][ i ][ 0 ] == 'G' )
      x = x + BigInt( dirx[ dir ] ),
      y = y + BigInt( diry[ dir ] );
    else if( func[ no ][ i ][ 0 ] == 'L' ) dir = ( dir + 3 ) % 4;
    else if( func[ no ][ i ][ 0 ] == 'R' ) dir = ( dir + 1 ) % 4;
    else{
      int nxt = atoi( func[ no ][ i ].substr( 1 ).data() );
      DP( nxt , x , y , dir );
      for( int j = 0 ; j < 4 ; j ++ ){
        BigInt tx = x + dpx[ nxt ][ dir ][ j ] - ox[ no ][ odir ];
        BigInt ty = y + dpy[ nxt ][ dir ][ j ] - oy[ no ][ odir ];
        for( int k = 0 ; k < 4 ; k ++ ){
          if( tx.mulsign( sgnx[ k ] ) + ty.mulsign( sgny[ k ] ) >
              dpx[ no ][ odir ][ k ].mulsign( sgnx[ k ] ) +
              dpy[ no ][ odir ][ k ].mulsign( sgny[ k ] ) ){
            dpx[ no ][ odir ][ k ] = tx;
            dpy[ no ][ odir ][ k ] = ty;
          }
        }
      }
      x = x + dpx[ nxt ][ dir ][ 4 ];
      y = y + dpy[ nxt ][ dir ][ 4 ];
      dir = ( dir + dpdir[ nxt ][ dir ] ) % 4;
    }
    for( int k = 0 ; k < 4 ; k ++ ){
      BigInt tx = x - ox[ no ][ odir ];
      BigInt ty = y - oy[ no ][ odir ];
      if( tx.mulsign( sgnx[ k ] ) +
          ty.mulsign( sgny[ k ] ) >
          dpx[ no ][ odir ][ k ].mulsign( sgnx[ k ] ) +
          dpy[ no ][ odir ][ k ].mulsign( sgny[ k ] ) ){
        dpx[ no ][ odir ][ k ] = tx;
        dpy[ no ][ odir ][ k ] = ty;
      }
    }
  }
  dpx[ no ][ odir ][ 4 ] = x - ox[ no ][ odir ];
  dpy[ no ][ odir ][ 4 ] = y - oy[ no ][ odir ];
  dpdir[ no ][ odir ] = ( dir - odir + 4 ) % 4;
  on[ no ][ odir ] = false;
  dn[ no ][ odir ] = true;

  // printf( "%d %d :\n" , no , odir );
  // printf( "%d\n" , dpdir[ no ][ odir ] );
  // ox[ no ][ odir ].print(); putchar( ' ' );
  // oy[ no ][ odir ].print(); putchar( '\n' );
  // for( int i = 0 ; i < 5 ; i ++ ){
    // dpx[ no ][ odir ][ i ].print(); putchar( ' ' );
    // dpy[ no ][ odir ][ i ].print(); putchar( '\n' );
  // }
}
void solve(){
  DP( 1 , BigInt( 0 ) , BigInt( 0 ) , 0 );
  find_ans();
}
int main(){
  freopen( "journey.in" , "r" , stdin );
  freopen( "journey.out" , "w" , stdout );
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
