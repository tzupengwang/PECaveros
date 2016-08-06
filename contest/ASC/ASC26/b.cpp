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
#define N 55
#define K 10101
D lg[ 101 ];
void build(){
  for( int i = 1 ; i < 101 ; i ++ )
    lg[ i ] = log( (D)i / 100.0 );
}
int n;
D x;
int a[ N ] , b[ N ];
void init(){
  n = getint();
  x = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    a[ i ] = getint();
    b[ i ] = getint();
  }
}
D dp[ 2 ][ N * K ];
int bk[ N ][ N * K ];
bool got[ N ][ N * K ];
queue< PII > Q;
inline void find_ans( int lst ){
  vector< int > rev , frt;
  for( int i = n ; i >= 1 ; i -- ){
    if( lst == bk[ i ][ lst ] )
      rev.push_back( i );
    else
      frt.push_back( i );
    lst = bk[ i ][ lst ];
  }
  reverse( ALL( rev ) );
  reverse( ALL( frt ) );
  for( int i : rev ) printf( "%d reverse\n" , i );
  for( int i : frt ) printf( "%d front\n" , i );
}
void solve(){
  Q.push( { 0 , 0 } );
  dp[ 0 ][ 0 ] = 0;
  while( Q.size() ){
    PII tp = Q.front(); Q.pop();
    int xn = tp.FI;
    int xc = tp.SE;
    int now = xn & 1;
    int nxt = 1 - now;
    if( xn == n ) continue;
    { // * ( 100 - b[ xn + 1 ] )
      int nxtn = xn + 1;
      int nxtc = xc;
      D  nxtv = dp[ now ][ xc ] + lg[ 100 - b[ xn + 1 ] ];
      if( !got[ nxtn ][ nxtc ] || nxtv < dp[ nxt ][ nxtc ] ){
        dp[ nxt ][ nxtc ] = nxtv;
        bk[ nxtn ][ nxtc ] = xc;
        if( !got[ nxtn ][ nxtc ] ){
          got[ nxtn ][ nxtc ] = true;
          Q.push( { nxtn , nxtc } );
        }
      }
    }
    { // - a[ xn + 1 ]
      int nxtn = xn + 1;
      int nxtc = xc + a[ xn + 1 ];
      D  nxtv = dp[ now ][ xc ];
      if( !got[ nxtn ][ nxtc ] || nxtv < dp[ nxt ][ nxtc ] ){
        dp[ nxt ][ nxtc ] = nxtv;
        bk[ nxtn ][ nxtc ] = xc;
        if( !got[ nxtn ][ nxtc ] ){
          got[ nxtn ][ nxtc ] = true;
          Q.push( { nxtn , nxtc } );
        }
      }
    }
  }
  D bstans = x + x;
  int ac = 0;
  for( int i = 0 ; i < n * 10000 ; i ++ )
    if( got[ n ][ i ] ){
      D tans = x * exp( dp[ n & 1 ][ i ] ) - i;
      if( tans < bstans ){
        bstans = tans;
        ac = i;
      }
    }
  find_ans( ac );
}
int main(){
  freopen( "discount.in" , "r" , stdin );
  freopen( "discount.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
