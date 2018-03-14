#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL a[ 3 ] , w[ 2 ];
bool fit( LL x , LL y ){
  return x <= w[ 0 ] and y <= w[ 1 ];
}
bool go(){
  if( fit( a[ 0 ] + a[ 0 ] + a[ 2 ] + a[ 2 ] ,
           a[ 1 ] + a[ 2 ] + a[ 2 ] ) )
    return true;
  if( fit( a[ 0 ] + a[ 1 ] + a[ 2 ] ,
           a[ 0 ] + a[ 1 ] + a[ 2 ] + a[ 2 ] ) )
    return true;
  if( fit( a[ 0 ] + a[ 1 ] + a[ 2 ] ,
           a[ 0 ] + a[ 0 ] + a[ 1 ] + a[ 1 ] ) )
    return true;
  if( fit( a[ 0 ] + a[ 2 ] ,
           a[ 0 ] + a[ 1 ] + a[ 1 ] + a[ 1 ] + a[ 2 ] ) )
    return true;
  return false;
}
int main(){
  for( int i = 0 ; i < 3 ; i ++ )
    cin >> a[ i ];
  for( int i = 0 ; i < 2 ; i ++ )
    cin >> w[ i ];
  sort( a , a + 3 );
  do{
    sort( w , w + 2 );
    do{
      if( go() ){
        puts( "Yes" );
        exit(0);
      }
    }while( next_permutation( w , w + 2 ) );
  }while( next_permutation( a , a + 3 ) );
  puts( "No" );
}
