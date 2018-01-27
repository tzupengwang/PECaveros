#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-7;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef pair<double,double> Pt;
#define X first
#define Y second
PLL operator-( const PLL& p1 , const PLL& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
LL operator*( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
LL operator^( const PLL& p1 , const PLL& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , double kk ){
  return { tp.X * kk , tp.Y * kk };
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
double operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
#define N 111
#define A(i) get<0>(i)
#define H(i) get<1>(i)
#define B(i) get<2>(i)
int ori( const PLL& o , const PLL& a , const PLL& b ){
  LL ret = ( a - o ) ^ ( b - o );
  return ret / max( 1ll , abs( ret ) );
}
// p1 == p2 || q1 == q2 need to be handled
bool banana( const PLL& p1 , const PLL& p2 ,
             const PLL& q1 , const PLL& q2 ){
  if( ( ( p2 - p1 ) ^ ( q2 - q1 ) ) == 0 ){ // parallel
    if( ori( p1 , p2 , q1 ) ) return false;
    return false;
    //return ( ( p1 - q1 ) * ( p2 - q1 ) ) < 0 ||
           //( ( p1 - q2 ) * ( p2 - q2 ) ) < 0 ||
           //( ( q1 - p1 ) * ( q2 - p1 ) ) < 0 ||
           //( ( q1 - p2 ) * ( q2 - p2 ) ) < 0;
  }
  return (ori( p1, p2, q1 ) * ori( p1, p2, q2 ) <= 0) &&
         (ori( q1, q2, p1 ) * ori( q1, q2, p2 ) <= 0);
}

double norm( const Pt& pp ){
  return sqrt( pp * pp );
}

int n;
vector< tuple<LL,LL,LL> > v;
PLL lft_p( int idi ){
  return { 2LL * A( v[ idi ] ) - B( v[ idi ] ) , 0 };
}
PLL cen_p( int idi ){
  return { 2LL * A( v[ idi ] ) , 2LL * H( v[ idi ] ) };
}
PLL rgt_p( int idi ){
  return { 2LL * A( v[ idi ] ) + B( v[ idi ] ) , 0 };
}
void init(){
  v.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    cin >> A( v[ i ] ) >> H( v[ i ] ) >> B( v[ i ] );
}
double ans;
bool cover( int idi , int idj ){
  if( H( v[ idi ] ) <= H( v[ idj ] ) ) return false;
  if( 2LL * A( v[ idi ] ) + B( v[ idi ] ) <=
      2LL * A( v[ idj ] ) - B( v[ idj ] ) )
    return false;
  if( 2LL * A( v[ idi ] ) - B( v[ idi ] ) >=
      2LL * A( v[ idj ] ) + B( v[ idj ] ) )
    return false;
  if( banana( lft_p( idi ) , cen_p( idi ) ,
              lft_p( idj ) , cen_p( idj ) ) )
    return false;
  if( banana( lft_p( idi ) , cen_p( idi ) ,
              rgt_p( idj ) , cen_p( idj ) ) )
    return false;
  if( banana( rgt_p( idi ) , cen_p( idi ) ,
              lft_p( idj ) , cen_p( idj ) ) )
    return false;
  if( banana( rgt_p( idi ) , cen_p( idi ) ,
              rgt_p( idj ) , cen_p( idj ) ) )
    return false;
  return true;
}
double sqr( double x ){
  return x * x;
}

Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2, bool& res){
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

vector< pair<double,int> > lcand , rcand;

void check( const Pt& p1 , const Pt& p2 , const Pt& ii , bool& res ){
  if( !res ) return;
  res = ( (ii - p1) * (p2 - p1) > -eps ) and
        ( (ii - p2) * (p1 - p2) > -eps );
}

void shrink( Pt lp1 , Pt cp1 , Pt rp1 ,
             Pt lp2 , Pt cp2 , Pt rp2 ){
  lp1 = lp1 * .5;
  cp1 = cp1 * .5;
  rp1 = rp1 * .5;
  lp2 = lp2 * .5;
  cp2 = cp2 * .5;
  rp2 = rp2 * .5;
  {
    bool lres , rres;
    Pt linter = interPnt( lp1 , cp1 , lp2 , cp2 , lres );
    Pt rinter = interPnt( lp1 , cp1 , cp2 , rp2 , rres );
    check( lp1 , cp1 , linter , lres );
    check( lp1 , cp1 , rinter , rres );

    if( lres and rres ){
      lcand.push_back( { linter.Y , +1 } );
      lcand.push_back( { rinter.Y , -1 } );
    }else if( lres ){
      lcand.push_back( { linter.Y , +1 } );
    }else if( rres ){
      lcand.push_back( { 0 , +1 } );
      lcand.push_back( { rinter.Y , -1 } );
    }
  }
  {
    bool lres , rres;
    Pt linter = interPnt( rp1 , cp1 , lp2 , cp2 , lres );
    Pt rinter = interPnt( rp1 , cp1 , cp2 , rp2 , rres );
    check( rp1 , cp1 , linter , lres );
    check( rp1 , cp1 , rinter , rres );

    if( lres and rres ){
      rcand.push_back( { rinter.Y , +1 } );
      rcand.push_back( { linter.Y , -1 } );
    }else if( lres ){
      rcand.push_back( { 0 , +1 } );
      rcand.push_back( { linter.Y , -1 } );
    }else if( rres ){
      rcand.push_back( { rinter.Y , +1 } );
    }
  }
}

int _cs;

void cal( vector< pair<double,int> >& cc ,
          Pt lp , Pt cp ){
  lp = lp * .5;
  cp = cp * .5;

  //printf( "%.4f %.4f\n" , lp.X , lp.Y );
  //printf( "%.4f %.4f\n" , cp.X , cp.Y );

  //for( auto i : cc )
    //cout << i.first << " " << i.second << endl;

  cc.push_back( { 0 , 0 } );
  cc.push_back( { cp.Y , 0 } );
  sort( cc.begin() , cc.end() );
  size_t sum = 0;
  double gd = 0;
  for( size_t i = 0 ; i < cc.size() ; i ++ ){
    if( i and sum == 0 ){
      gd += cc[ i ].first - cc[ i - 1 ].first;
    }
    sum += cc[ i ].second;
  }

  ans += norm( lp - cp ) * gd / cp.Y;
}

void solve(){
  ans = 0;
  sort( v.begin() , v.end() );
  v.resize( unique( v.begin() , v.end() ) - v.begin() );
  for( size_t i = 0 ; i < v.size() ; i ++ ){
    lcand.clear();
    rcand.clear();
    Pt lp = lft_p( i );
    Pt cp = cen_p( i );
    Pt rp = rgt_p( i );
    bool gg = false;
    for( size_t j = 0 ; j < v.size() ; j ++ ){
      if( i == j ) continue;
      if( cover( i , j ) ) continue;
      if( cover( j , i ) ){
        gg = true;
        break;
      }
      shrink( lp , cp , rp ,
              lft_p( j ) , cen_p( j ) , rgt_p( j ) );
    }
    if( gg ) continue;
    cal( lcand , lp , cp );
    cal( rcand , lp , cp );
  }
  printf( "Case %d: %lld\n\n" , ++ _cs , (LL)( ans + .5 ) );
}
int main(){
  while( cin >> n and n ){
    init();
    solve();
  }
}
