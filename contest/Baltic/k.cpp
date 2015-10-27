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
#define N 20
ll lvl[ N ];
set<ll> S;
queue<ll> Q;
void build(){
  lvl[ 0 ] = 1;
  for( ll i = 1 ; i < N ; i ++ )
    lvl[ i ] = lvl[ i - 1 ] * i;
  S.insert( 1 );
  Q.push( 1 );
  while( Q.size() ){
    ll tmp = Q.front(); Q.pop();
    ll mx = 1000000000000000000ll / tmp;
    for( int i = 2 ; i < N ; i ++ ){
      if( lvl[ i ] > mx ) break;
      ll nxt = tmp * lvl[ i ];
      if( S.count( nxt ) == 0 ){
        S.insert( nxt );
        Q.push( nxt );
      }
    }
  }
}
ll n;
void init(){
  n = getint();
}
void solve(){
  puts( S.count( n ) == 0 ? "NO" : "YES" );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
