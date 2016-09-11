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
const type eps = 1e-9;
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
struct Mec{
  // return pair of center and r^2
  static const int N = 101010;
  int n;
  Pt p[ N ], cen;
  double r2;  
  void init( int _n , Pt _p[] ){
    n = _n;
    memcpy( p , _p , sizeof(Pt) * n );
  }
  double sqr(double a){ return a*a; }
  Pt center(Pt p0, Pt p1, Pt p2) {
    Pt a = p1-p0;
    Pt b = p2-p0;
    double c1=norm2( a ) * 0.5;
    double c2=norm2( b ) * 0.5;
    double d = a ^ b;
    double x = p0.X + (c1 * b.Y - c2 * a.Y) / d;
    double y = p0.Y + (a.X * c2 - b.X * c1) / d;
    return Pt(x,y);
  }
  pair<Pt,double> solve(){
    random_shuffle(p,p+n);
    r2=0;
    for (int i=0; i<n; i++){
      if (norm2(cen-p[i]) <= r2) continue;
      cen = p[i];
      r2 = 0;
      for (int j=0; j<i; j++){
        if (norm2(cen-p[j]) <= r2) continue;
        cen = Pt((p[i].X+p[j].X)*0.5, (p[i].Y+p[j].Y)*0.5);
        r2 = norm2(cen-p[j]);
        for (int k=0; k<j; k++){
          if (norm2(cen-p[k]) <= r2) continue;
          cen = center(p[i],p[j],p[k]);
          r2 = norm2(cen-p[k]);
        }
      }
    }
    return {cen,r2};
  }
} mec;
#define N 101010
int n , k;
Pt tp[ N ];
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 0 ; i < n ; i ++ )
    scan( tp[ i ] );
}
void solvek2(){
  type bst = 1e10;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ )
      bst = min( bst , norm( tp[ i ] - tp[ j ] ) * 0.5 );
  printf( "%.9f\n" , bst );
  exit( 0 );
}
void solven3(){
  type ans = 1e10;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ )
      for( int u = j + 1 ; u < n ; u ++ ){
        Pt xp[ 3 ] = { tp[ i ] , tp[ j ] , tp[ u ] };
        mec.init( 3 , xp );
        pair<Pt,double> cir = mec.solve();
        if( cir.R > ans - eps ) continue;
        int cnt = 0;
        for( int p = 0 ; p < n ; p ++ )
          if( norm( tp[ p ] - cir.O ) < cir.R + eps )
            cnt ++;
        if( cnt >= k )
          ans = min( ans , cir.R );
      }
  printf( "%.9f\n" , ans );
  exit( 0 );
}
void solve(){
  if( k == 2 ) solvek2();
  solven3();
}
int main(){
  init();
  solve();
}
