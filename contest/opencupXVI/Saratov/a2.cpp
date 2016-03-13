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
#define N 514
void build(){

}
int n , t[ N ];
vector<int> v[ 3 ];
int sum[ 3 ] , nsum[ 3 ];
void init(){
  srand( 514514 );
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    t[ i ] = getint();
    int ii = rand() % 3;
    v[ ii ].PB( i );
    sum[ ii ] += t[ i ];
  }
}
#define K 100000000
void solve(){
  for( int i = 0 ; i < K ; i ++ ){
    int mx = 0 , mn = 0;
    for( int j = 1 ; j < 3 ; j ++ ){
      if( sum[ j ] > sum[ mx ] ) mx = j;
      if( sum[ j ] < sum[ mn ] ) mn = j;
    }
    if( mx == mn ) break;
    int xx = rand() % (int)v[ mx ].size();
    nsum[ mx ] = sum[ mx ] - t[ v[ mx ][ xx ] ];
    nsum[ mn ] = sum[ mn ] + t[ v[ mx ][ xx ] ];
    int nmx = 0 , nmn = 0;
    for( int j = 1 ; j < 3 ; j ++ ){
      if( nsum[ j ] > nsum[ nmx ] ) nmx = j;
      if( nsum[ j ] < nsum[ nmn ] ) nmn = j;
    }
    if( nsum[ nmx ] - nsum[ nmn ] >=
        sum[ mx ] - sum[ mn ] ) continue;
    swap( v[ mx ][ xx ] , v[ mx ].back() );
    v[ mn ].push_back( v[ mx ].back() );
    sum[ mx ] -= t[ v[ mx ].back() ];
    sum[ mn ] += t[ v[ mx ].back() ];
    v[ mx ].pop_back();
  }
  int mx = 0 , mn = 0;
  for( int j = 1 ; j < 3 ; j ++ ){
    if( sum[ j ] > sum[ mx ] ) mx = j;
    if( sum[ j ] < sum[ mn ] ) mn = j;
  }
  printf( "%d\n" , sum[ mx ] - sum[ mn ] );
  for( int i = 0 ; i < 3 ; i ++ ){
    printf( "%d " , (int)v[ i ].size() );
    for( size_t j = 0 ; j < v[ i ].size() ; j ++ )
      printf( "%d%c" , v[ i ][ j ] + 1 , " \n"[ j + 1 == v[ i ].size() ] );
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
