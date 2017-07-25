#include <bits/stdc++.h>
using namespace std;
#define double long double
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
const double eps = 1e-11;
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
  return sqrtl( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
void scan( Pt& tp ){
  int x , y;
  cin >> x >> y;
  tp = {x, y};
  //scanf( "%lf%lf" , &tp.X , &tp.Y );
}
double sqr( double x ){
  return x * x;
}
void print( const Pt& tp ){
  printf( "%.6LF, %.6LF\n" , tp.X , tp.Y );
}
#define N 55
int n;
Pt p[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scan( p[ i ] );
}
double dist( const Pt& o , const Line& tl ){
  Pt dlt = tl.second - tl.first;
  double dd = ( dlt * ( o - tl.first ) ) / norm( dlt );
  return sqrtl( max( (double)0.0 , norm2( o - tl.first ) - sqr( dd ) ) );
}
inline Pt rotate( const Pt& tp , double ang ){
  return { cosl( ang ) * tp.X - sinl( ang ) * tp.Y ,
           sinl( ang ) * tp.X + cosl( ang ) * tp.Y };
}
bool okay( double tar , int i1 , int i2 ){
  for( int i = 0 ; i < 2 ; i ++ ){
    Pt dir = perp( p[ i2 ] - p[ i1 ] );
    {
      vector<Pt> res;
      for( int j = 0 ; j < n ; j ++ ){
        if( j == i1 or j == i2 ) continue;
        Pt tmp = p[ j ] - p[ i1 ];
        if( ( tmp * dir ) < 0 ){
          res.push_back( p[ j ] );
          continue;
        }
        if( dist( p[ j ] , { p[ i1 ] , p[ i2 ] } ) > tar )
          res.push_back( p[ j ] );
      }
      if( res.empty() ){
        //printf( "%d here\n" , i );
        return true;
      }
      double mnn = res[ 0 ] * perp( dir );
      double mxx = res[ 0 ] * perp( dir );
      for( size_t j = 1 ; j < res.size() ; j ++ ){
        mnn = min( mnn , res[ j ] * perp( dir ) );
        mxx = max( mxx , res[ j ] * perp( dir ) );
      }
      if( ( mxx - mnn ) / norm( dir ) < tar ){
        //for( auto ii : res )
          //print( ii );
        //printf( "%.12LF %.12LF\n" , mnn , mxx );
        //printf( "%d here2\n" , i );
        return true;
      }
    }
    if( norm( dir ) > tar - eps ){
      double ang = acos( min( (double)1. , tar / norm( dir ) ) );
      for( int _ = -1 ; _ <= 1 ; _ += 2 ){
        Pt pi1 = p[ i1 ];
        Pt pi2 = p[ i1 ] +
          rotate( p[ i2 ] - p[ i1 ] , ang * _ )
          / norm( p[ i2 ] - p[ i1 ] )
          * tar;
        Pt ndir = pi2 - pi1;
        Pt pi3 = perp( ndir ) + pi1;
        vector<Pt> res;
        for( int j = 0 ; j < n ; j ++ ){
          Pt tmp = p[ j ] - pi1;
          if( ( tmp * ndir ) < 0 ){
            res.push_back( p[ j ] );
            continue;
          }
          if( dist( p[ j ] , { pi1 , pi3 } ) > tar )
            res.push_back( p[ j ] );
        }
        if( res.empty() ) return true;
        double mnn = res[ 0 ] * perp( ndir );
        double mxx = res[ 0 ] * perp( ndir );
        for( size_t j = 1 ; j < res.size() ; j ++ ){
          mnn = min( mnn , res[ j ] * perp( ndir ) );
          mxx = max( mxx , res[ j ] * perp( ndir ) );
        }
        if( ( mxx - mnn ) / norm( ndir ) < tar )
          return true;
      }
    }
    swap( i1 , i2 );
  }
  return false;
}
Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	//if( fabs( f ) < eps ) return Pt( nan(""), nan("") );
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
Pt ans[ 4 ];
void output(){
  for( int i = 0 ; i < 4 ; i ++ )
    printf( "%.12LF %.12LF\n" , ans[ i ].X , ans[ i ].Y );
  exit(0);
}
Line l1[ 2 ] , l2[ 2 ];
void output2(){
  for( int i = 0 ; i < 2 ; i ++ )
    for( int j = 0 ; j < 2 ; j ++ ){
      //print( l1[ i ].first );
      //print( l1[ i ].second );
      //print( l2[ j ].first );
      //print( l2[ j ].second );
      //puts( "======" );
      ans[ i * 2 + j ] = interPnt( l1[ i ].first , l1[ i ].second ,
                                   l2[ j ].first , l2[ j ].second );
    }
  swap( ans[ 2 ] , ans[ 3 ] );
  output();
}
void gogo( double tar , int i1 , int i2 ){
  for( int i = 0 ; i < 2 ; i ++ ){
    Pt dir = perp( p[ i2 ] - p[ i1 ] );
    {
      vector<Pt> res;
      for( int j = 0 ; j < n ; j ++ ){
        if( j == i1 or j == i2 ) continue;
        Pt tmp = p[ j ] - p[ i1 ];
        if( ( tmp * dir ) < -eps ){
          res.push_back( p[ j ] );
          continue;
        }
        if( dist( p[ j ] , { p[ i1 ] , p[ i2 ] } ) > tar + eps )
          res.push_back( p[ j ] );
      }
      if( res.empty() ){
        ans[ 0 ] = p[ i1 ];
        ans[ 1 ] = p[ i1 ] + ( p[ i2 ] - p[ i1 ] ) / norm( p[ i2 ] - p[ i1 ] ) * tar;
        ans[ 2 ] = p[ i1 ] + dir / norm( dir ) * tar;
        ans[ 3 ] = ans[ 1 ] + ans[ 2 ] - ans[ 0 ];
        swap( ans[ 2 ] , ans[ 3 ] );
        output();
      }
      int mnwho = 0 , mxwho = 0;
      double mnn = res[ 0 ] * perp( dir );
      double mxx = res[ 0 ] * perp( dir );
      for( size_t j = 1 ; j < res.size() ; j ++ ){
        if( perp( dir ) * res[ j ] < mnn ){
          mnn = min( mnn , res[ j ] * perp( dir ) );
          mnwho = j;
        }
        if( perp( dir ) * res[ j ] > mxx ){
          mxx = max( mxx , res[ j ] * perp( dir ) );
          mxwho = j;
        }
      }
      if( ( mxx - mnn ) < tar * norm( dir ) ){
        l1[ 0 ] = { p[ i1 ] , p[ i2 ] };
        Pt tmp = dir / norm( dir ) * tar;
        l1[ 1 ] = { p[ i1 ] + tmp , p[ i2 ] + tmp };
        tmp = perp( tmp );
        l2[ 0 ] = { res[ mnwho ]       , res[ mnwho ] + dir };
        if( tmp * ( res[ mxwho ] - res[ mnwho ] ) < 0 ) tmp = tmp * -1;
        l2[ 1 ] = { res[ mnwho ] + tmp , res[ mnwho ] + dir + tmp };
        output2();
      }
    }
    if( norm( dir ) > tar - eps ){
      double ang = acosl( min( (double)1. , tar / norm( dir ) ) );
      for( int _ = -1 ; _ <= 1 ; _ += 2 ){
        Pt pi1 = p[ i1 ];
        Pt pi2 = p[ i1 ] +
          rotate( p[ i2 ] - p[ i1 ] , ang * _ )
          / norm( p[ i2 ] - p[ i1 ] )
          * tar;
        Pt ndir = pi2 - pi1;
        Pt pi3 = perp( ndir ) + pi1;
        vector<Pt> res;
        for( int j = 0 ; j < n ; j ++ ){
          Pt tmp = p[ j ] - pi1;
          if( ( tmp * ndir ) < -eps ){
            res.push_back( p[ j ] );
            continue;
          }
          if( dist( p[ j ] , { pi1 , pi3 } ) > tar + eps )
            res.push_back( p[ j ] );
        }
        if( res.empty() ){
          ans[ 0 ] = pi1;
          ans[ 1 ] = pi1 + ( pi3 - pi1 ) / norm( pi3 - pi1 ) * tar;
          ans[ 2 ] = pi1 + ndir / norm( ndir ) * tar;
          ans[ 3 ] = ans[ 1 ] + ans[ 2 ] - ans[ 0 ];
          swap( ans[ 2 ] , ans[ 3 ] );
          output();
        }
        int mnwho = 0 , mxwho = 0;
        double mnn = res[ 0 ] * perp( ndir );
        double mxx = res[ 0 ] * perp( ndir );
        for( size_t j = 1 ; j < res.size() ; j ++ ){
          if( res[ j ] * perp( ndir ) < mnn ){
            mnn = min( mnn , res[ j ] * perp( ndir ) );
            mnwho = j;
          }
          if( res[ j ] * perp( ndir ) > mxx ){
            mxx = max( mxx , res[ j ] * perp( ndir ) );
            mxwho = j;
          }
        }
        if( ( mxx - mnn ) < tar * norm( ndir ) + eps ){
          l1[ 0 ] = { pi1 , pi3 };
          Pt tmp = ndir / norm( ndir ) * tar;
          l1[ 1 ] = { pi1 + tmp , pi3 + tmp };
          tmp = perp( tmp );
          l2[ 0 ] = { res[ mnwho ]       , res[ mnwho ] + ndir };
          if( tmp * ( res[ mxwho ] - res[ mnwho ] ) < 0 ) tmp = tmp * -1;
          l2[ 1 ] = { res[ mnwho ] + tmp , res[ mnwho ] + ndir + tmp };
          output2();
        }
      }
    }
    swap( i1 , i2 );
  }
}
bool okay( double tar ){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      if( i != j and okay( tar , i , j ) )
        return true;
  return false;
}
void construct( double tar ){
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      if( i != j )
        gogo( tar , i , j );
  assert( false );
}
void solve(){
  double bl = 0 , br = 1e5;
  //cout << okay( eps ) << endl;
  for( int _ = 0 ; _ < 200 ; _ ++ ){
    double mid = (bl + br) * 0.5;
    if( okay( mid ) ) br = mid;
    else bl = mid;
    //printf( "%.12LF\n" , br );
  }
  construct( br + eps );
}
int main(){
  init();
  solve();
}
