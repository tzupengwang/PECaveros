#include <bits/stdc++.h>
using namespace std;
#define N 1021
typedef long long LL;
LL n , m , d , res;
LL a[ N ] , b[ N ] , c[ N ];
bool flg[ N ];
void solve(){
  LL k = m % d;
  while( k < n ) k += d;
  res = ( m - k ) / d;
  LL who = res % n;
  for( LL i = 0 ; i < n ; i ++ )
    b[ i ] = a[ i ] = 1;
  b[ who ] = a[ who ] = k - ( n - 1 );
  LL p = 1;
  while( p * d < n ) p ++;
  LL tms = res / p , xxx = 0;
  while( !flg[ who ] && tms > 0 ){
    tms --; xxx ++;
    flg[ who ] = true;
    who = ( who - p + n ) % n;
    for( LL i = 0 ; i < n ; i ++ )
      b[ i ] += 1;
    b[ who ] += p * d - n;
  }
  if( tms > 0 ){
    LL multi = tms / xxx;
    tms %= xxx;
    for( LL i = 0 ; i < n ; i ++ )
      c[ i ] = b[ i ] - a[ i ];
    for( LL i = 0 ; i < n ; i ++ )
      b[ i ] += c[ i ] * multi;
    while( tms > 0 ){
      tms --;
      who = ( who - p + n ) % n;
      for( LL i = 0 ; i < n ; i ++ )
        b[ i ] += 1;
      b[ who ] += p * d - n;
    }
  }
  for( LL i = 0 ; i < n ; i ++ )
    printf( "%lld%c" , b[ i ] , " \n"[ i + 1 == n ] );
}
int main(){
  freopen( "coins.in" , "r" , stdin );
  freopen( "coins.out" , "w" , stdout );
  scanf( "%lld%lld%lld" , &n , &m , &d );
  solve();
}
