#include <bits/stdc++.h>
using namespace std;
char c[ 3 ][ 9 ];
void input(){
  int x = 0;
  for( int i = 0 ; i < 3 ; i ++ ){
    scanf( "%s" , c[ i ] );
    for( int j = 0 ; j < 3 ; j ++ )
      x += c[ i ][ j ] == 'x';
  }
  if( x == 9 ) exit(0);
}
void output(){
  for( int i = 0 ; i < 3 ; i ++ , puts( "" ) )
    for( int j = 0 ; j < 3 ; j ++ )
      putchar( c[ i ][ j ] );
  fflush( stdout );
}
int main(){
  while( true ){
    input(); // empty
    c[ 1 ][ 1 ] = 'x';
    output();
    int xx[ 8 ] = {0,0,1,2,2,2,1,0};
    int yy[ 8 ] = {1,0,0,0,1,2,2,2};
    input();
    if( c[ 0 ][ 1 ] == 'o' or
        c[ 1 ][ 0 ] == 'o' or
        c[ 1 ][ 2 ] == 'o' or 
        c[ 2 ][ 1 ] == 'o' ){
      // case1
      int nx[ 9 ] = {};
      int ny[ 9 ] = {};
      for( int i = 0 ; i < 8 ; i += 2 )
        if( c[ xx[ i ] ][ yy[ i ] ] == 'o' ){
          nx[ 0 ] = xx[ (i+2) % 8 ];
          ny[ 0 ] = yy[ (i+2) % 8 ];

          nx[ 1 ] = xx[ (i+6) % 8 ];
          ny[ 1 ] = yy[ (i+6) % 8 ];

          nx[ 2 ] = xx[ (i+3) % 8 ];
          ny[ 2 ] = yy[ (i+3) % 8 ];

          nx[ 3 ] = xx[ (i+1) % 8 ];
          ny[ 3 ] = yy[ (i+1) % 8 ];
          
          nx[ 4 ] = xx[ (i+7) % 8 ];
          ny[ 4 ] = yy[ (i+7) % 8 ];
          break;
        }
      c[ nx[ 0 ] ][ ny[ 0 ] ] = 'x';
      output();
      input();
      if( c[ nx[ 1 ] ][ ny[ 1 ] ] == '.' ){
        c[ nx[ 1 ] ][ ny[ 1 ] ] = 'x';
        output();
        continue;
      }
      c[ nx[ 2 ] ][ ny[ 2 ] ] = 'x';
      output();
      input();
      for( int i = 3 ; i <= 4 ; i ++ )
        if( c[ nx[ i ] ][ ny[ i ] ] == '.' ){
          c[ nx[ i ] ][ ny[ i ] ] = 'x';
          output();
          break;
        }
    }else{
      // case2
      int nx[ 9 ] = {};
      int ny[ 9 ] = {};
      for( int i = 1 ; i < 8 ; i += 2 )
        if( c[ xx[ i ] ][ yy[ i ] ] == 'o' ){
          nx[ 0 ] = xx[ ( i + 4 ) % 8 ];
          ny[ 0 ] = yy[ ( i + 4 ) % 8 ];

          nx[ 1 ] = xx[ ( i + 3 ) % 8 ];
          ny[ 1 ] = yy[ ( i + 3 ) % 8 ];

          nx[ 2 ] = xx[ ( i + 2 ) % 8 ];
          ny[ 2 ] = yy[ ( i + 2 ) % 8 ];
          
          nx[ 3 ] = xx[ ( i + 7 ) % 8 ];
          ny[ 3 ] = yy[ ( i + 7 ) % 8 ];

          nx[ 4 ] = xx[ ( i + 5 ) % 8 ];
          ny[ 4 ] = yy[ ( i + 5 ) % 8 ];

          nx[ 5 ] = xx[ ( i + 1 ) % 8 ];
          ny[ 5 ] = yy[ ( i + 1 ) % 8 ];
          
          nx[ 6 ] = xx[ ( i + 6 ) % 8 ];
          ny[ 6 ] = yy[ ( i + 6 ) % 8 ];
          break;
        }
      c[ nx[ 0 ] ][ ny[ 0 ] ] = 'x';
      output();
      input();
      for( int i = 1 ; i <= 4 ; i += 3 ){
        bool ok = true;
        for( int j = 0 ; j < 3 ; j ++ )
          if( c[ nx[ i + j ] ][ ny[ i + j ] ] != '.' )
            ok = false;
        if( not ok ) continue;
        c[ nx[ i ] ][ ny[ i ] ] = 'x';
        output();
        input();
        for( int j = 1 ; j < 3 ; j ++ )
          if( c[ nx[ i + j ] ][ ny[ i + j ] ] == '.' ){
            c[ nx[ i + j ] ][ ny[ i + j ] ] = 'x';
            output();
            break;
          }
        break;
      }
    }
  }
}
