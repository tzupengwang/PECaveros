#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> PL;
typedef pair<double,double> Pt;
const double pi = acos( -1. );
const double eps = 1e-7;
#define X first
#define Y second

template<typename T>
pair<T,T> operator+( const pair<T,T>& p1 , const pair<T,T>& p2 ){
  return {p1.X + p2.X, p1.Y + p2.Y};
}
template<typename T>
pair<T,T> operator-( const pair<T,T>& p1 , const pair<T,T>& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y};
}
template<typename T>
pair<T,T> operator*( const pair<T,T>& p1 , T tk ){
  return {p1.X * tk, p1.Y * tk};
}
template<typename T>
T operator*( const pair<T,T>& p1 , const pair<T,T>& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
template<typename T>
T operator^( const pair<T,T>& p1 , const pair<T,T>& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
template<typename T>
T norm2( const pair<T,T>& tp ){
  return tp * tp;
}
template<typename T>
double norm( const pair<T,T>& tp ){
  return sqrt( tp * tp );
}
void scan( PL& pp ){
  cin >> pp.X >> pp.Y;
}
void print( const Pt& pp ){
  printf( "%.6f %.6f\n" , pp.X , pp.Y );
}
bool between( const PL& p1 , const PL& pp , const PL& p2 ){
  if( (pp - p1) ^ (p2 - p1) ) return false;
  return ((pp - p1) * (p2 - p1)) >= 0 and
         ((pp - p2) * (p1 - p2)) >= 0;
}
bool betweenp( const Pt& p1 , const Pt& pp , const Pt& p2 ){
  if( fabs((pp - p1) ^ (p2 - p1)) > eps )
    return false;
  return ((pp - p1) * (p2 - p1)) > -eps and
         ((pp - p2) * (p1 - p2)) > -eps;
}
double angle( const Pt& p1 , const Pt& p2 ){
  double theta = acos( max( -1. , min( 1. , (p1 * p2) / norm(p1) / norm(p2) ) ) );
  if( (p1 ^ p2) > -eps ) return theta;
  return -theta;
}
int ori( const Pt& o , const Pt& a , const Pt& b ){
  double ret = ( a - o ) ^ ( b - o );
  return (ret > eps) - (ret < -eps);
}
// p1 == p2 || q1 == q2 need to be handled
bool banana( const Pt& p1 , const Pt& p2 ,
             const Pt& q1 , const Pt& q2 ){
  if( fabs( ( p2 - p1 ) ^ ( q2 - q1 ) ) < eps ){ // parallel
    return false;
  }
  return (ori( p1, p2, q1 ) * ori( p1, p2, q2 ) < eps) &&
         (ori( q1, q2, p1 ) * ori( q1, q2, p2 ) < eps);
}
int ori( const PL& o , const PL& a , const PL& b ){
  LL ret = ( a - o ) ^ ( b - o );
  return ret / max( 1ll , abs( ret ) );
}
// p1 == p2 || q1 == q2 need to be handled
bool bananaExact( const PL& p1 , const PL& p2 ,
                  const PL& q1 , const PL& q2 ){
  if( ( ( p2 - p1 ) ^ ( q2 - q1 ) ) == 0 ){ // parallel
    return false;
  }
  return (ori( p1, p2, q1 ) * ori( p1, p2, q2 )<=0) &&
         (ori( q1, q2, p1 ) * ori( q1, q2, p2 )<=0);
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ) return {0, 0};
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
double cross(Pt o, Pt a, Pt b){
  return (a-o) ^ (b-o);
}
vector<Pt> convex_hull(vector<Pt> pt){
  if(pt.empty()) return pt;
  sort(pt.begin(),pt.end());
  int top=0;
  vector<Pt> stk(2*pt.size());
  for (int i=0; i<(int)pt.size(); i++){
    while (top >= 2 && cross(stk[top-2],stk[top-1],pt[i]) < eps)
      top--;
    stk[top++] = pt[i];
  }
  for (int i=pt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-2],stk[top-1],pt[i]) < eps)
      top--;
    stk[top++] = pt[i];
  }
  stk.resize(top-1);
  return stk;
}
struct Poly{
  vector<PL> v;
  vector<Pt> vp;
  PL dir;
  Pt dirp;
  void read(){
    int n; cin >> n;
    v.resize( n );
    vp.clear();
    for( int i = 0 ; i < n ; i ++ ){
      scan( v[ i ] );
      vp.push_back( v[ i ] );
    }
    v.push_back( v[ 0 ] );
    vp.push_back( vp[ 0 ] );
    scan( dir );
    dirp = dir;
  }
  void advance( double cur ){
    for( size_t i = 0 ; i < v.size() ; i ++ )
      vp[ i ] = (Pt)v[ i ] + dirp * cur;
  }
  bool containExact( const PL& pp ) const{
    for( size_t i = 0 ; i + 1 < v.size() ; i ++ )
      if( between( v[ i ] , pp , v[ i + 1 ] ) )
        return true;
    double sum = 0;
    for( size_t i = 0 ; i + 1 < v.size() ; i ++ )
      sum += angle( v[ i ] - pp , v[ i + 1 ] - pp );
    sum = fabs( sum );
    return sum > pi;
  }
  bool contain( const Pt& pp ) const{
    for( size_t i = 0 ; i + 1 < vp.size() ; i ++ )
      if( betweenp( vp[ i ] , pp , vp[ i + 1 ] ) )
        return true;
    double sum = 0;
    for( size_t i = 0 ; i + 1 < vp.size() ; i ++ )
      sum += angle( vp[ i ] - pp , vp[ i + 1 ] - pp );
    sum = fabs( sum );
    return sum > pi;
  }
  void print() const{
    puts( "Polygon" );
    for( size_t i = 0 ; i + 1 < vp.size() ; i ++ )
      printf( "%.6f %.6f\n" , vp[ i ].X , vp[ i ].Y );
    puts( "..." );
  }
} p[ 2 ];
double Area( double cur , Poly& c1 , const Poly& c2 ){
  vector<Pt> cand;
  c1.advance( cur );
  for( size_t i = 0 ; i + 1 < c1.vp.size() ; i ++ )
    if( c2.contain( c1.vp[ i ] ) )
      cand.push_back( c1.vp[ i ] );
  for( size_t i = 0 ; i + 1 < c2.vp.size() ; i ++ )
    if( c1.contain( c2.vp[ i ] ) )
      cand.push_back( c2.vp[ i ] );
  for( size_t i = 0 ; i + 1 < c1.vp.size() ; i ++ )
    for( size_t j = 0 ; j + 1 < c2.vp.size() ; j ++ )
      if( banana( c1.vp[ i ] , c1.vp[ i + 1 ],
                  c2.vp[ j ] , c2.vp[ j + 1 ] ) )
        cand.push_back( interPnt( c1.vp[ i ] , c1.vp[ i + 1 ],
                                  c2.vp[ j ] , c2.vp[ j + 1 ] ) );
  cand = convex_hull( cand );
  double ret = 0;
  for( size_t i = 0 ; i < cand.size() ; i ++ )
    ret += cand[ i ] ^ cand[ (i + 1) % cand.size() ];
  return fabs( ret );
}
bool intersectExact( const Poly& c1 , const Poly& c2 ){
  for( size_t i = 0 ; i + 1 < c1.v.size() ; i ++ )
    if( c2.containExact( c1.v[ i ] ) )
      return true;
  for( size_t i = 0 ; i + 1 < c2.v.size() ; i ++ )
    if( c1.containExact( c2.v[ i ] ) )
      return true;
  for( size_t i = 0 ; i + 1 < c1.v.size() ; i ++ )
    for( size_t j = 0 ; j + 1 < c2.v.size() ; j ++ )
      if( bananaExact( c1.v[ i ] , c1.v[ i + 1 ],
                       c2.v[ j ] , c2.v[ j + 1 ] ) )
        return true;
  return false;
}
double times( const Pt& p1 , const Pt& p2 , const Pt& pp ){
  return (pp - p1) * (p2 - p1) / norm2( p2 - p1 );
}
void upd( const PL& pp , const PL& dd , const Poly& ch , double& lt , double& rt ){
  PL til = pp + dd * 10000000LL;
  for( size_t i = 0 ; i + 1 < ch.v.size() ; i ++ ){
    PL p1 = ch.v[ i ] , p2 = ch.v[ i + 1 ];
    if( ((p2 - p1) ^ dd) == 0 ){
      if( (p2 - pp) ^ dd ) continue;
      if( between( pp , p1 , til ) or between( pp , p2 , til ) ){
        double t1 = times( pp , pp + dd , p1 );
        double t2 = times( pp , pp + dd , p2 );
        if( t1 > t2 ) swap( t1 , t2 );
        t1 = max(t1, 0.);
        t2 = max(t2, 0.);
        lt = min( lt , t1 );
        rt = max( rt , t2 );
      }
      continue;
    }
    if( bananaExact( pp , til , p1 , p2 ) ){
      Pt ii = interPnt( pp , til , p1 , p2 );
      double tt = times( pp , pp + dd , ii );
      lt = min( lt , tt );
      rt = max( rt , tt );
    }
  }
}
int main(){
  p[ 0 ].read();
  p[ 1 ].read();
  p[ 0 ].dir  = p[ 0 ].dir  - p[ 1 ].dir ;
  p[ 0 ].dirp = p[ 0 ].dirp - p[ 1 ].dirp;
  if( p[ 0 ].dir.X == 0 and p[ 0 ].dir.Y == 0 ){
    if( intersectExact( p[ 0 ] , p[ 1 ] ) )
      puts( "0" );
    else
      puts( "never" );
    return 0;
  }
  double lt = 1e10 , rt = -1e10;
  for( size_t i = 0 ; i + 1 < p[ 0 ].v.size() ; i ++ )
    upd( p[ 0 ].v[ i ] , p[ 0 ].dir * +1LL , p[ 1 ] , lt , rt );
  for( size_t i = 0 ; i + 1 < p[ 1 ].v.size() ; i ++ )
    upd( p[ 1 ].v[ i ] , p[ 0 ].dir * -1LL , p[ 0 ] , lt , rt );
  if( rt < -1 ){
    puts( "never" );
    return 0;
  }
  for( int _ = 0 ; _ < 100 ; _ ++ ){
    double mid1 = (lt + lt + rt) / 3;
    double mid2 = (lt + rt + rt) / 3;
    double area1 = Area( mid1 , p[ 0 ] , p[ 1 ] );
    double area2 = Area( mid2 , p[ 0 ] , p[ 1 ] );
    if( area1 > area2 - eps )
      rt = mid2;
    else
      lt = mid1;
  }
  printf( "%.12f\n" , lt );
}
