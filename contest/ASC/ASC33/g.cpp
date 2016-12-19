#include <bits/stdc++.h>
using namespace std;
vector< int > ans1[ 4 ][ 4 ][ 4 ];
vector< int > ans2[ 4 ][ 4 ][ 4 ];
int main(){
  freopen( "nimfor3.in" , "r" , stdin );
  freopen( "nimfor3.out" , "w" , stdout );
  ans1[ 0 ][ 0 ][ 0 ] = { 1 , 1 , 2 };
  ans2[ 0 ][ 0 ][ 0 ] = { 1 };
  ans1[ 0 ][ 0 ][ 1 ] = { 1 };
  ans2[ 0 ][ 0 ][ 1 ] = { 1 };
  ans1[ 0 ][ 0 ][ 3 ] = { 1 };
  ans2[ 0 ][ 0 ][ 3 ] = { 2 };
  
  ans1[ 0 ][ 1 ][ 0 ] = { 2 };
  ans2[ 0 ][ 1 ][ 0 ] = { 1 , 1 };
  ans1[ 0 ][ 1 ][ 2 ] = { 1 };
  ans2[ 0 ][ 1 ][ 2 ] = { 1 , 1 };
  ans1[ 0 ][ 1 ][ 3 ] = { 1 , 1 , 2 };
  ans2[ 0 ][ 1 ][ 3 ] = { 1 , 1 };

  ans1[ 0 ][ 2 ][ 0 ] = { 1 };
  ans2[ 0 ][ 2 ][ 0 ] = { 1 , 1 , 1 };
  ans1[ 0 ][ 3 ][ 0 ] = { 1 };
  ans2[ 0 ][ 3 ][ 0 ] = { 1 , 2 };
  ans1[ 0 ][ 3 ][ 3 ] = { 2 };
  ans2[ 0 ][ 3 ][ 3 ] = { 1 , 2 };

  ans1[ 1 ][ 1 ][ 0 ] = { 1 , 1 };
  ans2[ 1 ][ 1 ][ 0 ] = { 1 , 1 };

  ans1[ 1 ][ 2 ][ 1 ] = { 1 , 1 };
  ans2[ 1 ][ 2 ][ 1 ] = { 1 , 1 , 1 };
  
  ans1[ 1 ][ 3 ][ 0 ] = { 1 , 1 };
  ans2[ 1 ][ 3 ][ 0 ] = { 1 , 2 };
  ans1[ 1 ][ 3 ][ 3 ] = { 1 , 1 };
  ans2[ 1 ][ 3 ][ 3 ] = { 5 , 5 };
  
  ans1[ 2 ][ 2 ][ 2 ] = { 0 };
  ans2[ 2 ][ 2 ][ 2 ] = { 0 };

  ans1[ 2 ][ 3 ][ 3 ] = { 0 };
  ans2[ 2 ][ 3 ][ 3 ] = { 1 , 2 };

  ans1[ 3 ][ 3 ][ 3 ] = { 5 , 5 };
  ans2[ 3 ][ 3 ][ 3 ] = { 5 , 5 };

  for( int i = 0 ; i < 4 ; i ++ )
    for( int j = 0 ; j < 4 ; j ++ )
      for( int k = 0 ; k < 4 ; k ++ )
        if( ans1[ i ][ j ][ k ].size() && ans1[ j ][ i ][ k ].empty() ){
          ans1[ j ][ i ][ k ] = ans2[ i ][ j ][ k ];
          ans2[ j ][ i ][ k ] = ans1[ i ][ j ][ k ];
        }

  char c[ 9 ]; scanf( "%s" , c );
  int vl[ 9 ];
  for( int i = 0 ; i < 3 ; i ++ )
    vl[ i ] = c[ i ] - 'N';
  if( ans1[ vl[ 0 ] ][ vl[ 1 ] ][ vl[ 2 ] ].empty() )
    puts( "NO" );
  else{
    puts( "YES" );
    for( size_t i = 0 ; i < ans1[ vl[ 0 ] ][ vl[ 1 ] ][ vl[ 2 ] ].size() ; i ++ )
      printf( "%d%c" , ans1[ vl[ 0 ] ][ vl[ 1 ] ][ vl[ 2 ] ][ i ] , 
              " \n"[ i + 1 == ans1[ vl[ 0 ] ][ vl[ 1 ] ][ vl[ 2 ] ].size() ] );
    for( size_t i = 0 ; i < ans2[ vl[ 0 ] ][ vl[ 1 ] ][ vl[ 2 ] ].size() ; i ++ )
      printf( "%d%c" , ans2[ vl[ 0 ] ][ vl[ 1 ] ][ vl[ 2 ] ][ i ] , 
              " \n"[ i + 1 == ans2[ vl[ 0 ] ][ vl[ 1 ] ][ vl[ 2 ] ].size() ] );
  }
}
