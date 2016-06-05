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
#define N 101010
int kd[ N + N ];
void build(){
  kd[ 0 ] = 0;
  kd[ 1 ] = 1;
  for( int now = 2 ; now <= 512 ; now *= 2 )
    for( int i = now ; i < now + now ; i ++ )
      kd[ i ] = 1 - kd[ i - now ];
}
int n;
void init(){
  
}
void solve(){
  if( ( n & ( -n ) ) == n ){
    puts( "Yes" );
    vector<int> v1 , v2;
    int all = n * 2;
    for( int i = 1 ; i <= all ; i += 4 ){
      if( kd[ i / 4 ] == 0 ){
        v1.PB( i + 0 );
        v1.PB( i + 3 );
        v2.PB( i + 1 );
        v2.PB( i + 2 );
      }else{
        v1.PB( i + 1 );
        v1.PB( i + 2 );
        v2.PB( i + 0 );
        v2.PB( i + 3 );
      }
    }



    // vector<int> a1 , a2;
    // for( size_t i = 0 ; i < v1.size() ; i ++ )
      // for( size_t j = i + 1 ; j < v1.size() ; j ++ )
        // a1.PB( v1[ i ] + v1[ j ] );
    // for( size_t i = 0 ; i < v2.size() ; i ++ )
      // for( size_t j = i + 1 ; j < v2.size() ; j ++ )
        // a2.PB( v2[ i ] + v2[ j ] );
    // sort( ALL( a1 ) );
    // sort( ALL( a2 ) );

    for( size_t i = 0 ; i < v1.size() ; i ++ )
      printf( "%d%c" , v1[ i ] , " \n"[ i + 1 == v1.size() ] );
    for( size_t i = 0 ; i < v2.size() ; i ++ )
      printf( "%d%c" , v2[ i ] , " \n"[ i + 1 == v2.size() ] );
  }else puts( "No" );
}
int main(){
  build();
  freopen( "analogous.in" , "r" , stdin );
  freopen( "analogous.out" , "w" , stdout );
  //__ = getint();
  // while( __ -- ){
  while( scanf( "%d" , &n ) == 1 ){
    if( n == 0 ) break;
    init();
    solve();
  }
}
