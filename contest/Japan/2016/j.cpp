#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
const double pi = acosl( -1 );
const double eps = 1e-8;
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
void print( const Pt& tp , char ap = ' ' ){
  fprintf( stderr , "%.3f %.3f%c" , tp.X , tp.Y , ap );
}
#define N 12
#define K 60
#define KK 1021
#define PER 100
int n; double r;
Pt p[ N ] , tp[ N ] , o;
int sgn[ N ];
inline double normal( double xx ){
  while( xx < 0 ) xx += pi + pi;
  while( xx > pi + pi ) xx -= pi + pi;
  return xx;
}
inline double ang( const Pt& p1 , const Pt& p2 ){
  return normal( acosl( ( p1 * p2 ) / norm( p1 ) / norm( p2 ) ) );
}
inline pair<double,double> min_dist( const Pt& p1 , const Pt& p2 ){
  double tmp = min( norm( p1 ) , norm( p2 ) );
  Pt dlt = p2 - p1;
  Pt vv2 = make_pair( 0 , 0 ) - p1;
  double vv = ( vv2 * dlt ) / norm2( dlt );
  if( -eps < vv and vv < 1 + eps )
    tmp = min( tmp , norm( p1 + dlt * vv ) );
  return { tmp , vv };
}
inline double cal( const Pt& p1 , const Pt& p2 ){
  double r1 = norm( p1 );
  double r2 = norm( p2 );
  if( max( r1 , r2 ) < r + eps )
    return fabs( p1 ^ p2 ) * 0.5;
  pair<double,double> md = min_dist( p1 , p2 );
  if( md.first > r - eps ){
    double all = pi * r * r;
    return all / ( pi + pi ) * ang( p1 , p2 );
  }
  if( min( r1 , r2 ) > r - eps ){
    Pt mid = p1 + ( p2 - p1 ) * md.second;
    Pt pp1 , pp2;
    {
      Pt dir = p1 - mid;
      double bl = 0 , br = 1;
      for( int i = 0 ; i < K ; i ++ ){
        double bmid = (bl + br) * 0.5;
        Pt tmp = mid + dir * bmid;
        if( norm( tmp ) < r )
          bl = bmid;
        else
          br = bmid;
      }
      pp1 = mid + dir * bl;
    }
    {
      Pt dir = p2 - mid;
      double bl = 0 , br = 1;
      for( int i = 0 ; i < K ; i ++ ){
        double bmid = (bl + br) * 0.5;
        Pt tmp = mid + dir * bmid;
        if( norm( tmp ) < r )
          bl = bmid;
        else
          br = bmid;
      }
      pp2 = mid + dir * bl;
    }
    return cal( p1 , pp1 ) +
           cal( pp1 , pp2 ) +
           cal( pp2 , p2 );
  }
  if( r1 < r2 ){
    Pt dir = p2 - p1;
    double bl = 0 , br = 1;
    for( int i = 0 ; i < K ; i ++ ){
      double bmid = (bl + br) * 0.5;
      Pt tmp = p1 + dir * bmid;
      double rr = norm( tmp );
      if( rr > r ) br = bmid;
      else bl = bmid;
    }
    Pt tmp = p1 + dir * bl;
    return cal( p1 , tmp ) + cal( tmp , p2 );
  }
  Pt dir = p1 - p2;
  double bl = 0 , br = 1;
  for( int i = 0 ; i < K ; i ++ ){
    double bmid = (bl + br) * 0.5;
    Pt tmp = p2 + dir * bmid;
    double rr = norm( tmp );
    if( rr > r ) br = bmid;
    else bl = bmid;
  }
  Pt tmp = p2 + dir * bl;
  return cal( p1 , tmp ) + cal( tmp , p2 );
}
double cal( const Pt& oo ){
  for( int i = 0 ; i < n ; i ++ )
    tp[ i ] = p[ i ] - oo;
  tp[ n ] = tp[ 0 ];
  double ret = 0;
  for( int i = 0 ; i < n ; i ++ ){
    double tmp = tp[ i ] ^ ( tp[ i + 1 ] );
    if( fabs( tmp ) < eps ) continue;
    int tsgn = 1;
    if( tmp < 0 ) tsgn = -1;
    //print( tp[ i ] );
    //print( tp[ i + 1 ] , '\n' );
    //printf( "%d %.6f\n" ,
            //tsgn , cal( tp[ i ] , tp[ i + 1 ] ) );
    ret += tsgn * cal( tp[ i ] , tp[ i + 1 ] );
  }
  return fabs( ret );
}
void init(){
  scanf( "%d" , &n );
  scanf( "%lf" , &r );
  for( int i = 0 ; i < n ; i ++ ){
    scan( p[ i ] );
    o = o + p[ i ];
  }
  o = o / n;
}
const double down = 0.93;
inline Pt rotate( const Pt& pp , double aa ){
  return { pp.X * cosl( aa ) - pp.Y * sinl( aa ) ,
           pp.X * sinl( aa ) + pp.Y * cosl( aa ) };
}
void solve(){
  double ans = 0.0;
  double dep = 200;
  for( int i = 0 ; i < KK ; i ++ ){
    Pt bst = o;
    double ba = cal( bst );
    for( int j = 0 ; j < PER ; j ++ ){
      double ang = ( pi + pi ) / (double)PER * j;
      Pt nxti = o + rotate( { dep , 0 } , ang );
      double tmp = cal( nxti );
      if( tmp > ba ){
        ba = tmp;
        bst = nxti;
      }
    }
    o = bst;
    ans = max( ans , ba );
    dep *= down;
  }
  //fprintf( stderr , "%.12f %.12f\n" , o.X , o.Y );
  printf( "%.12f\n" , ans );
}
int main(){
  init();
  solve();
}
