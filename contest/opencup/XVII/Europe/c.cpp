#include <bits/stdc++.h>
using namespace std;
#define N 222
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
typedef double D;
const D pi = acos( -1.0 );
int n;
char c[ N ];
inline double sqr( double x ){ return x * x; }
inline double cir( double x ){
  double dd = norm( make_pair( 0 , 0.5 * sqrt( 3 ) ) -
                    make_pair( x , 0.5 ) );
  double rd = sqrt( sqr( dd ) - sqr( 0.5 ) );
  Pt too = { x , 0.5 * ( 1 - sqrt( 3 ) ) };
  double theta = acos( rd / dd );
  Pt tot = { cos( theta ) * too.X - sin( theta ) * too.Y ,
             sin( theta ) * too.X + cos( theta ) * too.Y };
  tot = ( tot / dd ) * rd;
  tot = tot + make_pair( 0 , 0.5 * sqrt( 3 ) );
  tot = tot - make_pair( x , 0.5 );
  theta = ( tot * make_pair( 0 , 1 ) ) / norm( tot );
  return rd + acos( theta ) * 0.5;
}
int main(){
  scanf( "%d" , &n );
  scanf( "%s" , c + 1 );
  int lft = n + 1 , rgt = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( c[ i ] != 'T' ){
      lft = min( lft , i );
      rgt = max( rgt , i );
    }
  if( rgt == 0 ){
    double ans = n + n + 1;
    printf( "%.12f\n" , ans );
    exit(0);
  }
  double ans = n - 1 + rgt - lft;
  if( lft == 1 ){
    if( c[ 1 ] == 'S' )
      ans += 2;
    else
      ans += pi * 0.5;
  }else{
    if( c[ lft ] == 'S' ){
      ans += 2;
      ans += norm( make_pair( 0.5 , 0.5 * sqrt( 3 ) ) -
                   make_pair( lft - 1 , 1 ) );
    }else{
      ans += 1.5;
      ans += cir( lft - 1 );
    }
  }
  if( rgt == n ){
    if( c[ n ] == 'S' )
      ans += 2;
    else
      ans += pi * 0.5;
  }else{
    if( c[ rgt ] == 'S' ){
      ans += 2;
      ans += norm( make_pair( n - 0.5 , 0.5 * sqrt( 3 ) ) -
                   make_pair( rgt , 1 ) );
    }else{
      ans += 1.5;
      ans += cir( n - rgt );
    }
  }
  printf( "%.12f\n" , ans );
}
