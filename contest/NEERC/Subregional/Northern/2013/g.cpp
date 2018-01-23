#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL W , H , w , h;
int main(){
  freopen( "garage.in" , "r" , stdin );
  freopen( "garage.out" , "w" , stdout );
  scanf( "%lld%lld%lld%lld" , &W , &H , &w , &h );
  if( W < w || H < h ){
    puts( "0" );
    exit( 0 );
  }
  LL aw = 1 , ah = 1;
  while( ( aw * 2 + 1 ) * w <= W ) aw ++;
  while( ( ah * 2 + 1 ) * h <= H ) ah ++;
  printf( "%lld\n" , aw * ah );
}
