#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 22
int n , m;
int f[ N ] , f_who[ N ];
int s[ N ] , s_who[ N ];
int main(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= m ; i ++ ){
    f[ i ] = 1e9;
    s[ i ] = -1e9;
  }
  for( int i = 1 ; i <= n ; i ++ ){
    int si , ti , di;
    scanf( "%d%d%d" , &si , &ti , &di );
    if( ti < f[ di ] ){
      f[ di ] = ti;
      f_who[ di ] = i;
    }
    if( si > s[ di ] ){
      s[ di ] = si;
      s_who[ di ] = i;
    }
  }
  for( int i = 1 ; i <= m ; i ++ )
    if( f[ i ] < s[ i ] )
      printf( "TAK %d %d\n" , f_who[ i ] , s_who[ i ] );
    else
      printf( "NIE\n" );
}
