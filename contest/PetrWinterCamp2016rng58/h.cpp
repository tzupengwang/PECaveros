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
// #define M 300
// int cnt[ M + M ][ M + M ];
// ll ans , sum;
// int dx[]={0,0,1,-1};
// int dy[]={1,-1,0,0};
// void DFS( int step , int nx , int ny ){
  // bool flag = false;
  // if( cnt[ nx ][ ny ] == 0 ) flag = true;
  // cnt[ nx ][ ny ] ++;
  // if( flag ) sum ++;
  // if( step == 0 ){
    // ans += sum;
  // }else{
    // for( int i = 0 ; i < 4 ; i ++ )
      // DFS( step - 1 , nx + dx[ i ] , ny + dy[ i ] );
  // }
  // cnt[ nx ][ ny ] --;
  // if( flag ) sum --;
// }
#define N 5050
ll n , m , f[ N ] , g[ N ] , c[ N ][ N ];
void build(){

}
void init(){
  n = getint(); m = getint();
}
void pre_solve(){
  for( int i = 0 ; i < N ; i ++ )
    c[ i ][ 0 ] = c[ i ][ i ] = 1;
  for( int i = 2 ; i < N ; i ++ )
    for( int j = 1 ; j < i ; j ++ )
      c[ i ][ j ] = add( c[ i - 1 ][ j ] , c[ i - 1 ][ j - 1 ] , m );
  for( int i = 2 ; i < N ; i += 2 )
    for( int j = 0 ; j <= i ; j += 2 )
      g[ i ] = add( g[ i ] , mul( c[ i ][ j ] , mul( c[ j ][ j / 2 ] , c[ i - j ][ ( i - j ) / 2 ] , m ) , m ) , m );
  for( int i = 2 ; i < N ; i += 2 ){
    f[ i ] = g[ i ];
    for( int j = 2 ; j < i ; j += 2 )
      f[ i ] = sub( f[ i ] , mul( f[ j ] , g[ i - j ] , m ) , m );
  }
}
ll x[ N ] , dp[ N ];
void solve(){
  pre_solve();
  x[ 2 ] = 12; 
  for( int i = 3 ; i <= n ; i ++ ){
    x[ i ] = mul( x[ i - 1 ] , 4 , m );
    if( i % 2 == 0 ) x[ i ] = sub( x[ i ] , f[ i ] , m );
  }
  dp[ 1 ] = 8; dp[ 2 ] = 44;
  for( int i = 3 ; i <= n ; i ++ )
    dp[ i ] = add( mul( dp[ i - 1 ] , 4 , m ) , x[ i ] , m );
  cout << dp[ n ] << endl;
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
