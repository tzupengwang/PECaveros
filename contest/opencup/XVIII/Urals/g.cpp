#include <bits/stdc++.h>
using namespace std;
typedef double type;
const double eps = 1e-9;
const double pi = acosl( -1. );
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
//#define O first
//#define R second
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
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ) return Pt( nan(""), nan("") );
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
#define N 101010
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
double st[ N << 2 ];
void build_st( int no , int l , int r ){
  st[ no ] = 0;
  if( l == r ) return ;
  build_st( L( no ) , l , mid );
  build_st( R( no ) , mid + 1 , r );
}
void push( int no , int l , int r ){
  for( int id : { L( no ) , R( no ) } )
    if( st[ no ] > st[ id ] )
      st[ id ] = st[ no ];
}
void modify( int no , int l , int r , int ql , int qr , double x ){
  if( r < ql or l > qr or ql > qr ) return;
  if( x < st[ no ] ) return;
  if( ql <= l and r <= qr ){
    st[ no ] = x;
    return;
  }
  push( no , l , r );
  modify( L( no ) , l , mid , ql , qr , x );
  modify( R( no ) , mid + 1 , r , ql , qr , x );
}
double query( int no , int l , int r , int p ){
  if( l == r ) return st[ no ];
  push( no , l , r );
  if( p <= mid ) return query( L( no ) , l , mid , p );
  return query( R( no ) , mid + 1 , r , p );
}
bool equal( double x , double y ){
  return x > y - eps and x < y + eps;
}
int n;
double alpha;
Pt p[ N ];
inline double angle( const Pt& pp ){
  return atan2( pp.Y , pp.X );
}
inline double norm( double x ){
  while( x < 0 ) x += pi + pi;
  while( x > pi + pi ) x -= pi + pi;
  return x;
}
vector<double> va;
int vsz;
inline int idx( double x ){
  int bl = 0 , br = vsz - 1 , ba = 0;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( x > va[ bmid ] - eps ) ba = bmid , bl = bmid + 1;
    else br = bmid - 1;
  }
  return ba;
}
void init(){
  scanf( "%d%lf" , &n , &alpha );
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
  va.clear();
  va.push_back( 0 );
  va.push_back( pi + pi );
  for( int i = 0 ; i < n ; i ++ ){
    double ca = angle( p[ i ] );
    va.push_back( norm( ca ) );
    va.push_back( norm( ca + alpha ) );
  }
  sort( va.begin() , va.end() );
  size_t sz = 1;
  for( size_t i = 1 ; i < va.size() ; i ++ )
    if( va[ i ] - va[ sz - 1 ] > eps )
      va[ sz ++ ] = va[ i ];
  va.resize( sz );
  vsz = (int)va.size();
  build_st( 1 , 0 , vsz - 1 );
}
const Pt ori = {0 , 0};
vector< pair<Pt,Pt> > wt[ N ];
inline Pt at( const Pt& pp1 , const Pt& pp2 , double ang ){
  return interPnt( pp1 , pp2 ,
                   {0, 0} , {cosl(ang), sinl(ang)} );
}
inline double dist( const pair<Pt,Pt>& pp ){
  double ret = min( norm( pp.first ) , norm( pp.second ) );
  if( (ori - pp.first) * (pp.second - pp.first) > -eps and
      (ori - pp.second) * (pp.first - pp.second) > -eps )
    ret = fabs( ((ori - pp.first) ^ (pp.second - pp.first)) / norm( pp.second - pp.first ) );
  return ret;
}
double sen_tri( const pair<Pt,Pt>& pp , double rr , double la , double ra ){
  double p1 = norm( pp.first );
  double p2 = norm( pp.second );
  if( rr > p1 - eps and rr > p2 - eps )
    return (ra - la) * rr * rr * .5;
  double d = dist( pp );
  if( d > rr - eps )
    return fabs( pp.first ^ pp.second ) * .5;
  if( norm( pp.first ) > rr and norm( pp.second ) > rr ){
    double mc = ((pp.second - pp.first) * (ori - pp.first)) / norm2(pp.second - pp.first);
    double aa1 , aa2;
    Pt dlt = pp.second - pp.first;
    {
      double bl = 0 , br = mc;
      for( int i = 0 ; i < 30 ; i ++ ){
        double bmid = (bl + br) * .5;
        if( norm( pp.first + dlt * bmid ) < rr )
          br = bmid;
        else
          bl = bmid;
      }
      aa1 = bl;
    }
    {
      double bl = mc , br = 1;
      for( int i = 0 ; i < 30 ; i ++ ){
        double bmid = (bl + br) * .5;
        if( norm( pp.first + dlt * bmid ) < rr )
          bl = bmid;
        else
          br = bmid;
      }
      aa2 = bl;
    }
    Pt pp1 = at( pp.first , pp.second , aa1 );
    Pt pp2 = at( pp.first , pp.second , aa2 );
    return sen_tri( { pp.first , pp1 } , rr , la , aa1 ) +
           sen_tri( { pp1 , pp2 } , rr , aa1 , aa2 ) +
           sen_tri( { pp2 , pp.second } , rr , aa2 , ra );
  }
  if( norm( pp.first ) < rr ){
    double bl = 0 , br = 1;
    Pt dlt = pp.second - pp.first;
    for( int i = 0 ; i < 30 ; i ++ ){
      double bmid = (bl + br) * .5;
      if( norm( pp.first + dlt * bmid ) < rr )
        bl = bmid;
      else
        br = bmid;
    }
    Pt ppp = at( pp.first , pp.second , bl );
    return sen_tri( { pp.first , ppp } , rr , la , bl ) +
           sen_tri( { ppp , pp.second } , rr , bl , ra );
  }
  if( norm( pp.second ) < rr ){
    double bl = 0 , br = 1;
    Pt dlt = pp.second - pp.first;
    for( int i = 0 ; i < 30 ; i ++ ){
      double bmid = (bl + br) * .5;
      if( norm( pp.first + dlt * bmid ) < rr )
        br = bmid;
      else
        bl = bmid;
    }
    Pt ppp = at( pp.first , pp.second , bl );
    return sen_tri( { pp.first , ppp } , rr , la , bl ) +
           sen_tri( { ppp , pp.second } , rr , bl , ra );
  }
  assert( false );
  return 0;
}
double calc2( vector< pair<Pt,Pt> > tris , double rr ,
              double la , double ra ){
  vector< pair<Pt,Pt> > tt;
  for( size_t i = 0 ; i < tris.size() ; i ++ ){
    bool keep = true;
    double n1 = norm( tris[ i ].first );
    double n2 = norm( tris[ i ].second );
    for( size_t j = 0 ; j < tris.size() ; j ++ ){
      if( i == j ) continue;
      double m1 = norm( tris[ j ].first );
      double m2 = norm( tris[ j ].second );
      if( equal( n1 , m1 ) and equal( n2 , m2 ) ){
        if( j < i ){
          keep = false;
          break;
        }
        continue;
      }
      if( m1 > n1 - eps and m2 > n2 - eps ){
        keep = false;
        break;
      }
    }
    if( keep )
      tt.push_back( tris[ i ] );
  }
  tris = tt;
  if( tris.size() == 1u )
    return sen_tri( tris[ 0 ] , rr , la , ra );
  double ret = 0;
  //vector<double> mma;
  //for( size_t i = 0 ; i < tris.size() ; i ++ )
    //for( size_t j = i + 1 ; j < tris.size() ; j ++ ){
      //Pt fuck = interPnt( tris[ i ].first , tris[ i ].second ,
                          //tris[ j ].first , tris[ j ].second );
      //double aaa = norm( angle( fuck ) );
      //if( aaa < la + eps ) continue;
      //if( aaa > ra - eps ) continue;
      //mma.push_back( aaa );
      //break;
    //}
  //mma.push_back( la );
  //mma.push_back( ra );
  //sort( mma.begin() , mma.end() );
  //size_t mmsz = 1;
  //for( size_t i = 1 ; i < mma.size() ; i ++ )
    //if( mma[ i ] > mma[ mmsz - 1 ] + eps )
      //mma[ mmsz ++ ] = mma[ i ];
  //mma.resize( mmsz );
  //for( size_t i = 0 ; i + 1 < mma.size() ; i ++ ){
    //vector< pair<Pt,Pt> > tris2;
    //double nla = mma[ i ];
    //double nra = mma[ i + 1 ];
    //for( size_t j = 0 ; j < tris.size() ; j ++ )
      //tris2.push_back( { at( tris[ j ].first , tris[ j ].second , nla ) ,
                         //at( tris[ j ].first , tris[ j ].second , nra ) } );
    //ret += calc2( tris2 , rr , nla , nra );
  //}
  //return ret;



  //assert( tris.size() == 2u );
  Pt midp = interPnt( tris[ 0 ].first , tris[ 0 ].second ,
                      tris[ 1 ].first , tris[ 1 ].second );
  double aa = norm( angle( midp ) );
  {
    vector< pair<Pt,Pt> > tris2;
    for( int i = 0 ; i < 2 ; i ++ )
      tris2.push_back( { tris[ i ].first , at( tris[ i ].first ,
                                               tris[ i ].second ,
                                               aa ) } );
    ret += calc2( tris2 , rr , la , aa );
  }
  {
    vector< pair<Pt,Pt> > tris2;
    for( int i = 0 ; i < 2 ; i ++ )
      tris2.push_back( { at( tris[ i ].first ,
                             tris[ i ].second ,
                            aa ) ,
                         tris[ i ].second } );
    ret += calc2( tris2 , rr , aa , ra );
  }
  return ret;
}
void calc(){
  double ans = 0.;
  for( int i = 0 ; i + 1 < vsz ; i ++ ){
    double rr = query( 1 , 0 , vsz - 1 , i );
    vector< pair<Pt,Pt> > tris;
    for( auto ii : wt[ i ] ){
      Pt p1 = at( ii.first , ii.second , va[ i     ] );
      Pt p2 = at( ii.first , ii.second , va[ i + 1 ] );
      tris.push_back( { p1 , p2 } );
    }
    ans += calc2( tris , rr , va[ i ] , va[ i + 1 ] );
  }
  printf( "%.12f\n" , ans );
}
inline Pt rotate( const Pt& pp , double aa ){
  return { pp.X * cosl( aa ) - pp.Y * sinl( aa ) ,
           pp.X * sinl( aa ) + pp.Y * cosl( aa ) };
}
void solve(){
  for( int i = 0 ; i < vsz ; i ++ )
    wt[ i ].clear();
  for( int i = 0 ; i < n ; i ++ ){
    double sa = norm( angle( p[ i ] ) );
    double ta = sa + alpha;
    double rr = norm( p[ i ] );
    int s = idx( sa );
    int t = idx( norm( ta ) );
    if( s < t )
      modify( 1 , 0 , vsz - 1 , s , t - 1 , rr );
    else{
      modify( 1 , 0 , vsz - 1 , s , vsz - 1 , rr );
      modify( 1 , 0 , vsz - 1 , 0 , t - 1 , rr );
    }
    double ta2 = norm( angle( p[ (i + 1) % n ] ) );
    int t2 = idx( norm( ta2 ) );
    for( int j = s ; j % vsz != t2 ; j ++ )
      wt[ j % vsz ].push_back( { p[ i ] , p[ (i + 1) % n ] } );
    int ss2 = idx( norm( sa + alpha ) );
    int tt2 = idx( norm( ta2 + alpha ) );
    Pt ppp1 = rotate( p[ i ] , alpha );
    Pt ppp2 = rotate( p[ (i + 1) % n ] , alpha );
    for( int j = ss2 ; j % vsz != tt2 ; j ++ )
      wt[ j % vsz ].push_back( { ppp1 , ppp2 } );
  }
  calc();
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
