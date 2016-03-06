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
#define N 33
int n , a[ N ];
ll fac[ N ];
void build(){
  fac[ 0 ] = 1ll;
  for( ll i = 1 ; i < N ; i ++ )
    fac[ i ] = fac[ i - 1 ] * i;
}
int pos[ N ];
bool got[ N ];
int psum[ N ];
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ )
    psum[ i ] = 1;
  for( int i = 1 ; i <= n ; i ++ ){
    a[ i ] = getint();
    if( a[ i ] ){
      pos[ a[ i ] ] = i;
      got[ a[ i ] ] = true;
      psum[ a[ i ] ] --;
    }
  }
  for( int i = n - 1 ; i >= 1 ; i -- )
    psum[ i ] += psum[ i + 1 ];
}
int at[ N ] , l , r;
ll ans;
void DFS( int now ){
  if( now > r ){
    vector<int> vv;
    // for( int i = 1 ; i <= n ; i ++ )
      // printf( "%d%c" , a[ i ] , " \n"[ i == n ] );
    for( int i = 1 ; i <= r ; i ++ ){
      int mx = max( a[ i * 2 ] , a[ i * 2 - 2 ] );
      int nnow = i * 2 - 1;
      if( a[ nnow ] && a[ nnow ] < mx * 2 ) return;
      if( a[ nnow ] == 0 )
        vv.PB( psum[ max( mx * 2 , n / 2 + 1 ) ] );
    }
    if( a[ n ] && a[ n ] < a[ n - 1 ] * 2 ) return;
    if( a[ n ] == 0 )
      vv.PB( psum[ max( a[ n - 1 ] * 2 , n / 2 + 1 ) ] );
    sort( ALL( vv ) );
    ll tans = 1;
    for( size_t i = 0 ; i < vv.size() ; i ++ ){
      if( vv[ i ] < (int)i ) tans = 0;
      else tans *= ( vv[ i ] - (int)i );
    }
    ans += tans;
    return;
  }
  if( got[ now ] ) DFS( now + 1 );
  else{
    for( int i = 1 ; i <= r ; i ++ )
      if( a[ i * 2 ] == 0 ){
        a[ i * 2 ] = now;
        DFS( now + 1 );
        a[ i * 2 ] = 0;
      }
  }
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    if( ( i % 2 ) && a[ i ] && a[ i ] <= n / 2 ){
      puts( "0" );
      return;
    }else if( i % 2 == 0 && a[ i ] && a[ i ] > n / 2 ){
      puts( "0" );
      return;
    }
  if( n == 1 ){
    puts( "1" );
    return;
  }
  ans = 0;
  l = ( n + 1 ) / 2 / 2 + 1;
  r = n / 2;
  // printf( "%d %d\n" , l , r );
  DFS( l );
  int tgot = 0;
  for( int i = 1 ; i < l ; i ++ )
    if( !got[ i ] )
      tgot ++;
  ans *= fac[ tgot ];
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
