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
const type eps = 1e-7;
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
inline pair<Pt,bool> center( Pt p0 , Pt p1 , Pt p2 ){
  Pt a = p1 - p0;
  Pt b = p2 - p0;
  double c1 = norm2( a ) * 0.5;
  double c2 = norm2( b ) * 0.5;
  double d = a ^ b;
  if( d < eps ) return { { 0 , 0 } , false };
  double x = p0.X + (c1 * b.Y - c2 * a.Y) / d;
  double y = p0.Y + (a.X * c2 - b.X * c1) / d;
  return { Pt(x, y) , true };
}
#define N 514
int n , m;
Pt p[ N ] , q[ N ];
vector< Pt > v;
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < n ; i ++ ){
    scan( p[ i ] );
    v.push_back( p[ i ] );
  }
  for( int i = 0 ; i < m ; i ++ ){
    scan( q[ i ] );
    v.push_back( q[ i ] );
  }
}
void check( const Circle& cc ){
  bool in = 0 , out = 0;
  for( int i = 0 ; i < n ; i ++ ){
    type dd = norm( p[ i ] - cc.O );
    if( dd < cc.R - eps ) in = 1;
    if( dd > cc.R + eps ) out = 1;
    if( in && out ) return;
  }
  bool in2 = 0 , out2 = 0;
  for( int i = 0 ; i < m ; i ++ ){
    type dd = norm( q[ i ] - cc.O );
    if( dd < cc.R - eps ) in2 = 1;
    if( dd > cc.R + eps ) out2 = 1;
    if( in2 && out2 ) return;
    if( in2 && in ) return;
    if( out2 && out ) return;
  }
  puts( "YES" );
  printf( "%.12f %.12f %.12f\n" , cc.O.X , cc.O.Y , cc.R );
  exit( 0 );
}
void solve(){
  for( size_t i = 0 ; i < v.size() ; i ++ )
    for( size_t j = 0 ; j < v.size() ; j ++ ){
      if( i == j ) continue;
      check( { v[ i ] , norm( v[ i ] - v[ j ] ) } );
    }
  for( size_t i = 0 ; i < v.size() ; i ++ )
    for( size_t j = i + 1 ; j < v.size() ; j ++ )
      for( size_t k = j + 1 ; k < v.size() ; k ++ ){
        pair<Pt,bool> tp = center( v[ i ] , v[ j ] , v[ k ] );
        if( !tp.second ) continue;
        check( { tp.first , norm( v[ i ] - tp.first ) } );
      }
  puts( "NO" );
}
int main(){
  freopen( "wall.in" , "r" , stdin );
  freopen( "wall.out" , "w" , stdout );
  init();
  solve();
}
