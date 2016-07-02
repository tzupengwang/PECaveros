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
void build(){

}
inline int trans( char ctmp ){
  if( ctmp >= '2' && ctmp <= '9' )
    return ctmp - '0';
  if( ctmp == 'T' ) return 10;
  if( ctmp == 'J' ) return 11;
  if( ctmp == 'Q' ) return 12;
  if( ctmp == 'K' ) return 13;
  if( ctmp == 'A' ) return 14;
  assert( false );
  return -1;
}
const char val[] = "TJQKA";
inline char rtrans( int vl ){
  if( vl <= 9 ) return vl + '0';
  assert( vl <= 14 );
  return val[ vl - 10 ];
}
struct card{
  int vl;
  char dump;
  void read(){
    char c[ 20 ];
    scanf( "%s" , c );
    vl = trans( c[ 0 ] );
    dump = c[ 1 ];
  }
  void print(){
    printf( "%c%c" , rtrans( vl ) , dump );
  }
};
bool cmp( card c1 , card c2 ){
  return c1.vl < c2.vl;
}
#define N 13
card a[ N ];
void init(){
  for( int i = 0 ; i < N ; i ++ )
    a[ i ].read();
}
inline bool same( const vector<card>& vv , size_t l , size_t r ){
  for( size_t i = l ; i < r ; i ++ )
    if( vv[ i ].vl != vv[ l ].vl )
      return false;
  return true;
}
inline bool okay2( int msk ){
  vector< card > vv;
  for( int i = 0 ; i < N ; i ++ )
    if( ( msk >> i ) & 1 )
      vv.push_back( a[ i ] );
  if( (int)vv.size() == 1 ) return true;
  if( (int)vv.size() >= 2 &&
      (int)vv.size() <= 4 ) return same( vv , 0 , vv.size() );
  sort( ALL( vv ) , cmp );
  if( (int)vv.size() == 5 ){
    if( same( vv , 0 , 2 ) && same( vv , 2 , 5 ) ) return true;
    if( same( vv , 0 , 3 ) && same( vv , 3 , 5 ) ) return true;
  }
  for( size_t i = 1 ; i < vv.size() ; i ++ )
    if( vv[ i ].vl != vv[ i - 1 ].vl + 1 )
      return false;
  return true;
}
bool tag[ 1 << N ];
bool ok[ 1 << N ];
inline bool okay( int msk ){
  if( tag[ msk ] ) return ok[ msk ];
  tag[ msk ] = true;
  return ok[ msk ] = okay2( msk );
}
int dp[ 1 << N ];
int nxt[ 1 << N ];
bool got[ 1 << N ];
void go( int msk ){
  while( msk ){
    int nxtmsk = nxt[ msk ];
    int now = msk ^ nxtmsk;
    vector<int> vv;
    for( int i = 0 ; i < N ; i ++ )
      if( ( now >> i ) & 1 )
        vv.push_back( i );
    for( size_t i = 0 ; i < vv.size() ; i ++ ){
      a[ vv[ i ] ].print();
      putchar( " \n"[ i + 1 == vv.size() ] );
    }
    msk = nxtmsk;
  }
}
int DP( int msk ){
  if( msk == 0 ) return 0;
  if( got[ msk ] ) return dp[ msk ];
  if( msk == ( msk & (-msk) ) ){
    got[ msk ] = true;
    nxt[ msk ] = 0;
    dp[ msk ] = 1;
    return 1;
  }
  got[ msk ] = true;
  dp[ msk ] = N + N;
  for( int submsk = msk ; submsk ; submsk = ( submsk - 1 ) & msk ){
    if( okay( submsk ) ){
      int tdp = 1 + DP( msk ^ submsk );
      if( tdp < dp[ msk ] ){
        dp[ msk ] = tdp;
        nxt[ msk ] = msk ^ submsk;
      }
    }
  }
  return dp[ msk ];
}
void solve(){
  for( int i = 0 ; i < ( 1 << N ) ; i ++ )
    tag[ i ] = got[ i ] = false;
  printf( "%d\n" , DP( ( 1 << N ) - 1 ) );
  go( ( 1 << N ) - 1 );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
