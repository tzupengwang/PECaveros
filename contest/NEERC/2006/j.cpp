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
#define N 310
map<ll,ll> my;
ll n , m , x[ N ] , y[ N ] , k[ N ];
bool done[ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  for( int i = 0 ; i < n ; i ++ ){
    x[ i ] = getint();
    y[ i ] = getint();
    k[ i ] = 0;
    if( x[ i ] > 0 && y[ i ] <= 0 ){
      y[ i ] %= x[ i ];
      y[ i ] += x[ i ];
    }
    if( x[ i ] < 0 && y[ i ] > m ){
      x[ i ] = -x[ i ];
      y[ i ] %= x[ i ];
      if( y[ i ] == 0 ) y[ i ] += x[ i ];
    }
  }
}
bool vst[ N ];
bool match( int now ){
  vst[ now ] = true;
  ll tk = 0;
  while( x[ now ] * tk + y[ now ] <= m &&
         x[ now ] * tk + y[ now ] > 0 ){
    ll tmp = x[ now ] * tk + y[ now ];
    if( my.count( tmp ) == 0 ||
        ( !vst[ my[ tmp ] ] && match( my[ tmp ] ) ) ){
      k[ now ] = tk;
      my[ tmp ] = now;
      return true;
    }
    if( x[ now ] == 0 ) break;
    tk ++;
  }
  return false;
}
void solve(){
  for( int i = 0 ; i < n ; i ++ ){
    for( int j = 0 ; j < n ; j ++ ) vst[ j ] = false;
    done[ i ] = match( i );
  }
  int pre = 1;
  for( int i = 0 ; i < n ; i ++ ){
    ll ans;
    if( done[ i ] ) ans = x[ i ] * k[ i ] + y[ i ];
    else{
      while( my.count( pre ) ) pre ++;
      ans = pre;
      pre ++;
    }
    cout << ans << " \n"[ i == n - 1 ];
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
