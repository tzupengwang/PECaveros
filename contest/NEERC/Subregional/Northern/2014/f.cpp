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
#define N 101010
void build(){

}
int n , a[ N ] , p[ N ] , sz[ N ] , vsz;
int find_p( int x ){
  return x == p[ x ] ? x : p[ x ] = find_p( p[ x ] );
}
void Union( int x , int y ){
  x = find_p( x );
  y = find_p( y );
  if( x == y ) return;
  p[ x ] = y;
  sz[ y ] += sz[ x ];
}
void init(){
  n = getint();
  vector< int > li;
  for( int i = 1 ; i <= n ; i ++ ){
    a[ i ] = getint();
    li.push_back( a[ i ] );
    p[ i ] = i;
  }
  sort( li.begin() , li.end() );
  li.resize( unique( li.begin() , li.end() ) - li.begin() );
  for( int i = 1 ; i <= n ; i ++ )
    a[ i ] = lower_bound( li.begin() , li.end() , a[ i ] ) - li.begin() + 1;
  vsz = (int)li.size();
}
int cnt[ N ];
bool lft[ N ] , rgt[ N ] , both[ N ];
vector< pair< PII , int > > vv;
vector< int > dp[ N ][ 2 ];
vector< PII > id[ N ] , from[ N ][ 2 ];
void cal( size_t l , size_t r , int vl , int vr ){
  for( int i = vl ; i <= vr ; i ++ ){
    id[ i ].push_back( { 0 , 0 } );
    dp[ i ][ 0 ].push_back( 0 );
    dp[ i ][ 1 ].push_back( 0 );
    from[ i ][ 0 ].push_back( { 0 , 0 } );
    from[ i ][ 1 ].push_back( { 0 , 0 } );
  }
  for( size_t i = l ; i < r ; i ++ ){
    for( int tvl = vv[ i ].FI.FI , j = 0 ; tvl <= vv[ i ].FI.SE ; tvl ++ , j ++ ){
      id[ tvl ].push_back( { i + 1 , vv[ i ].SE + j } );
      dp[ tvl ][ 0 ].push_back( 0 );
      dp[ tvl ][ 1 ].push_back( 0 );
      from[ tvl ][ 0 ].push_back( { 0 , 0 } );
      from[ tvl ][ 1 ].push_back( { 0 , 0 } );
    }
  }
  for( int i = vl ; i < vr ; i ++ )
    for( size_t j = 0 ; j < id[ i ].size() ; j ++ )
      for( size_t k = 0 ; k < id[ i + 1 ].size() ; k ++ ){
        if( dp[ i ][ 0 ][ j ] > dp[ i + 1 ][ 0 ][ k ] ){
          dp[ i + 1 ][ 0 ][ k ] = dp[ i ][ 0 ][ j ];
          from[ i + 1 ][ 0 ][ k ] = { 0 , j };
        }
        if( dp[ i ][ 1 ][ j ] > dp[ i + 1 ][ 0 ][ k ] &&
            j != 0 ){
          dp[ i + 1 ][ 0 ][ k ] = dp[ i ][ 1 ][ j ];
          from[ i + 1 ][ 0 ][ k ] = { 1 , j };
        }
        if( dp[ i ][ 0 ][ j ] + 1 > dp[ i + 1 ][ 1 ][ k ] &&
            k != 0 &&
            lft[ id[ i + 1 ][ k ].SE ] ){
          dp[ i + 1 ][ 1 ][ k ] = dp[ i ][ 0 ][ j ] + 1;
          from[ i + 1 ][ 1 ][ k ] = { 0 , j };
        }
        if( dp[ i ][ 1 ][ j ] + 1 > dp[ i + 1 ][ 1 ][ k ] &&
            j != 0 && k != 0 &&
            lft[ id[ i + 1 ][ k ].SE ] &&
            ( id[ i ][ j ].FI != id[ i + 1 ][ k ].FI ||
              both[ id[ i ][ j ].SE ] ) ){
          dp[ i + 1 ][ 1 ][ k ] = dp[ i ][ 1 ][ j ] + 1;
          from[ i + 1 ][ 1 ][ k ] = { 1 , j };
        }
      }
  int bst = 0 , xi = -1 , xj = -1;
  for( int i = 0 ; i < 2 ; i ++ )
    for( size_t j = 0 ; j < id[ vr ].size() ; j ++ )
      if( dp[ vr ][ i ][ j ] > bst ){
        bst = dp[ vr ][ i ][ j ];
        xi = i; xj = j;
      }
  for( int i = vr ; i > vl ; i -- ){
    if( xi ) Union( id[ i ][ xj ].SE , id[ i ][ xj ].SE - 1 );
    PII tp = from[ i ][ xi ][ xj ];
    xi = tp.FI; xj = tp.SE;
  }
}
void gogo(){
  sort( vv.begin() , vv.end() );
  for( size_t l = 0 , r = 0 ; l < vv.size() ; l = r ){
    int nl = vv[ l ].FI.FI , nr = vv[ l ].FI.SE;
    while( r < vv.size() && vv[ r ].FI.FI <= nr )
      nr = max( nr , vv[ r ++ ].FI.SE );
    cal( l , r , nl , nr );
  }
}
void solve(){
  int tn = 1;
  sz[ 1 ] = 1;
  for( int i = 2 ; i <= n ; i ++ )
    if( a[ i ] == a[ i - 1 ] )
      sz[ tn ] ++;
    else{
      a[ ++ tn ] = a[ i ];
      sz[ tn ] = 1;
    }
  n = tn;
  for( int i = 1 ; i <= n ; i ++ )
    cnt[ a[ i ] ] ++;
  for( int i = 1 ; i <= n ; i ++ ){
    if( i > 1 && a[ i - 1 ] == a[ i ] - 1 )
      lft[ i ] = true;
    if( i < n && a[ i + 1 ] == a[ i ] + 1 )
      rgt[ i ] = true;
    if( lft[ i ] && rgt[ i ] && cnt[ a[ i ] ] == 1 )
      both[ i ] = true;
  }
  for( int l = 1 , r = 1 ; l < n ; l = r + 1 ){
    r = l;
    while( r < n && rgt[ r ] ) r ++;
    if( l != r )
      vv.push_back( { { a[ l ] , a[ r ] } , l } );
  }
  gogo();
  vector< int > ans;
  for( int i = 1 ; i <= n ; i ++ )
    if( i == find_p( i ) )
      ans.push_back( sz[ i ] );
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
int main(){
  freopen( "fragmentation.in" , "r" , stdin );
  freopen( "fragmentation.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
