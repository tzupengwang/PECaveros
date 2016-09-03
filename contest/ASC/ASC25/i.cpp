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
#define N 101010
map< int , int > x , y , xay , xmy;
set< int > vx[ N ] , vy[ N ] , vxay[ N ] , vxmy[ N ];
int xidx , yidx , xayidx , xmyidx;
void build(){

}
void Add( int nx , int ny ){
  if( !x.count( nx ) ) x[ nx ] = xidx ++;
  if( !y.count( ny ) ) y[ ny ] = yidx ++;
  if( !xay.count( nx + ny ) ) xay[ nx + ny ] = xayidx ++;
  if( !xmy.count( nx - ny ) ) xmy[ nx - ny ] = xmyidx ++;
  vx[ x[ nx ] ].insert( ny );
  vy[ y[ ny ] ].insert( nx );
  vxay[ xay[ nx + ny ] ].insert( nx - ny );
  vxmy[ xmy[ nx - ny ] ].insert( nx + ny );
}
void Sub( int nx , int ny ){
  vx[ x[ nx ] ].erase( ny );
  vy[ y[ ny ] ].erase( nx );
  vxay[ xay[ nx + ny ] ].erase( nx - ny );
  vxmy[ xmy[ nx - ny ] ].erase( nx + ny );
}
int n , ix[ N ] , iy[ N ];
void init(){
  n = getint();
  Add( 0 , 0 );
  for( int i = 0 ; i < n ; i ++ ){
    ix[ i ] = getint();
    iy[ i ] = getint();
    Add( ix[ i ] , iy[ i ] );
  }
}
bool okay( int sx , int sy , int nx , int ny ){
  if( sx == nx ){
    if( sy > ny ) swap( sy , ny );
    auto it1 = vx[ x[ sx ] ].lower_bound( ny );
    auto it2 = vx[ x[ sx ] ].lower_bound( sy );
    return it1 == ++it2;
  }
  if( sy == ny ){
    if( sx > nx ) swap( sx , nx );
    auto it1 = vy[ y[ sy ] ].lower_bound( nx );
    auto it2 = vy[ y[ sy ] ].lower_bound( sx );
    return it1 == ++it2; 
  }
  if( sx + sy == nx + ny ){
    int sub1 = sx - sy;
    int sub2 = nx - ny;
    if( sub1 > sub2 ) swap( sub1 , sub2 );
    auto it1 = vxay[ xay[ sx + sy ] ].lower_bound( sub2 );
    auto it2 = vxay[ xay[ sx + sy ] ].lower_bound( sub1 );
    return it1 == ++it2;
  }
  if( sx - sy == nx - ny ){
    int add1 = sx + sy;
    int add2 = nx + ny;
    if( add1 > add2 ) swap( add1 , add2 );
    auto it1 = vxmy[ xmy[ sx - sy ] ].lower_bound( add2 );
    auto it2 = vxmy[ xmy[ sx - sy ] ].lower_bound( add1 );
    return it1 == ++it2;
  }
  return false;
}
void solve(){
  int ans = 0 , fx = 0 , fy = 0;
  for( int i = 0 ; i < n ; i ++ ){
    if( !okay( fx , fy , ix[ i ] , iy[ i ] ) ) break;
    ans ++;
    Sub( fx , fy );
    fx = ix[ i ]; fy = iy[ i ];
  }
  printf( "%d\n" , ans );
}
int main(){
  freopen( "queen2.in" , "r" , stdin );
  freopen( "queen2.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
