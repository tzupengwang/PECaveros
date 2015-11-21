// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
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
ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 234560
vector< pair<string,int> > M3[ N ];
string ss[ N ];
bool tag[ N ];
char c[ 10001001 ];
int len, midx, nidx;
void build(){

}
void parse( int now ){
  while( nidx < len ){
    string ts = ""; nidx ++;
    while( c[ nidx ] != '\"' ) ts += c[ nidx ++ ];
    ++ midx;
    ss[ midx ] = ts;
    M3[ now ].PB( MP( ts , midx ) );
    int tnow = midx;
    ++ nidx; // "\""
    if( c[ nidx ] != ':' ) return;
    ++ nidx; // ":"
    if( c[ nidx ] == '\"' ){
      tag[ tnow ] = true;
      parse( tnow );
    }else{
      ++ nidx;
      parse( tnow );
    }
    if( c[ nidx ] == ',' ) nidx ++;
    else if( c[ nidx ] == '}' ){
      nidx ++;
      return;
    }
  }
}
void init(){
  scanf( "%s" , c );
  len = strlen( c );
  nidx = midx = 0;
  nidx ++;
  parse( 0 );
  // for( int i = 0 ; i <= midx ; i ++ ){
    // sort( ALL( M3[ i ] ) );
    // printf( "%d : \n" , i );
    // for( int j = 0 ; j < (int)M3[ i ].size() ; j ++ )
      // printf( "  %s %d\n" , M3[ i ][ j ].FI.data() , M3[ i ][ j ].SE );
  // }
}
void print( int now , bool flag ){
  if( tag[ now ] ){
    if( !flag )
      cout << "\"" << ss[ now ] << "\":";
    cout << "\"";
    for( int i = 0 ; i < (int)M3[ now ].size() ; i ++ )
      cout << M3[ now ][ i ].FI;
    cout << "\"";
  }else{
    if( !flag )
      cout << "\"" << ss[ now ] << "\":";
    cout << "{";
    for( int i = 0 ; i < (int)M3[ now ].size() ; i ++ ){
      print( M3[ now ][ i ].SE , false );
      if( i != (int)M3[ now ].size() - 1 ) cout << ",";
    }
    cout << "}";
  }
}
void read( int now ){
  string ts = ""; nidx ++;
  while( nidx < len && c[ nidx ] != '\"' )
    ts += c[ nidx ++ ];
  if( lower_bound( ALL( M3[ now ] ) , MP( ts , -100 ) ) ==
      upper_bound( ALL( M3[ now ] ) , MP( ts , midx + midx ) ) ){
    printf( "Error!" );
    return;
  }
  int idx = lower_bound( ALL( M3[ now ] ) , MP( ts , -100 ) ) - M3[ now ].begin();
  nidx ++;
  if( nidx >= len ) print( M3[ now ][ idx ].SE , true );
  else{
    if( tag[ M3[ now ][ idx ].SE ] ){
      printf( "Error!" );
      return;
    }
    nidx ++;
    read( M3[ now ][ idx ].SE );
  }
}
int tcnt;
void solve(){
  int q = getint(); while( q -- ){
    scanf( "%s" , c );
    len = strlen( c );
    nidx = 0;
    read( 0 );
    cout << endl;
  }
  // sidx.clear();
  for( int i = 0 ; i <= midx ; i ++ ){
    M3[ i ].clear();
    tag[ i ] = false;
  }
  nidx = midx = 0;
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
