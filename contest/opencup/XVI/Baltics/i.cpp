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
// inline ll add( ll _x , ll _y , ll _mod = mod7 ){
  // ll _ = _x + _y;
  // if( _ >= _mod ) _ -= _mod;
  // return _;
// }
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
#define N 6
#define R (1ll<<63)
class Matrix{
public:
  ll a[ N ][ N ];
  Matrix(){
    for( int i = 0 ; i < N ; i ++ )
      for( int j = 0 ; j < N ; j ++ )
        a[ i ][ j ] = 0;
  }
  Matrix operator*( const Matrix & m ) const{
    Matrix v;
    for( int i = 0 ; i < N ; i ++ )
      for( int j = 0 ; j < N ; j ++ )
        for( int k = 0 ; k < N ; k ++ )
          v.a[ i ][ j ] += a[ i ][ k ] * m.a[ k ][ j ];
    return v;
  }
};
void build(){
}
char c[ 200 ];
int len , nxt[ 200 ] , ndep[ 200 ];
Matrix mm[ 200 ][ 26 ] , Plus , Minus , add;
bool got[ 200 ][ 26 ];
void init(){
  scanf( "%s" , c + 1 );
  len = strlen( c + 1 );
  vector<int> vv;
  for( int i = 1 ; i <= len ; i ++ ){
    if( c[ i ] == '[' ) vv.PB( i );
    if( c[ i ] == ']' ){
      nxt[ vv.back() ] = i;
      ndep[ vv.back() ] = (int)vv.size() - 1;
      vv.pop_back();
    }
  }
  for( int i = 1 ; i <= 4 ; i ++ )
    Plus.a[ i - 1 ][ i ] = Minus.a[ i - 1 ][ i ] = 1;
  Plus.a[ 5 ][ 5 ] = Minus.a[ 5 ][ 5 ] = 1;
  Plus.a[ 4 ][ 5 ] = Minus.a[ 4 ][ 5 ] = R;
  Plus.a[ 0 ][ 0 ] = 1;
  Minus.a[ 0 ][ 0 ] = -1;
  for( int i = 1 ; i <= 4 ; i ++ )
    add.a[ i ][ i - 1 ] = 1;
  add.a[ 5 ][ 5 ] = 1;
}
Matrix cal( int l , int r , int dep ){
  Matrix I;
  for( int i = 0 ; i < N ; i ++ )
    I.a[ i ][ i ] = 1;
  if( l > r ) return I;
  // for( int i = l ; i <= r ; i ++ )
    // if( c[ i ] == '[' && ndep[ i ] == dep ){
      // int nn = nxt[ i ];
      // got[ dep ][ c[ nn + 1 ] - 'a' ] = true;
      // mm[ dep ][ c[ nn + 1 ] - 'a' ] = cal( i + 1 , nn - 1 , dep + 1 );
    // }

  for( int i = l ; i <= r ; i ++ )
    if( c[ i ] == '[' ){
      if( ndep[ i ] == dep ){
        got[ dep ][ c[ nxt[ i ] + 1 ] - 'a' ] = true;
        mm[ dep ][ c[ nxt[ i ] + 1 ] - 'a' ] = cal( i + 1 , nxt[ i ] - 1 , dep + 1 );
      }
      i = nxt[ i ] + 1;
    }else if( c[ i ] == '+' ) I = Plus * I;
    else if( c[ i ] == '-' ) I = Minus * I;
    else if( c[ i ] >= '0' && c[ i ] <= '9' ){
      add.a[ 0 ][ 5 ] = c[ i ] - '0';
      I = add * I;
    }else if( c[ i ] >= 'a' && c[ i ] <= 'z' ){
      int ii = c[ i ] - 'a';
      for( int k = dep ; k >= 0 ; k -- )
        if( got[ k ][ ii ] ){
          I = mm[ k ][ ii ] * I;
          break;
        }
    }

  for( int i = l ; i <= r ; i ++ )
    if( c[ i ] == '[' && ndep[ i ] == dep ){
      int nn = nxt[ i ];
      got[ dep ][ c[ nn + 1 ] - 'a' ] = false;
    }

  return I;
}
vector<ll> va , vans;
void solve(){
  Matrix ans = cal( 1 , len , 0 );
  for( int i = 0 ; i < 5 ; i ++ )
    va.PB( R );
  va.PB( 1 );
  vans.resize( 6 );
  for( int i = 0 ; i < 6 ; i ++ ){
    vans[ i ] = 0;
    for( int j = 0 ; j < 6 ; j ++ )
      vans[ i ] += ans.a[ i ][ j ] * va[ j ];
  }
  int sz = 0;
  for( int i = 0 ; i < 5 ; i ++ )
    if( vans[ i ] != R ) sz ++;
  printf( "%d\n" , sz );
  for( int i = 0 ; i < sz ; i ++ )
    printf( "%lld%c" , vans[ i ] , " \n"[ i + 1 == sz ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
