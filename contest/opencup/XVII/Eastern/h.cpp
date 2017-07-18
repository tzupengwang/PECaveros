#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10000001
int p[ N ];
LL c[ N ] , d[ N ];
void build(){
  for( LL i = 2 ; i < N ; i ++ ){
    d[ i ] = d[ i - 1 ];
    if( ( d[ i ] + 1 ) * ( d[ i ] + 1 ) <= i ) d[ i ] ++;
    if( !p[ i ] ){
      for( LL j = i ; i * j < N ; j ++ ){
        if( c[ i * j ] == 0 )
          c[ i * j ] = i;
        p[ i * j ] = 1;
      }
    }
  }
  for( LL i = 2 ; i < N ; i ++ ){
    if( !p[ i ] )
      c[ i ] = max( d[ i ] - 1 , 0LL );
    else
      c[ i ] -= 1;
    c[ i ] += c[ i - 1 ];
    p[ i ] += p[ i - 1 ];
  }
}
int main(){
  build();
  int t; scanf( "%d" , &t ); while( t -- ){
    int n; scanf( "%d" , &n );
    LL up = c[ n ];
    LL dn = n - 1 - p[ n ];
    LL g = __gcd( up , dn );
    printf( "%lld/%lld\n" , up / g , dn / g );
  }
}
