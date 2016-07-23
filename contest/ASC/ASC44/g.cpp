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
#define N 50505
#define MX 2000000000
int lft[ N << 2 ];
int rgt[ N << 2 ];
int bst[ N << 2 ];
int pos[ N << 2 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
void build_st( int no , int l , int r ){
  lft[ no ] = rgt[ no ] = bst[ no ] = 0;
  pos[ no ] = l;
  if( l == r ) return;
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid + 1 , r );
}
void modify( int no , int l , int r , int qpos , int lc , int rc ){
  if( l == r ){
    lft[ no ] += lc;
    rgt[ no ] += rc;
    bst[ no ] = lft[ no ] + rgt[ no ];
    pos[ no ] = l;
    return;
  }
  if( qpos <= mid ) modify( L( no ) , l , mid , qpos , lc , rc );
  else modify( R( no ) , mid + 1 , r , qpos , lc , rc );
  lft[ no ] = lft[ L( no ) ] + lft[ R( no ) ];
  rgt[ no ] = rgt[ L( no ) ] + rgt[ R( no ) ];
  bst[ no ] = lft[ L( no ) ] + rgt[ R( no ) ];
  pos[ no ] = mid + 1;
  if( bst[ L( no ) ] + rgt[ R( no ) ] > bst[ no ] ){
    bst[ no ] = bst[ L( no ) ] + rgt[ R( no ) ];
    pos[ no ] = pos[ L( no ) ];
  }
  if( lft[ L( no ) ] + bst[ R( no ) ] >= bst[ no ] ){
    bst[ no ] = lft[ L( no ) ] + bst[ R( no ) ];
    pos[ no ] = pos[ R( no ) ];
  }
}
int n , x[ N ] , y[ N ] , c[ N ];
void build(){
}
void init(){
  for( int i = 0 ; i < n ; i ++ ){
    x[ i ] = getint();
    y[ i ] = getint();
    c[ i ] = getint();
  }
}
struct Ans{
  int ans;
  int ax1[ 3 ] , ax2[ 3 ];
  int ay1[ 3 ] , ay2[ 3 ];
  Ans(){
    ans = 0;
  }
  void output(){
    printf( "%d\n" , ans );
    for( int i = 0 ; i < 3 ; i ++ ){
      if( ax1[ i ] > ax2[ i ] ) swap( ax1[ i ] , ax2[ i ] );
      if( ay1[ i ] > ay2[ i ] ) swap( ay1[ i ] , ay2[ i ] );
      printf( "%d %d %d %d\n" , ax1[ i ] , ay1[ i ] , ax2[ i ] , ay2[ i ] );
    }
  }
};
inline Ans cal1( int clr1 , int clr2 , int clr3 ){
  Ans tmp;
  vector< PII > vv;
  int tans = 0;
  for( int i = 0 ; i < n ; i ++ ){
    int tclr = 0;
    if( c[ i ] == clr2 ) tclr = 1;
    if( c[ i ] == clr3 ) tclr = 2;
    vv.push_back( { x[ i ] , tclr } );
    if( tclr == 0 ) tans ++;
  }
  sort( ALL( vv ) );
  tmp.ans = tans;
  tmp.ax1[ clr1 ] = -MX; tmp.ax2[ clr1 ] = MX - 2;
  tmp.ay1[ clr1 ] = -MX; tmp.ay2[ clr1 ] = MX;

  tmp.ax1[ clr2 ] = MX - 2; tmp.ax2[ clr2 ] = MX - 1;
  tmp.ay1[ clr2 ] = -MX; tmp.ay2[ clr2 ] = MX;

  tmp.ax1[ clr3 ] = MX - 1; tmp.ax2[ clr3 ] = MX;
  tmp.ay1[ clr3 ] = -MX; tmp.ay2[ clr3 ] = MX;
  build_st( 1 , 1 , n );
  for( int i = n - 1 ; i >= 0 ; i -- ){
    int px = vv[ i ].FI;
    int pc = vv[ i ].SE;
    if( pc == 0 ) tans --;
    else{
      if( pc == 1 ) modify( 1 , 1 , n , i + 1 , 1 , 0 );
      else modify( 1 , 1 , n , i + 1 , 0 , 1 );
    }
    if( tans + bst[ 1 ] > tmp.ans ){
      if( vv[ pos[ 1 ] - 1 ].FI <= px ) continue;
      tmp.ans = tans + bst[ 1 ];
      tmp.ax1[ clr1 ] = -MX; tmp.ax2[ clr1 ] = px;
      tmp.ay1[ clr1 ] = -MX; tmp.ay2[ clr1 ] = MX;

      tmp.ax1[ clr2 ] = px; tmp.ax2[ clr2 ] = vv[ pos[ 1 ] - 1 ].FI;
      tmp.ay1[ clr2 ] = -MX; tmp.ay2[ clr2 ] = MX;

      tmp.ax1[ clr3 ] = vv[ pos[ 1 ] - 1 ].FI;
      tmp.ax2[ clr3 ] = MX;
      tmp.ay1[ clr3 ] = -MX; tmp.ay2[ clr3 ] = MX;
    }
  }
  return tmp;
}
inline Ans cal2( int clr1 , int clr2 , int clr3 ){
  Ans tmp;
  vector< tiii > vv;
  int tans = 0;
  vector< tiii > li;
  vector< int > ppos;
  for( int i = 0 ; i < n ; i ++ ){
    int tclr = 0;
    if( c[ i ] == clr2 ) tclr = 1;
    if( c[ i ] == clr3 ) tclr = 2;
    vv.push_back( MT( x[ i ] , tclr , i ) );
    if( tclr ) li.push_back( MT( y[ i ] , tclr , i ) );
    else tans ++;
  }
  sort( ALL( li ) );
  sort( ALL( vv ) );
  ppos.resize( n );
  for( size_t i = 0 ; i < li.size() ; i ++ )
    ppos[ get<2>( li[ i ] ) ] = i + 1;
  int xx = (int)li.size();
  if( xx == 0 ) return tmp;
  build_st( 1 , 1 , xx );
  reverse( ALL( vv ) );
  for( size_t i = 0 ; i < vv.size() ; i ++ ){
    int px = get<0>( vv[ i ] );
    int pc = get<1>( vv[ i ] );
    int pi = get<2>( vv[ i ] );
    if( pc == 0 ) tans --;
    else{
      int npos = ppos[ pi ];
      if( pc == 1 ) modify( 1 , 1 , xx , npos , 1 , 0 );
      else modify( 1 , 1 , xx , npos , 0 , 1 );
    }
    if( tans + bst[ 1 ] > tmp.ans ){
      tmp.ans = tans + bst[ 1 ];
      
      tmp.ax1[ clr1 ] = -MX; tmp.ax2[ clr1 ] = px;
      tmp.ay1[ clr1 ] = -MX; tmp.ay2[ clr1 ] = MX;

      tmp.ax1[ clr2 ] =  px; tmp.ax2[ clr2 ] = MX;
      tmp.ay1[ clr2 ] = -MX; tmp.ay2[ clr2 ] = get<0>( li[ pos[ 1 ] - 1 ] );
      
      tmp.ax1[ clr3 ] =  px; tmp.ax2[ clr3 ] = MX;
      tmp.ay1[ clr3 ] = get<0>( li[ pos[ 1 ] - 1 ] );
      tmp.ay2[ clr3 ] = MX;
    }
  }
  return tmp;
}
inline Ans go(){
  Ans abst;
  for( int i = 0 ; i < 4 ; i ++ ){
    int per[3]={0,1,2};
    do{
      Ans tans1 = cal1( per[ 0 ] , per[ 1 ] , per[ 2 ] );
      Ans tans2 = cal2( per[ 0 ] , per[ 1 ] , per[ 2 ] );
      if( tans1.ans > abst.ans ) abst = tans1;
      if( tans2.ans > abst.ans ) abst = tans2;
    }while( next_permutation( per , per + 3 ) );
    for( int j = 0 ; j < n ; j ++ ){
      int tx = y[ j ];
      int ty = -x[ j ];
      x[ j ] = tx;
      y[ j ] = ty;
    }
    for( int j = 0 ; j < 3 ; j ++ ){
      int tx1 = abst.ay1[ j ] , ty1 = -abst.ax1[ j ];
      int tx2 = abst.ay2[ j ] , ty2 = -abst.ax2[ j ];
      abst.ax1[ j ] = tx1;
      abst.ay1[ j ] = ty1;
      abst.ax2[ j ] = tx2;
      abst.ay2[ j ] = ty2;
    }
  }
  return abst;
}
void solve(){
  go().output();
}
int main(){
  freopen( "gold.in" , "r" , stdin );
  freopen( "gold.out" , "w" , stdout );
  build();
  while( scanf( "%d" , &n ) == 1 && n ){
    init();
    solve();
  }
}
