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
#define N 1010
int nxt[ N ][ 2 ];
void build(){
  int now = 1;
  for( int i = now ; i < ( 1 << 8 ) - 1 ; i ++ ){
    nxt[ i ][ 0 ] = i * 2;
    nxt[ i ][ 1 ] = i * 2 + 1;
  }
}
int n , p , q;
void init(){
  // p = getint();
  // q = getint();
}
void solve(){
  for( int l = ( 1 << 7 ) , li = 0 ; l < ( 1 << 8 ) ; l ++ , li ++ ){
    if( li >= q ){
      nxt[ l ][ 0 ] = 1;
      nxt[ l ][ 1 ] = 1;
    }else if( li >= p ){
      nxt[ l ][ 0 ] = 257;
      nxt[ l ][ 1 ] = 257;
    }else{
      nxt[ l ][ 0 ] = 256;
      nxt[ l ][ 1 ] = 256;
    }
  }
  printf( "%d\n" , 257 );
  for( int i = 1 ; i <= 255 ; i ++ )
    printf( "%d %d\n" , nxt[ i ][ 0 ] , nxt[ i ][ 1 ] );
}
int main(){
  build();
  freopen( "drunkard.in" , "r" , stdin );
  freopen( "drunkard.out" , "w" , stdout );
  //__ = getint();
  // while( __ -- ){
  while( scanf( "%d%d" , &p , &q ) == 2 ){
    if( p == 0 && q == 0 ) break;
    init();
    solve();
  }
}
