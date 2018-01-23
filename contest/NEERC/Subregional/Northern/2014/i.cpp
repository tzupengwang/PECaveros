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
#define N 60
#define M 1021
#define S 0
#define P 1
int type[ N ] , arr[ N ] , dir[ N ];
vector< int > nxt[ N ];
int n , m , ti[ M ] , tar[ M ];
void build(){

}
int go( int now ){
  if( type[ now ] == P ) return arr[ now ];
  for( int son : nxt[ now ] )
    arr[ now ] |= go( son );
  return arr[ now ];
}
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    char c[ 9 ];
    scanf( "%s" , c );
    if( c[ 0 ] == 's' ){
      type[ i ] = S;
      int prt = getint();
      nxt[ prt ].push_back( i );
    }else{
      type[ i ] = P;
      int prt = getint();
      scanf( "%s" , c );
      nxt[ prt ].push_back( i );
      arr[ i ] = ( 1 << ( c[ 0 ] - 'a' ) );
    }
  }
  go( 0 );
  m = getint();
  for( int i = 1 ; i <= m ; i ++ ){
    ti[ i ] = getint();
    char c[ 9 ]; scanf( "%s" , c );
    tar[ i ] = ( 1 << ( c[ 0 ] - 'a' ) );
  }
}
int on[ N ] , nowt , to[ N ];
vector< PII > v;
void gogo( int now ){
  if( type[ now ] == P ) return;
  for( int son : nxt[ now ] )
    gogo( son );
  if( on[ now ] ){
    if( type[ nxt[ now ][ to[ now ] ] ] != P )
      on[ nxt[ now ][ to[ now ] ] ] = on[ now ];
    on[ now ] = 0;
  }
}
inline void toggle(){
  for( int i = 0 ; i <= n ; i ++ )
    if( on[ i ] ){
      int tnxt = -1;
      for( size_t j = 0 ; j < nxt[ i ].size() ; j ++ )
        if( ( arr[ nxt[ i ][ j ] ] & tar[ on[ i ] ] ) == tar[ on[ i ] ] ){
          tnxt = j;
          break;
        }
      if( tnxt != dir[ i ] ){
        dir[ i ] = tnxt;
        v.push_back( { i , nowt } );
      }
      to[ i ] = tnxt;
    }
  gogo( 0 );
}
void solve(){
  int ptr = 1;
  for( int i = 0 ; i <= ti[ m ] + n ; i ++ ){
    if( ptr <= m && ti[ ptr ] == i )
      on[ 0 ] = ptr ++;
    nowt = i;
    toggle();
  }
  printf( "%d\n" , (int)v.size() );
  for( PII tp : v ) printf( "%d %d\n" , tp.FI , tp.SE );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
