#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
const double eps = 1e-9;
const double pi = acosl( -1. );
struct Pt{
  double X , Y , Z;
};
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return {p1.X + p2.X, p1.Y + p2.Y, p1.Z + p2.Z};
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y, p1.Z - p2.Z};
}  
Pt operator*( const Pt& p1 , double tk ){
  return {p1.X * tk, p1.Y * tk, p1.Z * tk};
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X +
         p1.Y * p2.Y +
         p1.Z * p2.Z;
}
Pt operator^( const Pt& p1 , const Pt& p2 ){
  return {p1.Y * p2.Z - p1.Z * p2.Y,
          p1.Z * p2.X - p1.X * p2.Z,
          p1.X * p2.Y - p1.Y * p2.X};
}
double norm2( const Pt& pp ){
  return pp * pp;
}
double norm( const Pt& pp ){
  return sqrt( norm2( pp ) );
}
int n;
double alpha;
double myacos( double v ){
  return acos( max( -1. , min( 1. , v ) ) );
}
Pt p[ N ] , s;
double cosalpha;
double tanalpha;
void init(){
  scanf( "%d%lf" , &n , &alpha );
  alpha = (alpha / 180.) * pi + eps;
  scanf( "%lf%lf%lf" , &s.X , &s.Y , &s.Z );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%lf%lf" , &p[ i ].X , &p[ i ].Y );
    p[ i ].Z = 0;
    p[ i ] = p[ i ] - s;
    p[ i ] = p[ i ] * (1. / norm( p[ i ] ));
  }
  cosalpha = cosl( alpha );
  tanalpha = tanl( alpha );
}
int ans , _cs;
void solve(){
  ans = 1;
  for( int i = 0 ; i < n ; i ++ ){
    int tans = 1;
    vector< pair<double,int> > intv;
    Pt ver1 = {0, -p[ i ].Z, p[ i ].Y};
    Pt ver2 = p[ i ] ^ ver1;
    ver1 = ver1 * (1. / norm(ver1));
    ver2 = ver2 * (1. / norm(ver2));
    for( int j = 0 ; j < n ; j ++ ){
      if( i == j ) continue;
      if( norm( p[ i ] - p[ j ] ) < eps ){
        tans ++;
        continue;
      }
      double jia = myacos( p[ i ] * p[ j ] ) * .5;
      double tjia = tan( jia );
      tjia /= tanalpha;
      if( tjia > 1 + eps ) continue;

      double theta = myacos( tjia );
      double ss = atan2( p[ j ] * ver2 , p[ j ] * ver1 );
      for( int d = -1 ; d <= 1 ; d ++ ){
        intv.push_back( {ss - theta + d * (pi + pi) - eps, +1} );
        intv.push_back( {ss + theta + d * (pi + pi) + eps, -1} );
      }
    }
    ans = max( ans , tans );
    sort( intv.begin() , intv.end() );
    int sum = 0;
    for( auto ii : intv ){
      sum += ii.second;
      ans = max( ans , tans + sum );
    }
  }
  printf( "Case #%d: %d\n" , ++ _cs , ans );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
