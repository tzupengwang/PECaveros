#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define double long double
typedef double type;
const double eps = 1e-10;
const double pi = acosl( -1.0 );
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
  cin >> tp.X >> tp.Y;
  //scanf( "%lf%lf" , &tp.X , &tp.Y );
}
double ang(Pt a){return atan2l(a.Y, a.X);}
Pt unit(double th){return {cosl(th), sinl(th)};}
#define PB push_back
vector<Line> tangent( Circle c1 , Circle c2){
  if( c1.R > c2.R ) swap( c1 , c2 );
  double d = norm( c1.O - c2.O );
  double phi = ang( c2.O - c1.O );
  vector<Line> res;
  if( c1.R + c2.R < d + eps ){
    double th = acosl(min((double)1., (c1.R+c2.R)/d));
    res.PB({c2.O + unit(phi + th) * c1.R, c2.O + unit(phi + pi + th) * c2.R});
    res.PB({c2.O + unit(phi - th) * c1.R, c2.O + unit(phi + pi - th) * c2.R});
  }
  if( c2.R - c1.R < d + eps){
    double th = asinl(min((double)1., (c2.R-c1.R)/d));
    res.PB({c2.O + unit(phi + pi/2 + th) * c1.R, c2.O + unit(phi + pi/2 + th) * c2.R});
    res.PB({c2.O + unit(phi - pi/2 - th) * c1.R, c2.O + unit(phi - pi/2 - th) * c2.R});
  }
  res.PB({c2.O + unit(phi) * c1.R, c2.O + unit(phi) * c1.R + unit(phi + pi/2)});
  
  vector<Line> vl;
  for(auto l: res)
    if(norm(l.first - l.second) > 1E-5 and
       !isnanl(l.first.first) and !isnanl(l.second.first))
      vl.PB(l);

  return vl;
}
vector<Line> go( const Circle& c1 , const Circle& c2 ){
  vector<Line> ret;
  double d_sq = norm2( c1.O - c2.O );
  if( d_sq < eps ) return ret;
  double d = sqrt( d_sq );
  Pt v = ( c2.O - c1.O ) / d;
  for( int sign1 = 1 ; sign1 >= -1 ; sign1 -= 2 ){
    double c = ( c1.R - sign1 * c2.R ) / d;
    if( c * c > 1 ) continue;
    double h = sqrt( max( (double)0.0 , 1.0 - c * c ) );
    for( int sign2 = 1 ; sign2 >= -1 ; sign2 -= 2 ){
      Pt n;
      n.X = v.X * c - sign2 * h * v.Y;
      n.Y = v.Y * c + sign2 * h * v.X;
      Pt p1 = c1.O + n * c1.R;
      Pt p2 = c2.O + n * ( c2.R * sign1 );
      if( fabs( p1.X - p2.X ) < eps and
          fabs( p1.Y - p2.Y ) < eps )
        p2 = p1 + perp( c2.O - c1.O );
      ret.push_back( { p1 , p2 } );
    }
  }
  return ret;
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2, bool & res){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ){
    res = false;
    return Pt( 0 , 0 );
  }
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
Pt a , b;
double da[ 3 ] , db[ 3 ];
bool ina , inb;
bool on_line( const Pt& p1 , const Pt& p2 , const Pt& pp ){
  return fabs( ( p2 - p1 ) ^ ( pp - p1 ) ) < eps;
}
void print( const Pt& pp ){
  cout << fixed << setprecision( 12 );
  cout << pp.X << " " << pp.Y << endl;
  //printf( "%.12f %.12f\n" , pp.X , pp.Y );
}
double reg( double ang ){
  while( ang < 0 ) ang += pi + pi;
  while( ang > +pi + pi ) ang -= pi + pi; 
  return ang;
}
bool in( const Pt& p1 , const Pt& p2 , const Pt& p3 , const Pt& pp ){
  double ang = 0.0;
  ang += reg( acosl( ( ( p2 - pp ) * ( p1 - pp ) ) / norm( p1 - pp ) / norm( p2 - pp ) ) );
  ang += reg( acosl( ( ( p1 - pp ) * ( p3 - pp ) ) / norm( p1 - pp ) / norm( p3 - pp ) ) );
  ang += reg( acosl( ( ( p3 - pp ) * ( p2 - pp ) ) / norm( p3 - pp ) / norm( p2 - pp ) ) );
  return ang > pi + pi - eps;
}
double dist( const Pt& p1 , const Pt& p2 , const Pt& pp ){
  double tmp = ( pp - p1 ) * ( p2 - p1 ) / norm2( p2 - p1 );
  double ret = norm( pp - ( p1 + ( p2 - p1 ) * tmp ) );
  return ret;
}
void gogo( const Pt& p1 , const Pt& p2 , const Pt& p3 ){
  if( fabs( p1.X ) > 1e9 ) return;
  if( fabs( p1.Y ) > 1e9 ) return;
  if( fabs( p2.X ) > 1e9 ) return;
  if( fabs( p2.Y ) > 1e9 ) return;
  if( fabs( p3.X ) > 1e9 ) return;
  if( fabs( p3.Y ) > 1e9 ) return;
  if( norm( p1 - p2 ) < eps ) return;
  if( norm( p1 - p3 ) < eps ) return;
  if( norm( p3 - p2 ) < eps ) return;
  if( on_line( p1 , p2 , a ) ) return;
  if( on_line( p1 , p3 , a ) ) return;
  if( on_line( p3 , p2 , a ) ) return;
  if( on_line( p1 , p2 , b ) ) return;
  if( on_line( p1 , p3 , b ) ) return;
  if( on_line( p3 , p2 , b ) ) return;
  if( on_line( p1 , p2 , p3 ) ) return;
  if( ina != in( p1 , p2 , p3 , a ) ) return;
  if( inb != in( p1 , p2 , p3 , b ) ) return;
  if( fabs( da[ 0 ] - dist( p1 , p2 , a ) ) > eps ) return;
  if( fabs( da[ 1 ] - dist( p1 , p3 , a ) ) > eps ) return;
  if( fabs( da[ 2 ] - dist( p2 , p3 , a ) ) > eps ) return;
  if( fabs( db[ 0 ] - dist( p1 , p2 , b ) ) > eps ) return;
  if( fabs( db[ 1 ] - dist( p1 , p3 , b ) ) > eps ) return;
  if( fabs( db[ 2 ] - dist( p2 , p3 , b ) ) > eps ) return;
  print( p2 ); // X
  print( p1 ); // Y
  print( p3 ); // Z
  exit(0);
}
int main(){
  scan( a );
  for( int i = 0 ; i < 3 ; i ++ )
    cin >> da[ i ];
  if( da[ 0 ] > 0 ) ina = true;
  for( int i = 0 ; i < 3 ; i ++ )
    da[ i ] = fabs( da[ i ] );
  scan( b );
  for( int i = 0 ; i < 3 ; i ++ )
    cin >> db[ i ];
  if( db[ 0 ] > 0 ) inb = true;
  for( int i = 0 ; i < 3 ; i ++ )
    db[ i ] = fabs( db[ i ] );
  vector<Line> e1 = go( { a , fabs( da[ 0 ] ) } , { b , fabs( db[ 0 ] ) } );
  vector<Line> e2 = go( { a , fabs( da[ 1 ] ) } , { b , fabs( db[ 1 ] ) } );
  vector<Line> e3 = go( { a , fabs( da[ 2 ] ) } , { b , fabs( db[ 2 ] ) } );
  if( norm( a - b ) < 1e-2 ){
    if( ina ){
      Pt sp = a - make_pair( da[ 0 ] , 0 );
      e1 = { { sp , sp + perp( make_pair( da[ 0 ] , 0 ) ) } };
      sp = a - make_pair( 0 , da[ 1 ] );
      e2 = { { sp , sp + perp( make_pair( 0 , da[ 1 ] ) ) } };
      double dd = da[ 2 ] / sqrt( 2 );
      sp = a + make_pair( dd , dd );
      e3 = { { sp , sp + perp( make_pair( dd , dd ) ) } };
    }else{
      Pt sp = a - make_pair( da[ 0 ] , 0 );
      e1 = { { sp , sp + perp( make_pair( da[ 0 ] , 0 ) ) } };
      sp = a - make_pair( 0 , da[ 1 ] );
      e2 = { { sp , sp + perp( make_pair( 0 , da[ 1 ] ) ) } };
      double dd = da[ 2 ] / sqrt( 2 );
      sp = a - make_pair( dd , dd );
      e3 = { { sp , sp + perp( make_pair( dd , dd ) ) } };
    }
  }
  for( auto l1 : e1 )
    for( auto l2 : e2 )
      for( auto l3 : e3 ){
        bool res = true;
        Pt p1 = interPnt( l1.first , l1.second , l2.first , l2.second , res );
        if( not res ) continue;
        Pt p2 = interPnt( l1.first , l1.second , l3.first , l3.second , res );
        if( not res ) continue;
        Pt p3 = interPnt( l3.first , l3.second , l2.first , l2.second , res );
        if( not res ) continue;
        gogo( p1 , p2 , p3 );
      }
  assert( false );
}
