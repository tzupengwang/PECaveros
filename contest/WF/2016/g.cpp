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
#define eps 1e-13
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
#define N 2222
ll n , x[ N ][ 2 ] , y[ N ] , v[ N ] , ans;
inline PLL operator-( const PLL& p1 , const PLL& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
inline ll cross( PLL p1 , PLL p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
const LD pi = acosl( -1.0 );
inline LD angle( PLL tp ){
  if( tp.Y == 0 ) return 0;
  if( tp.Y < 0 )
    return atan2l( tp.Y , tp.X ) + pi;
  return atan2l( tp.Y , tp.X );
}
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    x[ i ][ 0 ] = getint();
    x[ i ][ 1 ] = getint();
    y[ i ] = getint();
    v[ i ] = abs( x[ i ][ 0 ] - x[ i ][ 1 ] );
  }
}
bool cmp( pair< LD , LL > p1 , pair< LD , LL > p2 ){
  if( !equal( p1.FI , p2.FI ) )
    return p1.FI < p2.FI;
  return p1.SE > p2.SE;
}
void cal( PLL o , int idx ){
  vector< pair< LD , LL > > lp , up;
  ll sans = v[ idx ];
  for( int i = 0 ; i < n ; i ++ ){
    if( i == idx ) continue;
    PLL p1 = MP( x[ i ][ 0 ] , y[ i ] ) - o;
    PLL p2 = MP( x[ i ][ 1 ] , y[ i ] ) - o;
    if( p1.Y == 0 ) continue;
    if( cross( p1 , p2 ) < 0 ) swap( p1 , p2 );
    if( p1.Y < 0 || ( p1.Y == 0 && p1.X < 0 ) )
      lp.PB( MP( angle( p1 ) , v[ i ] ) );
    else up.PB( MP( angle( p1 ) , v[ i ] ) );
    if( p2.Y < 0 || ( p2.Y == 0 && p2.X < 0 ) )
      lp.PB( MP( angle( p2 ) , -v[ i ] ) );
    else up.PB( MP( angle( p2 ) , -v[ i ] ) );
  }
  sort( ALL( lp ) , cmp );
  sort( ALL( up ) , cmp );
  int sz1 = (int)lp.size();
  int sz2 = (int)up.size();
  ll tans = 0 , nans = 0;
  LD nangle = 0.0;
  for( int i1 = 0 , i2 = 0 ; i1 < sz1 || i2 < sz2 ;  ){
    while( i1 < sz1 && equal( lp[ i1 ].FI , nangle )
                    && lp[ i1 ].SE > 0 )
      nans += lp[ i1 ++ ].SE; 
    while( i2 < sz2 && equal( up[ i2 ].FI , nangle )
                    && up[ i2 ].SE > 0 )
      nans += up[ i2 ++ ].SE; 
    if( !equal( nangle , 0.0 ) )
      tans = max( tans , nans );
    while( i1 < sz1 && equal( lp[ i1 ].FI , nangle ) )
      nans += lp[ i1 ++ ].SE; 
    while( i2 < sz2 && equal( up[ i2 ].FI , nangle ) )
      nans += up[ i2 ++ ].SE; 
    LD nxtangle = pi * 4.0;
    if( i1 < sz1 ) nxtangle = min( nxtangle , lp[ i1 ].FI );
    if( i2 < sz2 ) nxtangle = min( nxtangle , up[ i2 ].FI );
    nangle = nxtangle;
  }
  ans = max( ans , tans + sans );
}
void go( int ii ){
  cal( MP( x[ ii ][ 0 ] , y[ ii ] ) , ii );
  cal( MP( x[ ii ][ 1 ] , y[ ii ] ) , ii );
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    go( i );
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
