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
#define N 3333
void build(){

}
int b , I , d , c , len[ 2 ];
char s[ 2 ][ N ];
void init(){
  b = getint();
  I = getint();
  d = getint();
  c = getint();
  for( int i = 0 ; i < 2 ; i ++ ){
    scanf( "%s" , s[ i ] + 1 );
    len[ i ] = strlen( s[ i ] + 1 );
  }
}
int dp[ N ][ N ] , bst[ N ];
int bk[ N ][ N ];
void backtracking(){
  printf( "%d\n" , dp[ len[ 0 ] ][ len[ 1 ] ] );
  vector< PII > v;
  string cmd;
  int ni = len[ 0 ] , nj = len[ 1 ];
  while( ni + nj > 0 ){
    if( bk[ ni ][ nj ] == -1 ){
      cmd += "D";
      ni --;
      continue;
    }
    if( bk[ ni ][ nj ] == -2 ){
      cmd += "I";
      nj --;
      continue;
    }
    if( bk[ ni ][ nj ] == -3 ){
      cmd += "C";
      ni --; nj --;
      continue;
    }
    v.push_back( { bk[ ni ][ nj ] + 1 , ni } );
    ni = bk[ ni ][ nj ];
  }
  reverse( ALL( v ) );
  reverse( ALL( cmd ) );
  printf( "%d\n" , (int)v.size() );
  for( PII tp : v ) printf( "%d %d\n" , tp.FI , tp.SE );
  printf( "%s\n" , cmd.c_str() );
}
void solve(){
  for( int i = 0 ; i <= len[ 0 ] ; i ++ )
    for( int j = 0 ; j <= len[ 1 ] ; j ++ ){
      dp[ i ][ j ] = INF;
      bst[ j ] = -1;
    }
  dp[ 0 ][ 0 ] = 0;
  bst[ 0 ] = 0;
  for( int i = 0 ; i <= len[ 0 ] ; i ++ )
    for( int j = 0 ; j <= len[ 1 ] ; j ++ ){
      if( i == 0 && j == 0 ) continue;
      if( i > 0 ){
        int cstd = dp[ i - 1 ][ j ] + d;
        if( cstd < dp[ i ][ j ] ){
          dp[ i ][ j ] = cstd;
          bk[ i ][ j ] = -1;
        }
      }
      if( j > 0 ){
        int csti = dp[ i ][ j - 1 ] + I;
        if( csti < dp[ i ][ j ] ){
          dp[ i ][ j ] = csti;
          bk[ i ][ j ] = -2;
        }
      }
      if( i > 0 && j > 0 && s[ 0 ][ i ] == s[ 1 ][ j ] ){
        int cstc = dp[ i - 1 ][ j - 1 ] + c;
        if( cstc < dp[ i ][ j ] ){
          dp[ i ][ j ] = cstc;
          bk[ i ][ j ] = -3;
        }
      }
      if( bst[ j ] != -1 ){
        int cstb = dp[ bst[ j ] ][ j ] + b;
        if( cstb < dp[ i ][ j ] ){
          dp[ i ][ j ] = cstb;
          bk[ i ][ j ] = bst[ j ];
        }
      }
      if( bst[ j ] == -1 ||
          dp[ i ][ j ] < dp[ bst[ j ] ][ j ] )
        bst[ j ] = i;
    }
  backtracking();
}
int main(){
  freopen( "block.in" , "r" , stdin );
  freopen( "block.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
