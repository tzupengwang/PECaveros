#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 15
int n , ans[ N ][ N ][ N ];
void output(){
  for( int i = 0 ; i < n ; i ++ ){
    if( i ) puts( "" );
    for( int j = 0 ; j < n ; j ++ , puts( "" ) )
      for( int k = 0 ; k < n ; k ++ )
        if( ans[ i ][ j ][ k ] )
          putchar( 'A' + ans[ i ][ j ][ k ] - 1 );
        else
          putchar( '.' );
  }
  exit(0);
}
char c[ 6 ][ N ][ N ] , tmp[ N ][ N ];
void rotate( int id ){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      tmp[ i ][ j ] = c[ id ][ i ][ j ];
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      c[ id ][ i ][ j ] = tmp[ n - j - 1 ][ i ];
}
void reflect( int id ){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      tmp[ i ][ j ] = c[ id ][ i ][ j ];
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      c[ id ][ i ][ j ] = tmp[ j ][ i ];
}
int atx[ 6 ][ N ][ N ];
int aty[ 6 ][ N ][ N ];
int atz[ 6 ][ N ][ N ];
void go( int now , int msk ){
  if( now == 6 ) output();
  for( int _ = 0 ; _ < 2 ; _ ++ ){
    for( int _r = 0 ; _r < 4 ; _r ++ ){
      for( int at = 0 ; at < 6 ; at ++ ){
        if( (msk >> at) & 1 ) continue;
          
        for( int dx = -1 ; dx <= 1 ; dx ++ )
          for( int dy = -1 ; dy <= 1 ; dy ++ ){
            bool ok = true;
            for( int i = 0 ; i < n and ok ; i ++ )
              for( int j = 0 ; j < n and ok ; j ++ ){
                int ati = i + dx;
                int atj = j + dy;
                if( 1 <= ati and ati + 1 < n and
                    1 <= atj and atj + 1 < n and
                    c[ now ][ i ][ j ] == '.' )
                  ok = false;
                if( ( ati < 0 or ati >= n or
                      atj < 0 or atj >= n ) and
                    c[ now ][ i ][ j ] != '.' )
                  ok = false;
              }
            if( not ok ) continue;
            for( int i = 0 ; i < n and ok ; i ++ )
              for( int j = 0 ; j < n and ok ; j ++ ){
                if( c[ now ][ i ][ j ] == '.' ) continue;
                int ati = i + dx;
                int atj = j + dy;
                int px = atx[ at ][ ati ][ atj ];
                int py = aty[ at ][ ati ][ atj ];
                int pz = atz[ at ][ ati ][ atj ];
                if( ans[ px ][ py ][ pz ] )
                  ok = false;
              }
            if( not ok ) continue;
            for( int i = 0 ; i < n and ok ; i ++ )
              for( int j = 0 ; j < n and ok ; j ++ ){
                if( c[ now ][ i ][ j ] == '.' ) continue;
                int ati = i + dx;
                int atj = j + dy;
                int px = atx[ at ][ ati ][ atj ];
                int py = aty[ at ][ ati ][ atj ];
                int pz = atz[ at ][ ati ][ atj ];
                ans[ px ][ py ][ pz ] = now + 1;
              }
            go( now + 1 , msk | (1 << at) );
            for( int i = 0 ; i < n and ok ; i ++ )
              for( int j = 0 ; j < n and ok ; j ++ ){
                if( c[ now ][ i ][ j ] == '.' ) continue;
                int ati = i + dx;
                int atj = j + dy;
                int px = atx[ at ][ ati ][ atj ];
                int py = aty[ at ][ ati ][ atj ];
                int pz = atz[ at ][ ati ][ atj ];
                ans[ px ][ py ][ pz ] = 0;
              }
          }
      }
      rotate( now );
    }
    reflect( now );
  }
}
void solve(){
  go( 0 , 0 );
}
int main(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < 6 ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      scanf( "%s" , c[ i ][ j ] );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ ){
      {
        atx[ 0 ][ i ][ j ] = 0;
        aty[ 0 ][ i ][ j ] = i;
        atz[ 0 ][ i ][ j ] = j;
      }
      {
        atx[ 1 ][ i ][ j ] = n - 1;
        aty[ 1 ][ i ][ j ] = i;
        atz[ 1 ][ i ][ j ] = j;
      }
      {
        atx[ 2 ][ i ][ j ] = i;
        aty[ 2 ][ i ][ j ] = 0;
        atz[ 2 ][ i ][ j ] = j;
      }
      {
        atx[ 3 ][ i ][ j ] = i;
        aty[ 3 ][ i ][ j ] = n - 1;
        atz[ 3 ][ i ][ j ] = j;
      }
      {
        atx[ 4 ][ i ][ j ] = i;
        aty[ 4 ][ i ][ j ] = j;
        atz[ 4 ][ i ][ j ] = 0;
      }
      {
        atx[ 5 ][ i ][ j ] = i;
        aty[ 5 ][ i ][ j ] = j;
        atz[ 5 ][ i ][ j ] = n - 1;
      }
    }
  solve();
}
