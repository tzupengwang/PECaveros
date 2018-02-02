#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
double pi = acos( -1. );
typedef long long LL;
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

//int dice[ 3 ][ 6 ];
vector<int> dice[ 3 ];
int qt;

Pt at , v;

void query( int d ){
  assert( ++ qt <= 7500 );
#ifdef LOCAL
  int which = rand() % 6;
  int deg = dice[ d ][ which ];
  double ang = (deg / 180.0)
#else
  printf( "%d\n" , d );
  fflush( stdout );
  int deg;
  char ok[ 9 ];
  scanf( "%d%s" , &deg , ok );
  if( ok[ 0 ] == 'Y' ) exit(0);
#endif
}
void scan( Pt& tp ){
  scanf( "%lf%lf" , &tp.X , &tp.Y );
}

double ang( const Pt& p1 , const Pt& p2 ){
  double vv = p1 * p2 / norm( p1 ) / norm( p2 );
  return acosl( min( 1. , max( -1. , vv ) ) );
}

int main(){
  scan( at );
  scan( v );

  double tar = pi / 4;
  
  //for( int i = 1 ; i <= 6 ; i ++ )
    //dice[ 1 ][ i - 1 ] = 57 + i;
  //for( int i = 0 ; i < 6 ; i ++ )
    //dice[ 2 ][ i ] = (363 - i) % 360;
  
  for( int i : {57, 58, 59, 61, 62, 63} )
    dice[ 1 ].push_back( i );

  for( int i : {1, 2, 3, 359, 358, 357} )
    dice[ 2 ].push_back( i );

#ifndef LOCAL
  for( int i = 1 ; i <= 2 ; i ++ )
    for( int j = 0 ; j < 6 ; j ++ )
      printf( "%d%c" , dice[ i ][ j ] , " \n"[ j + 1 == 6 ] );
#endif

  while( true ){
    Pt goal = at * -1;
    if( ang( v , goal ) < tar ) query( 2 );
    else query( 1 );
    //if( (v ^ goal) > 0 ) query( 1 );
    //else query( 2 );
    scan( at );
    scan( v );
  }
}
