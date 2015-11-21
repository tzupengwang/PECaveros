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
#define N 202020
int n;
vector<int> v[ N ];
void build(){

}
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ )
    v[ i ].clear();
  for( int i = 1 ; i < n ; i ++ ){
    int ui = getint();
    int vi = getint();
    v[ ui ].PB( vi );
    v[ vi ].PB( ui );
  }
}
int got[ N ] , gott;
int dp[ N ] , bdr;
void DP( int now , int prt ){
  int low = 0, high = 0;
  int cl = 0, ch = 0;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( v[ now ][ i ] != prt ){
      DP( v[ now ][ i ] , now );
      if( dp[ v[ now ][ i ] ] < 0 )
        cl ++, low = min( low , dp[ v[ now ][ i ] ] );
      else if( dp[ v[ now ][ i ] ] > 0 )
        ch ++, high = max( high , dp[ v[ now ][ i ] ] );
    }
  if( cl == 0 && ch == 0 ){
    dp[ now ] = 1;
    if( now == 1 ){
      got[ gott ++ ] = now;
      dp[ now ] = -bdr;
    }
  }else{
    if( cl == 0 ){
      dp[ now ] = high + 1;
      if( now == 1 || dp[ now ] - 1 == bdr ){
        got[ gott ++ ] = now;
        dp[ now ] = -bdr;
      }
    }else if( ch == 0 )
      dp[ now ] = low + 1;
    else{
      if( low + 1 + high <= 0 )
        dp[ now ] = low + 1;
      else{
        dp[ now ] = high + 1;
        if( now == 1 || dp[ now ] - 1 == bdr ){
          got[ gott ++ ] = now;
          dp[ now ] = -bdr;
        }
      }
    }
  }
}
bool good( int now ){
  gott = 0; bdr = now;
  DP( 1 , 1 );
  while( gott < 2 ){
    got[ gott ] = got[ gott - 1 ] + 1;
    if( got[ gott ] > n ) got[ gott ] -= n;
    gott ++;
  }
  return gott <= 2;
}
void solve(){
  if( n == 2 ){
    puts( "0 1 2" );
    return;
  }
  int l = 1, r = n, mid , ans = n, ans1 = 1 , ans2 = 2;
  while( l <= r ){
    mid = ( l + r ) >> 1;
    if( good( mid ) ) r = mid - 1, ans = mid, ans1 = got[ 0 ], ans2 = got[ 1 ];
    else l = mid + 1;
  }
  printf( "%d %d %d\n" , ans , ans1 , ans2 );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
