#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define double long double
typedef pair<double,double> Pt;
#define X first
#define Y second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return {p1.X + p2.X, p1.Y + p2.Y};
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y};
}
Pt operator*( const Pt& p1 , double tk ){
  return {p1.X * tk, p1.Y * tk};
}
Pt operator/( const Pt& p1 , double tk ){
  return {p1.X / tk, p1.Y / tk};
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
double operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
double norm2( const Pt& pp ){
  return pp * pp;
}
double norm( const Pt& pp ){
  return sqrt( norm2( pp ) );
}
const double eps = 1e-10;
void scan( Pt& pp ){
  cin >> pp.X >> pp.Y;
}
double myacos( double x ){
  return acosl( min( (double)1. , max( (double)-1. , x ) ) );
}
#define N 111
int n , r;
Pt p[ N ];
double Area( Pt p1 , Pt p2 ){
  if( norm( p1 ) < r + eps and
      norm( p2 ) < r + eps )
    return fabs( p1 ^ p2 ) * .5;
  double per = (p2 - p1) * (make_pair(0, 0) - p1) / norm2( p2 - p1 );
  double dd = 1e20;
  if( per > -eps and per < 1 + eps )
    dd = fabs( (p1 ^ (p2 - p1)) / norm(p2 - p1) );
  else
    dd = min( norm( p1 ) , norm( p2 ) );
  if( dd > r - eps ){
    double theta = myacos( p1 * p2 / norm( p1 ) / norm( p2 ) );
    return fabs( theta * r * r ) * .5;
  }
  if( norm( p1 ) < norm( p2 ) )
    swap( p1 , p2 );
  if( norm( p2 ) < r + eps ){
    double bl = 0 , br = 1;
    Pt dlt = p2 - p1;
    for( int i = 0 ; i < 70 ; i ++ ){
      double bmid = (bl + br) * .5;
      Pt at = p1 + dlt * bmid;
      if( norm( at ) < r )
        br = bmid;
      else
        bl = bmid;
    }
    Pt at = p1 + dlt * bl;
    //cerr << norm( p1 ) << endl;
    //cerr << norm( at ) << endl;
    //cerr << norm( p2 ) << endl;
    //cerr << endl;
    return Area( p1 , at ) + Area( at , p2 );
  }
  Pt dlt = p2 - p1 , at1 , at2;
  {
    double bl = 0 , br = per;
    for( int i = 0 ; i < 70 ; i ++ ){
      double bmid = (bl + br) * .5;
      Pt at = p1 + dlt * bmid;
      if( norm( at ) < r )
        br = bmid;
      else
        bl = bmid;
    }
    at1 = p1 + dlt * bl;
  }
  {
    double bl = per , br = 1;
    for( int i = 0 ; i < 70 ; i ++ ){
      double bmid = (bl + br) * .5;
      Pt at = p1 + dlt * bmid;
      if( norm( at ) < r )
        bl = bmid;
      else
        br = bmid;
    }
    at2 = p1 + dlt * bl;
  }
  return Area( p1 , at1 ) + Area( at1 , at2 ) + Area( at2 , p2 );
}
int main(){
  cin >> n >> r;
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
  double area = 0;
  for( int i = 0 ; i < n ; i ++ ){
    double ret = Area( p[ i ] , p[ (i + 1) % n ] );
    if( (p[ i ] ^ p[ (i + 1) % n ]) > 0 )
      area += ret;
    else
      area -= ret;
  }
  cout << fixed << setprecision( 12 ) << area << endl;
  //printf( "%.12f\n" , area );
}
