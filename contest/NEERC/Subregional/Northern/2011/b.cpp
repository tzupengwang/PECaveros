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
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
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
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = mul( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = mul( _tmp , _a , _mod );
  return _tmp;
}
ll mymul( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 0ll;
  ll _tmp = mymul( _a , _x / 2 , _mod );
  _tmp = add( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = add( _tmp , _a , _mod );
  return _tmp;
}
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 5050
int m , n , S , k;
char c[ N ];
void build(){

}
void init(){
  m = getint();
  n = getint();
  S = getint();
  k = getint();
  scanf( "%s" , c );
}
void solve(){
  int len = strlen( c );
  int cnt = 0 , s = -1 , xen = 0;
  for( int i = 0 ; i <= len ; i ++ )
    if( i == len || c[ i ] == '.' ){
      if( s != -1 ){
        cnt ++;
        xen = i - s;
        s = -1;
      }
    }else if( s == -1 ) s = i;
  // printf( "%d %d %d\n" , cnt , xen , s );
  if( cnt == 0 ){
    bool ucan = false , dcan = false;
    if( k - 1 >= S ) ucan = true;
    if( m - k >= S ) dcan = true;
    if( !ucan && !dcan ) puts( "Impossible" );
    else if( ucan && dcan ) puts( "Ambiguous" );
    else if( ucan ){
      if( k - 1 == S && n == S ) puts( "Unique" );
      else puts( "Ambiguous" );
    }else{
      if( m - k == S && n == S ) puts( "Unique" );
      else puts( "Ambiguous" );
    }
  }else if( cnt != 1 || xen != S ) puts( "Impossible" );
  else if( m != S && S > 1 && k != 1 && k != m ) puts( "Ambiguous" );
  else puts( "Unique" );
}
int main(){
  freopen( "black.in" , "r" , stdin );
  freopen( "black.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
