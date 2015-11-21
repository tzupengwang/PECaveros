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
#define N 202020
#define L 10211021
char buf[ L ];
vector<string> vl[ N ];
vector<int> nxt[ N ];
string ss[ N ];
int len, midx, ptr;
bool dir[ N ];
void build(){
  
}
string parse_string(){
  string ts = "";
  ptr ++;
  while( buf[ ptr ] != '\"' )
    ts += buf[ ptr ++ ];
  ptr ++;
  return ts;
}
void parse( int key ){
// pure key
  if( buf[ ptr ] == '\"' ){
    ss[ ++ midx ] = parse_string();
    dir[ key ] = true;
    vl[ key ].PB( ss[ midx ] );
    nxt[ key ].PB( midx );
    return;
  }
// nested
  ++ ptr; // {
  while( buf[ ptr ] != '}' && ptr < len ){
    ss[ ++ midx ] = parse_string();
    vl[ key ].PB( ss[ midx ] );
    nxt[ key ].PB( midx );
    ++ ptr; // :
    parse( midx );
    if( buf[ ptr ] == ',' ) ++ ptr;
    else if( buf[ ptr ] == '}' ) break;
  }
  ++ ptr; // }
}
void init(){
  scanf( "%s" , buf );
  len = strlen( buf );
  midx = ptr = 0;
  parse( 0 );
}
void print_string( int idx ){
  cout << "\"" << ss[ idx ] << "\"";
}
void print( int idx , bool flag ){
  if( dir[ idx ] ){
    if( !flag ) print_string( idx ), cout << ":";
    for( int i = 0 ; i < (int)nxt[ idx ].size() ; i ++ )
      print_string( nxt[ idx ][ i ] );
    return;
  }
  if( !flag ) print_string( idx ), cout << ":";
  cout << "{";
  for( int i = 0 ; i < (int)nxt[ idx ].size() ; i ++ ){
    print( nxt[ idx ][ i ] , false );
    if( i < (int)nxt[ idx ].size() - 1 ) cout << ",";
  }
  cout << "}";
}
void read( int key ){
  string ts = parse_string();
  if( lower_bound( ALL( vl[ key ] ) , ts ) ==
      upper_bound( ALL( vl[ key ] ) , ts ) ){
    printf( "Error!" );
    return;
  }
  int idx = lower_bound( ALL( vl[ key ] ) , ts ) - vl[ key ].begin();
  if( ptr == len ) print( nxt[ key ][ idx ] , true );
  else if( dir[ key ] ){
    printf( "Error!" );
    return;
  }else{
    ptr ++; //.
    read( nxt[ key ][ idx ] );
  }
}
void solve(){
  int q = getint(); while( q -- ){
    scanf( "%s" , buf );
    len = strlen( buf );
    ptr = 0;
    read( 0 );
    puts( "" );
  }
  for( int i = 0 ; i <= midx ; i ++ ){
    vl[ i ].clear();
    nxt[ i ].clear();
    dir[ i ] = false;
  }
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
