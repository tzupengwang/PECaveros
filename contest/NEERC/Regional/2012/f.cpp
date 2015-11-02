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
#define N 50010
vector<int> v[ N << 2 ];
int n;
int p[ N ] , x[ N ] , y[ N ] , x2[ N ];
D sqr( D _ ){ return _ * _; }
D h( int idx , int nx ){
  if( nx < p[ idx ] || nx > x2[ idx ] ) return -1;
  return ( -y[ idx ] ) * sqr( nx - x[ idx ] ) /
                         sqr( p[ idx ] - x[ idx ] ) + y[ idx ];
}
bool cmp( int _x , int _y ){ return y[ _x ] > y[ _y ]; }
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
void build_st( int no , int l , int r ){
  for( int i = l ; i <= r ; i ++ ) v[ no ].PB( i );
  if( l == r ) return;
  sort( ALL( v[ no ] ) , cmp );
  int mid = ( l + r ) >> 1;
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid + 1 , r );
}
unordered_map<ll,D> ans[ N << 2 ];
D query( int no , int l , int r , int ql , int qr , int xl , int xr , ll hsh ){
  D tans = 0;
  if( l == ql && r == qr ){
    if( ans[ no ].count( hsh ) ) return ans[ no ][ hsh ];
    for( int i = 0 ; i < (int)v[ no ].size() ; i ++ ){
      int idx = v[ no ][ i ];
      if( y[ idx ] < tans ) break;
      if( xr < p[ idx ] || xl > x2[ idx ] ) continue;
      if( xl <= x[ idx ] && xr >= x[ idx ] ) tans = max( tans , (D)y[ idx ] );
      tans = max( tans , h( idx , xl ) );
      tans = max( tans , h( idx , xr ) );
    }
    return ans[ no ][ hsh ] = tans;
  }
  int mid = ( l + r ) >> 1;
  if( qr <= mid ) tans = query( L( no ) , l , mid , ql , qr , xl , xr , hsh );
  else if( mid < ql  ) tans = query( R( no ) , mid + 1 , r , ql , qr , xl , xr , hsh );
  else{
    tans = max( tans , query( L( no ) , l , mid , ql , mid , xl , xr , hsh ) );
    tans = max( tans , query( R( no ) , mid + 1 , r , mid + 1 , qr , xl , xr , hsh ) );
  }
  return tans;
}
void build(){

}
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    p[ i ] = getint();
    x[ i ] = getint();
    y[ i ] = getint();
    x2[ i ] = 2 * x[ i ] - p[ i ];
  }
  build_st( 1 , 1 , n );
}
void solve(){
  int q = getint(); while( q -- ){
    int ql = getint();
    int qr = getint();
    int xl = getint();
    int xr = getint();
    printf( "%.12f\n" , query( 1 , 1 , n , ql , qr , xl , xr , xl * N + xr ) );
  }
}
int main(){
  freopen( "flights.in" , "r" , stdin );
  freopen( "flights.out" , "w" , stdout );
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
