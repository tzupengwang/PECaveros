#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const double pi = acos( -1. );
const double R = 6370;
const double eps = 1e-6;
struct Pt{
  double X , Y , Z;
  void read(){
    double phi , theta;
    cin >> phi >> theta;
    phi = (phi / 180.) * pi;
    theta = (theta / 180.) * pi;
    X = R * cosl( phi ) * cosl( theta );
    Y = R * sinl( phi ) * cosl( theta );
    Z = R * sinl( theta );
  }
  void print(){
    printf( "(%.2f, %.2f, %.2f)\n" , X , Y , Z );
  }
  bool operator<( const Pt& he ) const{
    if( fabs( X - he.X ) > eps ) return X < he.X;
    if( fabs( Y - he.Y ) > eps ) return Y < he.Y;
    if( fabs( Z - he.Z ) > eps ) return Z < he.Z;
    return false;
  }
  bool operator==( const Pt& he ) const{
    return fabs( X - he.X ) < eps and
           fabs( Y - he.Y ) < eps and
           fabs( Z - he.Z ) < eps;
  }
};
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return {p1.X + p2.X, p1.Y + p2.Y, p1.Z + p2.Z};
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y, p1.Z - p2.Z};
}
Pt operator*( const Pt& pp , double td ){
  return {pp.X * td, pp.Y * td, pp.Z * td};
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y + p1.Z * p2.Z;
}
Pt operator^( const Pt& p1 , const Pt& p2 ){
  return { p1.Y * p2.Z - p1.Z * p2.Y ,
           p1.Z * p2.X - p1.X * p2.Z ,
           p1.X * p2.Y - p1.Y * p2.X };
}
double norm( const Pt& pp ){
  return sqrt( pp * pp );
}
Pt fit( const Pt& pp ){
  return pp * (R / norm(pp));
}
#define N 30
#define NN 1021
int n , nn;
double r;
Pt p[ NN ];
double dist( const Pt& p1 , const Pt& p2 ){
  return R * acos( min( 1. , max( -1. , (p1 * p2) / norm(p1) / norm(p2) ) ) );
}
#define K 30
void inter( const Pt& p1 , const Pt& p2 ){
  if( norm( p1 ^ p2 ) < 1e-8 ) return;
  Pt mid = fit((p1 + p2) * .5);
  Pt ver = fit(p1 ^ p2);
  if( dist( p1 , mid ) > r + eps ) return;
  for( int c1 = -1 ; c1 <= 1 ; c1 += 2 )
    for( int c2 = -1 ; c2 <= 1 ; c2 += 2 ){
      Pt lp = mid * c1 , rp = ver * c2;
      {
        double d1 = dist( p1 , lp );
        double d2 = dist( p1 , rp );
        if( d1 > r + eps and d2 > r + eps )
          continue;
        if( d1 < r - eps and d2 < r - eps )
          continue;
        if( d1 > d2 ) swap( lp , rp );
      }
      double lb = 0 , rb = 1;
      for( int _ = 0 ; _ < K ; _ ++ ){
        double bmid = (lb + rb) * .5;
        Pt cur = fit(lp * bmid + rp * (1. - bmid));
        if( dist( p1 , cur ) > r )
          lb = bmid;
        else
          rb = bmid;
      }
      p[ ++ nn ] = fit(lp * lb + rp * (1. - lb));
    }
}
#define K3 30
double fly( const Pt& p1 , const Pt& p2 ){
  if( norm( p1 ^ p2 ) < 1e-8 ) return 1e9;
  vector< pair<double,int> > cov;
  for( int i = 1 ; i <= n ; i ++ ){
    double al , ar;
    {
      double lb = 0 , rb = 1;
      for( int _ = 0 ; _ < K3 ; _ ++ ){
        double mid1 = (lb + lb + rb) / 3;
        double mid2 = (lb + rb + rb) / 3;
        Pt cand1 = fit(p1 * mid1 + p2 * (1. - mid1));
        Pt cand2 = fit(p1 * mid2 + p2 * (1. - mid2));
        if( dist( cand1 , p[ i ] ) < dist( cand2 , p[ i ] ) )
          rb = mid2;
        else
          lb = mid1;
      }
      Pt nearest = fit(p1 * lb + p2 * (1. - lb));
      if( dist( nearest , p[ i ] ) > r + eps )
        continue;
      al = ar = lb;
    }
    {
      double lb = 0 , rb = al;
      for( int _ = 0 ; _ < K ; _ ++ ){
        double bmid = (lb + rb) * .5;
        Pt cur = fit(p1 * bmid + p2 * (1. - bmid));
        if( dist( cur , p[ i ] ) > r )
          lb = bmid;
        else
          rb = bmid;
      }
      al = rb;
    }
    {
      double lb = 1 , rb = ar;
      for( int _ = 0 ; _ < K ; _ ++ ){
        double bmid = (lb + rb) * .5;
        Pt cur = fit(p1 * bmid + p2 * (1. - bmid));
        if( dist( cur , p[ i ] ) > r )
          lb = bmid;
        else
          rb = bmid;
      }
      ar = rb;
    }
    if( al < eps and ar > 1 - eps )
      return dist( p1 , p2 );
    cov.push_back( {al, +1} );
    cov.push_back( {ar, -1} );
  }
  cov.push_back( {1, 0} );
  double pre = 0 , gg = 0;
  int sum = 0;
  sort( cov.begin() , cov.end() );
  for( auto ev : cov ){
    if( sum == 0 ) gg += ev.first - pre;
    sum += ev.second;
    pre = ev.first;
  }
  return gg < eps ? dist( p1 , p2 ) : 1e9;
}
bool gt[ NN ][ NN ];
double sp[ NN ][ NN ];
void init(){
  for( int i = 1 ; i <= n ; i ++ )
    p[ i ].read();
  nn = n;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = i + 1 ; j <= n ; j ++ )
      inter( p[ i ] , p[ j ] );
  sort( p + n + 1 , p + nn + 1 );
  nn = (unique( p + n + 1 , p + nn + 1 ) - p) - 1;
  for( int i = 1 ; i <= nn ; i ++ ){
    for( int j = i + 1 ; j <= nn ; j ++ )
      sp[ i ][ j ] = 1e9;
    sp[ i ][ i ] = 0;
  }
  for( int i = 1 ; i <= n ; i ++ ){
    vector<int> cand;
    for( int j = 1 ; j <= nn ; j ++ )
      if( dist( p[ i ] , p[ j ] ) < r + eps )
        cand.push_back( j );
    for( int xx : cand )
      for( int yy : cand )
        sp[ xx ][ yy ] = dist( p[ xx ] , p[ yy ] );
  }
  for( int i = 1 ; i <= nn ; i ++ )
    for( int j = i + 1 ; j <= nn ; j ++ )
      if( sp[ i ][ j ] > 5e8 )
        sp[ i ][ j ] = sp[ j ][ i ] = fly( p[ i ] , p[ j ] );
  for( int k = 1 ; k <= nn ; k ++ )
    for( int i = 1 ; i <= nn ; i ++ )
      for( int j = 1 ; j <= nn ; j ++ )
        sp[ i ][ j ] = min( sp[ i ][ j ] , 
                            sp[ i ][ k ] + sp[ k ][ j ] );
}
double dt[ N ][ N ];
int _cs;
void solve(){
  printf( "Case %d:\n" , ++ _cs );
  int q; cin >> q; while( q -- ){
    int s , t; double c;
    cin >> s >> t >> c;
    for( int i = 1 ; i <= n ; i ++ )
      for( int j = 1 ; j <= n ; j ++ )
        dt[ i ][ j ] = ( sp[ i ][ j ] < c + eps ? 
                         sp[ i ][ j ] : 1e9 );
    for( int k = 1 ; k <= n ; k ++ )
      for( int i = 1 ; i <= n ; i ++ )
        for( int j = 1 ; j <= n ; j ++ )
          dt[ i ][ j ] = min( dt[ i ][ j ] ,
                              dt[ i ][ k ] + dt[ k ][ j ] );
    if( dt[ s ][ t ] > 1e8 )
      puts( "impossible" );
    else
      printf( "%.3f\n" , dt[ s ][ t ] );
  }
}
int main(){
  while( cin >> n >> r ){
    init();
    solve();
  }
}
