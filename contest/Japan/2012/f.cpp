#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
struct DJ{
  LL p[ N ] , w[ N ];
  void init( int n ){
    for( int i = 0 ; i <= n ; i ++ ){
      p[ i ] = i;
      w[ i ] = 0;
    }
  }
  int f( int x ){
    if( x == p[ x ] ) return x;
    int tmp = f( p[ x ] );
    LL dlt = w[ p[ x ] ];
    w[ x ] += dlt;
    p[ x ] = tmp;
    return p[ x ];
  }
  void uni( int x , int y , int dlt ){
    // wx + dlt = wy
    int px = f( x );
    int py = f( y );
    if( px == py ) return;
    p[ px ] = py;
    w[ px ] = dlt - w[ x ] + w[ y ];
  }
} djs;
int n , m;
bool init(){
  scanf( "%d%d" , &n , &m );
  if( n == 0 and m == 0 )
    return false;
  return true;
}
char cmd[ 9 ];
int a , b , w;
void solve(){
  djs.init( n );
  while( m -- ){
    scanf( "%s" , cmd );
    if( cmd[ 0 ] == '!' ){
      scanf( "%d%d%d" , &a , &b , &w );
      djs.uni( a , b , w );
    }else{
      scanf( "%d%d" , &a , &b );
      int pa = djs.f( a );
      int pb = djs.f( b );
      if( pa != pb )
        puts( "UNKNOWN" );
      else{
        printf( "%lld\n" , djs.w[ a ] - djs.w[ b ] );
      }
    }
  }
}
int main(){
  while( init() )
    solve();
}
