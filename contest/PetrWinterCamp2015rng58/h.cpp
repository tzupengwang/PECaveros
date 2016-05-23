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
#define K 20
#define N 202020
int n , p[ K ][ N ] , pos[ N ] , sz[ N ] , stp , dep[ N ];
ll d[ N ];
vector<int> son[ N ];
void go( int now , int tdep = 0 ){
  pos[ now ] = ++stp;
  sz[ now ] = 1;
  dep[ now ] = tdep;
  for( int i : son[ now ] ){
    d[ i ] += d[ now ];
    go( i , tdep + 1 );
    sz[ now ] += sz[ i ];
  }
}
inline int LCA( int a , int b ){
  if( dep[ a ] < dep[ b ] ) swap( a , b );
  int dif = dep[ a ] - dep[ b ];
  for( int i = 0 ; i < K ; i ++ )
    if( ( dif >> i ) & 1 )
      a = p[ i ][ a ];
  if( a == b ) return a;
  for( int i = K - 1 ; i >= 0 ; i -- )
    if( p[ i ][ a ] != p[ i ][ b ] ){
      a = p[ i ][ a ];
      b = p[ i ][ b ];
    }
  for( int i = 0 ; i < K ; i ++ )
    if( p[ i ][ a ] == p[ i ][ b ] )
      return p[ i ][ a ];
  return p[ 0 ][ a ];
}
inline bool sonof( int a , int b ){
  return pos[ b ] <= pos[ a ] &&
         pos[ a ] < pos[ b ] + sz[ b ];
}
int BIT[ N ] , lb[ N ];
inline void modify( int pp ){
  for( int i = pp ; i < N ; i += lb[ i ] )
    BIT[ i ] ++;
}
inline int qeury( int pp ){
  int res = 0;
  for( int i = pp ; i ; i -= lb[ i ] )
    res += BIT[ i ];
  return res;
}
inline int query( int v ){
  return qeury( pos[ v ] + sz[ v ] - 1 ) -
         qeury( pos[ v ] - 1 );
}
void build(){
  for( int i = 1 ; i < N ; i ++ )
    lb[ i ] = i & (-i);
}
void init(){
  n = getint();
  p[ 0 ][ 1 ] = 1;
  for( int i = 2 ; i <= n ; i ++ ){
    p[ 0 ][ i ] = getint();
    d[ i ] = getint();
    son[ p[ 0 ][ i ] ].PB( i );
  }
  go( 1 );
  for( int i = 1 ; i < K ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      p[ i ][ j ] = p[ i - 1 ][ p[ i - 1 ][ j ] ];
}
ll ans[ N ];
void solve(){
  modify( pos[ 1 ] );
  int bst = 1; ll anss = 0;
  for( int i = 2 ; i <= n ; i ++ ){
    modify( pos[ i ] );
    anss += d[ i ] + d[ bst ] - 2 * d[ LCA( i , bst ) ];
    if( sonof( i , bst ) ){
      if( i != bst ){
        int tmp = i;
        if( i - 2 * query( tmp ) >= 0 ){
          for( int j = K - 1 ; j >= 0 ; j -- )
            if( i - 2 * query( p[ j ][ tmp ] ) >= 0 )
              tmp = p[ j ][ tmp ];
          tmp = p[ 0 ][ tmp ];
        }
        if( sonof( tmp , bst ) ){
          anss += ( d[ tmp ] - d[ bst ] ) *
                  ( i - 2 * query( tmp ) );
          bst = tmp;
        }
      }
    }else if( i - 2 * query( bst ) > 0 ){
      int tmp = bst;
      for( int j = K - 1 ; j >= 0 ; j -- )
        if( i - 2 * query( p[ j ][ tmp ] ) > 0 )
          tmp = p[ j ][ tmp ];
      tmp = p[ 0 ][ tmp ];
      anss += ( d[ bst ] - d[ tmp ] ) *
              ( 2 * query( bst ) - i );
      bst = tmp;
      if( sonof( i , bst ) ){
        if( i != bst ){
          tmp = i;
          if( i - 2 * query( tmp ) >= 0 ){
            for( int j = K - 1 ; j >= 0 ; j -- )
              if( i - 2 * query( p[ j ][ tmp ] ) >= 0 )
                tmp = p[ j ][ tmp ];
            tmp = p[ 0 ][ tmp ];
          }
          if( sonof( tmp , bst ) ){
            anss += ( d[ tmp ] - d[ bst ] ) *
                    ( i - 2 * query( tmp ) );
            bst = tmp;
          }
        }
      }
    }
    ans[ i ] = anss;
  }
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%lld\n" , ans[ i ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
