#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
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
#define N 101010
int n , m;
Pt p[ N ];
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
  while( m -- ){
    Pt s , t;
    scan( s );
    scan( t );
    Pt dlt = t - s;
    for( int i = 0 ; i < n ; i ++ ){
      if( ( dlt ^ ( p[ i ] - s ) ) > -eps )
        continue;
      Pt p1 = s + dlt * ( ( ( p[ i ] - s ) * dlt ) / norm2( dlt ) );
      //printf( "%d : %.12f %.12f\n" , i , p1.X , p1.Y );
      p[ i ] = p1 + ( p1 - p[ i ] );
    }
    //for( int i = 0 ; i < n ; i ++ )
      //printf( "%.12f %.12f\n" , p[ i ].X , p[ i ].Y );
  }
  for( int i = 0 ; i < n ; i ++ )
    printf( "%.12f %.12f\n" , p[ i ].X , p[ i ].Y );
}
