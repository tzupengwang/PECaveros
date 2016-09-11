#include <bits/stdc++.h>
using namespace std;
#define N 200
char dir[]="<>^v" , mp[ N ][ N ];
bool tag[ N ][ N ];
bool in( int xn , int xm ){
  return 1 <= xn && xn < N - 1 &&
         1 <= xm && xm < N - 1;
}
int cmd[ N ];
int dn[]={0,0,-1,1};
int dm[]={-1,1,0,0};
int icmd;
void go( int sn , int sm ){
  for( int _ = 0 ; _ < N ; _ ++ ){
    icmd = ( icmd + 1 ) % N;
    tag[ sn ][ sm ] = true;
    mp[ sn ][ sm ] = '.';
    int ii = cmd[ icmd ];
    int nxtn = sn + dn[ ii ];
    int nxtm = sm + dm[ ii ];
    int okay = rand() % 10;
    if( okay && in( nxtn , nxtm ) && !tag[ nxtn ][ nxtm ] ){
      go( nxtn , nxtm );
      // break;
    }
  }
}
int main(){
  srand( 514514 );
  printf( "%d\n" , N );
  for( int i = 0 ; i < N ; i ++ ){
    if( i == 0 ) putchar( '>' );
    else if( i == 1 ) putchar( 'v' );
    else putchar( dir[ i % 4 ] );
  }
  puts( "" );
  for( int i = 0 ; i < N ; i ++ )
    for( int j = 0 ; j < N ; j ++ )
      mp[ i ][ j ] = '#';
  int sn = 100 , sm = 100;
  icmd = N - 1;
  go( sn , sm );
  mp[ sn ][ sm ] = 'R';
  for( int i = 0 ; i < N ; i ++ )
    puts( mp[ i ] );
}
