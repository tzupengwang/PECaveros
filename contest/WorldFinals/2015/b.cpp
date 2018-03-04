#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> Pt;
typedef pair<double,double> Ptt;
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

void scan( Pt& pp ){
  cin >> pp.X >> pp.Y;
}
double angle( const Pt& p1 , const Pt& p2 ){
  double vl = (p1 * p2) / norm(p1) / norm(p2);
  double theta = fabs( acos( min( 1. , max( -1. , vl ) ) ) );
  if( (p1 ^ p2) < 0 ) return +theta;
  return -theta;
}
double angle( const Ptt& p1 , const Ptt& p2 ){
  double vl = (p1 * p2) / norm(p1) / norm(p2);
  double theta = fabs( acos( min( 1. , max( -1. , vl ) ) ) );
  if( (p1 ^ p2) < -eps ) return +theta;
  return -theta;
}
double cross(Ptt o, Ptt a, Ptt b){
  return (a-o) ^ (b-o);
}
vector<Ptt> convex_hull(vector<Ptt> pt){
  sort(pt.begin(),pt.end());
  int top=0;
  vector<Ptt> stk(2*pt.size());
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
Ptt interPnt( Ptt p1, Ptt p2, Ptt q1, Ptt q2 , bool& res ){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ){
    res = false;
    return {0, 0};
  }
  res = true;
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
int ori( const Pt& o , const Pt& a , const Pt& b ){
  LL ret = ( a - o ) ^ ( b - o );
  return ret / max( 1ll , abs( ret ) );
}
// p1 == p2 || q1 == q2 need to be handled
bool banana( const Pt& p1 , const Pt& p2 ,
             const Pt& q1 , const Pt& q2 ){
  if( ( ( p2 - p1 ) ^ ( q2 - q1 ) ) == 0 ){ // parallel
    return false;
    //if( ori( p1 , p2 , q1 ) ) return false;
    //return ( ( p1 - q1 ) * ( p2 - q1 ) ) <= 0 ||
           //( ( p1 - q2 ) * ( p2 - q2 ) ) <= 0 ||
           //( ( q1 - p1 ) * ( q2 - p1 ) ) <= 0 ||
           //( ( q1 - p2 ) * ( q2 - p2 ) ) <= 0;
  }
  return (ori( p1, p2, q1 ) * ori( p1, p2, q2 ) <= 0) &&
         (ori( q1, q2, p1 ) * ori( q1, q2, p2 ) <= 0);
}

bool between( const Pt& p1 , const Pt& pp , const Pt& p2 ){
  if( (pp - p1) ^ (p2 - p1) ) return false;
  return (pp - p1) * (p2 - p1) >= 0 and
         (pp - p2) * (p1 - p2) >= 0;
}
bool between( const Ptt& p1 , const Ptt& pp , const Ptt& p2 ){
  if( fabs( (pp - p1) ^ (p2 - p1) ) > eps ) return false;
  return (pp - p1) * (p2 - p1) >= -eps and
         (pp - p2) * (p1 - p2) >= -eps;
}

struct Poly{
  vector<Pt> vv;
  Pt dir;
  void read(){
    int n; cin >> n;
    vv.resize( n );
    for( int i = 0 ; i < n ; i ++ )
      scan( vv[ i ] );
    scan( dir );
  }
  bool inside( const Pt& pp ) const{
    for( size_t i = 0 ; i < vv.size() ; i ++ )
      if( between( vv[ i ] , pp , vv[ (i + 1) % vv.size() ] ) )
        return true;
    double sum = 0.;
    for( size_t i = 0 ; i < vv.size() ; i ++ )
      sum += angle( vv[ i ] , vv[ (i + 1) % vv.size() ] );
    sum = fabs( sum );
    return sum > pi;
  }
  bool inside( const Ptt& pp ) const{
    for( size_t i = 0 ; i < vv.size() ; i ++ )
      if( between( (Ptt)vv[ i ] , pp , (Ptt)vv[ (i + 1) % vv.size() ] ) )
        return true;
    double sum = 0.;
    for( size_t i = 0 ; i < vv.size() ; i ++ )
      sum += angle( vv[ i ] , vv[ (i + 1) % vv.size() ] );
    sum = fabs( sum );
    return sum > pi;
  }
} p[ 2 ];
double Area_Exact(){
  vector<Ptt> cand;
  for( auto pp : p[ 0 ].vv )
    if( p[ 1 ].inside( pp ) )
      cand.push_back( pp );
  for( auto pp : p[ 1 ].vv )
    if( p[ 0 ].inside( pp ) )
      cand.push_back( pp );
  for( size_t i = 0 ; i < p[ 0 ].vv.size() ; i ++ )
    for( size_t j = 0 ; j < p[ 1 ].vv.size() ; j ++ ){
      Pt p1 = p[ 0 ].vv[ i ];
      Pt p2 = p[ 0 ].vv[ (i + 1) % p[ 0 ].vv.size() ];
      if( not banana( p1 , p2 ,
                      p[ 1 ].vv[ j ] , p[ 1 ].vv[ (j + 1) % p[ 1 ].vv.size() ] ) )
          continue;
      bool res;
      cand.push_back( interPnt( p1 , p2 ,
                                p[ 1 ].vv[ j ] , p[ 1 ].vv[ (j + 1) % p[ 1 ].vv.size() ] , res ) );
    }
  if( cand.empty() ) return -1;
  cand = convex_hull( cand );
  double ret = 0;
  for( size_t i = 0 ; i < cand.size() ; i ++ )
    ret += cand[ i ] ^ cand[ (i + 1) % cand.size() ];
  return fabs( ret );
}
double Area( double tt ){
  vector<Ptt> cand;
  for( auto pp : p[ 0 ].vv ){
    Ptt tp = (Ptt)pp + (Ptt)p[ 0 ].dir * tt;
    if( p[ 1 ].inside( tp ) )
      cand.push_back( tp );
  }
  //cout << tt << endl;
  //for( auto i : cand )
    //cout << i.X << " " << i.Y << endl;
  //puts( "====" );
  for( auto pp : p[ 1 ].vv )
    if( p[ 0 ].inside( (Ptt)pp - (Ptt)p[ 0 ].dir * tt ) )
      cand.push_back( (Ptt)pp );
  for( size_t i = 0 ; i < p[ 0 ].vv.size() ; i ++ )
    for( size_t j = 0 ; j < p[ 1 ].vv.size() ; j ++ ){
      Ptt p1 = (Ptt)p[ 0 ].vv[ i ] + (Ptt)p[ 0 ].dir * tt;
      Ptt p2 = (Ptt)p[ 0 ].vv[ (i + 1) % p[ 0 ].vv.size() ] + (Ptt)p[ 0 ].dir * tt;
      if( not banana( p1 , p2 ,
                      p[ 1 ].vv[ j ] ,
                      p[ 1 ].vv[ (j + 1) % p[ 1 ].vv.size() ] ) )
          continue;
      bool res;
      cand.push_back( interPnt( p1 , p2 ,
                                p[ 1 ].vv[ j ] ,
                                p[ 1 ].vv[ (j + 1) % p[ 1 ].vv.size() ] , res ) );
    }
  cand = convex_hull( cand );
  double ret = 0;
  for( size_t i = 0 ; i < cand.size() ; i ++ )
    ret += cand[ i ] ^ cand[ (i + 1) % cand.size() ];
  return fabs( ret );
}
double times( const Ptt& pp , const Ptt& nd , const Ptt& jiou ){
  return ((jiou - pp) * nd) / norm2( nd );
}
void upd( const Pt& pp , const Pt& nd , const Poly& target , double& lt , double& rt ){
  Pt til = pp + nd * (1000000000LL);
  for( size_t i = 0 ; i < target.vv.size() ; i ++ ){
    if( not banana( target.vv[ i ] , target.vv[ (i + 1) % target.vv.size() ] ,
                    pp , til ) ){
      Pt p1 = target.vv[ i ];
      Pt p2 = target.vv[ (i + 1) % target.vv.size() ];
      if( (p2 - p1) ^ nd ) continue;
      if( (p2 - pp) ^ nd ) continue;
      double t1 = times( pp , nd , p1 );
      double t2 = times( pp , nd , p2 );
      if( t1 > t2 ) swap( t1 , t2 );
      if( t2 < -eps ) continue;
      t1 = max( t1 , 0. );
      t2 = max( t2 , 0. );
      lt = min( lt , t1 );
      rt = max( rt , t2 );
      continue;
    }
    bool res;
    Ptt jiou = interPnt( target.vv[ i ] , target.vv[ (i + 1) % target.vv.size() ] ,
                        pp , til , res );
    if( !res ) continue;
    double cur = times( pp , nd , jiou );
    if( cur < -eps ) continue;
    lt = min( lt , cur );
    rt = max( rt , cur );
  }
}
int main(){
  p[ 0 ].read();
  p[ 1 ].read();
  p[ 0 ].dir = p[ 0 ].dir - p[ 1 ].dir;
  if( p[ 0 ].dir.X == 0 and p[ 0 ].dir.Y == 0 ){
    double ans = Area_Exact();
    if( ans < -.5 ) puts( "never" );
    else printf( "%.12f\n" , 0. );
    exit(0);
  }
  double lt = 1e12 , rt = -1e12;
  for( size_t i = 0 ; i < p[ 0 ].vv.size() ; i ++ )
    upd( p[ 0 ].vv[ i ] , p[ 0 ].dir * +1LL , p[ 1 ] , lt , rt );
  for( size_t i = 0 ; i < p[ 1 ].vv.size() ; i ++ )
    upd( p[ 1 ].vv[ i ] , p[ 0 ].dir * -1LL , p[ 0 ] , lt , rt );
  if( rt < -10 ){
    puts( "never" );
    exit(0);
  }
  //Area( 4.19 );
  //exit(0);
  //for( auto i : p[ 0 ].vv )
    //printf( "%.4f %.4f\n" , i.X + p[ 0 ].dir.X * 4.19 , 
                            //i.Y + p[ 0 ].dir.Y * 4.19 );
  //for( auto i : p[ 1 ].vv )
    //printf( "%.4f %.4f\n" , (double)i.X  , 
                            //(double)i.Y );
  for( int _ = 0 ; _ < 100 ; _ ++ ){
    double mid1 = (lt + lt + rt) / 3;
    double mid2 = (lt + rt + rt) / 3;
    double area1 = Area( mid1 );
    double area2 = Area( mid2 );
    if( area1 > area2 - eps )
      rt = mid2;
    else
      lt = mid1;
  }
  printf( "%.12f\n" , lt );
}
