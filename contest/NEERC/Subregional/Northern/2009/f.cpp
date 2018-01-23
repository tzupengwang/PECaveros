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
const type pi = acos( -1.0 );
const type eps = 1e-8;
inline bool equal( type t1 , type t2 ){
  return t1 - eps < t2 && t2 < t1 + eps;
}
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
bool operator==( const Pt& p1 , const Pt& p2 ){
  return equal( p1.X , p2.X ) &&
         equal( p1.Y , p2.Y );
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
  printf( "%.6f %.6f\n" , tp.X , tp.Y );
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2 ){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ) return Pt( nan(""), nan("") );
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
inline Pt rotate( const Pt& p1 , type deg ){
  type theta = deg / 180.0 * pi;
  return { cos( theta ) * p1.X - sin( theta ) * p1.Y ,
           sin( theta ) * p1.X + cos( theta ) * p1.Y };
}
Pt p[ 4 ];
void init(){
  for( int i = 0 ; i < 4 ; i ++ )
    scan( p[ i ] );
}
Pt o[ 2 ];
#define K2 3
#define K 100000
void go( int op ){
  int os = 0;
  for( int i = 1 ; i < 4 ; i ++ )
    if( i != op )
      o[ os ++ ] = p[ i ];
  Pt dir = p[ op ] - p[ 0 ];
  dir = dir / norm( dir );
  for( int _ = 0 ; _ < K2 ; _ ++ ){
    type deg = 180.0 * ( (type)( _ * 2 + 1 ) / ( 2 * K2 ) );
    type dlt = 180.0 / (type)(2.0 * K2);
    type rr = 0.7;
    for( int __ = 0 ; __ < K ; __ ++ ){
      Pt dir1 = rotate( dir , deg );
      Pt dir2 = perp( dir1 );
      type dst1 = fabs( perp( dir1 ) * p[ 0 ] - perp( dir1 ) * p[ op ] );
      type dst2 = fabs( perp( dir2 ) * o[ 0 ] - perp( dir2 ) * o[  1 ] );
      if( equal( dst1 , dst2 ) ){
        vector< Pt > ans;
        ans.push_back( interPnt( p[ 0 ] , p[ 0 ] + dir1 , o[ 0 ] , o[ 0 ] + dir2 ) );
        ans.push_back( interPnt( p[ op ] , p[ op ] + dir1 , o[ 0 ] , o[ 0 ] + dir2 ) );
        ans.push_back( interPnt( p[ op ] , p[ op ] + dir1 , o[ 1 ] , o[ 1 ] + dir2 ) );
        ans.push_back( interPnt( p[ 0 ] , p[ 0 ] + dir1 , o[ 1 ] , o[ 1 ] + dir2 ) );
        bool flag = true;
        for( size_t i = 0 ; i < 4 && flag ; i ++ )
          for( size_t j = 0 ; j < 4 ; j ++ )
            if( ans[ i ] == p[ j ] ){
              flag = false;
              break;
            }
        {
          type c1 = perp( dir1 ) * p[ 0 ] , c2 = perp( dir1 ) * p[ op ];
          if( c1 > c2 ) swap( c1 , c2 );
          type d1 = perp( dir1 ) * o[ 0 ];
          if( d1 < c1 + eps || d1 > c2 - eps ) flag = false;
          type d2 = perp( dir1 ) * o[ 1 ];
          if( d2 < c1 + eps || d2 > c2 - eps ) flag = false;
        }
        {
          type c1 = perp( dir2 ) * o[ 0 ] , c2 = perp( dir2 ) * o[ 1 ];
          if( c1 > c2 ) swap( c1 , c2 );
          type d1 = perp( dir2 ) * p[ 0 ];
          if( d1 < c1 + eps || d1 > c2 - eps ) flag = false;
          type d2 = perp( dir2 ) * p[ op ];
          if( d2 < c1 + eps || d2 > c2 - eps ) flag = false;
        }
        if( flag ){
          for( auto i : ans )
            printf( "%.9f %.9f\n" , i.X , i.Y );
          exit( 0 );
        }
      }
      type bst1 = fabs( dst1 - dst2 ) , who = deg;
      {
        dir1 = rotate( dir , deg + dlt );
        dir2 = perp( dir1 );
        dst1 = fabs( perp( dir1 ) * p[ 0 ] - perp( dir1 ) * p[ op ] );
        dst2 = fabs( perp( dir2 ) * o[ 0 ] - perp( dir2 ) * o[  1 ] );
        type tmp = fabs( dst1 - dst2 );
        if( tmp < bst1 ){
          bst1 = tmp;
          who = deg + dlt;
        }
      }
      {
        dir1 = rotate( dir , deg - dlt );
        dir2 = perp( dir1 );
        dst1 = fabs( perp( dir1 ) * p[ 0 ] - perp( dir1 ) * p[ op ] );
        dst2 = fabs( perp( dir2 ) * o[ 0 ] - perp( dir2 ) * o[  1 ] );
        type tmp = fabs( dst1 - dst2 );
        if( tmp < bst1 ){
          bst1 = tmp;
          who = deg - dlt;
        }
      }
      dlt *= rr;
      deg = who;
    }
  }
}
void solve(){
  for( int i = 1 ; i < 4 ; i ++ )
    go( i );
  puts( "0 0" );
  puts( "0 0" );
  puts( "0 0" );
  puts( "0 0" );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "four.in" , "r" , stdin );
  freopen( "four.out" , "w" , stdout );
#endif
  init();
  solve();
}
