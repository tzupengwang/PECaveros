#include <bits/stdc++.h>
using namespace std;
typedef long double D;
const D pi = acosl( -1.0 );
const D eps = 1e-10;
D a , b , c , r;
#define K 100
D arr( D aa , D ll ){
  if( fabs( aa - ll ) < eps ) return 0.0;
  D hf = ll * pi * 0.5;
  if( aa > hf - eps ){
    D bl = ll * 0.5 , br = 1e20;
    for( int i = 0 ; i < K ; i ++ ){
      D mid = ( bl + br ) * 0.5;
      D theta = 2.0 * asinl( ll / ( 2.0 * mid ) );
      theta = 2.0 * pi - theta;
      D exa = theta * mid;
      if( exa < aa ) bl = mid;
      else br = mid;
    }
    bl = ( bl + br ) * 0.5;
    D theta = aa / bl;
    D area = bl * bl * theta / 2.0;
    D triarea = fabs( bl * bl * sinl( 2.0 * pi - theta ) / 2.0 );
    return area + triarea;
  }
  D bl = ll * 0.5 + eps , br = 1e20;
  for( int i = 0 ; i < K ; i ++ ){
    D mid = ( bl + br ) * 0.5;
    D theta = 2.0 * asinl( ll / ( 2.0 * mid ) );
    D exa = theta * mid;
    if( exa < aa ) br = mid;
    else bl = mid;
  }
  bl = ( bl + br ) * 0.5;
  D theta = aa / bl;
  D area = bl * bl * theta / 2.0;
  D triarea = fabs( bl * bl * sinl( theta ) / 2.0 );
  return area - triarea;
}
D cal2( D mr ){
  D aa = b + c + mr , ll = a;
  if( fabs( aa - ll ) < eps ) return 0.0;
  D hf = ll * pi * 0.5;
  D bc = acosl( ( b * b + c * c - a * a ) / ( 2 * b * c ) );
  //printf( "%.12f\n" , (double)bc );
  if( aa > hf - eps ){
    D bl = ll * 0.5 , br = 1e20;
    for( int i = 0 ; i < K ; i ++ ){
      D mid = ( bl + br ) * 0.5;
      D theta = 2.0 * asinl( ll / ( 2.0 * mid ) );
      theta = 2.0 * pi - theta;
      D exa = theta * mid;
      if( exa < aa ) bl = mid;
      else br = mid;
    }
    bl = ( bl + br ) * 0.5;
    D theta = aa / bl;
    if( ( 2.0 * pi - theta ) > 2.0 * bc + eps ) return 0.0;
    D area = bl * bl * theta / 2.0;
    D triarea = fabs( bl * bl * sinl( 2.0 * pi - theta ) / 2.0 );
    return area + triarea;
  }
  return 0.0;
}
D area;
D cal( D mr ){
  D bl = 0.0 , br = mr , bst = 0;
  for( int i = 0 ; i < K ; i ++ ){
    D m1 = bl + ( br - bl ) / 3.0;
    D m2 = br - ( br - bl ) / 3.0;
    D a1 = arr( b + m1 , b ) + arr( c + mr - m1 , c );
    D a2 = arr( b + m2 , b ) + arr( c + mr - m2 , c );
    bst = max( bst , a1 );
    bst = max( bst , a2 );
    if( a1 > a2 ) br = m2;
    else bl = m1;
  }
  bst = max( bst , cal2( mr ) - area );
  return bst;
}
void solve(){
  if( b > a ) swap( a , b );
  if( c > a ) swap( a , c );
  D sl = ( a + b + c ) * 0.5;
  area = sqrtl( sl * ( sl - a ) * ( sl - b ) * ( sl - c ) );
  D rr = 2 * pi * ( ( a * b * c ) / ( 4.0 * area ) );
  if( a * a > b * b + c * c )
    rr = min( rr , pi * a );
  if( r > rr - eps ){
    D ar = r / ( 2.0 * pi );
    printf( "%.12f\n" , (double)(pi * ar * ar) );
    exit( 0 );
  }
  D ans = 0.0;
  for( int _ = 0 ; _ < 3 ; _ ++ ){
    D mr = r - a - b - c;
    D bl = 0.0 , br = mr , bst = 0;
    for( int i = 0 ; i < K ; i ++ ){
      D m1 = bl + ( br - bl ) / 3.0;
      D m2 = br - ( br - bl ) / 3.0;
      D a1 = cal( mr - m1 ) + arr( a + m1 , a );
      D a2 = cal( mr - m2 ) + arr( a + m2 , a );
      bst = max( bst , a1 );
      bst = max( bst , a2 );
      if( a1 > a2 ) br = m2;
      else bl = m1;
    }
    ans = max( ans , bst + area );
    D sw = a; a = b; b = c; c = sw;
  }
  //D ans = bst + area;
  printf( "%.12f\n" , (double)ans );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "border.in" , "r" , stdin );
  freopen( "border.out" , "w" , stdout );
#endif
  double ia , ib , ic , ir;
  scanf( "%lf%lf%lf%lf" , &ia , &ib , &ic , &ir );
  a = ia;
  b = ib;
  c = ic;
  r = ir;
  solve();
}
