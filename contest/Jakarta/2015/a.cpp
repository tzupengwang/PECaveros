#include <bits/stdc++.h>
using namespace std;
int a[ 4 ];
void init(){
  for( int i = 0 ; i < 4 ; i ++ )
    scanf( "%d" , &a[ i ] );
}
int _cs;
char op( int x ){
  if( x == 0 ) return '=';
  if( x == 1 ) return '+';
  if( x == 2 ) return '-';
  return 0;
}
bool okay( int x , int y , int z ){
  vector< int > vv;
  int u[ 3 ] = { x , y , z };
  int now = -1;
  for( int i = 0 ; i < 4 ; i ++ ){
    if( i && u[ i - 1 ] == 0 ){
      vv.push_back( now );
      now = -1;
    }
    if( now == -1 ) now = a[ i ];
    else if( i && u[ i - 1 ] == 1 ){
      now += a[ i ];
    }else if( i && u[ i - 1 ] == 2 ){
      now -= a[ i ];
    }
  }
  vv.push_back( now );
  int xx = now;
  for( int uu : vv )
    if( uu != xx )
      return false;
  return true;
}
void solve(){
  for( int i = 0 ; i < 3 ; i ++ )
    for( int j = 0 ; j < 3 ; j ++ )
      for( int k = 0 ; k < 3 ; k ++ ){
        if( i && j && k ) continue;
        if( okay( i , j , k ) ){
          printf( "Case #%d: %d %c %d %c %d %c %d\n" , ++ _cs ,
                  a[ 0 ] , op( i ) ,
                  a[ 1 ] , op( j ) ,
                  a[ 2 ] , op( k ) ,
                  a[ 3 ] );
          return;
        }
      }
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
