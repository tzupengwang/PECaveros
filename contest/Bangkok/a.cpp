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
#define N 30010
#define X 32
int bt[ 40000000 ];
inline void md( int x ){
  bt[ x >> 5 ] |= ( 1 << ( x & 31 ) );
}
inline bool tk( int x ){
  return ( bt[ x >> 5 ] >> ( x & 31 ) ) & 1;
}
int ans[ N ];
void build(){
  int nans = 1;
  ans[ 0 ] = 1;
  for( int i = 1 ; i <= 30000 ; i ++ ){
    int st = (i&1) ? 1 : (i / 4 + 1);
    for( int j = st, tmp = i * st ; j <= i ; j ++, tmp += i ){
      if( !tk( tmp ) ){
        md( tmp );
        nans ++;
      }
    }
    ans[ i ] = nans;
  }
}
int n;
void init(){
  n = getint();
}
void solve(){
  printf( "%d\n" , ans[ n ] );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
