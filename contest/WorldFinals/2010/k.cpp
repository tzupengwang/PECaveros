#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const double eps = 1e-8;
struct Pt{
  double X , Y , Z;
  bool read(){
    if( scanf( "%lf%lf%lf" , &X , &Y , &Z ) == 3 )
      return true;
    return false;
  }
  void print(){
    fprintf( stderr , "%.2f %.2f %.2f\n" , X , Y , Z );
  }
};
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return {p1.X + p2.X, p1.Y + p2.Y, p1.Z + p2.Z};
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y, p1.Z - p2.Z};
}
Pt operator*( const Pt& pp , double tk ){
  return {pp.X * tk ,
          pp.Y * tk ,
          pp.Z * tk };
}
Pt operator/( const Pt& pp , double tk ){
  return {pp.X / tk ,
          pp.Y / tk ,
          pp.Z / tk };
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y + p1.Z * p2.Z;
}
Pt operator^( const Pt& p1 , const Pt& p2 ){
  return {p1.Y * p2.Z - p1.Z * p2.Y,
          p1.Z * p2.X - p1.X * p2.Z,
          p1.X * p2.Y - p1.Y * p2.X};
}
double norm( const Pt& pp ){
  return sqrt( pp * pp );
}
double norm2( const Pt& pp ){
  return pp * pp;
}
Pt a , b , c , d , e , f;
Pt project( const Pt& p1 , const Pt& p2 ){
  return p2 * ((p1 * p2) / norm2( p2 ));
}
Pt find_center(){
  Pt cenab = (a + b) * .5;
  Pt cen = (cenab * 2. + c ) / 3;
  Pt cend = (cen * 3. + d) / 4;
  Pt cene = (cen * 3. + e) / 4;
  Pt far = (b - a) ^ (c - a);
  double vold = norm( project( d - a , far ) );
  double vole = norm( project( e - a , far ) );
  return (cend * vold + cene * vole) / (vold + vole);
}
double min_ans , max_ans;
bool got;

void test( const Pt& fa , const Pt& pp , bool& lft , bool& rgt ){
  double v = fa * pp;
  if( v < -eps ) lft = true;
  if( v > +eps ) rgt = true;
}

void cal( Pt p1 , Pt p2 , Pt p3 , Pt cen , Pt goal , Pt o1 , Pt o2 ){

  bool left = false , right = false;

  p2 = p2 - p1;
  p3 = p3 - p1;
  cen = cen - p1;
  goal = goal - p1;
  o1 = o1 - p1;
  o2 = o2 - p1;
  
  Pt far = p2 ^ p3;

  test( far , o1 , left , right );
  test( far , o2 , left , right );
  if( left and right ) return;

  Pt x = cen - project( cen , far );
  Pt x2 = x - project( x , p2 );
  Pt x3 = x - project( x , p3 );
  Pt x4 = x - p2 - project( x - p2 , p3 - p2 );

  double t1 = (x * p2) / norm2( p2 );
  double t2 = (x * p3) / norm2( p3 );
  double cur = norm( project( goal , far ) );
  if( t1 < -eps or t2 < -eps or t1 + t2 > 1 + eps ){
    if( norm( x2 ) > 0.2 and
        norm( x3 ) > 0.2 and
        norm( x4 ) > 0.2 )
      return;
  }
  cerr << cur << endl;
  if( not got ){
    min_ans = max_ans = cur;
    got = true;
  }else{
    min_ans = min( min_ans , cur );
    max_ans = max( max_ans , cur );
  }
}
int _cs;
void solve(){
  got = false;
  Pt cen = find_center();
  cen.print();
  cal( a , b , d , cen , f , c , e );
  cal( a , b , e , cen , f , c , d );
  cal( a , c , d , cen , f , b , e );
  cal( a , c , e , cen , f , b , d );
  cal( b , c , d , cen , f , a , e );
  cal( b , c , e , cen , f , a , d );
  cal( d , e , a , cen , f , b , c );
  cal( d , e , b , cen , f , a , c );
  cal( d , e , c , cen , f , a , b );
  printf( "Case %d: %.5f %.5f\n" , ++ _cs , min_ans , max_ans );
}
int main(){
  while( a.read() ){
    b.read();
    c.read();
    d.read();
    e.read();
    f.read();
    solve();
  }
}
