#include <bits/stdc++.h>
using namespace std;
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pt operator/( const Pt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
void scan( Pt& tp ){
  scanf( "%lf%lf" , &tp.X , &tp.Y );
}
void print( const Pt& tp ){
  printf( "(%.6f, %.6f)\n" , tp.X , tp.Y );
}
int n , q;
#define N 101010
Pt p[ N ];
void init(){
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
  //for( int i = 0 ; i < n ; i ++ )
    //print( p[ i ] );
}
int _cs , tms[ N ];
double sqr( double _ ){ return _ * _; }
double f( double aa , double bb ){
  double ret = 0;
  for( int i = 0 ; i < n ; i ++ )
    ret += tms[ i ] * ( sqr( p[ i ].Y - ( aa + bb * p[ i ].X ) ) / ( 1 + bb * bb ) );
  return ret;
}
double cal(){
  Pt s = { 0 , 0 };
  int tot = 0;
  double sumxx = 0 , sumxy = 0 , sumyy = 0;
  for( int i = 0 ; i < n ; i ++ ){
    s = s + ( p[ i ] * tms[ i ] );
    tot += tms[ i ];
    sumxx += tms[ i ] * p[ i ].X * p[ i ].X;
    sumxy += tms[ i ] * p[ i ].X * p[ i ].Y;
    sumyy += tms[ i ] * p[ i ].Y * p[ i ].Y;
  }
  s = s / tot;
  double B = ( sumyy - tot * s.Y * s.Y ) - ( sumxx - tot * s.X  * s.X );
  B /= ( tot * s.X * s.Y - sumxy );
  B /= 2;
  double b1 = -B + sqrt( B * B + 1 );
  double b2 = -B - sqrt( B * B + 1 );
  double a1 = s.Y - b1 * s.X;
  double a2 = s.Y - b2 * s.X;
  double cst1 = f( a1 , b1 );
  double cst2 = f( a2 , b2 );
  return min( cst1 , cst2 ) / tot;
}
void solve(){
  printf( "Case %d:\n" , ++ _cs );
  for( int i = 0 ; i < n ; i ++ )
    tms[ i ] = 1;
  printf( "%.12f\n" , cal() );
  int __ = 0;
  while( q -- ){
    int s , m;
    scanf( "%d%d" , &s , &m );
    tms[ s ] = m;
    printf( "%d: %.12f\n" , ++ __ , cal() );
    tms[ s ] = 1;
  }
}
int main(){
  while( scanf( "%d%d" , &n , &q ) == 2 && n ){
    init();
    solve();
  }
}
