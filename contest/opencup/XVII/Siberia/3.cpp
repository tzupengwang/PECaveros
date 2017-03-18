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
const double eps1 = 1;
const double eps2 = 1e-8;
const double eps = 1e-7;
inline bool equal( double a , double b ){
  return a - eps < b and b < a + eps;
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
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
// {p,q} p : ax + by <= c
pair<double,double> ask( double a , double b , double c ){
  printf( "? %.12f %.12f %.12f\n" , a , b , c );
  fflush( stdout );
  double p , q;
  scanf( "%lf%lf" , &p , &q );
  return { p , q };
}
tuple<double,double,double> lline( const Pt& p1 , const Pt& p2 ){
  if( equal( p1.X , p2.X ) ) return make_tuple( 1 , 0 , p1.X );
  if( equal( p1.Y , p2.Y ) ) return make_tuple( 0 , 1 , p1.Y );
  Pt ver = perp( p2 - p1 );
  if( ver.X < 0.0 ){
    ver.X *= -1;
    ver.Y *= -1;
  }
  return make_tuple( ver.X , ver.Y , ver * p1 );
}
void answer( Pt p1 , Pt p2 , Pt p3 ){
  for( int _ = 0 ; _ < 2 ; _ ++ ){
    double lb = 1e-4 , rb = 1;
    for( int i = 0 ; i < 40 ; i ++ ){
      double mid = ( lb + rb ) * 0.5;
      Pt pp = p1 + ( p3 - p1 ) * mid;
      auto gg = lline( pp , p2 );
      auto ret = ask( get<0>( gg ) , get<1>( gg ) , get<2>( gg ) );
      double tk = min( ret.first , ret.second );
      if( tk < eps ) rb = mid;
      else lb = mid;
    }
    p3 = p1 + ( p3 - p1 ) * ( ( lb + rb ) * 0.5 );
    swap( p2 , p3 );
  }
  for( int _ = 0 ; _ < 2 ; _ ++ ){
    double lb = 1e-4 , rb = 1;
    for( int i = 0 ; i < 40 ; i ++ ){
      double mid = ( lb + rb ) * 0.5;
      Pt pp = p2 + ( p3 - p2 ) * mid;
      auto gg = lline( pp , p1 );
      auto ret = ask( get<0>( gg ) , get<1>( gg ) , get<2>( gg ) );
      double tk = min( ret.first , ret.second );
      if( tk < eps ) rb = mid;
      else lb = mid;
    }
    p3 = p2 + ( p3 - p2 ) * ( ( lb + rb ) * 0.5 );
    swap( p2 , p3 );
  }
  printf( "! %d %d %d %d %d %d\n" ,
          (int)round( p1.X ) , (int)round( p1.Y ) , 
          (int)round( p2.X ) , (int)round( p2.Y ) ,
          (int)round( p3.X ) , (int)round( p3.Y ) );
  fflush( stdout );
  exit(0);
}
inline int len( const pair<int,int>& p1 , const pair<int,int>& p2 ){
  return abs( p1.X - p2.X ) + abs( p1.Y - p2.Y );
}
inline Pt at( const pair<int,int>& p1 ,
              const pair<int,int>& p2 , int tlen ){
  if( p1.X == p2.X )
    return { p1.X , p1.Y + tlen * ( ( p2.Y - p1.Y ) / abs( p2.Y - p1.Y ) ) };
  return { p1.X + tlen * ( ( p2.X - p1.X ) / abs( p2.X - p1.X ) ) , p1.Y };
}
inline Pt at( const pair<int,int>& p1 ,
              const pair<int,int>& p2 ,
              const pair<int,int>& p3 ,
              int xx ){
  if( xx <= len( p1 , p2 ) )
    return at( p1 , p2 , xx );
  return at( p2 , p3 , xx - len( p1 , p2 ) );
}
int r1 , r2;
void solve( const Pt& op ,
            const pair<int,int>& p1 ,
            const pair<int,int>& p2 ,
            const pair<int,int>& p3 ){
  int tlen = len( p1 , p2 ) + len( p2 , p3 );
  r1 = tlen; r2 = 0;
  {
    int bl = 0 , br = tlen;
    while( bl <= br ){
      int mid = ( bl + br ) >> 1;
      Pt who = at( p1 , p2 , p3 , mid );
      auto gg = lline( who , op );
      if( equal( ask( get<0>( gg ) , get<1>( gg ) , get<2>( gg ) ).first , 0.0 ) )
        r1 = mid , br = mid - 1;
      else bl = mid + 1; 
    }
  }
  {
    int bl = 0 , br = tlen;
    while( bl <= br ){
      int mid = ( bl + br ) >> 1;
      Pt who = at( p1 , p2 , p3 , mid );
      auto gg = lline( who , op );
      if( equal( ask( get<0>( gg ) , get<1>( gg ) , get<2>( gg ) ).first , 1.0 ) )
        bl = mid + 1 , r2 = mid;
      else br = mid - 1; 
    }
  }
  Pt who1 = at( p1 , p2 , p3 , r1 );
  Pt who2 = at( p1 , p2 , p3 , r2 );
  answer( op , who1 , who2 );
}
int lx , rx , ly , ry;
int main(){
  {
    int bl = -1000 , br = 1000;
    while( bl <= br ){
      int mid = ( bl + br ) >> 1;
      auto ret = ask( 1 , 0 , mid );
      if( equal( ret.first , 0 ) )
        lx = mid , bl = mid + 1;
      else
        br = mid - 1;
    }
  }
  {
    int bl = -1000 , br = 1000;
    while( bl <= br ){
      int mid = ( bl + br ) >> 1;
      auto ret = ask( 1 , 0 , mid );
      if( equal( ret.first , 1 ) )
        rx = mid , br = mid - 1;
      else
        bl = mid + 1;
    }
  }
  {
    int bl = -1000 , br = 1000;
    while( bl <= br ){
      int mid = ( bl + br ) >> 1;
      auto ret = ask( 0 , 1 , mid );
      if( equal( ret.first , 0 ) )
        ly = mid , bl = mid + 1;
      else
        br = mid - 1;
    }
  }
  {
    int bl = -1000 , br = 1000;
    while( bl <= br ){
      int mid = ( bl + br ) >> 1;
      auto ret = ask( 0 , 1 , mid );
      if( equal( ret.first , 1 ) )
        ry = mid , br = mid - 1;
      else
        bl = mid + 1;
    }
  }
  auto ret = ask( 1 , -1 , lx - ry + eps1 );
  if( ret.first > eps2 )
    solve( { lx , ry } , { rx , ry } , { rx , ly } , { lx , ly } );
       ret = ask( -1 , 1 , - rx + ly + eps1 );
  if( ret.first > eps2 )
    solve( { rx , ly } , { rx , ry } , { lx , ry } , { lx , ly } );
       ret = ask( 1 , 1 , lx + ly + eps1 );
  if( ret.first > eps2 )
    solve( { lx , ly } , { rx , ly } , { rx , ry } , { lx , ry } );
  solve( { rx , ry } , { rx , ly } , { lx , ly } , { lx , ry } );
}
