#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<double,double> Pt;
typedef pair<Pt,double> Cir;
const double eps = 1e-7;
double myacos( double x ){
  return acosl( min( 1. , max( -1. , x ) ) );
}
#define X first
#define Y second
#define O first
#define R second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return {p1.X + p2.X, p1.Y + p2.Y};
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y};
}
Pt operator*( const Pt& pp , double tk ){
  return {pp.X * tk, pp.Y * tk};
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
Pt rotate( const Pt& pp , double theta ){
  return {pp.X * cosl( theta ) - pp.Y * sinl( theta ),
          pp.X * sinl( theta ) + pp.Y * cosl( theta ) };
}
double norm( const Pt& pp ){
  return sqrt( pp * pp );
}
#define K 60
int d[ 4 ];
double ans;
Cir c[ 5 ];
bool go( int now ){
  if( now == 4 ){
    for( int i = 0 ; i < 4 ; i ++ )
      if( norm( c[ i ].O - c[ 4 ].O ) > 
          c[ 4 ].R - c[ i ].R + eps )
        return false;
    for( int i = 0 ; i < 4 ; i ++ )
      for( int j = i + 1 ; j < 4 ; j ++ )
        if( norm( c[ i ].O - c[ j ].O ) + eps <
            c[ i ].R + c[ j ].R )
          return false;
    return true;
  }
  c[ now ].R = d[ now ];
  for( int i = 0 ; i < now ; i ++ ){
    double l1 = c[ 4 ].R - c[ i ].R;
    double l2 = c[ 4 ].R - c[ now ].R;
    double l3 = c[ i ].R + c[ now ].R;
    if( l1 < eps or l2 < eps or l3 < eps ) continue;
    double theta = myacos( (l1 * l1 + l3 * l3 - l2 * l2) / (2 * l1 * l3) );
    Pt p1 = rotate( c[ 4 ].O - c[ i ].O , +theta );
    Pt p2 = rotate( c[ 4 ].O - c[ i ].O , -theta );
    c[ now ].O = c[ i ].O + p1 * (l3 / norm( p1 ));
    if( go( now + 1 ) )
      return true;
    c[ now ].O = c[ i ].O + p2 * (l3 / norm( p2 ));
    if( go( now + 1 ) )
      return true;
  }
  for( int i = 0 ; i < now ; i ++ )
    for( int j = i + 1 ; j < now ; j ++ ){
      double l1 = c[ i ].R + c[ now ].R;
      double l2 = c[ j ].R + c[ now ].R;
      double l3 = c[ i ].R + c[ j ].R;
      if( l1 < eps or l2 < eps or l3 < eps ) continue;
      double theta = myacos( (l1 * l1 + l3 * l3 - l2 * l2) / (2 * l1 * l3) );
      Pt p1 = rotate( c[ j ].O - c[ i ].O , +theta );
      Pt p2 = rotate( c[ j ].O - c[ i ].O , -theta );
      c[ now ].O = c[ i ].O + p1 * (l1 / norm( p1 ));
      if( go( now + 1 ) )
        return true;
      c[ now ].O = c[ i ].O + p2 * (l1 / norm( p2 ));
      if( go( now + 1 ) )
        return true;
    }
  return false;
}
bool okay( double cd ){
  c[ 4 ] = { {0, 0} , cd };
  c[ 0 ] = { {cd - d[ 0 ], 0} , d[ 0 ] };
  return go( 1 );
}
void cal(){
  double bl = *max_element( d , d + 4 ) , br = ans;
  for( int _ = 0 ; _ < K ; _ ++ ){
    double mid = (bl + br) * .5;
    if( okay( mid ) ) br = mid;
    else bl = mid;
  }
  ans = min( ans , br );
}
int _cs;
int main(){
  while( cin >> d[ 0 ] and d[ 0 ] ){
    for( int i = 1 ; i < 4 ; i ++ )
      cin >> d[ i ];
    ans = 1e6;
    sort( d , d + 4 );
    do cal();
    while( next_permutation( d , d + 4 ) );
    printf( "Case %d: %.0f\n" , ++ _cs , ans );
  }
}
