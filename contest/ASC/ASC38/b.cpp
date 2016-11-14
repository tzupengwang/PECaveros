#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n , m;
bool okay( LL x ){
  LL res = n;
  for( LL i = 1 ; i <= m && res > 0 ; i ++ )
    res -= x / i;
  return res <= 0;
}
int main(){
  freopen( "bigset.in" , "r" , stdin );
  freopen( "bigset.out" , "w" , stdout );
  scanf( "%lld%lld" , &n , &m );
  LL bl = 1 , br = n , mid , ans = n;
  while( bl <= br ){
    mid = ( bl + br ) >> 1;
    if( okay( mid ) ) ans = mid , br = mid - 1;
    else bl = mid + 1;
  }
  printf( "%lld\n" , ans );
}
