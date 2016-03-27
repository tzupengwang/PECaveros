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
int d , k , l;
void init(){
  d = getint();
  k = getint();
  l = getint();
}
void solve(){
  if( d >= l && l >= k ){
    int n = 12 + k + 12 + 1;
    vector<PII> v;
    for( int i = 1 ; i <= 12 ; i ++ )
      for( int j = i + 1 ; j <= 12 ; j ++ )
        v.PB( MP( i , j ) );
    for( int i = 1 ; i <= 12 ; i ++ )
      for( int j = 13 ; j <= 12 + k ; j ++ )
        v.PB( MP( i , j ) );
    for( int i = 12 + k + 1 ; i <= 12 + k + 12 ; i ++ )
      for( int j = i + 1 ; j <= 12 + k + 12 ; j ++ )
        v.PB( MP( i , j ) );
    for( int i = 12 + k + 1 ; i <= 12 + k + l ; i ++ ){
      int j = i - 12 - k - 1;
      j %= k; j ++;
      v.PB( MP( 12 + j , i ) );
    }
    for( int i = 12 + k + 1 ; i <= 12 + k + d ; i ++ )
      v.PB( MP( i , n ) );
    printf( "%d %d\n" , n , (int)v.size() );
    for( size_t i = 0 ; i < v.size() ; i ++ )
      printf( "%d %d\n" , v[ i ].FI , v[ i ].SE );
  }else{
    puts( "0 0" );
    exit( 0 );
  }
}
int main(){
  freopen( "dkl.in" , "r" , stdin );
  freopen( "dkl.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
