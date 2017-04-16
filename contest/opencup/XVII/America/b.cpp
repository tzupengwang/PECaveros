#include <bits/stdc++.h>
using namespace std;
#define N 1024
struct DJS{
  int p[ N ];
  void init( int n ){
    for( int i = 0 ; i < n ; i ++ )
      p[ i ] = i;
  }
  int f( int x ){
    return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
  }
  void uni( int x , int y ){
    p[ f( x ) ] = f( y );
  }
} djs;
typedef long long LL;
typedef pair<double,pair<double,double>> Pt;
typedef pair<Pt,Pt> Ln;
typedef vector<Pt> Fc;
#define X first
#define Y second.first
#define Z second.second
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , { p1.Y + p2.Y , p1.Z + p2.Z } };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , { p1.Y - p2.Y , p1.Z - p2.Z } };
}
Pt operator*( const Pt& p1 , double xx ){
  return { p1.X * xx, { p1.Y * xx , p1.Z * xx } };
}
Pt operator/( const Pt& p1 , double xx ){
  return { p1.X / xx, { p1.Y / xx , p1.Z / xx } };
}
Pt operator^( const Pt& p1 , const Pt& p2 ){
  return { p1.Y * p2.Z - p1.Z * p2.Y ,
           { p1.Z * p2.X - p1.X * p2.Z , 
             p1.X * p2.Y - p1.Y * p2.X } };
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y + p1.Z * p2.Z;
}
double norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( tp * tp );
}
void scan( Pt& tp ){
  scanf( "%lf%lf%lf" , &tp.X , &tp.Y , &tp.Z );
}
int n;
Pt p[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
  random_shuffle( p , p + n );
}
int id;
map< Ln , int > M;
vector< pair< double , pair<int,int> > > e;
double sum;
void build_edge( int id1 , int id2 , double td ){
  e.push_back( { td , { id1 , id2 } } );
  sum += td;
}
struct Mec{
  // return pair of center and r
  //static const int N = 1021;
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
    double d = norm( a ^ b );
    double x = p0.X + (c1 * b.Y - c2 * a.Y) / d;
    double y = p0.Y + (a.X * c2 - b.X * c1) / d;
    return {x,{y,0}};
  }
  double solve(){
    random_shuffle(p,p+n);
    r2=0;
    for (int i=0; i<n; i++){
      if (norm2(cen-p[i]) <= r2) continue;
      cen = p[i];
      r2 = 0;
      for (int j=0; j<i; j++){
        if (norm2(cen-p[j]) <= r2) continue;
        cen={(p[i].X+p[j].X)/2,{(p[i].Y+p[j].Y)/2,0}};
        r2 = norm2(cen-p[j]);
        for (int k=0; k<j; k++){
          if (norm2(cen-p[k]) <= r2) continue;
          cen = center(p[i],p[j],p[k]);
          r2 = norm2(cen-p[k]);
        }
      }
    }
    return r2;
    //return {cen,sqrt(r2)};
  }
} mec;
const double pi = acos( -1.0 );
double ans;
Pt cand[ N ];
void test( Fc f ){
  Pt p1 = f[ 1 ] - f[ 0 ] , p2 = f[ 2 ] - f[ 0 ];
  p1 = p1 / norm( p1 );
  double tmp = p1 * p2;
  p2 = p2 - ( p1 * tmp );
  p2 = p2 / norm( p2 );
  Pt pp = p1 ^ p2;
  pp = pp / norm( pp );
  double mn = 0 , mx = 0;
  for( int i = 0 ; i < n ; i ++ ){
    Pt tp = p[ i ] - f[ 0 ];
    double d1 = tp * p1;
    double d2 = tp * p2;
    cand[ i ] = { d1 , { d2 , 0 } };
    double dd = tp * pp;
    if( i == 0 ) mn = mx = dd;
    else{
      mn = min( mn , dd );
      mx = max( mx , dd );
    }
  }
  mec.init( n , cand );
  double area = pi * mec.solve();
  ans = min( ans , area * ( mx - mn ) );
}
void solve(){
  ans = 1e20;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ )
      for( int k = j + 1 ; k < n ; k ++ ){
        Pt far = ( p[ j ] - p[ i ] ) ^ ( p[ k ] - p[ i ] );
        LL vl = far * p[ i ];
        bool le = false , gr = false;
        for( int u = 0 ; u < n ; u ++ ){
          LL tvl = far * p[ u ];
          if( tvl < vl ) le = true;
          if( tvl > vl ) gr = true;
          if( le && gr ) break;
        }
        if( le && gr ) continue;
        Fc f = { p[ i ] , p[ j ] , p[ k ] };
        test( f );
      }
  printf( "%.12f\n" , ans );
}
int main(){
  init();
  solve();
}
