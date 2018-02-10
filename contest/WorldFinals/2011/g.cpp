#include <bits/stdc++.h>
using namespace std;
//#define double long double
const double pi = acosl( -1. );
const double eps = 1e-9;
const double eps2 = 1e-9;
typedef long long LL;
#define N 514
int n , l[ N ] , sl[ N ] , mx[ N ][ N ];
int mxat[ N ][ N ];
double dp[ N ];
void init(){
  for( int i = 1 ; i <= n ; i ++ ){
    //scanf( "%d" , &l[ i ] );
    cin >> l[ i ];
    sl[ i ] = sl[ i - 1 ] + l[ i ];
  }
  for( int i = 1 ; i <= n ; i ++ ){
    int tmx = i;
    for( int j = i ; j <= n ; j ++ ){
      if( l[ j ] > l[ tmx ] )
        tmx = j;
      mx[ i ][ j ] = l[ tmx ];
      mxat[ i ][ j ] = tmx;
    }
  }
}
double ang2( int i , int j , double rr ){
  double sum = 0;
  for( int k = i ; k <= j ; k ++ )
    if( k == mxat[ i ][ j ] )
      sum -= acosl( max( (double)-1. , min( (double)1. , (2. * rr * rr - l[ k ] * l[ k ]) / (2. * rr * rr) ) ) );
    else
      sum += acosl( max( (double)-1. , min( (double)1. , (2. * rr * rr - l[ k ] * l[ k ]) / (2. * rr * rr) ) ) );
  return sum;
}
double ang( int i , int j , double rr ){
  double sum = 0;
  for( int k = i ; k <= j ; k ++ )
    sum += acosl( max( (double)-1. , min( (double)1. , (2. * rr * rr - l[ k ] * l[ k ]) / (2. * rr * rr) ) ) );
  return sum;
}
#define K 60
#define UB 1e9
double cal2( int i , int j ){
  double bl = 0 , br = UB;
  for( int k = i ; k <= j ; k ++ )
    bl = max( bl , (double)l[ k ] * .5 );
  for( int _ = 0 ; _ < K ; _ ++ ){
    double bmid = (bl + br) * .5;
    double ret = ang2( i , j , bmid );
    if( ret < 0 ) bl = bmid;
    else br = bmid;
  }
  if( bl > UB - eps2 )
    return 0;
  double ret = 0 , rr = bl;
  for( int k = i ; k <= j ; k ++ ){
    double aa = acosl( max( (double)-1. , min( (double)1. , (2. * rr * rr - l[ k ] * l[ k ]) / (2. * rr * rr) ) ) );
    //double h = sqrt( rr * rr - l[ k ] * l[ k ] / 4. );
    //double aa = h * l[ k ] * .5;
    if( k == mxat[ i ][ j ] ){
      //ret -= aa;
      ret -= fabs( .5 * rr * rr * sinl( aa ) );
    }else{
      //ret += aa;
      ret += fabs( .5 * rr * rr * sinl( aa ) );
    }
  }
  //printf( "cal2 %d %d %.12f rr = %.12f\n" , i , j , ret , rr );
  return ret;
}
double cal( int i , int j ){
  double bl = 0 , br = UB;
  for( int k = i ; k <= j ; k ++ )
    bl = max( bl , (double)l[ k ] * .5 );

  if( ang( i , j , bl ) < pi + pi - eps )
    return cal2( i , j );

  for( int _ = 0 ; _ < K ; _ ++ ){
    double bmid = (bl + br) * .5;
    double ret = ang( i , j , bmid );
    if( ret < pi + pi ) br = bmid;
    else bl = bmid;
  }

  double ret = 0 , rr = bl;
  for( int k = i ; k <= j ; k ++ ){
    double aa = acosl( max( (double)-1. , min( (double)1. , (2. * rr * rr - l[ k ] * l[ k ]) / (2. * rr * rr) ) ) );
    ret += fabs( .5 * rr * rr * sinl( aa ) );
    //double h = sqrt( rr * rr - l[ k ] * l[ k ] / 4. );
    //double aa = h * l[ k ] * .5;
    //ret += aa;
  }
  //printf( "cal %d %d %.12f\n" , i , j , ret );
  return ret;
}
int _cs;
bool gt[ N ][ N ];
double memo[ N ][ N ];
double gogo( int bl , int br ){
  if( bl + 2 > br ) return 0;
  if( gt[ bl ][ br ] ) return memo[ bl ][ br ];
  gt[ bl ][ br ] = true;
  double ret = 0;
  if( mx[ bl ][ br ] + mx[ bl ][ br ] < sl[ br ] - sl[ bl - 1 ] )
    ret = max( ret , cal( bl , br ) );
  ret = max( ret , gogo( bl , mxat[ bl ][ br ] - 1 ) +
                   gogo( mxat[ bl ][ br ] + 1 , br ) );
  return memo[ bl ][ br ] = ret;
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      gt[ i ][ j ] = false;
  printf( "Case %d: %.12lf\n" , ++ _cs , gogo( 1 , n ) );
}
int main(){
  while( scanf( "%d" , &n ) == 1 and n ){
    init();
    solve();
  }
}
