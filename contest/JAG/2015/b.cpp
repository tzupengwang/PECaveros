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
#define N 11
char c[ N ];
int len;
void build(){

}
ll bs , ov;
void init(){
  scanf( "%s" , c );
  len = strlen( c );
  bs = 1; ov = 0;
  for( int i = 0 ; i < len ; i ++ ){
    bs *= 10ll;
    ov = ov * 10ll + ( c[ i ] - '0' );
  }
}
ll bans;
vector<int> ans;
void cal( vector<int>& tv ){
  ll vl = 0;
  for( int i = 0 ; i < len ; i ++ )
    vl = vl * 10 + tv[ i ];
  ll dif = min( abs( vl - ov ) , bs - abs( vl - ov ) );
  if( vl == ov ) return;
  if( dif > bans ){
    ans = tv;
    bans = dif;
  }
}
void solve(){
  vector<int> v;
  for( int i = 0 ; i < 10 ; i ++ ) v.PB( i );
  do cal( v );
  while( next_permutation( ALL( v ) ) );
  for( int i = 0 ; i < len ; i ++ )
    printf( "%d" , ans[ i ] );
  puts( "" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
