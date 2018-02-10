#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1024
int s[ N + N ][ N + N ];
int dx , dy , n , q;
void init(){
  for( int i = 0 ; i <= dx + dy ; i ++ )
    for( int j = 0 ; j <= dx + dy ; j ++ )
      s[ i ][ j ] = 0;
  while( n -- ){
    int x , y;
    scanf( "%d%d" , &x , &y );
    s[ x + y ][ x - y + dy ] ++;
  }
  for( int i = 0 ; i <= dx + dy ; i ++ )
    for( int j = 0 ; j <= dx + dy ; j ++ ){
      if( i ) s[ i ][ j ] += s[ i - 1 ][ j ];
      if( j ) s[ i ][ j ] += s[ i ][ j - 1 ];
      if( i and j ) s[ i ][ j ] -= s[ i - 1 ][ j - 1 ];
    }
}
int _cs;
void solve(){
  printf( "Case %d:\n" , ++ _cs );
  while( q -- ){
    int m; scanf( "%d" , &m );
    int ans = -1 , ax = 1 , ay = 1;
    for( int i = 1 ; i <= dx ; i ++ )
      for( int j = 1 ; j <= dy ; j ++ ){
        int xl = max( i + j - m      , 1 );
        int xr = min( i + j + m      , dx + dy );
        int yl = max( i - j + dy - m , 1 );
        int yr = min( i - j + dy + m , dx + dy );
        int ress = s[ xr ][ yr ] -
                   s[ xl - 1 ][ yr ] -
                   s[ xr ][ yl - 1 ] +
                   s[ xl - 1 ][ yl - 1 ];
        if( ress > ans or
            (ress == ans and j < ay) or
            (ress == ans and j == ay and i < ax) ){
          ans = ress;
          ax = i;
          ay = j;
        }
      }
    printf( "%d (%d,%d)\n" , ans , ax , ay );
  }
}
int main(){
  while( scanf( "%d%d%d%d" , &dx , &dy , &n , &q ) == 4 and dx ){
    init();
    solve();
  }
}
