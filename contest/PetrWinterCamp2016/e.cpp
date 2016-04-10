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
#define N 202020
ll n , m , s[ N ] , t[ N ] , g[ N ] , yy[ N ];
vector<int> v[ N ] , r[ N ] , in[ N ] , p[ N ];
vector<PII> vv[ N ];
bool okay[ N ][ 2 ];
void build(){

}
void init(){
  n = getint(); m = getint();
  if( n == 0 && m == 0 ) exit( 0 );
  for( int i = 0 ; i < n ; i ++ ){
    v[ i ].clear();
    vv[ i ].clear();
    in[ i ].clear();
    p[ i ].clear();
  }
  for( int i = 0 ; i < m ; i ++ ){
    int ri = getint() - 1;
    v[ ri ].PB( i );
    s[ i ] = ri;
    int ki = getint();
    r[ i ].clear();
    t[ i ] = 0;
    g[ i ] = 0;
    yy[ i ] = 0;
    while( ki -- ){
      char cc[ 20 ];
      scanf( "%s" , cc );
      if( cc[ 0 ] == 'a' || cc[ 0 ] == 'b' ) t[ i ] ++;
      else{
        int xi; sscanf( cc , "%d" , &xi );
        xi --;
        r[ i ].PB( xi );
        in[ xi ].PB( i );
        p[ xi ].PB( ri );
      }
    }
    sort( ALL( r[ i ] ) );
    r[ i ].resize( unique( ALL( r[ i ] ) ) - r[ i ].begin() );
  }
  for( int i = 0 ; i < n ; i ++ ){
    for( int j = 0 ; j < 2 ; j ++ )
      okay[ i ][ j ] = false;
    sort( ALL( in[ i ] ) );
    for( size_t tl = 0 , tr = 0 ; tl < in[ i ].size() ; tl = tr ){
      while( tr < in[ i ].size() && in[ i ][ tl ] == in[ i ][ tr ] ) tr ++;
      vv[ i ].PB( MP( in[ i ][ tl ] , tr - tl ) );
    }
    sort( ALL( p[ i ] ) );
    p[ i ].resize( unique( ALL( p[ i ] ) ) - p[ i ].begin() );
  }
}
queue<int> Q;
bool inq[ N ] , tag[ N ];
void check( int rn ){
  if( g[ rn ] < (int)r[ rn ].size() ) return;
  if( yy[ rn ] ){
    if( !okay[ s[ rn ] ][ 0 ] ||
        !okay[ s[ rn ] ][ 1 ] ){
      okay[ s[ rn ] ][ 0 ] =
      okay[ s[ rn ] ][ 1 ] = true;
      if( !inq[ s[ rn ] ] ){
        inq[ s[ rn ] ] = true;
        Q.push( s[ rn ] );
      }
    }
  }else{
    if( !okay[ s[ rn ] ][ t[ rn ] % 2 ] ){
      okay[ s[ rn ] ][ t[ rn ] % 2 ] = true;
      if( !inq[ s[ rn ] ] ){
        Q.push( s[ rn ] );
        inq[ s[ rn ] ] = false;
      }
    }
  }
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    inq[ i ] = tag[ i ] = false;
  for( int i = 0 ; i < m ; i ++ )
    if( (int)r[ i ].size() == 0 ){
      if( !okay[ s[ i ] ][ t[ i ] % 2 ] ){
        okay[ s[ i ] ][ t[ i ] % 2 ] = true;
        if( !inq[ s[ i ] ] ){
          Q.push( s[ i ] );
          inq[ s[ i ] ] = false;
        }
      }
    }
  while( Q.size() ){
    int xn = Q.front(); Q.pop(); inq[ xn ] = false;
    int dlt = tag[ xn ] ? 0 : 1;
    tag[ xn ] = true;
    if( okay[ xn ][ 0 ] && okay[ xn ][ 1 ] ){
      for( size_t i = 0 ; i < vv[ xn ].size() ; i ++ ){
        int rn = vv[ xn ][ i ].FI;
        g[ rn ] += dlt;
        yy[ rn ] = 1;
        check( rn );
      }
    }else if( okay[ xn ][ 0 ] ){
      for( size_t i = 0 ; i < vv[ xn ].size() ; i ++ ){
        int rn = vv[ xn ][ i ].FI;
        g[ rn ] += dlt;
        check( rn );
      }
    }else if( okay[ xn ][ 1 ] ){
      for( size_t i = 0 ; i < vv[ xn ].size() ; i ++ ){
        int rn = vv[ xn ][ i ].FI;
        int ln = vv[ xn ][ i ].SE;
        g[ rn ] += dlt;
        t[ rn ] += ln;
        check( rn );
      }
    }
  }
  puts( okay[ 0 ][ 1 ] ? "YES" : "NO" );
}
int main(){
  build();
  //__ = getint();
  while( true ){
    init();
    solve();
  }
}
