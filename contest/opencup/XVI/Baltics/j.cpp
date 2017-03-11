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
vector<int> v;
void build(){

}
inline int len( int xx ){
  int cnt = 0;
  if( xx == 0 ) return 1;
  while( xx ){
    cnt ++;
    xx /= 10;
  }
  return cnt;
}
void init(){
  int x;
  while( scanf( "%d" , &x ) == 1 )
    v.PB( x );
}
vector< vector< char > > ans;
int mxdep;
int pre;
void write( int vl , int dep ){
  if( (int)ans.size() < dep + 1 )
    ans.resize( dep + 1 );
  int tlen = len( vl ); 
  if( (int)ans[ dep ].size() < pre + tlen )
    ans[ dep ].resize( pre + tlen );
  for( int i = pre + tlen - 1 ; i >= pre ; i -- ){
    ans[ dep ][ i ] = ( vl % 10 ) + '0';
    vl /= 10;
  }
  pre += tlen;
}
void find_ans( int l , int r , int dep ){
  if( l > r ) return;
  mxdep = max( mxdep , dep );
  if( l == r ){
    write( v[ l ] , dep );
    return;
  }
  int tl = l + 1 , tr = r , tmid , ta = -1;
  while( tl <= tr ){
    tmid = ( tl + tr ) >> 1;
    if( v[ tmid ] <= v[ l ] ) ta = tmid , tl = tmid + 1;
    else tr = tmid - 1;
  }
  if( ta != -1 )
    find_ans( l + 1 , ta , dep + 1 );
  write( v[ l ] , dep );
  if( ta == -1 )
    find_ans( l + 1 , r , dep + 1 );
  else 
    find_ans( ta + 1 , r , dep + 1 );
  return;
}
void solve(){
  find_ans( 0 , v.size() - 1 , 0 );
  for( int i = 0 ; i <= mxdep ; i ++ ){
    for( size_t j = 0 ; j < ans[ i ].size() ; j ++ )
      if( ans[ i ][ j ] )
        putchar( ans[ i ][ j ] );
      else putchar( ' ' );
    puts( "" );
  }
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
