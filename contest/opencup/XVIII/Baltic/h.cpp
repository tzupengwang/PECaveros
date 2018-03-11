#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 110
int n , m , k;
bool fix[ N ][ N ];
int a[ N ][ N ] , id[ N ][ N ] , nid;
int u[ N * N * 6 ];
int v[ N * N * 6 ];
int c[ N * N * 6 ];
int e;
const int inf = 1000000000;
void build_edge( int ui , int vi , int ci ){
  u[ e ] = ui;
  v[ e ] = vi;
  c[ e ] = ci;
  e ++;
}
void init(){
  scanf( "%d%d%d" , &n , &m , &k );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      id[ i ][ j ] = ++ nid;
  while( k -- ){
    int ai , bi , ci;
    scanf( "%d%d%d" , &ai , &bi , &ci );
    fix[ ai ][ bi ] = true;
    a[ ai ][ bi ] = ci;
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ ){
      if( fix[ i ][ j ] ){
        build_edge( 0 , id[ i ][ j ] , +a[ i ][ j ] );
        build_edge( id[ i ][ j ] , 0 , -a[ i ][ j ] );
      }else{
        build_edge( 0 , id[ i ][ j ] , inf );
        build_edge( id[ i ][ j ] , 0 , 0 );
      }
      if( i + 1 <= n ){
        build_edge( id[ i ][ j ] , id[ i + 1 ][ j ] , m );
        build_edge( id[ i + 1 ][ j ] , id[ i ][ j ] , m );
      }
      if( j + 1 <= n ){
        build_edge( id[ i ][ j ] , id[ i ][ j + 1 ] , m );
        build_edge( id[ i ][ j + 1 ] , id[ i ][ j ] , m );
      }
    }
}
int dst[ N * N ];
void solve(){
  dst[ 0 ] = 0;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      dst[ id[ i ][ j ] ] = inf;
  for( int _ = 0 ; _ <= n * n + 1 ; _ ++ ){
    bool upd = false;
    for( int j = 0 ; j < e ; j ++ ){
      if( dst[ u[ j ] ] + c[ j ] < dst[ v[ j ] ] ){
        upd = true;
        dst[ v[ j ] ] = dst[ u[ j ] ] + c[ j ];
      }
    }
    if( _ == n * n + 1 and upd ){
      puts( "NO" );
      exit(0);
    }
  }
  puts( "YES" );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      printf( "%d%c" , dst[ id[ i ][ j ] ] , " \n"[ j == n ] );
}
int main(){
  init();
  solve();
}
