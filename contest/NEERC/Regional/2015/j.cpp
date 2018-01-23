#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
int n , qq;
char c[ N ] , ans[ N ];
int query(){
  assert( ++ qq <= n + 500 );
#ifdef EDDY
  int ret = 0;
  for( int i = 0 ; i < n ; i ++ )
    if( c[ i ] == ans[ i ] )
      ret ++;
  if( ret != n / 2 and ret != n )
    ret = 0;
#else
  puts( c );
  fflush( stdout );
  int ret; scanf( "%d" , &ret );
#endif
  if( ret == n ){
    //fprintf( stderr , "AC with %d\'s query\n" , qq );
    exit(0);
  }
  return ret;
}
bool same[ N ];
int main(){
  scanf( "%d" , &n );
#ifdef EDDY
  for( int i = 0 ; i < n ; i ++ )
    ans[ i ] = (rand() & 1) + '0';
#endif
  while( true ){
    for( int i = 0 ; i < n ; i ++ )
      c[ i ] = (rand() & 1) + '0';
    if( query() == n / 2 )
      break;
  }
  for( int i = 1 ; i < n ; i ++ ){
    c[ 0 ] = c[ 0 ] ^ 1;
    c[ i ] = c[ i ] ^ 1;
    int ret = query();
    if( ret == n / 2 ){
      if( c[ 0 ] == c[ i ] )
        same[ i ] = false;
      else
        same[ i ] = true;
    }else{
      if( c[ 0 ] == c[ i ] )
        same[ i ] = true;
      else
        same[ i ] = false;
    }
    c[ 0 ] = c[ 0 ] ^ 1;
    c[ i ] = c[ i ] ^ 1;
  }
  for( int i = 0 ; i < 2 ; i ++ ){
    c[ 0 ] = '0' + i;
    for( int j = 1 ; j < n ; j ++ )
      if( same[ j ] )
        c[ j ] = c[ 0 ];
      else
        c[ j ] = c[ 0 ] ^ 1;
    query();
  }
}
