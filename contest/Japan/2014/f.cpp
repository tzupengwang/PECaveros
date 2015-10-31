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
#define N 510
int p[ N ];
int find_p( int x ){
  return x == p[ x ] ? x : p[ x ] = find_p( p[ x ] );
}
void Union( int x , int y ){
  x = find_p( x );
  y = find_p( y );
  p[ x ] = y;
}
typedef tuple<int,int,int> tiii;
vector< tiii > v;
int n , m;
void build(){

}
void init(){
  n = getint();
  m = getint();
  for( int i = 1 ; i <= n ; i ++ ) p[ i ] = i;
  for( int i = 0 ; i < m ; i ++ ){
    int tu = getint();
    int tv = getint();
    int tc = getint();
    v.PB( MT( tc , tu , tv ) );
  }
  sort( ALL( v ) );
}
int ans1 = 0, ans2 = 0, cnt;
vector<int> e[ N ];
bool usd[ N ];
int low[ N ], dst[ N ], tidx;
void Tarjan( int now , int np ){
  usd[ now ] = true;
  low[ now ] = dst[ now ] = ++ tidx;
  int cntp = 0;
  for( int i = 0 ; i < (int)e[ now ].size() ; i ++ )
    if( e[ now ][ i ] == np ) cntp ++;
    else if( usd[ e[ now ][ i ] ] )
      low[ now ] = min( dst[ e[ now ][ i ] ] , low[ now ] );
    else{
      Tarjan( e[ now ][ i ] , now );
      low[ now ] = min( low[ now ] , low[ e[ now ][ i ] ] );
    }
  if( cntp > 1 ) 
    low[ now ] = min( low[ now ] , dst[ np ] );
  if( now != np && low[ now ] >= dst[ now ] )
    cnt ++;
}
void test( int l , int r ){
  for( int i = 1 ; i <= n ; i ++ ){
    e[ i ].clear();
    usd[ i ] = false;
  }
  cnt = 0;
  for( int i = l ; i < r ; i ++ ){
    int tu = find_p( get<1>( v[ i ] ) );
    int tv = find_p( get<2>( v[ i ] ) );
    if( tu == tv ) continue;
    e[ tu ].PB( tv );
    e[ tv ].PB( tu );
  }
  for( int i = 1 ; i <= n ; i ++ )
    if( i == find_p( i ) && !usd[ i ] ){
      tidx = 0;
      Tarjan( i , i );
    }
  ans1 += cnt;
  ans2 += cnt * get<0>( v[ l ] );
}
void solve(){
  for( int i = 0 ; i < m ; ){
    int nv = get<0>( v[ i ] );
    int r = i;
    while( r < m && get<0>( v[ r ] ) == nv ) r ++;
    test( i , r );
    for( int j = i ; j < r ; j ++ )
      Union( get<1>( v[ j ] ) , get<2>( v[ j ] ) );
    i = r;
  }
  printf( "%d %d\n" , ans1 , ans2 );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
