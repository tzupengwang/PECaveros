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
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
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
#define N 202020
void build(){

}
int n , m , deg[ N ];
vector<int> e[ N ];
void init(){
  n = getint();
  m = getint();
  for( int i = 0 ; i < m ; i ++ ){
    int ui = getint();
    int vi = getint();
    e[ ui ].PB( vi );
    e[ vi ].PB( ui );
    deg[ ui ] ++;
    deg[ vi ] ++;
  }
}
vector<PII> v;
bool got[ N ] , flag;
void go( int now , int prt , int b ){
  if( now == b ) return;
  // if( deg[ now ] > 2 ) flag = false;
  if( got[ now ] ){
    flag = false;
    return;
  }
  got[ now ] = true;
  for( size_t i = 0 ; i < e[ now ].size() ; i ++ )
    if( e[ now ][ i ] != prt )
      go( e[ now ][ i ] , now , b );
}
void check( int a , int b ){
  got[ a ] = got[ b ] = true; flag = true;
  for( size_t i = 0 ; i < e[ a ].size() ; i ++ )
    go( e[ a ][ i ] , a , b );
  if( flag ){
    printf( "2\n%d %d\n" , min( a , b ) , max( a , b ) );
    exit( 0 );
  }
}
bool got2[ N ] , flag2;
void go2( int now , int prt , int ed ){
  if( now == ed ) return;
  // if( deg[ now ] > 2 ) flag2 = false;
  if( got2[ now ] ){
    flag2 = false;
    return;
  }
  got2[ now ] = true;
  for( size_t i = 0 ; i < e[ now ].size() ; i ++ )
    if( e[ now ][ i ] != prt )
      go2( e[ now ][ i ] , now , ed );
}
void test( int a , int b ){
  got2[ a ] = got2[ b ] = true;
  for( size_t i = 0 ; i < e[ b ].size() ; i ++ )
    go2( e[ b ][ i ] , b , a );
}
void check2( int a ){
  flag2 = true;
  for( int i = (int)v.size() - 2 ; i >= 0 ; i -- )
    if( !got2[ v[ i ].SE ] ){
      test( a , v[ i ].SE );
      if( !flag2 ) break;
    }
  // for( int i = 1 ; i <= n ; i ++ )
    // if( !got2[ i ] ){
      // flag2 = false;
      // break;
    // }
  if( flag2 ){
    printf( "1\n%d\n" , a );
    exit( 0 );
  }
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    if( deg[ i ] % 2 ){
      puts( "0" );
      exit( 0 );
    }
  for( int i = 1 ; i <= n ; i ++ )
    v.PB( MP( deg[ i ] , i ) );
  sort( ALL( v ) );
  if( v.back().FI == 2 ){
    printf( "%d\n" , n );
    for( int i = 1 ; i <= n ; i ++ )
      printf( "%d%c" , i , " \n"[ i == n ] );
    exit( 0 );
  }
  if( v[ (int)v.size() - 3 ].FI == 2 )
    check( v[ (int)v.size() - 1 ].SE , v[ (int)v.size() - 2 ].SE );
  check2( v[ (int)v.size() - 1 ].SE );
  puts( "0" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
