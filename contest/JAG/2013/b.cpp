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
#define N 1021
void build(){

}
char c[ 3 ][ N ];
bool init(){
  scanf( "%s" , c[ 0 ] + 1 );
  if( !strcmp( c[ 0 ] + 1 , "0" ) ) return false;
  scanf( "%s" , c[ 1 ] + 1 );
  scanf( "%s" , c[ 2 ] + 1 );
  return true;
}
int len , dp[ N ][ N ];
bool got[ N ][ N ];
queue< PII > Q;
void solve(){
  int ans = 0;
  for( int i = 0 ; i <= len ; i ++ )
    for( int j = 0 ; j < N ; j ++ ){
      dp[ i ][ j ] = 0;
      got[ i ][ j ] = false;
    }
  len = strlen( c[ 0 ] + 1 );
  for( int i = 0 ; i < 10 ; i ++ )
    if( c[ 0 ][ len ] == '?' || c[ 0 ][ len ] - '0' == i )
  for( int j = 0 ; j < 10 ; j ++ )
    if( c[ 1 ][ len ] == '?' || c[ 1 ][ len ] - '0' == j )
  for( int k = 0 ; k < 10 ; k ++ )
    if( c[ 2 ][ len ] == '?' || c[ 2 ][ len ] - '0' == k ){
      if( ( i + j ) % 10 != k ) continue;
      dp[ len ][ ( i + j ) / 10 ] ++;
      if( len == 1 && i != 0 && j != 0 && k != 0 && ( i + j ) < 10 ) ans ++;
      if( !got[ len ][ ( i + j ) / 10 ] ){
        got[ len ][ ( i + j ) / 10 ] = true;
        Q.push( { len , ( i + j ) / 10 } );
      }
    }
  if( len == 1 ){
    printf( "%d\n" , ans );
    return;
  }
  while( Q.size() ){
    PII tp = Q.front(); Q.pop();
    int pos = tp.FI , ad = tp.SE;
    if( pos == 1 ) continue;
    for( int i = 0 ; i < 10 ; i ++ )
      if( c[ 0 ][ pos - 1 ] == '?' || c[ 0 ][ pos - 1 ] - '0' == i )
    for( int j = 0 ; j < 10 ; j ++ )
      if( c[ 1 ][ pos - 1 ] == '?' || c[ 1 ][ pos - 1 ] - '0' == j )
    for( int k = 0 ; k < 10 ; k ++ )
      if( c[ 2 ][ pos - 1 ] == '?' || c[ 2 ][ pos - 1 ] - '0' == k ){
        if( ( i + j + ad ) % 10 != k ) continue;
        dp[ pos - 1 ][ ( i + j + ad ) / 10 ] =
          add( dp[ pos - 1 ][ ( i + j + ad ) / 10 ] ,
               dp[ pos ][ ad ] );
        if( pos == 2 && i != 0 && j != 0 && k != 0 && 
            ( i + j + ad ) / 10 == 0 )
          ans = add( ans , dp[ pos ][ ad ] );
        if( !got[ pos - 1 ][ ( i + j + ad ) / 10 ] ){
          got[ pos - 1 ][ ( i + j + ad ) / 10 ] = true;
          Q.push( { pos - 1 , ( i + j + ad ) / 10 } );
        }
      }
  }
  printf( "%d\n" , ans );
}
int main(){
  build();
  //__ = getint();
  while( init() ){
    solve();
  }
}
