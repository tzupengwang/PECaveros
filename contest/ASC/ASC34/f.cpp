#include <bits/stdc++.h>
using namespace std;
#define N 55
int n , m , sg[ N ][ N ];
char c[ N ][ N ];
void pre(){
  sg[ 0 ][ 0 ] = 1;
  for( int i = 0 ; i < N ; i ++ )
    for( int j = 0 ; j < N ; j ++ ){
      if( i == 0 && j == 0 ) continue;
      set< int > S;
      S.insert( 0 );
      for( int jj = 0 ; jj < j ; jj ++ )
        S.insert( sg[ i ][ jj ] );
      for( int ii = 0 ; ii < i ; ii ++ )
        S.insert( sg[ ii ][ j ] );
      for( int ii = 0 ; ii < i ; ii ++ )
        for( int jj = 0 ; jj < j ; jj ++ )
          S.insert( sg[ ii ][ jj ] ^
                    sg[ ii ][ j ] ^
                    sg[ i ][ jj ] );
      while( S.count( sg[ i ][ j ] ) )
        sg[ i ][ j ] ++;
    }
}
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%s" , c[ i ] );
}
void solve(){
  int st = 0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < m ; j ++ )
      if( c[ i ][ j ] == '1' )
        st ^= sg[ i ][ j ];
  if( st ){
    puts( "Ann" );
    for( int i = 0 ; i < n ; i ++ )
      for( int j = 0 ; j < m ; j ++ )
        if( c[ i ][ j ] == '1' ){
          int tst = st ^ sg[ i ][ j ];
          if( tst == 0 ){
            printf( "%d %d\n" , i + 1 , j + 1 );
            puts( "0 0" );
            exit( 0 );
          }
          for( int ii = 0 ; ii < i ; ii ++ ){
            if( ( tst ^ sg[ ii ][ j ] ) == 0 ){
              printf( "%d %d\n" , i + 1 , j + 1 );
              printf( "%d %d\n" , ii + 1 , 0 );
              exit( 0 );
            }
          }
          for( int jj = 0 ; jj < j ; jj ++ ){
            if( ( tst ^ sg[ i ][ jj ] ) == 0 ){
              printf( "%d %d\n" , i + 1 , j + 1 );
              printf( "%d %d\n" , 0 , jj + 1 );
              exit( 0 );
            }
          }
          for( int ii = 0 ; ii < i ; ii ++ )
            for( int jj = 0 ; jj < j ; jj ++ )
              if( ( tst ^ sg[ ii ][ jj ] ^ sg[ ii ][ j ] ^ sg[ i ][ jj ] ) == 0 ){
                printf( "%d %d\n" , i + 1 , j + 1 );
                printf( "%d %d\n" , ii + 1 , jj + 1 );
                exit( 0 );
              }
        }
    assert( false );
  }else{
    puts( "Betty" );
  }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "coins.in" , "r" , stdin );
  freopen( "coins.out" , "w" , stdout );
#endif
  pre();
  init();
  solve();
}
