#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 2048
#define K 80
const double eps = 1e-6;
const double eps2 = 1e-8;
const double inf = 1e9;
int n , m , a[ N ] , b[ N ] , d[ N ];
bool got[ N ];
double o[ N ];
char buf[ N ];
void init(){
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%s" , buf );
    if( buf[ 0 ] == '?' ){
      got[ i ] = false;
      continue;
    }
    got[ i ] = true;
    sscanf( buf , "%lf" , &o[ i ] );
  }
  for( int i = 0 ; i < m ; i ++ )
    scanf( "%d%d%d" , &a[ i ] , &b[ i ] , &d[ i ] );
}
int es[ N + N ] , et[ N + N ];
double ed[ N + N ] , dst[ N + N ];
inline bool good( double T , bool con = false ){
  int S = n + 1 , eid = 0;
  for( int i = 0 ; i < m ; i ++ ){
    if( got[ a[ i ] ] and got[ b[ i ] ] ){
      if( o[ a[ i ] ] + d[ i ] > o[ b[ i ] ] + T + eps )
        return false;
      continue;
    }
    if( got[ a[ i ] ] ){
      es[ eid ] = b[ i ];
      et[ eid ] = S;
      ed[ eid ] = -o[ a[ i ] ] + T - d[ i ];
      eid ++;
      continue;
    }
    if( got[ b[ i ] ] ){
      es[ eid ] = S;
      et[ eid ] = a[ i ];
      ed[ eid ] = +o[ b[ i ] ] + T - d[ i ];
      eid ++;
      continue;
    }
    es[ eid ] = b[ i ];
    et[ eid ] = a[ i ];
    ed[ eid ] = T - d[ i ];
    eid ++;
  }
  for( int i = 1 ; i <= n ; i ++ ){
    es[ eid ] = S;
    et[ eid ] = i;
    ed[ eid ] = inf;
    eid ++;
  }
  for( int i = 1 ; i <= n + 2 ; i ++ )
    dst[ i ] = inf;
  dst[ S ] = 0;
  for( int _ = 0 ; _ <= n + 3 ; _ ++ ){
    bool upd = false;
    for( int j = 0 ; j < eid ; j ++ )
      if( dst[ es[ j ] ] + ed[ j ] < dst[ et[ j ] ] - eps ){
        upd = true;
        dst[ et[ j ] ] = dst[ es[ j ] ] + ed[ j ];
      }
    if( _ == n + 3 and upd )
      return false;
  }
  if( con ){
    for( int i = 1 ; i <= n ; i ++ )
      if( not got[ i ] )
        o[ i ] = dst[ i ];
  }
  return true;
}
void solve(){
  double lb = 0 , rb = inf;
  for( int i = 0 ; i < K ; i ++ ){
    double mid = (lb + rb) * .5;
    if( good( mid ) ) rb = mid;
    else lb = mid;
  }
  good( rb + eps2 , 1 );
  printf( "%.12f\n" , rb + eps2 );
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%.12f%c" , o[ i ] , " \n"[ i == n ] );
}
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 ){
    init();
    solve();
  }
}
