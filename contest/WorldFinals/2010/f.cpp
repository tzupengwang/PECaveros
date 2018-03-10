#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
double sqr( double x ){ return x * x; }
int s , p , d , h;
int a[ N ][ N ] , _cs;
double ans;
const double pi = acosl( -1. );
const double cosT = cosl( pi / 3. );
const double sinT = sinl( pi / 3. );
void rotate( double& xx , double& yy ){
  double rx = xx * cosT - yy * sinT;
  double ry = xx * sinT + yy * cosT;
  xx = rx; yy = ry;
}
double dist( double lh1 , double rh1 , double ph1 ,
             double lh2 , double rh2 , double ph2 ){
  double Ax = d * (ph1 - lh1) / (rh1 - lh1);
  double Ay = 0;
  double Bx = d * (ph2 - lh2) / (rh2 - lh2);
  double By = 0;
  rotate( Bx , By );
  return sqrt( sqr( Ax - Bx ) + sqr( Ay - By ) );
}
void cal( int h1 , int h2 , int h3 ){
  int mxh = max( h1 , max( h2 , h3 ) );
  int mnh = min( h1 , min( h2 , h3 ) );
  int mid = h1 + h2 + h3 - mxh - mnh;
  double cal_mid = false;
  if( mxh > mid ){
    int uph = mxh / h * h;
    int dnh = (mid + h - 1) / h * h;
    if( dnh == mid and dnh == mnh ) dnh += h;
    if( dnh == mid ) cal_mid = true;
    if( dnh <= uph ){
      int tot = (uph - dnh) / h + 1;
      double dnlen = dist( mxh , mid , dnh , mxh , mnh , dnh );
      double uplen = dist( mxh , mid , uph , mxh , mnh , uph );
      ans += (dnlen + uplen) * tot / 2.;
    }
  }
  if( mnh < mid ){
    int uph = mid / h * h;
    int dnh = (mnh + h - 1) / h * h;
    if( uph == mid and uph == mxh ) uph -= h;
    if( uph == mid and cal_mid ) uph -= h;
    if( dnh <= uph ){
      int tot = (uph - dnh) / h + 1;
      double dnlen = dist( mnh , mid , dnh , mnh , mxh , dnh );
      double uplen = dist( mnh , mid , uph , mnh , mxh , uph );
      ans += (dnlen + uplen) * tot / 2.;
    }
  }
  //printf( "%d %d %d %.12f\n" , h1 , h2 , h3 , ans );
}
void cal_border( int h1 , int h2 , int h3 , int h4 ){
  if( h1 != h2 ) return;
  if( h1 % h ) return;
  if( h1 == h3 and h1 == h4 ) return;
  //printf( "%d %d %d %d\n" , h1 , h2 , h3 , h4 );
  ans += d;
}
int A( int ii , int jj ){
  if( ii < 0 or ii >= s ) return -1;
  if( jj < 0 or jj >= p + (ii & 1) ) return -1;
  return a[ ii ][ jj ];
}
int main(){
  while( scanf( "%d" , &s ) == 1 and s ){
    scanf( "%d" , &p );
    scanf( "%d" , &d );
    scanf( "%d" , &h );
    for( int i = 0 ; i < s ; i ++ )
      for( int j = 0 ; j < p + (i & 1) ; j ++ )
        scanf( "%d" , &a[ i ][ j ] );
    ans = 0;
    for( int i = 0 ; i < s ; i ++ )
      for( int j = 0 ; j < p + (i & 1) ; j ++ ){
        if( i & 1 ){
          if( i + 1 < s and j > 0 and j < (p + ((i + 1) & 1)) )
            cal( a[ i ][ j ] , a[ i + 1 ][ j - 1 ] , a[ i + 1 ][ j ] );
          if( i and j > 0 and j < (p + ((i + 1) & 1)) )
            cal( a[ i ][ j ] , a[ i - 1 ][ j - 1 ] , a[ i - 1 ][ j ] );
        }else{
          if( i + 1 < s and j + 1 < (p + ((i + 1) & 1)) )
            cal( a[ i ][ j ] , a[ i + 1 ][ j ] , a[ i + 1 ][ j + 1 ] );
          if( i and j + 1 < (p + ((i + 1) & 1)) )
            cal( a[ i ][ j ] , a[ i - 1 ][ j ] , a[ i - 1 ][ j + 1 ] );
        }
      } 
    for( int i = 0 ; i < s ; i ++ )
      for( int j = 0 ; j + 1 < p + (i & 1) ; j ++ )
        if( i & 1 )
          cal_border( a[ i ][ j ] , a[ i ][ j + 1 ] , A( i - 1 , j ) , A( i + 1 , j ) );
        else
          cal_border( a[ i ][ j ] , a[ i ][ j + 1 ] , A( i - 1 , j + 1 ) , A( i + 1 , j + 1 ) );
    for( int i = 0 ; i + 1 < s ; i ++ )
      for( int j = 0 ; j < p + (i & 1) ; j ++ ){
        if( i & 1 ){
          if( j < p + ((i + 1) & 1) )
            cal_border( a[ i ][ j ] , a[ i + 1 ][ j ] , A( i , j + 1 ) , A( i + 1 , j - 1 ) );
          if( j )
            cal_border( a[ i ][ j ] , a[ i + 1 ][ j - 1 ] , A( i , j - 1 ) , A( i + 1 , j ) );
        }else{
          if( j + 1 < p + ((i + 1) & 1) )
            cal_border( a[ i ][ j ] , a[ i + 1 ][ j + 1 ] , A( i , j + 1 ) , A( i + 1 , j ) );
          {
            cal_border( a[ i ][ j ] , a[ i + 1 ][ j ] , A( i , j - 1 ) , A( i + 1 , j + 1 ) );
          }
        }
      }
    printf( "Case %d: %.0f\n" , ++ _cs , ans );
  }
}
