#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL n , a[ N ] , sum , ans = -1;
void test( LL ai ){
  if( ai == 0 ) return;
  LL tsum = sum;
  if( tsum > 0 ){
    LL atmst = tsum / abs( ai );
    tsum -= atmst * abs( ai );
  }
  if( tsum < 0 ){
    LL atmst = abs( tsum ) / abs( ai );
    tsum += atmst * abs( ai );
  }
  for( LL dd = -5 ; dd <= 5 ; dd ++ ){
    LL cur = tsum + dd * ai;
    if( cur >= 0 and cur % 2 == 0 ){
      if( ans == -1 or cur < ans )
        ans = cur;
    }
  }
}
int main(){
  scanf( "%lld" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &a[ i ] );
  sum = accumulate( a , a + n , 0LL );
  if( sum >= 0 and sum % 2 == 0 )
    ans = sum;
  for( int i = 0 ; i < n ; i ++ )
    test( a[ i ] );
  printf( "%lld\n" , ans );
}
