#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 102
char dp[ N ][ N ][ N ][ N ];
char odp[ N ][ N ][ N ][ N ];
const char cand[] = "ACGT";
int dgt( char ctmp ){
  for( int i = 0 ; i < 4 ; i ++ )
    if( ctmp == cand[ i ] )
      return i;
  assert( false );
  return -1;
}
#define INF 123
char s[ N ] , t[ N ];
int a[ N ] , n;
vector< int > in[ 4 ] , out[ 4 ];
void back( int now , int i , int j , int k );
void backi( int now , int i , int j , int k ){
  //printf( "i %d %d %d %d dp=%d\n" , now , i , j , k ,
          //dp[ now ][ i ][ j ][ k ] );
  if( now < 1 ) return;
  if( i - 1 >= 0 and i + j + k >= 1 and
      dp[ now ][ i ][ j ][ k ] ==
      dp[ now ][ i - 1 ][ j ][ k ] + 1 ){
    in[ 1 ].push_back( now );
    backi( now , i - 1 , j , k );
    return;
  }
  if( j - 1 >= 0 and i + j + k >= 1 and
      dp[ now ][ i ][ j ][ k ] ==
      dp[ now ][ i ][ j - 1 ][ k ] + 1 ){
    in[ 2 ].push_back( now );
    backi( now , i , j - 1 , k );
    return;
  }
  if( k - 1 >= 0 and i + j + k >= 1 and
      dp[ now ][ i ][ j ][ k ] ==
      dp[ now ][ i ][ j ][ k - 1 ] + 1 ){
    in[ 3 ].push_back( now );
    backi( now , i , j , k - 1 );
    return;
  }

  back( now - 1 , i , j , k );
}
void back( int now , int i , int j , int k ){
  //printf( "o %d %d %d %d dp=%d\n" , now , i , j , k ,
          //odp[ now ][ i ][ j ][ k ] );
  if( now < 1 ) return;
  if( i + 1 <= n and i + j + k < n and
      odp[ now ][ i + 1 ][ j ][ k ] ==
      odp[ now ][ i ][ j ][ k ] ){
    out[ 1 ].push_back( now );
    back( now , i + 1 , j , k );
    return;
  }
  if( j + 1 <= n and i + j + k < n and
      odp[ now ][ i ][ j + 1 ][ k ] ==
      odp[ now ][ i ][ j ][ k ] ){
    out[ 2 ].push_back( now );
    back( now , i , j + 1 , k );
    return;
  }
  if( k + 1 <= n and i + j + k < n and
      odp[ now ][ i ][ j ][ k ] ==
      odp[ now ][ i ][ j ][ k + 1 ] ){
    out[ 3 ].push_back( now );
    back( now , i , j , k + 1 );
    return;
  }

  backi( now , i , j , k ); 

}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "transform.in" , "r" , stdin );
  freopen( "transform.out" , "w" , stdout );
#endif
  scanf( "%s" , s );
  scanf( "%s" , t );
  n = strlen( s );
  for( int i = 0 ; i < n ; i ++ )
    a[ i + 1 ] = ( dgt( t[ i ] ) - dgt( s[ i ] ) + 4 ) % 4;
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; i + j <= n ; j ++ )
      for( int k = 0 ; i + j + k <= n ; k ++ )
        odp[ 0 ][ i ][ j ][ k ] = INF;
  odp[ 0 ][ 0 ][ 0 ][ 0 ] = 0;
  for( int now = 1 ; now <= n ; now ++ ){
    int pre = now - 1;
    for( int i = 0 ; i <= n ; i ++ )
      for( int j = 0 ; i + j <= n ; j ++ )
        for( int k = 0 ; i + j + k <= n ; k ++ )
          dp[ now ][ i ][ j ][ k ] = odp[ pre ][ i ][ j ][ k ];
    for( int i = 0 ; i <= n ; i ++ )
      for( int j = 0 ; i + j <= n ; j ++ )
        for( int k = 0 ; i + j + k <= n ; k ++ ){
          if( i )
            dp[ now ][ i ][ j ][ k ] = min( (int)dp[ now ][ i ][ j ][ k ] ,
                                            dp[ now ][ i - 1 ][ j ][ k ] + 1 );
          if( j )
            dp[ now ][ i ][ j ][ k ] = min( (int)dp[ now ][ i ][ j ][ k ] ,
                                            dp[ now ][ i ][ j - 1 ][ k ] + 1 );
          if( k )
            dp[ now ][ i ][ j ][ k ] = min( (int)dp[ now ][ i ][ j ][ k ] ,
                                            dp[ now ][ i ][ j ][ k - 1 ] + 1 );
        }
    for( int i = 0 ; i <= n ; i ++ )
      for( int j = 0 ; i + j <= n ; j ++ )
        for( int k = 0 ; i + j + k <= n ; k ++ ){
          int tmp = ( ( a[ now ] - i - j - j - k - k - k ) % 4 + 4 ) % 4;
          if( tmp )
            odp[ now ][ i ][ j ][ k ] = INF;
          else
            odp[ now ][ i ][ j ][ k ] = dp[ now ][ i ][ j ][ k ];
          //else
            //printf( "%d a=%d : %d %d %d : %d\n" , now , a[ now ] ,
                    //i , j , k , dp[ now ][ i ][ j ][ k ] );
        }
    for( int i = n ; i >= 0 ; i -- )
      for( int j = n - i ; j >= 0 ; j -- )
        for( int k = n - i - j ; k >= 0 ; k -- ){
          if( i + 1 <= n and i + j + k < n )
            odp[ now ][ i ][ j ][ k ] = min( odp[ now ][ i ][ j ][ k ],
                                            odp[ now ][ i + 1 ][ j ][ k ] );
          if( j + 1 <= n and i + j + k < n )
            odp[ now ][ i ][ j ][ k ] = min( odp[ now ][ i ][ j ][ k ],
                                            odp[ now ][ i ][ j + 1 ][ k ] );
          if( k + 1 <= n and i + j + k < n )
            odp[ now ][ i ][ j ][ k ] = min( odp[ now ][ i ][ j ][ k ],
                                            odp[ now ][ i ][ j ][ k + 1 ] );
        }
  }
  back( n , 0 , 0 , 0 );
  printf( "%d\n" , odp[ n ][ 0 ][ 0 ][ 0 ] );
  for( int i = 1 ; i < 4 ; i ++ ){
    assert( in[ i ].size() == out[ i ].size() );
    for( size_t j = 0 ; j < in[ i ].size() ; j ++ )
      printf( "%d %d %d\n" , in[ i ][ j ] , out[ i ][ j ] , i );
  }
}
