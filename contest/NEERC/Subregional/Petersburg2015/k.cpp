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
#define M 256
#define T 101
void build(){

}
int n , t , q[ N ] , x[ N ];
int pdp[ M ][ M ][ T ];
int pdpsum[ M ][ M ];
inline void pre_dp(){
  pdp[ 0 ][ 0 ][ 0 ] = 1;
  for( int i = 0 ; i + 1 < M ; i ++ )
    for( int j = 0 ; j <= i ; j ++ )
      for( int k = 0 ; k <= t ; k ++ ){
        if( pdp[ i ][ j ][ k ] == 0 ) continue;
        if( k == 0 )
          pdp[ i + 1 ][ j + 1 ][ t ] = add( pdp[ i + 1 ][ j + 1 ][ t ] , 
                                            pdp[ i ][ j ][ k ] );
        int nxtk = max( k - 1 , 0 );
        pdp[ i + 1 ][ j ][ nxtk ] = add( pdp[ i + 1 ][ j ][ nxtk ] ,
                                         pdp[ i ][ j ][ k ] );
        pdpsum[ i ][ j ] = add( pdpsum[ i ][ j ] ,
                                pdp[ i ][ j ][ k ] );
      }
  for( int i = 0 ; i < M ; i ++ ){
    pdpsum[ i ][ 0 ] = 0;
    for( int j = 1 ; j < M ; j ++ )
      pdpsum[ i ][ j ] = add( pdpsum[ i ][ j ] ,
                              pdpsum[ i ][ j - 1 ] );
  }
}
void init(){
  n = getint(); t = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    q[ i ] = getint();
    x[ i ] = getint();
  }
  pre_dp();
}
int dp[ N ][ T ];
void solve(){
  dp[ 0 ][ 0 ] = 1;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j <= t ; j ++ ){
      if( dp[ i ][ j ] == 0 ) continue;
      int nq = q[ i + 1 ] , nx = x[ i + 1 ];
      if( j >= nq ){
        dp[ i + 1 ][ j - nq ] = add( dp[ i + 1 ][ j - nq ] ,
                                     dp[ i ][ j ] );
      }else{
        dp[ i + 1 ][ 0 ] = add( dp[ i + 1 ][ 0 ] ,
                                dp[ i ][ j ] );
        int st = t + 1 - ( nq - j );
        if( nq - j > t ) st = 0;
        int mx = nq - nx;
        for( int nxtj = st ; nxtj <= t ; nxtj ++ ){
          if( nxtj == 0 ){
            int res = nq - j;
            if( res >= t ){
              dp[ i + 1 ][ nxtj ] = add( dp[ i + 1 ][ nxtj ] ,
                                         mul( dp[ i ][ j ] , pdpsum[ res - t ][ mx ] ) );
            }else{
              dp[ i + 1 ][ nxtj ] = add( dp[ i + 1 ][ nxtj ] ,
                                         dp[ i ][ j ] );
            }
          }else if( mx >= 1 ){
            int res = nq - j - 1 - t + nxtj;
            if( res >= t ){
              dp[ i + 1 ][ nxtj ] = add( dp[ i + 1 ][ nxtj ] ,
                                         mul( dp[ i ][ j ] , pdpsum[ res - t ][ mx - 1 ] ) );
            }else{
              dp[ i + 1 ][ nxtj ] = add( dp[ i + 1 ][ nxtj ] ,
                                         dp[ i ][ j ] );
            }
          }
        }
      }
    }
  int ans = 0;
  for( int i = 0 ; i <= t ; i ++ )
    ans = add( ans , dp[ n ][ i ] );
  printf( "%d\n" , ans );
}
int main(){
  // freopen( "kebab.in" , "r" , stdin );
  // freopen( "kebab.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
