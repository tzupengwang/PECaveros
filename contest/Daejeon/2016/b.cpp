#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , a[ N ];
inline int C2( int x ){
  return x * ( x - 1 ) / 2;
}
int main(){
  while( scanf( "%d" , &n ) == 1 ){
    for( int i = 0 ; i < n ; i ++ )
      scanf( "%d" , &a[ i ] );
    sort( a , a + n );
    bool ok = true;
    for( int i = 0 , sum = 0 ; i < n and ok ; i ++ ){
      sum += a[ i ];
      if( sum < C2( i + 1 ) )
        ok = false;
      if( i + 1 == n and sum != C2( n ) )
        ok = false;
    }
    puts( ok ? "1" : "-1" );
  }
}
