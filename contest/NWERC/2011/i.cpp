// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<LL,LL> Pt;
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
#define N 252525
typedef pair<Pt,Pt> Ln;
inline void scan( Pt& tp ){
  tp.X = getint();
  tp.Y = getint();
}
inline void scan( Ln& nl ){
  scan( nl.FI );
  scan( nl.SE );
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
inline LL operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline LL operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
inline LL dist2( const Pt& tp ){
  return tp * tp;
}
void build(){

}
LL s , r , w , p;
Pt ss[ N ] , pd[ N ];
Ln wl[ N ];
vector< Pt > ans[ N ];
vector< pair< Pt , int > > qry;
inline int ori( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  LL val = ( p2 - p1 ) ^ ( p3 - p1 );
  if( val == 0 ) return 0;
  return val > 0 ? 1 : -1;
}
inline bool intersect( const PLL& p1 , const PLL& p2 ,
                       const PLL& q1 , const PLL& q2 ){
  if( ( ( p2 - p1 ) ^ ( q2 - q1 ) ) == 0 ){ // parallel
    if( ori( p1 , p2 , q1 ) ) return false;
    return ( ( p1 - q1 ) * ( p2 - q1 ) ) <= 0 ||
           ( ( p1 - q2 ) * ( p2 - q2 ) ) <= 0 ||
           ( ( q1 - p1 ) * ( q2 - p1 ) ) <= 0 ||
           ( ( q1 - p2 ) * ( q2 - p2 ) ) <= 0;
  }
  return ( ori( p1 , p2 , q1 ) * ori( p1 , p2 , q2 ) <= 0 ) &&
         ( ori( q1 , q2 , p1 ) * ori( q1 , q2 , p2 ) <= 0 );
}
inline bool okay( Pt p1 , Pt p2 ){
  if( p1 == p2 ) return true;
  if( dist2( p1 - p2 ) > r * r ) return false;
  int inter = 0;
  for( int i = 0 ; i < w ; i ++ )
    if( intersect( p1 , p2 , wl[ i ].FI , wl[ i ].SE ) )
      inter ++;
  if( inter > r ) return false;
  if( dist2( p1 - p2 ) > ( r - inter ) * ( r - inter ) )
    return false;
  return true;
}
void init(){
  s = getint();
  r = getint();
  w = getint();
  p = getint();
  for( int i = 0 ; i < s ; i ++ )
    scan( ss[ i ] );
  for( int i = 0 ; i < w ; i ++ )
    scan( wl[ i ] );
  qry.clear();
  for( int i = 0 ; i < p ; i ++ ){
    scan( pd[ i ] );
    ans[ i ].clear();
    qry.push_back( { pd[ i ] , i } );
  }
  sort( ss , ss + s );
  sort( ALL( qry ) );
}
set< Pt > res;
void solve(){
  int lptr = 0 , rptr = 0;
  res.clear();
  for( size_t _ = 0 ; _ < qry.size() ; _ ++ ){
    Pt np = qry[ _ ].FI;
    int i = qry[ _ ].SE;
    while( rptr < s    && ss[ rptr ].X <= np.X + r ){
      res.insert( { ss[ rptr ].Y , ss[ rptr ].X } );
      rptr ++;
    }
    while( lptr < rptr && ss[ lptr ].X <  np.X - r ){
      res.erase(  { ss[ lptr ].Y , ss[ lptr ].X } );
      lptr ++;
    }
    auto it1 = res.lower_bound( { np.Y - r , -INF16 } );
    auto it2 = res.upper_bound( { np.Y + r , +INF16 } );
    for( auto it = it1 ; it != it2 ; it ++ )
      if( okay( { it->Y , it->X } , np ) )
        ans[ i ].push_back( { it->Y , it->X } );
  }
  for( int i = 0 ; i < p ; i ++ ){
    printf( "%d" , (int)ans[ i ].size() );
    sort( ALL( ans[ i ] ) );
    for( Pt tp : ans[ i ] ) printf( " (%lld,%lld)" , tp.X , tp.Y );
    puts( "" );
  }
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
