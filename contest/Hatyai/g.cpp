#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int getint(){
  int _x=0; char _tc=getchar();    
  while( _tc<'0'||_tc>'9' ) _tc=getchar();
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x;
}
#define N 111
#define H 1111
int n , h , c[ N ][ N ] , e[ N ][ H ];
void init(){
  n = getint();
  h = getint();
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      c[ i ][ j ] = getint();
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < h ; j ++ )
      e[ i ][ j ] = getint();
  string tmp;
  getline( cin , tmp );
}
const LL inf = 10000000000000000LL;
LL dp[ H ][ N ] , bk[ H ][ N ];
int st[ H ] , sc;
void go(){
  for( int i = 0 ; i <= sc + 1 ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      dp[ i ][ j ] = inf;
  dp[ sc + 1 ][ 0 ] = 0;
  for( int i = sc + 1 ; i > 1 ; i -- )
    for( int j = 0 ; j < n ; j ++ ){
      if( dp[ i ][ j ] == inf ) continue;
      for( int k = 0 ; k < n ; k ++ ){
        if( k == 0 ) continue;
        LL tdp = dp[ i ][ j ] + c[ k ][ j ] + e[ k ][ st[ i - 1 ] ];
        if( tdp < dp[ i - 1 ][ k ] ){
          dp[ i - 1 ][ k ] = tdp;
          bk[ i - 1 ][ k ] = j;
        }
      }
    }
  LL bst = 1 , ba = inf;
  for( int i = 0 ; i < n ; i ++ ){
    LL tdp = dp[ 1 ][ i ] + c[ 0 ][ i ];
    if( tdp < ba ){
      ba = tdp;
      bst = i;
    }
  }
  printf( "%lld\n" , ba );
  vector<int> va;
  int cur = 1;
  while( bst ){
    va.push_back( bst );
    bst = bk[ cur ][ bst ];
    cur ++;
  }
  for( size_t i = 0 ; i < va.size() ; i ++ )
    printf( "%d%c" , va[ i ] , " \n"[ i + 1 == va.size() ] );
}
void solve(){
  string tmp;
  while( getline( cin , tmp ) ){
    if( tmp.length() == 0 ) continue;
    stringstream ss( tmp );
    sc = 0; int tt;
    while( ss >> tt )
      st[ ++ sc ] = tt;
    go();
  }
}
int main(){
  init();
  solve();
}
