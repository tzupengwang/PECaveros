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
#define N 514
struct State{
  int type;
  int nxt[ 3 ];
  State(){
    type = 0;
    for( int i = 0 ; i < 3 ; i ++ )
      nxt[ i ] = -1;
  }
  State( int _ty , int nxt0 , int nxt1 , int nxt2 ){
    type = _ty;
    nxt[ 0 ] = nxt0; nxt[ 1 ] = nxt1; nxt[ 2 ] = nxt2;
  }
};
inline int trans( char ctmp ){
  if( ctmp == 'R' ) return 0;
  if( ctmp == 'P' ) return 1;
  if( ctmp == 'S' ) return 2;
  return -1;
}
const char cc[] = "RPSXXXXX";
inline char rtrans( int xx ){ return cc[ xx ]; }
vector< State > op , my;
inline vector<State> operator+( vector<State>& v1 , vector<State>& v2 ){
  int vsz = (int)v1.size();
  for( size_t i = 0 ; i < v2.size() ; i ++ ){
    v1.push_back( v2[ i ] );
    for( int j = 0 ; j < 3 ; j ++ )
      if( v1.back().nxt[ j ] != -1 )
        v1.back().nxt[ j ] += vsz;
  }
  return v1;
}
int n , nxt[ 3 ];
char c[ 3 ];
void build(){

}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%s" , c );
    for( int j = 0 ; j < 3 ; j ++ )
      nxt[ j ] = getint() - 1;
    op.push_back( State( trans( c[ 0 ] ) , nxt[ 0 ] , nxt[ 1 ] , nxt[ 2 ] ) );
  }
}
vector< State > tmp[ N ];
int tag[ N ];
inline void go( int id ){
  for( int i = 0 ; i < n ; i ++ ) tag[ i ] = -1;
  int now = id;
  while( tag[ now ] == -1 ){
    tag[ now ] = (int)tmp[ id ].size();
    int op_mv = op[ now ].type;
    int my_mv = ( op_mv + 1 ) % 3;
    tmp[ id ].push_back( State( my_mv , -1 , -1 , -1 ) );
    int nxt_op = op[ now ].nxt[ my_mv ];
    if( tag[ nxt_op ] != -1 ){
      tmp[ id ].back().nxt[ op_mv ] = tag[ nxt_op ];
      return;
    }
    tmp[ id ].back().nxt[ op_mv ] = tmp[ id ].size();
    now = nxt_op;
  }
}
int flag[ 50505 ][ 514 ];
int stp;
inline void add( int id ){
  stp ++;
  int now = id , mys = 0;
  while( flag[ mys ][ now ] != stp ){
    flag[ mys ][ now ] = stp;
    int my_mv = my[ mys ].type;
    int op_mv = op[ now ].type;
    int my_nxt = my[ mys ].nxt[ op_mv ];
    int op_nxt = op[ now ].nxt[ my_mv ];
    if( my_nxt == -1 ){
      my[ mys ].nxt[ op_mv ] = my.size();
      my = my + tmp[ op_nxt ];
      return;
    }
    mys = my_nxt;
    now = op_nxt;
  }
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    go( i );
  my = tmp[ 0 ];
  for( int i = 1 ; i < n ; i ++ )
    add( i );
  printf( "%d\n" , (int)my.size() );
  for( State& ss : my ){
    for( int j = 0 ; j < 3 ; j ++ )
      if( ss.nxt[ j ] == -1 )
        ss.nxt[ j ] = 1;
      else ss.nxt[ j ] ++;
    printf( "%c %d %d %d\n" , rtrans( ss.type ) , ss.nxt[ 0 ] , ss.nxt[ 1 ] , ss.nxt[ 2 ] );
  }
}
int main(){
  freopen( "epic.in" , "r" , stdin );
  freopen( "epic.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
