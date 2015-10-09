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
#define N 200010
int n , f[ N ];
int ans[ N ] , s = -1;
vector<int> fac[ N ];
void build(){
  for( int i = 1 ; i < N ; i ++ )
    for( int j = i ; j < N ; j += i )
      fac[ j ].PB( i );
}
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ )
    f[ i ] = getint();
}
vector< tuple<int,int,int> > v;
int bst[ N ] , cyc , ti;
bool vst[ N ];
void DFS( int now ){
  int snow = now;
  cyc = 0; ti = n + n;
  while( !vst[ now ] ){
    cyc ++; ti = min( ti , now );
    vst[ now ] = true;
    now = f[ now ];
  }
  v.PB( MT( ti , cyc , snow ) );
}
void go( int idx ){
  cyc = get<1>( v[ idx ] );
  ti = get<0>( v[ idx ] );
  int now = get<2>( v[ idx ] );
  bst[ cyc ] = min( bst[ cyc ] , ti );
  int tbst = ti;
  for( int i = 0 ; i < (int)fac[ cyc ].size() ; i ++ )
    tbst = min( tbst , bst[ fac[ cyc ][ i ] ] );
  while( ans[ now ] == 0 ){
    ans[ now ] = tbst;
    now = f[ now ];
    tbst = f[ tbst ];
  }
}
void solve(){
  for( int i = 0 ; i <= n ; i ++ ) bst[ i ] = n + n;
  for( int i = 1 ; i <= n ; i ++ )
    if( !vst[ i ] )
      DFS( i );
  sort( ALL( v ) );
  for( int i = 0 ; i < (int)v.size() ; i ++ )
    go( i );
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , ans[ i ] , i == n ? '\n' : ' ' );
}
int main(){
  freopen( "commuting.in" , "r" , stdin );
  freopen( "commuting.out" , "w" , stdout );
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
