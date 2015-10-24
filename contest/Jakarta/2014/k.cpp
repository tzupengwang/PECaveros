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
#define mod 997
int bt[ 10000 ];
int c[ 1010 ][ 1010 ];
void build(){
  for( int i = 0 ; i < 10000 ; i ++ )
    bt[ i ] = bt[ i / 2 ] + i % 2;
  for( int i = 0 ; i < 1010 ; i ++ )
    c[ i ][ 0 ] = c[ i ][ i ] = 1;
  for( int i = 2 ; i < 1010 ; i ++ )
    for( int j = 1 ; j < i ; j ++ )
      c[ i ][ j ] = ( c[ i - 1 ][ j ] + c[ i - 1 ][ j - 1 ] ) % mod;
}
int C( int a , int b ){
  int tans = 1;
  while( a || b ){
    tans = ( tans * c[ a % mod ][ b % mod ] ) % mod;
    a /= mod;
    b /= mod;
  }
  return tans;
}
int n , m , k;
vector< PII > v;
bool cmp( PII tp1 , PII tp2 ){
  return tp1.FI + tp1.SE < tp2.FI + tp2.SE;
}
void init(){
  v.clear();
  n = getint();
  m = getint();
  k = getint();
  for( int i = 0 ; i < k ; i ++ ){
    int tn = getint();
    int tm = getint();
    v.PB( MP( tn , tm ) );
  }
  sort( v.begin() , v.end() , cmp );
}
int a[ 15 ] , tn;
int tans;
int dltn[]={-1,0,1};
int dltm[]={1,0,-1};
void DFS( int now , int pn , int pm , int tcnt ){
  if( now == tn ){
    tcnt = ( tcnt * C( n - pn + m - pm , n - pn ) ) % mod;
    tans = ( tans + tcnt ) % mod;
    return;
  }
  for( int i = 0 ; i < 3 ; i ++ ){
    int npos = v[ a[ now ] ].FI + dltn[ i ];
    int mpos = v[ a[ now ] ].SE + dltm[ i ];
    if( npos >= pn && mpos >= pm ){
      DFS( now + 1 , npos , mpos , ( tcnt * C( npos - pn + mpos - pm , npos - pn ) ) % mod );
    }
  }
}
int cal( int msk ){
  tn = 0;
  for( int i = 0 ; i < k ; i ++ )
    if( ( msk >> i ) & 1 )
      a[ tn ++ ] = i;
  tans = 0;
  DFS( 0 , 1 , 1 , 1 );
  return tans;
}
void solve(){
  int ans = 0;
  for( int i = 0 ; i < ( 1 << k ) ; i ++ ){
    if( bt[ i ] % 2 == 1 )
      ans = ( ans - cal( i ) + mod ) % mod;
    else ans = ( ans + cal( i ) ) % mod;
  }
  printf( "Case #%d: %d\n" , ++ cs , ans % mod );
}
signed main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
