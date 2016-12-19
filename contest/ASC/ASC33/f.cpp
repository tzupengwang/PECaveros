#include <bits/stdc++.h>
using namespace std;
int n;
typedef long long LL;
void solve(){
  LL ret = 2e9;
  while( n -- ){
    LL x , y;
    scanf( "%lld%lld" , &x , &y );
    LL dlt = min( x / 3 , y / 3 );
    dlt = max( 0ll , dlt - 2 );
    LL cnt = dlt * 2;
    x -= 3 * dlt;
    y -= 3 * dlt;
    for( int i = 0 ; ; i = 1 - i )
      if( i == 0 ){
        if( x >= 2 && y >= 1 ){
          x -= 2; y --;
          cnt ++;
        }else if( x >= 2 ){
          x -= 2; y ++;
          cnt ++;
        }else break;
      }else{
        if( x >= 1 && y >= 2 ){
          x --; y -= 2;
          cnt ++;
        }else if( y >= 2 ){
          x ++; y -= 2;
          cnt ++;
        }else break;
      }
    //printf( "%lld\n" , cnt );
    ret = min( ret , cnt );
  }
  if( ret % 2 )
    puts( "Andrew wins the game" );
  else
    puts( "Peter wins the game" );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "knights.in" , "r" , stdin );
  freopen( "knights.out" , "w" , stdout );
#endif
  while( scanf( "%d" , &n ) == 1 && n )
    solve();
}
