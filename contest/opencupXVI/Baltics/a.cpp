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
#define N 21
int lb[ 1 << N ] , id[ 1 << N ] , cnt[ 1 << N ];
void build(){
  for( int i = 0 ; i < ( 1 << N ) ; i ++ ){
    lb[ i ] = i & (-i);
    cnt[ i ] = cnt[ i / 2 ] + ( i & 1 );
  }
  for( int i = 0 ; i < N ; i ++ )
    id[ 1 << i ] = i;
}
int n , m , gr[ N ] , agr[ N ] , deg[ N ] , adeg[ N ];
bool a[ 1 << N ] , c[ 1 << N ];
int pdpa[ 1 << N ] , pdpc[ 1 << N ];
inline bool C( int msk ){
  for( int i = 0 ; i < n ; i ++ )
    if( ( msk >> i ) & 1 ){
      if( ( gr[ i ] & msk ) != msk )
        return false;
    }
  return true;
}
inline bool A( int msk ){
  if( msk == ( msk & (-msk) ) )
    return true;
  for( int i = 0 ; i < n ; i ++ )
    if( ( msk >> i ) & 1 ){
      if( ( agr[ i ] & msk ) != msk )
        return false;
    }
  return true;
}
void init(){
  n = getint();
  m = getint();
  for( int i = 0 ; i < n ; i ++ ){
    gr[ i ] |= ( 1 << i );
    agr[ i ] = ( 1 << n ) - 1;
    deg[ i ] = 0;
    adeg[ i ] = n - 1;
  }
  while( m -- ){
    int ui = getint() - 1;
    int vi = getint() - 1;
    gr[ ui ] |= ( 1 << vi );
    gr[ vi ] |= ( 1 << ui );
    agr[ ui ] ^= ( 1 << vi );
    agr[ vi ] ^= ( 1 << ui );
    deg[ ui ] ++;
    deg[ vi ] ++;
    adeg[ ui ] --;
    adeg[ vi ] --;
  }
  for( int i = 1 ; i < ( 1 << n ) ; i ++ ){
    c[ i ] = C( i );
    a[ i ] = A( i );
    if( i == lb[ i ] ){
      pdpa[ i ] = pdpc[ i ] = lb[ i ];
    }else{
      // pdpa[ i ] = pdpa[ i ^ lb[ i ] ];
      // pdpc[ i ] = pdpc[ i ^ lb[ i ] ];
      // if( adeg[ id[ lb[ i ] ] ] < adeg[ id[ pdpa[ i ] ] ] )
        // pdpa[ i ] = lb[ i ];
      // if( deg[ id[ lb[ i ] ] ] < deg[ id[ pdpc[ i ] ] ] )
        // pdpc[ i ] = lb[ i ];
      int acnt = i & agr[ id[ lb[ i ] ] ];
      pdpa[ i ] = lb[ i ];
      for( int j = 0 ; j < n ; j ++ )
        if( ( i >> j ) & 1 ){
          int tcnt = i & agr[ j ];
          if( tcnt < acnt ){
            acnt = tcnt;
            pdpa[ i ] = ( 1 << j );
          }
        }
      int ccnt = i & gr[ id[ lb[ i ] ] ];
      pdpc[ i ] = lb[ i ];
      for( int j = 0 ; j < n ; j ++ )
        if( ( i >> j ) & 1 ){
          int tcnt = i & gr[ j ];
          if( tcnt < ccnt ){
            ccnt = tcnt;
            pdpc[ i ] = ( 1 << j );
          }
        }
    }
  }
}
bool ans[ N ][ N ];
int dpa[ 1 << N ] , dpc[ 1 << N ];
bool gota[ 1 << N ] , gotc[ 1 << N ];
int DPa( int );
void DFSa( int ns , int now , int msk , int mm2 ){
  if( dpa[ ns ] <= 2 ) return;
  if( now == 0 ){
    if( mm2 ) return;
    int tdp = DPa( ns ^ msk ) + 1;
    dpa[ ns ] = min( dpa[ ns ] , tdp );
    return;
  }
  int tk = pdpa[ now ];
  int nid = id[ tk ];
  DFSa( ns , ( now ^ tk ) & agr[ nid ] , tk ^ msk , ( mm2 ^ tk ) & agr[ nid ] );
  DFSa( ns , now ^ tk , msk , mm2 );
}
int DPa( int ns ){
  if( ns == 0 ) return 0;
  if( gota[ ns ] ) return dpa[ ns ];
  gota[ ns ] = true;
  if( a[ ns ] ) return dpa[ ns ] = 1;
  int tk = pdpa[ ns ];
  int nid = id[ tk ];
  DFSa( ns , ( ns ^ tk ) & agr[ nid ] , tk , ( ns ^ tk ) & agr[ nid ] );
  return dpa[ ns ];
}
int DPc( int );
void DFSc( int ns , int now , int msk , int mm2 ){
  if( dpc[ ns ] <= 2 ) return;
  if( now == 0 ){
    if( mm2 ) return;
    int tdp = DPc( ns ^ msk ) + 1;
    dpc[ ns ] = min( dpc[ ns ] , tdp );
    return;
  }
  int tk = pdpc[ now ];
  int nid = id[ tk ];
  DFSc( ns , ( now ^ tk ) & gr[ nid ] , tk ^ msk , ( mm2 ^ tk ) & gr[ nid ] );
  DFSc( ns , now ^ tk , msk , mm2 );
}
int DPc( int ns ){
  if( ns == 0 ) return 0;
  if( gotc[ ns ] ) return dpc[ ns ];
  gotc[ ns ] = true;
  if( c[ ns ] ) return dpc[ ns ] = 1;
  int tk = pdpc[ ns ];
  int nid = id[ tk ];
  DFSc( ns , ( ns ^ tk ) & gr[ nid ] , tk , ( ns ^ tk ) & gr[ nid ] );
  return dpc[ ns ];
}
void cal( int lft , int rgt ){
  int rdp = DPc( rgt );
  bool nd = false;
  for( int i = 0 ; i <= cnt[ lft ] && !nd ; i ++ ){
    for( int j = rdp ; j <= cnt[ rgt ] && !nd ; j ++ )
      nd |= ( !ans[ j ][ i ] );
  }
  if( !nd ) return;
  int ldp = DPa( lft );
  for( int i = ldp ; i <= cnt[ lft ] ; i ++ ){
    for( int j = rdp ; j <= cnt[ rgt ] ; j ++ )
      ans[ j ][ i ] = true;
  }
}
vector<int> l;
#define KK 675000
void solve(){
  for( int i = 0 ; i <= n ; i ++ )
    ans[ i ][ n - i ] = true;
  for( int i = 0 ; i < ( 1 << n ) ; i ++ )
    dpa[ i ] = dpc[ i ] = cnt[ i ];
  for( int lft = 0 ; lft < ( 1 << n ) ; lft ++ )
    l.PB( lft );
  random_shuffle( ALL( l ) );
  for( int i = 0 ; i < min( (int)l.size() , KK ) ; i ++ ){
    int lft = l[ i ];
    cal( lft , ( ( 1 << n ) - 1 ) ^ lft );
  }
  for( int i = 0 ; i <= n ; i ++ ){
    for( int j = 0 ; j <= n ; j ++ )
      if( ans[ i ][ j ] ) putchar( '1' );
      else putchar( '0' );
    puts( "" );
  }
}
int main(){
  srand( 0x514514 );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
