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
#define N 110
int a[ N ][ N ];
int dp1[ N ][ N ][ N ];
int dp2[ N ][ N ][ N ];
int ans1[ N ], ans2[ N ];
int n , m , k;
void build(){

}
void init(){
  n = getint(); m = getint();
  k = min( n , m );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      a[ i ][ j ] = getint();
  for( int i = 0 ; i <= k ; i ++ ){
    ans1[ i ] = -INF;
    ans2[ i ] = +INF;
  }
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; j <= m ; j ++ )
      for( int u = 0 ; u <= k + 1 ; u ++ )
        dp1[ i ][ j ][ u ] = -INF,
        dp2[ i ][ j ][ u ] = +INF; 
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; j <= m ; j ++ )
      dp1[ i ][ j ][ 0 ] =
      dp2[ i ][ j ][ 0 ] = 0;
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      for( int u = 1 ; u <= k ; u ++ ){
        int tmp;
        tmp = dp1[ i - 1 ][ j - 1 ][ u - 1 ];
        if( tmp + a[ i ][ j ] > dp1[ i ][ j ][ u ] )
          dp1[ i ][ j ][ u ] = tmp + a[ i ][ j ];
        tmp = dp2[ i - 1 ][ j - 1 ][ u - 1 ];
        if( tmp + a[ i ][ j ] < dp2[ i ][ j ][ u ] )
          dp2[ i ][ j ][ u ] = tmp + a[ i ][ j ];
        ans1[ u ] = max( ans1[ u ] , dp1[ i ][ j ][ u ] );
        ans2[ u ] = min( ans2[ u ] , dp2[ i ][ j ][ u ] );
        dp1[ i ][ j ][ u ] = max( dp1[ i ][ j ][ u ],
                                  dp1[ i ][ j - 1 ][ u ] );
        dp1[ i ][ j ][ u ] = max( dp1[ i ][ j ][ u ],
                                  dp1[ i - 1 ][ j ][ u ] );
        dp2[ i ][ j ][ u ] = min( dp2[ i ][ j ][ u ],
                                  dp2[ i ][ j - 1 ][ u ] );
        dp2[ i ][ j ][ u ] = min( dp2[ i ][ j ][ u ],
                                  dp2[ i - 1 ][ j ][ u ] );
      }
  int ans = 0;
  for( int i = 1 ; i * 2 <= k ; i ++ )
    ans = max( ans , ans1[ i ] - ans2[ i * 2 ] );
  printf( "%d\n" , ans );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
