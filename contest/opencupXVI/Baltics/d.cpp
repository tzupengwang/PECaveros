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
#define N 101010
ll n;
PLL p[ N ][ 3 ];
vector<ll> len[ N ];
int idx[ N ];
bool cmp( int ii , int jj ){
  return len[ ii ][ 0 ] < len[ jj ][ 0 ];
}
inline PLL operator-( const PLL& p1 , const PLL& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
inline ll operator^( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
inline ll operator%( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
inline ll norm( const PLL& tp ){
  return tp % tp;
}
void scan( PLL& tp ){
  tp.X = getint();
  tp.Y = getint();
}
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    idx[ i ] = i;
    for( int j = 0 ; j < 3 ; j ++ )
      scan( p[ i ][ j ] );
    if( ( ( p[ i ][ 1 ] - p[ i ][ 0 ] ) ^
          ( p[ i ][ 2 ] - p[ i ][ 1 ] ) ) < 0 )
      swap( p[ i ][ 1 ] , p[ i ][ 2 ] );
    len[ i ].PB( norm( p[ i ][ 0 ] - p[ i ][ 1 ] ) );
    len[ i ].PB( norm( p[ i ][ 1 ] - p[ i ][ 2 ] ) );
    len[ i ].PB( norm( p[ i ][ 0 ] - p[ i ][ 2 ] ) );
    if( len[ i ][ 1 ] > len[ i ][ 0 ] && len[ i ][ 1 ] > len[ i ][ 2 ] ){
      ll tlen = len[ i ][ 0 ];
      len[ i ][ 0 ] = len[ i ][ 1 ];
      len[ i ][ 1 ] = len[ i ][ 2 ];
      len[ i ][ 2 ] = tlen;
    }
    if( len[ i ][ 2 ] > len[ i ][ 0 ] && len[ i ][ 2 ] > len[ i ][ 1 ] ){
      ll tlen = len[ i ][ 2 ];
      len[ i ][ 2 ] = len[ i ][ 1 ];
      len[ i ][ 1 ] = len[ i ][ 0 ];
      len[ i ][ 0 ] = tlen;
    }
  }
  sort( idx , idx + n , cmp );
}
bool pr[ N ];
vector<PII> ans;
void gogogo( int l , int r ){
  set< pair<PLL,int> > S;
typedef set< pair<PLL,int> >::iterator si;
  for( int _ = l ; _ < r ; _ ++ ){
    int i = idx[ _ ];
    si it = S.lower_bound( MP( MP( len[ i ][ 2 ] , len[ i ][ 1 ] ) , -1 ) );
    bool got = false;
    if( it != S.end() ){
      pair<PLL,int> tp = *it;
      if( tp.FI.FI == len[ i ][ 2 ] && tp.FI.SE == len[ i ][ 1 ] ){
        pr[ i ] = pr[ tp.SE ] = true;
        S.erase( tp );
        ans.PB( MP( i + 1 , tp.SE + 1 ) );
        got = true;
      }
    }
    if( !got )
      S.insert( MP( MP( len[ i ][ 1 ] , len[ i ][ 2 ] ) , i ) );
  }
}
void solve(){
  for( int l = 0 , r = 0 ; l < n ; l = r ){
    while( r < n && len[ idx[ r ] ][ 0 ] == len[ idx[ l ] ][ 0 ] ) r ++;
    gogogo( l , r );
  }
  int cans = (int)ans.size();
  for( int i = 0 ; i < n ; i ++ )
    if( !pr[ i ] )
      cans ++;
  printf( "%d\n" , cans );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d-%d\n" , ans[ i ].FI , ans[ i ].SE );
  for( int i = 0 ; i < n ; i ++ )
    if( !pr[ i ] )
      printf( "0-%d\n" , i + 1 );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
