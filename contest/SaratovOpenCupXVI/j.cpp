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
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = ( _tmp * _tmp ) % _mod;
  if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
  return _tmp;
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
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 404040
void build(){

}
int n , m , mx;
int a[ N ] , b[ N ];
bool cmp( int i , int j ){
  return i > j;
}
void init(){
  n = getint();
  m = getint();
  for( int i = 0 ; i < n ; i ++ )
    a[ i ] = getint();
  sort( a , a + n , cmp );
  for( int i = 0 ; i < m ; i ++ )
    b[ i ] = getint();
  sort( b , b + m );
}
ll hole[ N ];
bool okay( int xx ){
  int nn = 0 , dep = 0;
  for( int i = 0 ; i <= n + m ; i ++ ) hole[ i ] = 0;
  hole[ 0 ] = 1;
  // puts( "=========" );
  for( int i = m - xx ; i < m ; i ++ ){
    while( dep < b[ i ] && nn < n ){
      while( hole[ dep ] && nn < n ){
        hole[ dep ] --;
        hole[ dep + 1 ] += a[ nn ++ ];
        // printf( "add %d : %d(%d)\n" , nn - 1 , dep + 1 , hole[ dep + 1 ] );
      }
      if( hole[ dep ] ) break;
      dep ++;
    }
    while( dep < b[ i ] && hole[ dep ] == 0 ) dep ++;
    // printf( "%d : %d %d %d %d\n" , xx , i , dep , hole[ dep ] , b[ i ] );
    if( hole[ dep ] == 0 ) return false;
    hole[ dep ] --;
  }
  return true;
}
void solve(){
  int l = 1 , r = m , mid , ans = 0;
  while( l <= r ){
    mid = ( l + r ) >> 1;
    if( okay( mid ) ) ans = mid , l = mid + 1;
    else r = mid - 1;
  }
  cout << ans << endl;
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
