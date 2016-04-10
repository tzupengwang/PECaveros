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
#define N 6001
bitset<13000> v[ N ];
int n;
char c[ N ];
void init(){
  n = getint();
  for( int i = 0 ; i <= n ; i ++ ){
    scanf( "%s" , c );
    int len = strlen( c );
    for( int j = 0 ; j < len ; j ++ ){
      int vl = c[ j ] - 33;
      for( int k = 0 ; k < 6 ; k ++ )
        if( ( vl >> k ) & 1 )
          v[ i ][ j * 6 + k ] = 1;
        else
          v[ i ][ j * 6 + k ] = 0;
    }
    // for( int j = 0 ; j < 2 * n ; j ++ )
      // printf( "%d" , (int)v[ i ][ j ] );
    // puts( "" );
  }
}
set<PII> S;
void test( int ii , int jj ){
  bitset<13000> yy = v[ ii ] & v[ jj ];
  if( (int)yy.count() * 2 >= n ){
    printf( "%d %d\n" , ii + 1 , jj + 1 );
    exit( 0 );
  }
}
void solve(){
  srand( 514514 );
  while( true ){
    int ii = rand() % ( n + 1 );
    int jj = rand() % ( n + 1 );
    if( ii == jj ) continue;
    if( ii > jj ) swap( ii , jj );
    if( S.count( MP( ii , jj ) ) ) continue;
    test( ii , jj );
    S.insert( MP( ii , jj ) );
  }
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
