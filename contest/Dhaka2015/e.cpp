#include <bits/stdc++.h>
//#pragma GCC optimize("O3")
using namespace std;
typedef long long LL;
#define N 20000001
LL sum[ N + N ] , mp[ N + N ];
bool np[ N + N ] , got[ N + N ];
void build(){
  got[ 1 ] = true;
  sum[ 1 ] = 1;
  for( LL i = 2 ; i < N ; i ++ ) if( !np[ i ] ){
    sum[ i ] = i + 1;
    got[ i ] = true;
    for( LL j = i + i ; j < N ; j += i ){
      mp[ j ] = i;
      np[ j ] = true;
    }
  }
  for( int i = 2 ; i < N ; i ++ )
    if( !np[ i ] )
      sum[ i ] = i + 1;
    else{
      LL pp = mp[ i ] , tmp = i , p2 = mp[ i ];
      while( tmp % pp == 0 ){
        tmp /= pp;
        p2 *= pp;
      }
      sum[ i ] = ( p2 - 1 ) * sum[ tmp ];
      sum[ i ] /= ( pp - 1 );
    }
  for( int i = 3 ; i < N ; i ++ )
    sum[ i ] += sum[ i - 1 ];
}
int main(){
  build();
  int n;
  //puts( "done" );
  while( scanf( "%d" , &n ) == 1 && n )
    printf( "%lld\n" , sum[ n ] );
}
