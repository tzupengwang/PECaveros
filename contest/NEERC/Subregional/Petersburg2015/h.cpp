// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
// #define X FI
// #define Y SE
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
typedef tuple< LL , LL , LL > Pt;
#define X(_) get<0>(_)
#define Y(_) get<1>(_)
#define Z(_) get<2>(_)
inline Pt operator+( const Pt& p1 , const Pt& p2 ){
  return make_tuple( X(p1) + X(p2) ,
                     Y(p1) + Y(p2) ,
                     Z(p1) + Z(p2) );
}
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return make_tuple( X(p1) - X(p2) ,
                     Y(p1) - Y(p2) ,
                     Z(p1) - Z(p2) );
}
inline Pt operator*( const Pt& p1 , const LL& tk ){
  return make_tuple( X(p1) * tk ,
                     Y(p1) * tk ,
                     Z(p1) * tk );
}
inline Pt operator/( const Pt& p1 , const LL& tk ){
  return make_tuple( X(p1) / tk ,
                     Y(p1) / tk ,
                     Z(p1) / tk );
}
inline Pt operator^( const Pt& p1 , const Pt& p2 ){
  return make_tuple( Y(p1) * Z(p2) - Y(p2) * Z(p1) ,
                     Z(p1) * X(p2) - Z(p2) * X(p1) ,
                     X(p1) * Y(p2) - X(p2) * Y(p1) );
}
inline LL operator*( const Pt& p1 , const Pt& p2 ){
  return X(p1) * X(p2) +
         Y(p1) * Y(p2) +
         Z(p1) * Z(p2);
}
inline bool operator==( const Pt& p1 , const Pt& p2 ){
  return X(p1) == X(p2) &&
         Y(p1) == Y(p2) &&
         Z(p1) == Z(p2);
}
inline double norm( const Pt& tp ){
  return sqrt( tp * tp );
}
void scan( Pt& tp ){
  X(tp) = getint();
  Y(tp) = getint();
  Z(tp) = getint();
}
void print( const Pt& tp ){
  printf( "%lld %lld %lld\n" , X(tp) , Y(tp) , Z(tp) );
}
void build(){

}
#define N 2048
int n , ids , idt;
Pt tri[ N ][ 3 ] , s , t;
D pi = acos( -1.0 );
inline D reg( D ang ){
  if( ang < -pi ) ang += 2.0 * pi;
  if( ang > +pi ) ang -= 2.0 * pi;
  return ang;
}
inline bool on_line( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  Pt cr = ( p2 - p1 ) ^ ( p3 - p1 );
  if( cr != make_tuple( 0 , 0 , 0 ) ) return false;
  return ( p1 - p2 ) * ( p3 - p2 ) <= 0;
}
inline bool in( int id , const Pt& tp ){
  for( int i = 0 ; i < 3 ; i ++ ){
    if( tp == tri[ id ][ i ] )
      return true;
    if( on_line( tri[ id ][ i ] , tp , tri[ id ][ ( i + 1 ) % 3 ] ) )
      return true;
  }
  D sum = 0.0;
  for( int i = 0 ; i < 3 ; i ++ ){
    Pt p1 = tri[ id ][ i ] - tp;
    Pt p2 = tri[ id ][ ( i + 1 ) % 3 ] - tp;
    sum += reg( acos( ( p1 * p2 ) / norm( p1 ) / norm( p2 ) ) );
  }
  return sum > pi;
}
inline int find_tri( const Pt& tp ){
  for( int i = 0 ; i < n ; i ++ ){
    Pt np = ( tri[ i ][ 1 ] - tri[ i ][ 0 ] ) ^
            ( tri[ i ][ 2 ] - tri[ i ][ 0 ] );
    if( ( ( np * tri[ i ][ 0 ] ) == ( np * tp ) ) &&
        in( i , tp ) )
      return i;
  }
  assert( false );
  return -1;
}
inline Pt find_h( Pt p1 , Pt p2 , LL ht ){
  if( Z(p1) > Z(p2) ) swap( p1 , p2 );
  assert( !( p1 == p2 ) );
  Pt dlt = p2 - p1;
  LL stp = abs( __gcd( X( dlt ) , __gcd( Y( dlt ) , Z( dlt ) ) ) );
  LL bl = 0 , br = stp , ba = 0;
  while( bl <= br ){
    LL bmid = ( bl + br ) >> 1;
    if( Z( p1 ) + bmid * ( Z(dlt) / stp ) <= ht )
      ba = bmid, bl = bmid + 1;
    else br = bmid - 1;
  }
  return p1 + ( dlt / stp ) * ba;
}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      scan( tri[ i ][ j ] );
  scan( s );
  scan( t );
  ids = find_tri( s );
  idt = find_tri( t );
}
map< Pt , int > id;
int p[ N * 5 ];
int find_p( int xi ){
  return xi == p[ xi ] ? xi : p[ xi ] = find_p( p[ xi ] );
}
void Union( int xi , int yi ){
  p[ find_p( xi ) ] = find_p( yi );
}
inline bool okay( LL ht ){
  id.clear();
  int midx = 0;
  for( int i = 0 ; i < n ; i ++ ){
    vector< Pt > pos;
    for( int j = 0 ; j < 3 ; j ++ ){
      if( Z( tri[ i ][ j ] ) <= ht ){
        pos.push_back( tri[ i ][ j ] );
        if( Z( tri[ i ][ ( j + 1 ) % 3 ] ) > ht )
          pos.push_back( find_h( tri[ i ][ j ],
                                 tri[ i ][ ( j + 1 ) % 3 ],
                                 ht ) );
      }
    }
    if( i == ids ) pos.push_back( s );
    if( i == idt ) pos.push_back( t );
    sort( ALL( pos ) );
    pos.resize( unique( ALL( pos ) ) - pos.begin() );
    int pid = -1;
    for( Pt tp : pos ){
      if( id.count( tp ) == 0 ){
        p[ midx ] = midx;
        id[ tp ] = midx ++;
      }
      int nid = id[ tp ];
      if( pid != -1 ) Union( pid , nid );
      pid = nid;
    }
  }
  return find_p( id[ s ] ) == find_p( id[ t ] );
}
vector< int > nxt[ N * 5 ];
Pt who[ N * 5 ];
bool vst[ N * 5 ];
Pt path[ N * 5 ];
void gotcha( int mst ){
  printf( "%d\n" , mst );
  for( int i = 0 ; i < mst ; i ++ )
    print( path[ i ] );
  exit( 0 );
}
void go( int idx , int stp ){
  vst[ idx ] = true;
  path[ stp ] = who[ idx ];
  if( who[ idx ] == t )
    gotcha( stp + 1 );
  for( int nn : nxt[ idx ] )
    if( !vst[ nn ] )
      go( nn , stp + 1 );
}
inline void output( LL ht ){
  id.clear();
  int midx = 0;
  for( int i = 0 ; i < n ; i ++ ){
    vector< Pt > pos;
    for( int j = 0 ; j < 3 ; j ++ ){
      if( Z( tri[ i ][ j ] ) <= ht ){
        pos.push_back( tri[ i ][ j ] );
        if( Z( tri[ i ][ ( j + 1 ) % 3 ] ) > ht )
          pos.push_back( find_h( tri[ i ][ j ],
                                 tri[ i ][ ( j + 1 ) % 3 ],
                                 ht ) );
      }
    }
    if( i == ids ) pos.push_back( s );
    if( i == idt ) pos.push_back( t );
    sort( ALL( pos ) );
    pos.resize( unique( ALL( pos ) ) - pos.begin() );
    int pid = -1;
    for( Pt tp : pos ){
      if( id.count( tp ) == 0 ){
        who[ midx ] = tp;
        id[ tp ] = midx ++;
      }
      int nid = id[ tp ];
      if( pid != -1 ){
        nxt[ pid ].push_back( nid );
        nxt[ nid ].push_back( pid );
      }
      pid = nid;
    }
  }
  go( id[ s ] , 0 );
}
void solve(){
  if( ids == idt ){
    puts( "2" );
    print( s );
    print( t );
    exit( 0 );
  }
  LL bl = max( Z( s ) , Z( t ) ) , br = 1000000 , ba = 1000000;
  while( bl <= br ){
    LL bmid = ( bl + br ) >> 1;
    if( okay( bmid ) ) ba = bmid , br = bmid - 1;
    else bl = bmid + 1;
  }
  output( ba );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
