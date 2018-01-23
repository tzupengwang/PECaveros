// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,ll> PII;
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
ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 50010
int n , a[ N ];
ll t , d[ N ];
void build(){

}
void init(){
  n = getint();
  t = getint();
  for( int i = 1 ; i < n ; i ++ )
    a[ i ] = getint();
  for( int i = 2 ; i < n ; i ++ )
    d[ i ] = getint();
}
deque<PII> dq;
ll dp[ N ];
bool cal( int now ){
  dq.clear();
  dq.PB( MP( 1 , -1 ) );
  for( int i = 2 ; i <= n ; i ++ ){
    while( i - now > dq[ 0 ].first ) dq.pop_front();
    dp[ i ] = dq[ 0 ].second + d[ i ] + i;
    while( dq.size() && dp[ i ] - i < dq.back().SE ) dq.pop_back();
    dq.push_back( MP( i , dp[ i ] - i ) );
  }
  return dp[ n ] <= t;
}
void solve(){
  int mn = a[ n - 1 ];
  for( int i = n - 1 ; i >= 1 ; i -- ){
    a[ i ] = min( mn , a[ i ] );
    mn = min( mn , a[ i ] );
  }
  int l = 1 , r = n - 1 , mid , ans = 1;
  while( l <= r ){
    mid = ( l + r ) >> 1;
    if( cal( mid ) ) r = mid - 1, ans = mid;
    else l = mid + 1;
  }
  printf( "%d\n" , a[ ans ] );
}
int main(){
  freopen( "journey.in" , "r" , stdin );
  freopen( "journey.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
