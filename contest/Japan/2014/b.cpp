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
#define N 200
void build(){

}
char c[ N ];
int n , x;
void init(){
  scanf( "%s" , c + 1 );
  x = getint();
  n = strlen( c + 1 );
}
int cal(){
  int ans = 0 , pre = 1;
  bool haspre = false;
  if( n == 1 ) return c[ 1 ] - '0';
  for( int i = 1 ; i <= n ; i += 2 )
    if( i != n && c[ i + 1 ] == '*' ){
      if( haspre ) pre *= ( c[ i ] - '0' );
      else haspre = true, pre = ( c[ i ] - '0' );
    }else if( i == n ){
      if( c[ i - 1 ] == '*' ) ans += pre * ( c[ i ] - '0' );
      else ans += c[ i ] - '0';
    }else if( c[ i - 1 ] == '*' ) ans += pre * ( c[ i ] - '0' ), haspre = false;
    else ans += c[ i ] - '0', haspre = false;
  return ans;
}
int cal2(){
  int ans = c[ 1 ] - '0';
  for( int i = 3 ; i <= n ; i += 2 )
    if( c[ i - 1 ] == '+' ) ans += c[ i ] - '0';
    else ans *= c[ i ] - '0';
  return ans;
}
void solve(){
  int ans1 = cal();
  int ans2 = cal2();
  if( ans1 == x && ans2 == x ) puts( "U" );
  else if( ans1 == x ) puts( "M" );
  else if( ans2 == x ) puts( "L" );
  else puts( "I" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
