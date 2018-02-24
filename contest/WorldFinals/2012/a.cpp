#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define double long double
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
double operator^( const pt& p1 , const pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
pt operator*( const pt& pp , double tk ){
  return {pp.X * tk , pp.Y * tk};
}
bool in( double lx , double xx , double rx ){
  return lx - eps2 < xx and xx < rx + eps2;
}
pt interPnt( pt p1, pt p2, pt q1, pt q2, bool& res){
  if( p1 > p2 ) swap( p1 , p2 );
  if( q1 > q2 ) swap( q1 , q2 );
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps2 ){
    res = false;
    return {0, 0};
  }
  res = true;
	pt ret_p = q1 * ( f2 / f ) + q2 * ( f1 / f );
  if( not in( p1.X , ret_p.X , p2.X ) )
    res = false;
  if( not in( q1.X , ret_p.X , q2.X ) )
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
#define N 55
int n;
Pt p[ N ] , v[ N ] , np[ N ];
bool gt[ N ];
bitset<N> tk[ N ] , cur[ N ];
double bst[ N ];
int fr[ N ];
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
      double td = norm( np[ who ] - np[ j ] );
      if( td < bst[ j ] - eps2 ){
        bst[ j ] = td;
        fr[ j ] = who;
      }
    }
  }
}
double dist( int id1 , int id2 , double _t ){
  return norm( (p[ id1 ] + v[ id1 ] * _t) -
               (p[ id2 ] + v[ id2 ] * _t) );
}
int _cs;
vector< pair<pt,pt> > f( int id1 , int id2 ){
  vector< pair<pt,pt> > ret;
  if( dist( id1 , id2 , 0 ) < dist( id1 , id2 , eps ) ){
    ret.push_back( { { 0       , dist( id1 , id2 , 0       ) } ,
                     { forever , dist( id1 , id2 , forever ) } } );
  }else{
    double bl = 0 , br = forever;
    for( int i = 0 ; i < N ; i ++ ){
      double mid1 = (bl + bl + br) / 3;
      double mid2 = (bl + br + br) / 3;
      if( dist( id1 , id2 , mid1 ) < dist( id1 , id2 , mid2 ) )
        br = mid2;
      else
        bl = mid1;
    }
    ret.push_back( { { 0       , dist( id1 , id2 , 0 ) } ,
                     { bl      , dist( id1 , id2 , bl ) } } );
    ret.push_back( { { bl      , dist( id1 , id2 , bl ) } ,
                     { forever , dist( id1 , id2 , forever ) } } );
  }
  return ret;
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
      vector< pair<pt,pt> > func1 = f( id1 , id2 );
      vector< pair<pt,pt> > func2 = f( jd1 , jd2 );
      for( auto ii : func1 )
        for( auto jj : func2 ){
          bool rr;
          pt ret = interPnt( ii.first , ii.second ,
                             jj.first , jj.second , rr );
          if( !rr ) continue;
          eve.push_back( { ret.X , { {id1, id2}, {jd1, jd2} } } );
        }
    }
  sort( eve.begin() , eve.end() );
  cal_mst( 0 );
  int ans = 1;
  for( int i = 0 ; i < n ; i ++ )
    cur[ i ] = tk[ i ];
  for( auto i : eve ){
    if( not cur[ i.second.first.first  ][ i.second.first.second  ] and
        not cur[ i.second.second.first ][ i.second.second.second ] )
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
