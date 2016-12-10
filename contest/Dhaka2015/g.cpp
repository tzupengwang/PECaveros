#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , x[ N ] , y[ N ];
int minx , maxx;
int miny , maxy;
int minxy , maxxy;
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d%d" , &x[ i ] , &y[ i ] );
  minx = maxx = x[ 0 ];
  miny = maxy = y[ 0 ];
  minxy = maxxy = x[ 0 ] + y[ 0 ];
  for( int i = 1 ; i < n ; i ++ ){
    minx = min( minx , x[ i ] );
    maxx = max( maxx , x[ i ] );
    miny = min( miny , y[ i ] );
    maxy = max( maxy , y[ i ] );
    minxy = min( minxy , x[ i ] + y[ i ] );
    maxxy = max( maxxy , x[ i ] + y[ i ] );
  }
}
typedef long long LL;
int id;
bool okay( LL a ){
  for( LL X = -100000 ; X <= 100000 ; X ++ ){
    if( X < maxx || X - 2 * a > minx ) continue;
    //if( X != 0 ) continue;
    LL ry = miny , ly = maxy - 2 * a;
    //printf( "%lld %lld\n" ,ly , ry );
    ly = max( ly , maxxy - X - a );
    ry = min( ry , minxy - X + a );
    //printf( "%lld %lld\n" ,ly , ry );
    if( ly > ry ) continue;
    return true;
  }
  return false;
}
void solve(){
  LL bl = 0 , br = 1000000 , ans = 0;
  //okay( 1 );
  while( bl <= br ){
    LL mid = ( bl + br ) >> 1;
    if( okay( mid ) )
      ans = mid , br = mid - 1;
    else
      bl = mid + 1;
  }
  //printf( "%lld\n" , ans );
  long long fans = ( ans + 1 ) * ans * 3 + 1;
  printf( "Case %d: %lld\n" , ++ id , fans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
