#include <bits/stdc++.h>
using namespace std;
#define N 99
#define WHITE 0
#define GREEN 1
#define YELLOW 2
#define BLUE 3
#define RED 4
int clr[ N ][ N ] , l[ N ] , w[ N ];
int color( int x , int y ){
  if( x > 8 ) x = 8 - ( x - 8 );
  if( y > 8 ) y = 8 - ( y - 8 );
  if( x > y ) swap( x , y );
  if( x == 1 and y == 1 ) return RED;
  if( x == 1 and y == 8 ) return RED;
  if( x == 1 and y == 15 ) return RED;

  if( x == 1 and y == 4 ) return GREEN;
  if( x == 1 and y == 12 ) return GREEN;
  if( x == 3 and y == 7 ) return GREEN;
  if( x == 3 and y == 9 ) return GREEN;
  if( x == 4 and y == 8 ) return GREEN;
  if( x == 7 and y == 7 ) return GREEN;
  if( x == 7 and y == 9 ) return GREEN;

  if( x == 2 and y == 6 ) return YELLOW;
  if( x == 2 and y == 10 ) return YELLOW;

  if( x == 2 and y == 2 ) return BLUE;
  if( x == 3 and y == 3 ) return BLUE;
  if( x == 4 and y == 4 ) return BLUE;
  if( x == 5 and y == 5 ) return BLUE;
  if( x == 2 and y == 14 ) return BLUE;
  if( x == 3 and y == 13 ) return BLUE;
  if( x == 4 and y == 12 ) return BLUE;
  if( x == 5 and y == 11 ) return BLUE;

  return WHITE;
}
int word[ 99 ];
void build(){
word[1]=1;
word[2]=3;
word[3]=2;
word[4]=3;
word[5]=2;
word[6]=1;
word[7]=5;
word[8]=5;
word[9]=1;
word[10]=2;
word[11]=2;
word[12]=2;
word[13]=2;
word[14]=1;
word[15]=1;
word[16]=2;
word[17]=2;
word[18]=2;
word[19]=2;
word[20]=3;
word[21]=10;
word[22]=5;
word[23]=10;
word[24]=5;
word[25]=10;
word[26]=10;
word[27]=10;
word[28]=5;
word[29]=5;
word[30]=10;
word[31]=10;
word[32]=3;
  l[ WHITE ] = 1;  w[ WHITE ] = 1;
  l[ GREEN ] = 2;  w[ GREEN ] = 1;
  l[ YELLOW ] = 3; w[ YELLOW ] = 1;
  l[ BLUE ] = 1;   w[ BLUE ] = 2;
  l[ RED ] = 1;    w[ RED ] = 3;
  for( int i = 1 ; i <= 15 ; i ++ )
    for( int j = 1 ; j <= 15 ; j ++ )
      clr[ i ][ j ] = color( i , j );
  
  //for( int i = 1 ; i <= 15 ; i ++ , puts( "" ) )
    //for( int j = 1 ; j <= 15 ; j ++ )
      //printf( "%d " , clr[ i ][ j ] );
}
typedef long long LL;
LL sc[ 5 ];
int n , m;
bool oc[ N ][ N ];
int main(){
  build();
  cin >> n >> m;
  for( int i = 0 ; i < m ; i ++ ){
    int ww; cin >> ww;
    int usd = 0;
    while( ww -- ){
      int ll; cin >> ll;
      string way; cin >> way;
      int nx , ny; cin >> nx >> ny;
      swap( nx , ny );
      LL totsc = 0 , mul = 1;
      int dx = 1 , dy = 0 , dump;
      if( way[ 0 ] == 'h' ) dx = 0 , dy = 1;
      for( int j = 0 ; j < ll ; j ++ ){
        cin >> dump;
        totsc += word[ dump ] * l[ clr[ nx ][ ny ] ];
        mul *= w[ clr[ nx ][ ny ] ];
        if( !oc[ nx ][ ny ] ){
          oc[ nx ][ ny ] = true;
          usd ++;
        }
        nx += dx;
        ny += dy;
      }
      //cout << totsc << " " << mul << endl;
      sc[ i % n ] += totsc * mul;
    }
    if( usd == 7 )
      sc[ i % n ] += 15;
  }
  //for( int i = 1 ; i <= 15 ; i ++ , puts( "" ) )
    //for( int j = 1 ; j <= 15 ; j ++ )
      //printf( "%d" , oc[ i ][ j ] );
  for( int i = 0 ; i < n ; i ++ )
    cout << sc[ i ] << endl;
}
