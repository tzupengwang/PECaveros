// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<D,D> Pt;
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
#define N 5050
inline LL operator^( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
inline LL Area( const PLL& p1 , const PLL& p2 , const PLL& p3 ){
  LL area = ( p1 ^ p2 ) + ( p2 ^ p3 ) + ( p3 ^ p1 );
  return abs( area );
}
PLL p[ N ];
inline LL Area( const short& s1 , const short& s2 , const short& s3 ){
  return Area( p[ s1 ] , p[ s2 ] , p[ s3 ] );
}
inline void scan( PLL& tp ){
  tp.X = getint();
  tp.Y = getint();
}
LL ans = -1;
int n , b[ 3 ] , s[ 3 ];
void update( LL tans , int b1 , int b2 , int b3 ,
                       int s1 , int s2 , int s3 ){
  if( tans > ans ){
    ans = tans;
    b[ 0 ] = b1; b[ 1 ] = b2; b[ 2 ] = b3;
    s[ 0 ] = s1; s[ 1 ] = s2; s[ 2 ] = s3;
  }
}
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
}
short bb[ N ][ N ][ 3 ];
short ss[ N ][ N ][ 3 ];
bool got[ N ][ N ];
void DP( int l , int r ){
  if( l == r ) return;
  if( got[ l ][ r ] ) return;
  got[ l ][ r ] = true;
  int dlt = 0;
  dlt = ( r - l + n ) % n;
  if( dlt < 2 ) return;
  if( dlt == 2 ){
    int tmp = ( l + 1 ) % n;
    ss[ l ][ r ][ 0 ] = bb[ l ][ r ][ 0 ] = l;
    ss[ l ][ r ][ 1 ] = bb[ l ][ r ][ 1 ] = r;
    ss[ l ][ r ][ 2 ] = bb[ l ][ r ][ 2 ] = tmp;
    return;
  }else{
    int nl = ( l + 1 ) % n , nr = r;
    DP( nl , nr );
    for( int i = 0 ; i < 3 ; i ++ )
      bb[ l ][ r ][ i ] = bb[ nl ][ nr ][ i ],
      ss[ l ][ r ][ i ] = ss[ nl ][ nr ][ i ];
    LL tarea = Area( p[ l ] , p[ r ] , p[ nl ] );
    if( tarea > Area( bb[ l ][ r ][ 0 ] , bb[ l ][ r ][ 1 ] , bb[ l ][ r ][ 2 ] ) ){
      bb[ l ][ r ][ 0 ] = l;
      bb[ l ][ r ][ 1 ] = r;
      bb[ l ][ r ][ 2 ] = nl;
    }
    if( tarea < Area( ss[ l ][ r ][ 0 ] , ss[ l ][ r ][ 1 ] , ss[ l ][ r ][ 2 ] ) ){
      ss[ l ][ r ][ 0 ] = l;
      ss[ l ][ r ][ 1 ] = r;
      ss[ l ][ r ][ 2 ] = nl;
    }
    LL tmparea = Area( bb[ nl ][ nr ][ 0 ] , bb[ nl ][ nr ][ 1 ] , bb[ nl ][ nr ][ 2 ] );
    if( tarea <= tmparea ){
      update( tmparea - tarea , bb[ nl ][ nr ][ 0 ] , 
                                bb[ nl ][ nr ][ 1 ] , 
                                bb[ nl ][ nr ][ 2 ] ,
                                l , r , nl );
    }
    tmparea = Area( ss[ nl ][ nr ][ 0 ] , ss[ nl ][ nr ][ 1 ] , ss[ nl ][ nr ][ 2 ] );
    if( tarea >= tmparea ){
      update( tarea - tmparea , l , r , nl ,
                                ss[ nl ][ nr ][ 0 ] , 
                                ss[ nl ][ nr ][ 1 ] , 
                                ss[ nl ][ nr ][ 2 ] );
    }
    nl = l; nr = ( r - 1 + n ) % n;
    DP( nl , nr );
    tarea = Area( p[ l ] , p[ r ] , p[ nr ] );
    if( Area( ss[ nl ][ nr ][ 0 ] , ss[ nl ][ nr ][ 1 ] , ss[ nl ][ nr ][ 2 ] ) <
        Area( ss[ l ][ r ][ 0 ] , ss[ l ][ r ][ 1 ] , ss[ l ][ r ][ 2 ] ) ){
      for( int i = 0 ; i < 3 ; i ++ )
        ss[ l ][ r ][ i ] = ss[ nl ][ nr ][ i ];
    }
    if( Area( bb[ nl ][ nr ][ 0 ] , bb[ nl ][ nr ][ 1 ] , bb[ nl ][ nr ][ 2 ] ) >
        Area( bb[ l ][ r ][ 0 ] , bb[ l ][ r ][ 1 ] , bb[ l ][ r ][ 2 ] ) ){
      for( int i = 0 ; i < 3 ; i ++ )
        bb[ l ][ r ][ i ] = bb[ nl ][ nr ][ i ];
    }
    tmparea = Area( bb[ l ][ r ][ 0 ] , bb[ l ][ r ][ 1 ] , bb[ l ][ r ][ 2 ] );
    if( tarea > tmparea ){
      bb[ l ][ r ][ 0 ] = l;
      bb[ l ][ r ][ 1 ] = r;
      bb[ l ][ r ][ 2 ] = nr;
    }
    tmparea = Area( ss[ l ][ r ][ 0 ] , ss[ l ][ r ][ 1 ] , ss[ l ][ r ][ 2 ] );
    if( tarea < tmparea ){
      ss[ l ][ r ][ 0 ] = l;
      ss[ l ][ r ][ 1 ] = r;
      ss[ l ][ r ][ 2 ] = nr;
    }
    tmparea = Area( bb[ nl ][ nr ][ 0 ] , bb[ nl ][ nr ][ 1 ] , bb[ nl ][ nr ][ 2 ] );
    if( tarea <= tmparea ){
      update( tmparea - tarea , bb[ nl ][ nr ][ 0 ] , 
                                bb[ nl ][ nr ][ 1 ] , 
                                bb[ nl ][ nr ][ 2 ] ,
                                l , r , nr );
    }
    tmparea = Area( ss[ nl ][ nr ][ 0 ] , ss[ nl ][ nr ][ 1 ] , ss[ nl ][ nr ][ 2 ] );
    if( tarea >= tmparea ){
      update( tarea - tmparea , l , r , nr ,
                                ss[ nl ][ nr ][ 0 ] , 
                                ss[ nl ][ nr ][ 1 ] , 
                                ss[ nl ][ nr ][ 2 ] );
    }
  }
  // printf( "%d %d\n" , l , r );
  // printf( "%.6f %.6f\n" , dpb[ l ][ r ] , dps[ l ][ r ] );
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      DP( i , j );
  printf( "%lld.%lld\n" , ans / 2 , 5 * ( ans % 2 ) );
  for( int i = 0 ; i < 3 ; i ++ )
    printf( "%d%c" , b[ i ] + 1 , " \n"[ i == 2 ] );
  for( int i = 0 ; i < 3 ; i ++ )
    printf( "%d%c" , s[ i ] + 1 , " \n"[ i == 2 ] );
}
int main(){
  freopen( "kids.in" , "r" , stdin );
  freopen( "kids.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
