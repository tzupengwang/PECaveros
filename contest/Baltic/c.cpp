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
#define N 100010
int n , k , ln;
int p[ N ] , a[ N ];
vector<int> v[ N ];
void build(){

}
void init(){
  n = getint();
  k = getint();
  for( int i = 2 ; i <= n ; i ++ ){
    p[ i ] = getint();
    v[ p[ i ] ].push_back( i );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    a[ i ] = getint();
    if( a[ i ] ) ln ++;
  }
}
int dp[ N ];
void DP_min( int now , int vl ){
  dp[ now ] = -1;
  if( a[ now ] ){
    if( a[ now ] <= vl ) dp[ now ] = 0;
    return;
  }
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    DP_min( v[ now ][ i ] , vl );
// put max
  int high = 0, sum = 0;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( dp[ v[ now ][ i ] ] == -1 ){
      high = 1; break;
    }else sum += dp[ v[ now ][ i ] ];
  if( high == 0 ) dp[ now ] = sum;
// put min
  int low = 0, mn = 1000000000;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( dp[ v[ now ][ i ] ] != -1 ){
      low = 1;
      mn = min( mn , dp[ v[ now ][ i ] ] );
    }
  if( low != 0 ){
    if( dp[ now ] == -1 || mn + 1 < dp[ now ] )
      dp[ now ] = mn + 1;
  }
}
void DP_max( int now , int vl ){
  dp[ now ] = -1;
  if( a[ now ] ){
    if( a[ now ] >= vl ) dp[ now ] = 0;
    return;
  }
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    DP_max( v[ now ][ i ] , vl );
// put min
  int low = 0, sum = 0;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( dp[ v[ now ][ i ] ] == -1 ){
      low = 1; break;
    }else sum += dp[ v[ now ][ i ] ];
  if( low == 0 ) dp[ now ] = sum;
// put max
  int high = 0, mn = 1000000000;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( dp[ v[ now ][ i ] ] != -1 ){
      high = 1;
      mn = min( mn , dp[ v[ now ][ i ] ] );
    }
  if( high != 0 ){
    if( dp[ now ] == -1 || mn + 1 < dp[ now ] )
      dp[ now ] = mn + 1;
  }
}
bool okay_min( int vl ){
  DP_min( 1 , vl );
  return dp[ 1 ] != -1 && dp[ 1 ] <= k;
}
bool okay_max( int vl ){
  DP_max( 1 , vl );
  return dp[ 1 ] != -1 && dp[ 1 ] <= n - ln - k;
}
void find_min(){
  int l = 1 , r = 1000000000 , mid , ans = 1;
  while( l <= r ){
    mid = ( l + r ) >> 1;
    if( okay_min( mid ) ) r = mid - 1 , ans = mid;
    else l = mid + 1;
  }
  printf( "%d " , ans );
}
void find_max(){
  int l = 1 , r = 1000000000 , mid , ans = 1;
  while( l <= r ){
    mid = ( l + r ) >> 1;
    if( okay_max( mid ) ) l = mid + 1 , ans = mid;
    else r = mid - 1;
  }
  printf( "%d\n" , ans );
}
void solve(){
  find_min();
  find_max();
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
