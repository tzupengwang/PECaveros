#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<double,double> Pt;
const double eps = 1e-9;
const double pi = acos( -1. );
#define X first
#define Y second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return {p1.X + p2.X , p1.Y + p2.Y};
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X , p1.Y - p2.Y};
}
Pt operator*( const Pt& p1 , double tk ){
  return {p1.X * tk, p1.Y * tk};
}
double operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
double norm2( const Pt& pp ){
  return pp * pp;
}
double norm( const Pt& pp ){
  return sqrt( norm2( pp ) );
}
bool between( const Pt& p1 , const Pt& p2 , const Pt& pp ){
  if( fabs((p2 - p1) ^ (pp - p1)) > eps ) return false;
  return (p2 - p1) * (pp - p1) > -eps and
         (p1 - p2) * (pp - p2) > -eps;
}
int side( const Pt& p1, const Pt& p2, const Pt& pp ){
  double val = (p2 - p1) ^ (pp - p1);
  return (val > eps) - (val < -eps);
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2, bool& res){
  if( side( p1 , p2 , q1 ) *
      side( p1 , p2 , q2 ) > 0 ){
    res = false;
    return {0, 0};
  }
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ){
    res = false;
    return {0, 0};
  }
  res = true;
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
void scan( Pt& tp ){
  scanf( "%lf%lf" , &tp.X , &tp.Y );
}
void print( const Pt& pp ){
  printf( "%.6f %.6f\n" , pp.X , pp.Y );
}
#define N 444
int n;
Pt p[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    scan( p[ i ] );
    p[ n + i ] = p[ i ];
  }
}
bool in_poly( const Pt& pp ){
  for( int i = 0 ; i < n ; i ++ ){
    if( between( p[ i ] , p[ i + 1 ] , pp ) )
      return true;
  }
  bool In = false;
  for( int i = 0 ; i < n ; i ++ ){
    Pt a = p[ i ] , b = p[ i + 1 ];
    if( fabs(a.X - b.X) < eps ) continue;
    if(a.X > b.X) swap(a, b);
    if(pp.X < a.X - eps) continue;
    if(pp.X > b.X - eps) continue;
    if( ((pp - a) ^ (b - a)) > 0 )
      In = !In;
  }
  return In;
}
double ans;
double at( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  return (p3 - p1) * (p2 - p1) / norm2( p2 - p1 );
}
pair<double,Pt> cand[ N ];
void go( const Pt& p1 , const Pt& p2 ){
  size_t psz = 0;
  cand[ psz ++ ] = {0, p1};
  cand[ psz ++ ] = {1, p2};
  for( int i = 0 ; i < n ; i ++ ){
    bool res;
    Pt ret = interPnt( p1 , p2 , p[ i ] , p[ i + 1 ] , res );
    if( not res ) continue;
    cand[ psz ++ ] = {at( p1 , p2 , ret ) , ret};
  }
  sort( cand , cand + psz );
  {
    size_t ppsz = 1;
    for( size_t i = 1 ; i < psz ; i ++ )
      if( cand[ i ].first - cand[ ppsz - 1 ].first > eps )
        cand[ ppsz ++ ] = cand[ i ];
    psz = ppsz;
  }
  double pre = cand[ 0 ].first , nn = norm( p1 - p2 );
  for( size_t i = 0 ; i + 1 < psz ; i ++ ){
    Pt mid = (cand[ i ].second + cand[ i + 1 ].second) * .5;
    if( not in_poly( mid ) )
      pre = cand[ i + 1 ].first;
    ans = max( ans , nn * (cand[ i + 1 ].first - pre) );
    if( ans > nn * (cand[ psz - 1 ].first - pre) )
      break;
  }
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ )
      go( p[ i ] , p[ j ] );
  printf( "%.12f\n" , ans );
}
int main(){
  init();
  solve();
}
