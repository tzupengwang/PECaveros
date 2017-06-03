#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 1616
typedef double D;
int n , m , k , vr , vf;
int x[ N ] , y[ N ];
double dist[ N ][ N ];
bool bike[ N ][ N ];
int route[ N ];
inline double sqr( double _ ){
  return _ * _;
}
void init(){
  scanf( "%d%d%d%d%d" , &n , &m , &k , &vr , &vf );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d%d" , &x[ i ] , &y[ i ] );
  while( m -- ){
    int ai , bi; scanf( "%d%d" , &ai , &bi );
    bike[ ai ][ bi ] = bike[ bi ][ ai ] = true;
  }
  route[ 0 ] = 1;
  for( int i = 1 ; i <= k ; i ++ )
    scanf( "%d" , &route[ i ] );
  route[ k + 1 ] = n;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      dist[ i ][ j ] = sqrt( sqr( x[ i ] - x[ j ] ) +
                             sqr( y[ i ] - y[ j ] ) );
}
int stmp[ N ] , from[ N ];
double dd[ N ];
vector<int> va;
void push( int now ){
  if( va.empty() or now != va.back() )
    va.push_back( now );
}
void add( int start , int now ){
  if( start == now ){
    push( start );
    return;
  }
  add( start , from[ now ] );
  push( now );
}
void solve(){
  double ans = 0.0;
  for( int _ = 1 ; _ <= k + 1 ; _ ++ ){
    int start = route[ _ - 1 ];
    int to = route[ _ ];
    for( int i = 1 ; i <= n ; i ++ )
      dd[ i ] = 1e20;
    dd[ start ] = 0;
    for( int i = 1 ; i <= n ; i ++ ){
      int bst = -1;
      for( int j = 1 ; j <= n ; j ++ ){
        if( stmp[ j ] == _ ) continue;
        if( bst == -1 or dd[ j ] < dd[ bst ] )
          bst = j;
      }
      if( bst == -1 ) break;
      stmp[ bst ] = _;
      for( int j = 1 ; j <= n ; j ++ ){
        {
          double td = dd[ bst ] + dist[ bst ][ j ] / vf;
          if( td < dd[ j ] ){
            dd[ j ] = td;
            from[ j ] = bst;
          }
        }
        if( bike[ bst ][ j ] ){
          double td = dd[ bst ] + dist[ bst ][ j ] / vr;
          if( td < dd[ j ] ){
            dd[ j ] = td;
            from[ j ] = bst;
          }
        }
      }
    }
    ans += dd[ to ];
    add( start , to );
  }
  printf( "%.12f\n" , ans );
  for( size_t i = 0 ; i < va.size() ; i ++ )
    printf( "%d%c" , va[ i ] , " \n"[ i + 1 == va.size() ] );
}
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  init();
  solve();
}
