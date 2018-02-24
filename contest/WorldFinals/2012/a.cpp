#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
//#define double long double
const double eps = 5e-7;
const double eps2 = 1e-9;
const double inf = 1e100;
const double forever = 1e6;
typedef pair<double,double> pt;
#define X first
#define Y second
pt operator+( const pt& p1 , const pt& p2 ){
  return {p1.X + p2.X, p1.Y + p2.Y};
}
pt operator-( const pt& p1 , const pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y};
}
double operator*( const pt& p1 , const pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
double operator^( const pt& p1 , const pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
pt operator*( const pt& pp , double tk ){
  return {pp.X * tk , pp.Y * tk};
}
bool in( double lx , double xx , double rx ){
  return lx - eps2 < xx and xx < rx + eps2;
}
bool in( const pt& p1 , const pt& cp , const pt& p2 ){
  return (cp - p1) * (p2 - p1) > -eps2 and
         (cp - p2) * (p1 - p2) > -eps2; 
}
pt interPnt( pt p1, pt p2, pt q1, pt q2, bool& res){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps2 ){
    res = false;
    return {0, 0};
  }
  res = true;
	pt ret_p = q1 * ( f2 / f ) + q2 * ( f1 / f );
  if( not in( p1 , ret_p , p2 ) )
    res = false;
  if( not in( q1 , ret_p , q2 ) )
    res = false;
  return ret_p;
}
struct Pt{
  double x , y , z;
  void read(){
    cin >> x >> y >> z;
  }
  Pt operator+( const Pt& he ) const{
    return { x + he.x , y + he.y , z + he.z };
  }
  Pt operator-( const Pt& he ) const{
    return { x - he.x , y - he.y , z - he.z };
  }
  Pt operator*( double tk ) const{
    return { x * tk , y * tk , z * tk };
  }
  double operator*( const Pt& he ) const{
    return x * he.x + y * he.y + z * he.z;
  }
};
double norm( const Pt& pp ){
  return sqrt( pp * pp );
}
double norm2( const Pt& pp ){
  return pp * pp;
}
#define N 55
#define K 60
int n;
Pt p[ N ] , v[ N ] , np[ N ];
bool gt[ N ];
bitset<N> tk[ N ] , cur[ N ];
double bst[ N ];
int fr[ N ];
double dist( int id1 , int id2 , double _t ){
  return norm( (p[ id1 ] + v[ id1 ] * _t) -
               (p[ id2 ] + v[ id2 ] * _t) );
}
double dist2( int id1 , int id2 , double _t ){
  return norm2( (p[ id1 ] + v[ id1 ] * _t) -
                (p[ id2 ] + v[ id2 ] * _t) );
}
int recal = 0;
void cal_mst( double _t ){
  for( int i = 0 ; i < n ; i ++ ){
    np[ i ] = p[ i ] + v[ i ] * _t;
    gt[ i ] = false;
    bst[ i ] = inf;
    tk[ i ].reset();
  }
  bst[ 0 ] = 0;
  fr[ 0 ] = 0;
  for( int rnd = 0 ; rnd < n ; rnd ++ ){
    int who = -1;
    for( int j = 0 ; j < n ; j ++ ){
      if( gt[ j ] ) continue;
      if( who == -1 or bst[ j ] < bst[ who ] - eps2 )
        who = j;
    }
    assert( who != -1 );
    if( fr[ who ] != who )
      tk[ min( who , fr[ who ] ) ][ max( who , fr[ who ] ) ] = true;
    gt[ who ] = true;
    for( int j = 0 ; j < n ; j ++ ){
      if( gt[ j ] ) continue;
      //double td = norm( np[ who ] - np[ j ] );
      double td = dist( who , j , _t );
      if( td < bst[ j ] - eps2 ){
        bst[ j ] = td;
        fr[ j ] = who;
      }
    }
  }
}
int _cs;
vector<double> calc( const Pt& p1 , const Pt& v1 , 
                     const Pt& p2 , const Pt& v2 ){
  // ax^2+bx+c = 0
  double a = v1 * v1 - v2 * v2;
  double b = 2 * (p1 * v1 - p2 * v2);
  double c = p1 * p1 - p2 * p2;
  if( fabs( a ) < eps2 ){
    if( fabs( b ) < eps2 ) return {};
    return {-c / b};
  }
  double bb4ac = b * b - 4. * a * c;
  if( bb4ac < -eps2 ) return {};
  bb4ac = max( bb4ac , 0. );
  return { (-b + sqrt(bb4ac)) / (2. * a) ,
           (-b - sqrt(bb4ac)) / (2. * a) };
}
void solve(){
  vector< pair<double,pair< pair<int,int> , pair<int,int> > > > eve;
  vector< pair<int,int> > vv;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ )
      vv.push_back( {i, j} );
  for( size_t i = 0 ; i < vv.size() ; i ++ )
    for( size_t j = i + 1 ; j < vv.size() ; j ++ ){
      int id1 = vv[ i ].first , id2 = vv[ i ].second;
      int jd1 = vv[ j ].first , jd2 = vv[ j ].second;
      vector<double> cand = calc( p[ id2 ] - p[ id1 ] , v[ id2 ] - v[ id1 ] ,
                                  p[ jd2 ] - p[ jd1 ] , v[ jd2 ] - v[ jd1 ] );
      for( auto tt : cand ){
        if( tt < eps ) continue;
        eve.push_back( { tt , { { id1 , id2 } , { jd1 , jd2 } } } );
      }
    }
  sort( eve.begin() , eve.end() );
  cal_mst( 0 );
  int ans = 1;
  for( int i = 0 ; i < n ; i ++ )
    cur[ i ] = tk[ i ];
  for( auto i : eve ){
    if( !cur[ i.second.first.first  ][ i.second.first.second  ] and
        !cur[ i.second.second.first ][ i.second.second.second ] )
      continue;
    cal_mst( i.first + eps );
    bool chg = false;
    for( int j = 0 ; j < n and not chg ; j ++ )
      if( tk[ j ] != cur[ j ] )
        chg = true;
    if( not chg ) continue;
    for( int j = 0 ; j < n ; j ++ )
      cur[ j ] = tk[ j ];
    ans ++;
  }
  printf( "Case %d: %d\n" , ++ _cs , ans );
}
int main(){
  while( cin >> n ){
    for( int i = 0 ; i < n ; i ++ ){
      p[ i ].read();
      v[ i ].read();
    }
    solve();
  }
}
