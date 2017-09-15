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
const double eps = 1e-8;
const double pi = acos( -1.0 );
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
void print( const Circle& cc ){
  printf( "(%.6f, %.6f), R = %.6f\n" ,
          cc.O.X , cc.O.Y , cc.R );
}
Pt interPnt( Line l1, Line l2, bool &res ){
  Pt p1, p2, q1, q2;
  tie(p1, p2) = l1;
  tie(q1, q2) = l2;
  double f1 = (p2 - p1) ^ (q1 - p1);
  double f2 = (p2 - p1) ^ (p1 - q2);
  double f = (f1 + f2);
  if( fabs(f) < eps)
  { res = false; return {0, 0}; }
  res = true;
  return q1 * (f2 / f) + q2 * (f1 / f);
}
vector<Line> cand;
void go( const Circle& c1 , const Circle& c2 ){
  double d_sq = norm2( c1.O - c2.O );
  //print( c1 );
  //print( c2 );
  assert( d_sq > eps );
  double d = sqrt( d_sq );
  Pt v = ( c2.O - c1.O ) / d;

  for( int sign1 = 1 ; sign1 >= -1 ; sign1 -= 2 ){
    double c = ( c1.R - sign1 * c2.R ) / d;
    //if( c * c > 1 ) continue;
    double h = sqrt( max( 0.0 , 1.0 - c * c ) );
    for( int sign2 = 1 ; sign2 >= -1 ; sign2 -= 2 ){
      Pt n;
      n.X = v.X * c - sign2 * h * v.Y;
      n.Y = v.Y * c + sign2 * h * v.X;
      Pt p1 = c1.O + n * c1.R;
      Pt p2 = c2.O + n * ( c2.R * sign1 );
      if( fabs( p1.X - p2.X ) < eps and
          fabs( p1.Y - p2.Y ) < eps )
        p2 = p1 + perp( c2.O - c1.O );
      cand.push_back( { p1 , p2 } );
      //cand.push_back( { c1.O + n * c1.R ,
                        //c2.O + n * ( c2.R * sign1 ) } );
    }
  }
}
void scan( Circle& tc ){
  cin >> tc.O.X >> tc.O.Y >> tc.R;
}
void print( const Pt& tp ){
  printf( "%.12f %.12f\n" , tp.X , tp.Y );
}
bool Intersec( const Pt& p1 , const Pt& p2 , Circle& cc ){
  Pt dp = p2 - p1;
  double a = dp * dp;
  double b = 2 * ( dp * ( p1 - cc.O ) );
  double c = cc.O * cc.O + p1 * p1 - 2 * ( cc.O * p1 ) - cc.R * cc.R;
  double bb4ac = b * b - 4 * a * c;
  return !( fabs( a ) < eps or bb4ac < 0 );
}
Pt rotate( const Pt& pp , double ang ){
  return { pp.X * cos( ang ) - pp.Y * sin( ang ) ,
           pp.X * sin( ang ) + pp.Y * cos( ang ) };
}
int n;
#define N 12
Circle c[ N ];
double x , y;
bool okay( const Pt& pp ){
  if( pp.X < 0 or pp.X > x or
      pp.Y < 0 or pp.Y > y )
    return false;
  for( int i = 0 ; i < n ; i ++ )
    if( norm( pp - c[ i ].O ) < c[ i ].R - eps )
      return false;
  vector< pair<double,int> > vv;
  for( int i = 0 ; i < n ; i ++ ){
    Pt tmp = c[ i ].O - pp;
    double mid = atan2( tmp.Y , tmp.X );
    double alpha = asin( c[ i ].R / norm( pp - c[ i ].O ) );
    double lb = mid - alpha , rb = mid + alpha;
    for( int zz = -1 ; zz <= 1 ; zz ++ ){
      vv.push_back( { lb + zz * ( pi + pi ) , +1 } );
      vv.push_back( { rb + zz * ( pi + pi ) , -1 } );
    }
  }
  sort( vv.begin() , vv.end() );
  double ss = 0;
  int cnt = 0;
  for( size_t i = 0 ; i < vv.size() ; i ++ ){
    if( i and cnt > 1 )
      ss += vv[ i ].first - vv[ i - 1 ].first;
    cnt += vv[ i ].second;
  }
  //print( pp );
  //printf( " %.12f\n" , ss );
  return ss < eps;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "zen.in" , "r" , stdin );
  freopen( "zen.out" , "w" , stdout );
#endif
  cin >> n >> x >> y;
  cand.push_back( { { 0 , 0 } , { x , 0 } } );
  cand.push_back( { { 0 , y } , { x , y } } );
  cand.push_back( { { 0 , 0 } , { 0 , y } } );
  cand.push_back( { { x , 0 } , { x , y } } );
  for( int i = 0 ; i < n ; i ++ )
    scan( c[ i ] );
  random_shuffle( c , c + n );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ )
      go( c[ i ] , c[ j ] );
  //for( auto l : cand ){
    //print( l.X );
    //print( l.Y );
    //puts( "====" );
  //}
  for( size_t i = 0 ; i < cand.size() ; i ++ )
    for( size_t j = i + 1 ; j < cand.size() ; j ++ ){
      bool r;
      Pt candp = interPnt( cand[ i ] , cand[ j ] , r );
      if( !r ) continue;
      if( okay( candp ) ){
        print( candp );
        exit( 0 );
      }
    }
  puts( "No Zen" );
}
