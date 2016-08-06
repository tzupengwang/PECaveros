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
#define N 1021
#define M 1021
int n , m , t , p[ M ];
int find_p( int x ){
  return x == p[ x ] ? x : p[ x ] = find_p( p[ x ] );
}
void uni( int x , int y ){
  p[ find_p( x ) ] = find_p( y );
}
struct Arc{
  int des , nxt;
}e[ M ];
int from[ N ];
bitset<M> v[ M ];
bool ter[ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  t = getint();
  for( int i = 0 ; i < t ; i ++ )
    ter[ getint() ] = true;
  for( int i = 1 ; i <= m ; i ++ ){
    int ui = getint();
    int vi = getint();
    e[ i ].des = ui;
    e[ i ].nxt = from[ vi ];
    from[ vi ] = i;
  }
}
int mx;
int ans[ M ] , sv[ M ];
inline void build_ans(){
  for( int i = 1 ; i <= mx ; i ++ ) p[ i ] = i;
  for( int i = 1 ; i <= m ; i ++ ){
    int pre = 0;
    for( int j = 1 ; j <= mx ; j ++ )
      if( v[ i ][ j ] ){
        if( pre ) uni( pre , j );
        pre = j;
      }
    sv[ i ] = pre;
  }
  int cnt = 0;
  for( int i = 1 ; i <= mx ; i ++ )
    if( i == find_p( i ) ){
      cnt ++;
      for( int j = 1 ; j <= mx ; j ++ )
        if( i == find_p( j ) )
          ans[ mx - j ] = cnt;
    }
  printf( "%d %d\n" , mx , cnt );
  for( int i = 0 ; i < mx ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == mx ] );
  for( int i = 1 ; i <= m ; i ++ )
    printf( "%d%c" , ans[ mx - sv[ i ] ] , " \n"[ i == m ] );
}
queue< PII > Q;
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    if( ter[ i ] ){
      for( int j = from[ i ] ; j ; j = e[ j ].nxt ){
        if( !v[ j ][ 1 ] ){
          v[ j ][ 1 ] = true;
          Q.push( { j , 1 } );
        }
      }
    }
  while( Q.size() ){
    PII tp = Q.front(); Q.pop();
    int xn = tp.FI;
    int xm = tp.SE;
    mx = max( mx , xm );
    int des = e[ xn ].des;
    for( int i = from[ des ] ; i ; i = e[ i ].nxt )
      if( !v[ i ][ xm + 1 ] ){
        v[ i ][ xm + 1 ] = true;
        Q.push( { i , xm + 1 } );
      }
  }
  build_ans();
}
int main(){
  freopen( "suffix.in" , "r" , stdin );
  freopen( "suffix.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
