#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1024
int n , m , f;
int dn[]={0,0,1,-1};
int dm[]={1,-1,0,0};
char cd[] = "GDPL";
char db[] = "><v^";
int dir[ N ][ N ];
int main(){
  scanf( "%d%d%d" , &n , &m , &f );
  for( int i = 2 ; i <= n ; i += 2 )
    for( int j = 1 ; j <= m ; j ++ )
      dir[ i ][ j ] = 1;
  for( int i = 1 ; i <= n ; i += 2 )
    dir[ i ][ m ] = 2;
  for( int i = 2 ; i <= n ; i ++ )
    dir[ i ][ 1 ] = 3;
  for( int i = 2 ; i < n ; i += 2 )
    dir[ i ][ 2 ] = 2;
  while( f -- ){
    int x , y;
    scanf( "%d%d" , &x , &y );
    if( y == 3 and (x & 1) == 0 ){
      dir[ x     ][ y - 1 ] = 1;
      dir[ x + 1 ][ y - 1 ] = 3;
      dir[ x + 1 ][ y - 2 ] = 0;
      dir[ x ][ y + 2 ] = 2;
    }else if( x & 1 ){
      dir[ x ][ y - 1 ] = 2;
      dir[ x + 1 ][ y + 2 ] = 3;
      dir[ x + 2 ][ y + 2 ] = 3;
      dir[ x + 1 ][ y + 3 ] = 2;
    }else{
      dir[ x ][ y + 2 ] = 2;
      dir[ x + 1 ][ y - 1 ] = 3;
      dir[ x + 2 ][ y - 1 ] = 3;
      dir[ x + 1 ][ y - 2 ] = 2;
    }
  }
  //for( int i = 1 ; i <= n ; i ++ , puts( "" ) )
    //for( int j = 1 ; j <= m ; j ++ )
      //putchar( db[ dir[ i ][ j ] ] );
  //return 0;
  int cn = 1 , cm = 1;
  puts( "TAK" );
  do{
    printf( "%c" , cd[ dir[ cn ][ cm ] ] );
    int nxtn = cn + dn[ dir[ cn ][ cm ] ];
    int nxtm = cm + dm[ dir[ cn ][ cm ] ];
    cn = nxtn;
    cm = nxtm;
  }while( cn != 1 or cm != 1 );
  puts( "" );
}
