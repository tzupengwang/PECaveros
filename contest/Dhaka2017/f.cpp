#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL e , p , k , r;
int cs;
inline LL cal(){
  if( p * k >= e ){
    LL bl = 1 , br = k , ba = k;
    while( bl <= br ){
      LL bmid = (bl + br) >> 1;
      if( p * bmid >= e )
        ba = bmid , br = bmid - 1;
      else
        bl = bmid + 1;
    }
    return ba;
  }
  if( p * k <= r ) return -1;
  LL one_time = p * k - r;
  LL nd = (e - p * k) / one_time;
  if( e - nd * one_time > p * k ) nd ++;
  LL ret = nd * k;
  e -= nd * one_time;
  assert( p * k >= e );
  LL bl = 1 , br = k , ba = k;
  while( bl <= br ){
    LL bmid = (bl + br) >> 1;
    if( p * bmid >= e )
      ba = bmid , br = bmid - 1;
    else
      bl = bmid + 1;
  }
  return ret + ba;
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    scanf( "%lld%lld%lld%lld" , &e , &p , &k , &r );
    printf( "Case %d: %lld\n" , ++ cs , cal() );
  }
}
