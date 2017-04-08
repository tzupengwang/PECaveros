#include <bits/stdc++.h>
using namespace std;
#define N 111
char dgt[ 10 ][ 10 ][ 10 ] = {
{
".XXXXX..","XX..XXX.","XX.XXXX.","XXXX.XX.","XXX..XX.","XXX..XX.",".XXXXX..","........"
},
{
"...XX...","..XXX...",".XXXX...","...XX...","...XX...","...XX...",".XXXXXX.","........"
},
{
".XXXXX..","XX...XX.",".....XX.","...XXX..",".XXX....","XX......","XXXXXXX.","........"
},
{
".XXXXX..","XX...XX.",".....XX.","..XXXX..",".....XX.","XX...XX.",".XXXXX..","........"
},
{
"...XXX..","..XXXX..",".XX.XX..","XX..XX..","XXXXXXX.","....XX..","...XXXX.","........"
},
{
"XXXXXXX.","XX......","XXXXXX..",".....XX.",".....XX.","XX...XX.",".XXXXX..","........"
},
{
".XXXXX..","XX...XX.","XX......","XXXXXX..","XX...XX.","XX...XX.",".XXXXX..","........"
},
{
"XXXXXXX.","XX...XX.","X....XX.","....XX..","...XX...","..XX....","..XX....","........"
},
{
".XXXXX..","XX...XX.","XX...XX.",".XXXXX..","XX...XX.","XX...XX.",".XXXXX..","........"
},
{
".XXXXX..","XX...XX.","XX...XX.",".XXXXXX.",".....XX.","XX...XX.",".XXXXX..","........"
}
};
char c[ N ][ N ] , cc[ N ][ N ];
void init(){
  for( int i = 0 ; i < 12 ; i ++ )
    scanf( "%s" , c[ i ] );
}
bool in( int nx , int ny ){
  return 0 <= nx and nx < 12 and
         0 <= ny and ny < 60;
}
void write( int si , int sj , int dd ){
  for( int i = 0 ; i < 8 ; i ++ )
    for( int j = 0 ; j < 8 ; j ++ ){
      int ni = i + si;
      int nj = j + sj;
      if( not in( ni , nj ) ) continue;
      cc[ ni ][ nj ] = dgt[ dd ][ i ][ j ];
    }
}
void go( int st , int mm ){
  for( int i = 0 ; i < 12 ; i ++ )
    for( int j = 0 ; j < 60 ; j ++ )
      cc[ i ][ j ] = '.';
  for( int d = -60 ; d <= 60 ; d += 12 ){
    for( int i = 0 ; i < 2 ; i ++ )
      for( int j = 0 ; j < 2 ; j ++ ){
        int nj = st + d + j;
        if( in( i , nj ) )
          cc[ i ][ nj ] = 'X';
      }
    int who = mm - ( d / 12 );
    if( who <   0 ) who += 60;
    if( who >= 60 ) who -= 60;
    if( who % 5 ) continue;
    if( who <= 5 ){
      write( 3 , st + d - 3 , who );
    }else{
      write( 3 , st + d - 7 , who / 10 );
      write( 3 , st + d + 1 , who % 10 );
    }
  }
  //for( int i = 0 ; i < 12 ; i ++ )
    //puts( cc[ i ] );
  for( int i = 0 ; i < 12 ; i ++ )
    for( int j = 0 ; j < 60 ; j ++ ){
      if( c[ i ][ j ] == '-' ) continue;
      if( c[ i ][ j ] != cc[ i ][ j ] )
        return;
    }
  int ss = ( st - 29 ) * 5;
  printf( "%02d:%02d\n" , mm , ss );
  exit( 0 );
}
void solve(){
  int st = 100;
  for( int i = 29 ; i + 1 < 60 ; i ++ )
    if( c[ 0 ][ i ] == 'X' and c[ 0 ][ i + 1 ] == 'X' and
        c[ 1 ][ i ] == 'X' and c[ 1 ][ i + 1 ] == 'X' ){
      st = i;
      break;
    }
  for( int i = 0 ; i < 60 ; i ++ )
    go( st , i );
}
int main(){
  init();
  solve();
}
