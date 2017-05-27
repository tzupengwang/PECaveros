#include <bits/stdc++.h>
using namespace std;
#define N 1010101
typedef long long LL;
int n , m , x[ N ] , y[ N ];
LL ans;
int xay[ N + N ] , xsy[ N + N ];
int main(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d" , &x[ i ] , &y[ i ] );
    xay[ x[ i ] + y[ i ] ] = 1;
    xsy[ x[ i ] - y[ i ] + n ] = 1;
  }
  ans = (LL)n * n;
  for( int i = 2 ; i <= n + n ; i ++ )
    if( xay[ i ] ){
      int cc = min( i - 1 , n + n - i + 1 );
      ans -= cc;
    }
  for( int i = 3 ; i <= n + n ; i ++ )
    xay[ i ] += xay[ i - 2 ];
  for( int i = 1 ; i < n + n ; i ++ )
    if( xsy[ i ] ){
      int vl = i - n;
      int cc = n - abs( vl );
      ans -= cc;
      {
        int lftx = max( 1 , vl + 1 );
        int rgtx = min( n , vl + n );
        if( lftx <= rgtx ){
          int lfty = lftx - vl;
          int rgty = rgtx - vl;
          int lft = lftx + lfty;
          int rgt = rgtx + rgty;
          lft --;
          //printf( "%d %d\n" , lftx , lfty );
          //printf( "%d %d\n" , rgtx , rgty );
          while( lft % 2 != rgt % 2 ) lft --;
          //printf( "%d %d\n" , lft , rgt );
          ans += xay[ rgt ] - xay[ lft ];
        }
      }
    }
  printf( "%lld\n" , ans );
}
