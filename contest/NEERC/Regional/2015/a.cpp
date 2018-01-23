#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N (1 << 20)
LL n , q , sr , cr , sc , cc;
bool tr[ N ] , tc[ N ];
int main(){
  freopen( "adjustment.in" , "r" , stdin );
  freopen( "adjustment.out" , "w" , stdout );
  cin >> n >> q;
  while( q -- ){
    char c[ 9 ]; int id;
    scanf( "%s%d" , c , &id );
    if( c[ 0 ] == 'R' ){
      if( tr[ id ] ){
        puts( "0" );
        continue;
      }
      tr[ id ] = true;
      LL ans = (1LL + n) * n / 2 + n * id;
      ans -= sc;
      ans -= cc * id;
      printf( "%lld\n" , ans );
      sr += id;
      cr ++;
    }else{
      if( tc[ id ] ){
        puts( "0" );
        continue;
      }
      tc[ id ] = true;
      LL ans = (1LL + n) * n / 2 + n * id;
      ans -= sr;
      ans -= cr * id;
      printf( "%lld\n" , ans );
      sc += id;
      cc ++;
    }
  }
}
