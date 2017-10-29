#include <bits/stdc++.h>
using namespace std;
int sb[ 3 ][ 3 ] , my;
void put( int x , int y ){
  printf( "%d %d\n" , x + 1 , y + 1 );
  sb[ x ][ y ] = my;
  fflush( stdout );
}
char c[ 11 ];
void print(){
  for( int i = 0 ; i < 3 ; i ++ , puts( "" ) )
    for( int j = 0 ; j < 3 ; j ++ )
      fprintf( stderr , "%c" , ".OX"[ sb[ i ][ j ] ] );
}
int bs[ 3 ][ 3 ];
int hsvl(){
  int ret = 0;
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      ret += bs[ i ][ j ] * sb[ i ][ j ];
  return ret;
}
pair<int,int> read(){
  //print();
  scanf( "%s" , c );
  if( c[ 0 ] == 'W' or
      c[ 0 ] == 'D' ) exit(0);
  if( c[ 0 ] == 'L' )
    assert( false );
  int x , y;
  sscanf( c , "%d" , &x );
  scanf( "%d" , &y );
  x --; y --;
  sb[ x ][ y ] = 3 - my;
  return { x , y };
}
int board[ 3 ][ 3 ];
bool winn( int who ){
  for( int i = 0 ; i < 3 ; i ++ ){
    {
      int cnt = 0;
      for( int j = 0 ; j < 3 ; j ++ )
        cnt += ( board[ i ][ j ] == who );
      if( cnt == 3 ) return true;
    }
    {
      int cnt = 0;
      for( int j = 0 ; j < 3 ; j ++ )
        cnt += ( board[ j ][ i ] == who );
      if( cnt == 3 ) return true;
    }
  }
  {
    int cnt = 0;
    for( int i = 0 ; i < 3 ; i ++ )
      cnt += ( board[ i ][ i ] == who );
    if( cnt == 3 ) return true;
  }
  {
    int cnt = 0;
    for( int i = 0 ; i < 3 ; i ++ )
      cnt += ( board[ i ][ 3 - i - 1 ] == who );
    if( cnt == 3 ) return true;
  }
  return false;
}
int win[ 20202 ];
// 0 lose 1 draw 2 win
bool gt[ 20202 ];
pair<int,int> tnxt[ 20202 ];
int Win( int cur ){
  if( gt[ cur ] ) return win[ cur ];
  int pt = 0;
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ ){
      board[ i ][ j ] = ( cur / bs[ i ][ j ] ) % 3;
      pt += ( board[ i ][ j ] > 0 );
    }
  int face = (pt & 1) + 1;
  gt[ cur ] = true;
  if( winn( 3 - face ) ){
    return win[ cur ] = 0;
  }
  if( pt == 9 ){
    bool f1 = winn( face );
    bool f2 = winn( 3 - face );
    if( f1 and not f2 ) win[ cur ] = 2;
    else if( f2 and not f1 ) win[ cur ] = 0;
    else win[ cur ] = 1;
    return win[ cur ];
  }
  int tb[ 3 ][ 3 ];
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      tb[ i ][ j ] = board[ i ][ j ];
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ ){
      if( tb[ i ][ j ] ) continue;
      int nxt = cur + bs[ i ][ j ] * face;
      int nwin = Win( nxt );
      if( nwin == 2 ) continue;
      if( nwin == 0 ){
        win[ cur ] = 2;
        tnxt[ cur ] = { i , j };
        return win[ cur ];
      }
    }
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ ){
      if( tb[ i ][ j ] ) continue;
      int nxt = cur + bs[ i ][ j ] * face;
      int nwin = Win( nxt );
      if( nwin == 2 ) continue;
      if( nwin == 1 ){
        win[ cur ] = 1;
        tnxt[ cur ] = { i , j };
        return win[ cur ];
      }
    }
  return win[ cur ] = 0;
}
int main(){
  for( int i = 0 , tb = 1 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ ){
      bs[ i ][ j ] = tb;
      tb *= 3;
    }
  scanf( "%s" , c );
  if( c[ 0 ] == 'X' ) my = 1;
  else my = 2;
  for( int _ = 1 ; _ <= 9 ; _ ++ ){
    if( (_ & 1) == (my & 1) ){
      int vl = hsvl();
      if( Win( vl ) ){
        put( tnxt[ vl ].first ,
             tnxt[ vl ].second );
      }
    }else read();
  }
  //read();
}
