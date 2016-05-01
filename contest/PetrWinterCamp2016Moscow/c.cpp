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
#define eps 1e-4
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
#define N 202020
inline Pt operator+( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
inline Pt operator*( const Pt& tp , const LD& tk ){
  return MP( tp.X * tk , tp.Y * tk );
}
inline Pt operator/( const Pt& tp , const LD& tk ){
  return MP( tp.X / tk , tp.Y / tk );
}
ll n , ix[ N ] , iy[ N ] , iphi[ N ] , ialpha[ N ];
LD phi[ N ] , alpha[ N ];
Pt pt[ N ];
const LD pi = acosl( -1.0 );
const LD pi_deg = 648000.0;
void build(){

}
inline Pt rotate( LD ang ){
  return MP( cosl( ang ) , sinl( ang ) );
}
inline Pt cal( const Pt &o , const Pt &v ){
  LD l = 0.0 , r = 1e10 , mid;
  Pt bdr = o;
  for( int i = 0 ; i < 60 ; i ++ ){
    mid = ( l + r ) * 0.5;
    Pt tmp = o + v * mid;
    if( max( fabsl( tmp.X ) , fabsl( tmp.Y ) ) > 1e9 ) r = mid;
    else l = mid , bdr = tmp;
  }
  return bdr;
}
inline LL roundUp( const LD& tk ){
  return ceil( tk );
  LL tmp = tk;
  if( equal( tk , tmp ) ) return tmp;
  if( tmp < tk ) return min( tmp + 1 , 1000000000ll );
  return tmp;
}
inline LL roundDown( const LD& tk ){
  return floor( tk );
  LL tmp = tk;
  if( equal( tk , tmp ) ) return tmp;
  if( tmp > tk ) return max( tmp - 1 , -1000000000ll );
  return tmp;
}
const ll mx = 1000000000ll;
inline PLL trans( const Pt& tp , bool st ){
  if( equal( tp.X , 1e9 ) ){
    if( st ) return MP( mx , roundDown( tp.SE ) );
    return MP( mx , roundUp( tp.SE ) );
  }
  if( equal( tp.X , -1e9 ) ){
    if( st ) return MP( -mx , roundUp( tp.SE ) );
    return MP( -mx , roundDown( tp.SE ) );
  }
  if( equal( tp.Y , 1e9 ) ){
    if( st ) return MP( roundUp( tp.FI ) , mx );
    return MP( roundDown( tp.FI ) , mx );
  }
  if( equal( tp.Y , -1e9 ) ){
    if( st ) return MP( roundDown( tp.FI ) , -mx );
    return MP( roundUp( tp.FI ) , -mx );
  }
  return MP( mx , mx );
}
LL mapping( const PLL &tp ){
  if( tp.X == mx ) return tp.Y + mx;
  if( tp.Y == mx ) return 2ll * mx + mx - tp.X;
  if( tp.X == -mx ) return 4ll * mx + mx - tp.Y;
  return 6ll * mx + tp.X + mx;
}
vector< PLL > vv;
void Add( ll s , ll t ){
  if( t < 8 * mx ){
    vv.PB( MP( s , +1 ) );
    vv.PB( MP( t , -1 ) );
  }else{
    // printf( "%lld %lld\n" , s , t );
    vv.PB( MP( s , +1 ) );
    vv.PB( MP( 8 * mx , -1 ) );
    vv.PB( MP( 0 , +1 ) );
    vv.PB( MP( t - 8 * mx , -1 ) );
  }
}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    ix[ i ] = getint();
    iy[ i ] = getint();
    phi[ i ] = iphi[ i ] = getint();
    alpha[ i ] = ialpha[ i ] = getint();
    pt[ i ] = MP( ix[ i ] , iy[ i ] );
    Pt s = rotate( alpha[ i ] / pi_deg * pi );
    Pt t = rotate( ( alpha[ i ] + phi[ i ] ) / pi_deg * pi );
    ll fp = mapping( trans( cal( pt[ i ] , s ) , true ) );
    ll tp = mapping( trans( cal( pt[ i ] , t ) , false ) );
    if( tp <= fp ) tp += 8 * mx;
    // printf( "s : %lld, t : %lld\n" , fp , tp );
    Add( fp , tp );
  }
  vv.PB( MP( 0 , 0 ) );
  vv.PB( MP( 2 * mx , 0 ) );
  vv.PB( MP( 4 * mx , 0 ) );
  vv.PB( MP( 6 * mx , 0 ) );
}
void output( LL vl ){
  puts( "YES" );
  vl %= 8 * mx;
  if( vl < 2 * mx ){
    printf( "%lld %lld\n" , +mx , vl - mx );
    exit( 0 );
  }
  vl -= 2 * mx;
  if( vl < 2 * mx ){
    printf( "%lld %lld\n" , mx - vl , +mx );
    exit( 0 );
  }
  vl -= 2 * mx;
  if( vl < 2 * mx ){
    printf( "%lld %lld\n" , -mx , mx - vl );
    exit( 0 );
  }
  vl -= 2 * mx;
  printf( "%lld %lld\n" , vl - mx , -mx );
  exit( 0 );
}
void solve(){
  sort( ALL( vv ) );
  int sz = (int)vv.size();
  for( int i = 0 ; i < sz ; i ++ )
    vv.PB( MP( vv[ i ].FI + 8 * mx , vv[ i ].SE ) );
  // for( size_t i = 0 ; i < vv.size() ; i ++ )
    // printf( "%lld %lld\n" , vv[ i ].X , vv[ i ].Y );
  ll cnt = 0;
  for( int i = 0 , j = 0 ; i < sz ; i = j ){
    while( j < (int)vv.size() && vv[ i ].FI == vv[ j ].FI ) j ++;
    for( int k = i ; k < j ; k ++ )
      cnt += vv[ k ].SE;
    if( cnt == 0 ){
      if( vv[ j ].FI - vv[ i ].FI >= 4 )
        output( ( vv[ j ].FI + vv[ i ].FI ) / 2 );
    }
  }
  puts( "NO" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
