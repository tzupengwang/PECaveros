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
#define N 50010
int n , a[ N ];
int deq[ N * 20 ] , s = N * 5 , t = N * 5;
int sz(){ return t - s; }
void p_f( int vl ){ deq[ -- s ] = vl; }
void p_b( int vl ){ deq[ t ++ ] = vl; }
int pop(){ return deq[ s ++ ]; }
int dp[ N ];
void build(){
  
}
void BFS(){
  dp[ 0 ] = 0;
  for( int i = 1 ; i <= a[ n - 1 ] ; i ++ )
    dp[ i ] = -1;
  p_b( 0 );
  while( sz() != 0 ){
    int now = pop();
    for( int j = 0 ; j < n - 1 ; j ++ ){
      int nxt = now + a[ j ];
      if( nxt >= a[ n - 1 ] && dp[ nxt - a[ n - 1 ] ] == -1 ){
        dp[ nxt - a[ n - 1 ] ] = dp[ now ] + 1;
        p_b( nxt - a[ n - 1 ] );
      }else if( nxt < a[ n - 1 ] && ( dp[ nxt ] == -1 ||
                                      dp[ now ] < dp[ nxt ] ) ){
        dp[ nxt ] = dp[ now ];
        p_f( nxt );
      }
    }
  }
}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ )
    a[ i ] = getint();
  BFS();
}
void solve(){
  int _ = getint(); while( _ -- ){
    int q = getint();
    if( dp[ q % a[ n - 1 ] ] == -1 ||
        dp[ q % a[ n - 1 ] ] > q / a[ n - 1 ] ) puts( "NIE" );
    else puts( "TAK" );
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
