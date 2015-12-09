// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
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
int __ = 1 , cs;
/*********default*********/
#define N 303030
int n , d[ N ] , x[ 2 ][ N ];
int st[ 2 ][ N << 2 ];
void build(){

}
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
void build_st( int no , int l , int r ){
  if( l == r ){
    st[ 0 ][ no ] = x[ 0 ][ l ];
    st[ 1 ][ no ] = x[ 1 ][ l ];
    return;
  }
  int mid = ( l + r ) >> 1;
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid + 1 , r );
  for( int i = 0 ; i < 2 ; i ++ )
    st[ i ][ no ] = min( st[ i ][ L( no ) ] , st[ i ][ R( no ) ] );
}
int query( int ty , int no , int l , int r , int ql , int qr ){
  if( l == ql && r == qr ) return st[ ty ][ no ];
  int mid = ( l + r ) >> 1;
  if( qr <= mid ) return query( ty , L( no ) , l , mid , ql , qr );
  if( mid < ql ) return query( ty , R( no ) , mid + 1 , r , ql , qr );
  return min( query( ty , L( no ) , l , mid , ql , mid ) ,
              query( ty , R( no ) , mid + 1 , r , mid + 1 , qr ) );
}
// 0 from left 1 from right
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    d[ i ] = getint();
    x[ 0 ][ i ] = d[ i ] - i;
    x[ 1 ][ i ] = d[ i ] - ( n - i + 1 );
  }
  build_st( 1 , 1 , n );
}
int dp[ N ] , from[ N ];
void solve(){
  dp[ 0 ] = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    int l = 1 , r = i - 1 , mid , a = i;
    while( l <= r ){
      mid = ( l + r ) >> 1;
      if( query( 0 , 1 , 1 , n , mid , i ) >= 1 - mid ||
          query( 1 , 1 , 1 , n , mid , i ) >= 1 - ( n - i + 1 ) )
        a = mid , r = mid - 1;
      else l = mid + 1;
    }
    dp[ i ] = dp[ a - 1 ] + 1;
    from[ i ] = a;
  }
  printf( "%d\n" , dp[ n ] );
  int now = n;
  while( now > 0 ){
    int xx = from[ now ];
    if( query( 0 , 1 , 1 , n , xx , now ) >= 1 - xx )
      printf( "%d %d\n" , xx , now ); 
    else printf( "%d %d\n" , now , xx );
    now = xx - 1;
  }
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
