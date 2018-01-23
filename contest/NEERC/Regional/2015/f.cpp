#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
const double eps = 1e-6;
int w , n;
int x[ N ] , y[ N ];
double bst , ax , ay;
bool ok[ N ][ 2 ];
pair<int,int> bk[ N ][ 2 ];
double d[ N ][ N ];
pair<int,int> que[ N + N ];
bool okay( double mx ){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 2 ; j ++ )
      ok[ i ][ j ] = false;
  int qt = 0;
  for( int i = 0 ; i < n ; i ++ ){
    if( x[ i ] < mx + eps ){
      ok[ i ][ 0 ] = true;
      bk[ i ][ 0 ] = { -1 , 0 };
      que[ qt ++ ] = { i , 0 };
    }else if( x[ i ] < mx + mx + eps ){
      ok[ i ][ 1 ] = true;
      bk[ i ][ 1 ] = { -1 , 0 };
      que[ qt ++ ] = { i , 1 };
    }
  }
  for( int _ = 0 ; _ < qt ; _ ++ ){
    int i = que[ _ ].first;
    int g = que[ _ ].second;
    for( int j = 0 ; j < n ; j ++ ){
      int ng = g;
      if( d[ i ][ j ] < mx + eps );
      else if( d[ i ][ j ] < mx + mx + eps ) ng ++;
      else continue;
      if( ng > 1 ) continue;
      if( ok[ j ][ ng ] ) continue;
      ok[ j ][ ng ] = true;
      bk[ j ][ ng ] = { i , g };
      que[ qt ++ ] = { j , ng };
    }
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < 2 ; j ++ ){
      if( not ok[ i ][ j ] ) continue;
      int ng = j;
      if( w - x[ i ] < mx + eps );
      else if( w - x[ i ] < mx + mx + eps ) ng ++;
      else continue;
      if( ng > 1 ) continue;
      bst = mx;
      if( ng > j or j == 0 ){
        ax = (w + x[ i ]) * .5;
        ay = y[ i ];
      }else{
        int ni = i , nj = j;
        while( ni >= 0 ){
          int bi , bj;
          tie(bi , bj) = bk[ ni ][ nj ];

          if( bj < j ){
            if(bi == -1){
              ax = x[ ni ] * .5;
              ay = y[ ni ];
            }else{
              ax = (x[ ni ] + x[ bi ]) * .5;
              ay = (y[ ni ] + y[ bi ]) * .5;
            }
            break;
          }
          tie(ni , nj) = tie(bi , bj);
        }
      }
      return true;
    }
  return false;
}
double sqr( double xx ){ return xx * xx; }
int main(){
  freopen( "froggy.in" , "r" , stdin );
  freopen( "froggy.out" , "w" , stdout );
  scanf( "%d%d" , &w , &n );
  //w = 1e9;
  //n = 1e3;
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%d%d" , &x[ i ] , &y[ i ] );
    //x[ i ] = rand() % (w - 1) + 1;
    //y[ i ] = rand() % (int)1e9;
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      d[ i ][ j ] = sqrt( sqr( x[ i ] - x[ j ] ) +
                          sqr( y[ i ] - y[ j ] ) );
  bst = w * .5;
  ax = w * .5;
  ay = 0;
  double bl = 0 , br = w / 2;
  for( int i = 0 ; i < 60 ; i ++ ){
    double bm = (bl + br) * .5;
    if( okay( bm ) ) br = bm;
    else bl = bm;
  }
  printf( "%.9f %.9f\n" , ax , ay );
}
