// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
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
int __ = 1 , cs;
/*********default*********/
#define N 514
char c[ 3 ][ N ];
int cnt[ N ];
void build(){

}
int trans( char ctmp ){
  if( ctmp == 'A' ) return 1;
  if( ctmp >= '0' && ctmp <= '9' ) return ctmp - '0';
  return 10;
}
void init(){
  scanf( "%s%s%s" , c[ 0 ] , c[ 1 ] , c[ 2 ] );
  for( int i = 1 ; i < 10 ; i ++ ) cnt[ i ] = 4;
  cnt[ 10 ] = 16;
  cnt[ trans( c[ 0 ][ 0 ] ) ] --;
  cnt[ trans( c[ 1 ][ 0 ] ) ] --;
  cnt[ trans( c[ 2 ][ 0 ] ) ] --;
}
D DFS2( int sc , int tsc , bool flag ){
  if( tsc >= 17 || ( flag && tsc + 10 <= 21 && tsc + 10 >= 17 ) ){
    if( flag && tsc + 10 <= 21 ) tsc += 10;
    if( sc > tsc || tsc > 21 ) return 1.0;
    if( sc < tsc && tsc <= 21 ) return -1.0;
    return 0.0;
  }
  D tsum = 0.0;
  int tcnt = 0;
  for( int j = 1 ; j <= 10 ; j ++ ) tcnt += cnt[ j ];
  for( int i = 1 ; i <= 10 ; i ++ )
    if( cnt[ i ] ){
      cnt[ i ] --;
      D tmp = DFS2( sc , tsc + i , flag | ( i == 1 ) );
      tsum += tmp * (D)( cnt[ i ] + 1 ) / (D)tcnt;
      cnt[ i ] ++;
    }
  return tsum;
}
D cal1( int sc ){
  if( ( trans( c[ 0 ][ 0 ] ) == 1 ||
        trans( c[ 1 ][ 0 ] ) == 1 ) &&
      sc + 10 <= 21 ) sc += 10;
  return DFS2( sc , trans( c[ 2 ][ 0 ] ) , c[ 2 ][ 0 ] == 'A' );
}
D DFS( int sc , bool flag , bool A ){
  if( sc > 21 ) return -1.0;
  D stand = -1e30 , go = 0.0;
  if( !flag ){
    int tsc = sc;
    if( A && tsc + 10 <= 21 ) tsc += 10;
    stand = DFS2( tsc , trans( c[ 2 ][ 0 ] ) , c[ 2 ][ 0 ] == 'A' );
  }
  int tcnt = 0;
  for( int i = 1 ; i <= 10 ; i ++ ) tcnt += cnt[ i ];
  for( int i = 1 ; i <= 10 ; i ++ ) if( cnt[ i ] ){
    cnt[ i ] --;
    D tans = DFS( sc + i , false , A | ( i == 1 ) ) * (D)( cnt[ i ] + 1 ) / (D)tcnt;
    go += tans;
    cnt[ i ] ++;
  }
  return max( stand , go );
}
D cal2( int sc ){
  return DFS( sc , true , c[ 0 ][ 0 ] == 'A' || c[ 1 ][ 0 ] == 'A' );
}
void solve(){
  int sc = trans( c[ 0 ][ 0 ] ) + trans( c[ 1 ][ 0 ] );
  D ans1 = cal1( sc );
  // printf( "%.12f\n" , ans1 );
  D ans2 = cal2( sc );
  // printf( "%.12f\n" , ans2 );
  if( ans1 > ans2 ) puts( "STAND" );
  else puts( "HIT" );
}
int main(){
  freopen( "blackjack.in" , "r" , stdin );
  freopen( "blackjack.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
