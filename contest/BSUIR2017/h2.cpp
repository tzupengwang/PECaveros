#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
char s[ N ] , t[ N ];
int k , lens , lent , same[ N ][ N ];
inline void better( int& x , int y ){
  if( x < 0 or y < x ) x = y;
}
int dp[ N ][ N ][ N ][ 2 ];
int go( int i , int j , int l , int who ){
  //printf( "%d %d %d %d\n" , i , j , l , who );
  if( i == lens and j == lent and l >= k ) return 0;
  if( i == lens and j == lent and l == 0 ) return 0;
  if( dp[ i ][ j ][ l ][ who ] ) return dp[ i ][ j ][ l ][ who ];
  int ret = -1;
  if( l == 0 or who == 0 ){
    for( int ii = max( i + 1 , k + i - l ) ; ii <= lens ; ii ++ ){
      for( int jj = j ; jj <= lent and jj - j <= ii - i ; jj ++ ){
        if( same[ ii - ( jj - j ) + 1 ][ j + 1 ] >= jj - j ){
          int tret = go( ii , jj , min( k , jj - j ) , 1 );
          if( tret == -1 ) continue;
          better( ret , tret + ii - i );
        }
      }
    }
  }
  if( l == 0 or who == 1 ){
    for( int jj = max( j + 1 , k + j - l ) ; jj <= lent ; jj ++ ){
      for( int ii = i ; ii <= lens and ii - i <= jj - j ; ii ++ ){
        if( same[ i + 1 ][ jj - ( ii - i ) + 1 ] >= ii - i ){
          int tret = go( ii , jj , min( k , ii - i ) , 0 );
          if( tret == -1 ) continue;
          better( ret , tret + jj - j );
        }
      }
    }
  }
  return dp[ i ][ j ][ l ][ who ] = ret;
}
int main(){
  scanf( "%d" , &k );
  scanf( "%s" , s + 1 );
  lens = strlen( s + 1 );
  scanf( "%s" , t + 1 );
  lent = strlen( t + 1 );
  for( int i = lens ; i ; i -- )
    for( int j = lent ; j ; j -- )
      if( s[ i ] == t[ j ] )
        same[ i ][ j ] = 1 + same[ i + 1 ][ j + 1 ];
  //memset( dp , -1 , sizeof dp );
  //dp[ 0 ][ 0 ][ 0 ][ 0 ] = 0;
  int ans = go( 0 , 0 , 0 , 0 );
  //for( int i = 0 ; i <= lens ; i ++ )
    //for( int j = 0 ; j <= lent ; j ++ )
      //for( int l = 0 ; l <= min( k , max( i , j ) ) ; l ++ )
        //for( int who = 0 ; who < 2 ; who ++ ){
          //if( dp[ i ][ j ][ l ][ who ] < 0 ) continue;
          //if( l == 0 or who == 0 ){
            //for( int ii = max( i + 1 , k + i - l ) ; ii <= lens ; ii ++ ){
              //for( int jj = j ; jj <= lent and jj - j <= ii - i ; jj ++ ){
                //if( same[ ii - ( jj - j ) + 1 ][ j + 1 ] >= jj - j )
                  //better( dp[ ii ][ jj ][ min( k , jj - j ) ][ 1 ] ,
                          //dp[ i ][ j ][ l ][ who ] + ii - i );
              //}
            //}
          //}
          //if( l == 0 or who == 1 ){
            //for( int jj = max( j + 1 , k + j - l ) ; jj <= lent ; jj ++ ){
              //for( int ii = i ; ii <= lens and ii - i <= jj - j ; ii ++ ){
                //if( same[ i + 1 ][ jj - ( ii - i ) + 1 ] >= ii - i )
                  //better( dp[ ii ][ jj ][ min( k , ii - i ) ][ 0 ] ,
                          //dp[ i ][ j ][ l ][ who ] + jj - j );
              //}
            //}
          //}
        //}
  //int ans = -1;
  //if( dp[ lens ][ lent ][ k ][ 0 ] >= 0 )
    //better( ans , dp[ lens ][ lent ][ k ][ 0 ] );
  //if( dp[ lens ][ lent ][ k ][ 1 ] >= 0 )
    //better( ans , dp[ lens ][ lent ][ k ][ 1 ] );
  //if( dp[ lens ][ lent ][ 0 ][ 0 ] >= 0 )
    //better( ans , dp[ lens ][ lent ][ 0 ][ 0 ] );
  //if( dp[ lens ][ lent ][ 0 ][ 1 ] >= 0 )
    //better( ans , dp[ lens ][ lent ][ 0 ][ 1 ] );
  printf( "%d\n" , ans );
}
