#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double type;
const double eps = 1e-8;
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
#define K 50
int n[ 2 ];
Pt p[ 2 ][ N ];
double ps[ 2 ][ N ];
double tot;
pair<Pt,Pt> cut( const Pt& p1 , const Pt& p2 , double s , double t ){
  Pt dlt = p2 - p1;
  double nn = norm(dlt);
  return {p1 + dlt * (s / nn),
          p1 + dlt * (t / nn)};
}
double mind( const Pt& p1 , const Pt& p2 , const Pt& vv ){
  Pt p3 = p2 + vv;
  double at = (p1 - p2) * (p3 - p2) / norm2(p3 - p2);
  if( -eps < at and at < 1. + eps )
    return fabs( ((p1 - p2) ^ (p3 - p2)) / norm(p3 - p2) );
  return min( norm( p1 - p2 ) , norm( p1 - p3 ) );
}
bool okay( double dlt ){
  int i[ 2 ] = {0, 0};
  while( i[ 1 ] + 1 < n[ 1 ] and ps[ 1 ][ i[ 1 ] + 1 ] < dlt + eps )
    i[ 1 ] ++;
  double cur = 0.;
  while( true ){
    double nxt = min( ps[ 0 ][ i[ 0 ] + 1 ] ,
                      ps[ 1 ][ i[ 1 ] + 1 ] - dlt );
    pair<Pt,Pt> p1 = cut( p[ 0 ][ i[ 0 ] ] , p[ 0 ][ i[ 0 ] + 1 ] ,
                          cur - ps[ 0 ][ i[ 0 ] ] , nxt - ps[ 0 ][ i[ 0 ] ] );
    pair<Pt,Pt> p2 = cut( p[ 1 ][ i[ 1 ] ] , p[ 1 ][ i[ 1 ] + 1 ] ,
                          cur - (ps[ 1 ][ i[ 1 ] ] - dlt) ,
                          nxt - (ps[ 1 ][ i[ 1 ] ] - dlt) );
    if( mind( p1.first , p2.first ,
              (p2.second - p2.first) - (p1.second - p1.first) ) < dlt + eps )
      return true;
    cur = nxt;
    if( fabs( nxt - ps[ 0 ][ i[ 0 ] + 1 ] ) < eps ) i[ 0 ] ++;
    if( fabs( nxt - (ps[ 1 ][ i[ 1 ] + 1 ] - dlt) ) < eps ) i[ 1 ] ++;
    if( i[ 0 ] == n[ 0 ] - 1 or
        i[ 1 ] == n[ 1 ] - 1 )
      break;
  }
  return false;
}
void solve(){
  double bl = 0 , br = tot;
  for( int i = 0 ; i < K ; i ++ ){
    double bmid = (bl + br) * .5;
    if( okay( bmid ) )
      br = bmid;
    else
      bl = bmid;
  }
  printf( "%.12f\n" , br );
}
int main(){
  for( int i = 0 ; i < 2 ; i ++ ){
    scanf( "%d" , &n[ i ] );
    for( int j = 0 ; j < n[ i ] ; j ++ )
      scan( p[ i ][ j ] );
    for( int j = 1 ; j < n[ i ] ; j ++ )
      ps[ i ][ j ] = ps[ i ][ j - 1 ] + norm( p[ i ][ j ] - p[ i ][ j - 1 ] );
  }
  tot = ps[ 1 ][ n[ 1 ] - 1 ];
  if( tot < norm( p[ 0 ][ 0 ] - p[ 1 ][ n[ 1 ] - 1 ] ) - eps ){
    puts( "impossible" );
    exit(0);
  }
  solve();
}
