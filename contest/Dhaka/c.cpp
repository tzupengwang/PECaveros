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
#define mod 21092013ll
#define N 101010
int n , l[ N ] , r[ N ];
vector<int> v[ N ];
int mu[ N ];
bool p[ N ];
void build(){
  for( int i = 1 ; i < 51 ; i ++ ) mu[ i ] = 1, p[ i ] = true;
  for( int i = 2 ; i < 51 ; i ++ ) if( p[ i ] ){
    for( int j = i ; j < 51 ; j += i ) mu[ j ] *= -1, p[ j ] = false;
    for( int j = i * i ; j < 51 ; j += i * i ) mu[ j ] = 0;
  }
}
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ ) v[ i ].clear();
  for( int i = 1 ; i < n ; i ++ ){
    int tu = getint();
    int tv = getint();
    v[ tu ].PB( tv );
    v[ tv ].PB( tu );
  }
  for( int i = 1 ; i <= n ; i ++ )
    l[ i ] = getint();
  for( int i = 1 ; i <= n ; i ++ )
    r[ i ] = getint();
}
ll dp[ N ];
ll ans[ 51 ];
ll rans[ 51 ];
int ngcd;
void DFS( int now , int np ){
  ll csum = 0;
  dp[ now ] = 0;
  ll cn = 0;
  cn = ( r[ now ] / ngcd ) - ( ( l[ now ] - 1 ) / ngcd );
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( v[ now ][ i ] != np ){
      DFS( v[ now ][ i ] , now );
      ll dlt = ( dp[ v[ now ][ i ] ] * ( ( csum * cn + cn ) % mod ) ) % mod;
      ans[ ngcd ] = ( ans[ ngcd ] + dlt ) % mod;
      csum = ( csum + dp[ v[ now ][ i ] ] ) % mod;
      dp[ now ] = ( dp[ now ] + dp[ v[ now ][ i ] ] * cn ) % mod;
    }
  dp[ now ] = ( dp[ now ] + cn ) % mod;
  ans[ ngcd ] = ( ans[ ngcd ] + cn ) % mod;
}
void cal( int ng ){
  ans[ ng ] = 0;
  ngcd = ng;
  DFS( 1 , 1 );
}
void solve(){
  for( int i = 1 ; i <= 50 ; i ++ ) cal( i );
  printf( "Case %d:\n" , ++ cs );
  for( int i = 1 ; i <= 50 ; i ++ ){
    rans[ i ] = 0;
    for( int j = 1 ; i * j <= 50 ; j ++ ){
      rans[ i ] += mu[ j ] * ans[ i * j ];
      rans[ i ] = ( rans[ i ] % mod + mod ) % mod;
    }
    printf( "%d: %lld\n" , i , rans[ i ] );
  }
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
