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
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 300010
#define M 610
int n , q;
char c[ N ];
int psum[ N / M + 2 ][ M ];
int psumpos[ N / M + 2 ][ 2 * M + 1 ];
void build(){

}
set<int> sl, sr;
int trans( char ctmp ){
  return ctmp == '(' ? 1 : -1;
}
void init(){
  n = getint(); q = getint();
  scanf( "%s" , c );
  for( int i = 0 ; i < n ; i ++ ){
    int npos = i / M , mpos = i % M;
    if( mpos == 0 ) psum[ npos ][ 0 ] = trans( c[ i ] );
    else psum[ npos ][ mpos ] =
          psum[ npos ][ mpos - 1 ] + trans( c[ i ] );
    psumpos[ npos ][ psum[ npos ][ mpos ] + M ] = mpos + 1;
    if( c[ i ] == '(' ) sl.insert( i );
    if( c[ i ] == ')' ) sr.insert( i );
  }
}
void rebuild( int x ){
  int l = x * M, r = min( n , ( x + 1 ) * M );
  for( int j = 0 ; j <= 2 * M ; j ++ )
    psumpos[ x ][ j ] = 0;
  for( int i = l ; i < r ; i ++ ){
    int mpos = i % M;
    if( mpos == 0 ) psum[ x ][ 0 ] = trans( c[ i ] );
    else psum[ x ][ mpos ] =
        psum[ x ][ mpos - 1 ] + trans( c[ i ] );
    psumpos[ x ][ psum[ x ][ mpos ] + M ] = mpos + 1;
  }
}
void flip( int tpos ){
  if( c[ tpos ] == '(' )
    sl.erase( tpos ), sr.insert( tpos );
  if( c[ tpos ] == ')' )
    sr.erase( tpos ), sl.insert( tpos );
  c[ tpos ] ^= 1;
  rebuild( tpos / M );
}
void solve(){
  while( q -- ){
    //puts( c );
    int tpos = getint() - 1;
    if( tpos == n - 1 || tpos == 0 ){
      printf( "%d\n" , tpos + 1 );
      continue;
    }
    int npos = tpos / M , mpos = tpos % M;
    flip( tpos );
    if( c[ tpos ] == ')' ){
      int tans = *sr.begin();
      flip( tans );
      printf( "%d\n" , tans + 1 );
      continue;
    }
    int ps = 0 , nptr = -1 , nptr2 = -1;
    for( int i = 0 ; i < npos ; i ++ ){
      if( M + 1 - ps >= 0 &&
          M + 1 - ps <= 2 * M &&
          psumpos[ i ][ M + 1 - ps ] != 0 )
        nptr2 = i * M + psumpos[ i ][ M + 1 - ps ] - 1;
      ps += psum[ i ][ M - 1 ];
    }
    for( int i = 0 ; i < mpos ; i ++ ){
      if( psum[ npos ][ i ] + ps == 1 )
        nptr2 = i + npos * M;
    }
    int ql = max( nptr , nptr2 ) + 1;
    int tans;
    if( c[ tpos ] == '(' ){
      tans = *sl.lower_bound( ql );
      printf( "%d\n" , tans + 1 );
    }else{
      tans = *sr.lower_bound( ql );
      printf( "%d\n" , tans + 1 );
    }
    flip( tans );
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
