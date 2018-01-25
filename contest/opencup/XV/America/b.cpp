#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-9;
typedef long long LL;
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Seg;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
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
  cin >> tp.X >> tp.Y;
}

Pt interPnt( Pt p1, Pt p2, Pt q1, Pt q2 , bool& res){
	double f1 = ( p2 - p1 ) ^ ( q1 - p1 );
	double f2 = ( p2 - p1 ) ^ ( p1 - q2 );
	double f = ( f1 + f2 );
	if( fabs( f ) < eps ){
    res = false;
    return { 0 , 0 };
  }
  res =true;
	return q1 * ( f2 / f ) + q2 * ( f1 / f );
}

vector<Seg> cand;

void upd( double& mnx , double& mxx , double& mny , double& mxy , const Pt& pp ){
  mnx = min( mnx , pp.X );
  mxx = max( mxx , pp.X );
  mny = min( mny , pp.Y );
  mxy = max( mxy , pp.Y );
}

double solve1( const vector<Seg>& cur ){
  if( cur.empty() ) return 0;
  double mnx = cur[ 0 ].first.X , mxx = mnx;
  double mny = cur[ 0 ].first.Y , mxy = mny;
  for( auto seg : cur ){
    upd( mnx , mxx , mny , mxy , seg.first );
    upd( mnx , mxx , mny , mxy , seg.second );
  }
  return max( mxx - mnx , mxy - mny );
}

void rotate( vector<Seg>& cur ){
  for( auto&& pp : cur ){
    pp.first = perp( pp.first );
    pp.second = perp( pp.second );
  }
}

int dx[]={0,0,1,1,0};
int dy[]={0,1,1,0,0};

bool In( const Pt& pp ,
         double mnx , double mny , double rr ){
  return mnx - eps < pp.X and pp.X < mnx + rr + eps and
         mny - eps < pp.Y and pp.Y < mny + rr + eps; 
}

vector<Seg> divide( Seg ss ,
            double mnx , double mny , double rr ){
  double in1 = In( ss.first , mnx , mny , rr );
  double in2 = In( ss.second , mnx , mny , rr );
  if( in1 and in2 ) return {};
  if( in2 ){
    swap( ss.first , ss.second );
    swap( in1 , in2 );
  }
  vector<double> mid;
  for( int i = 0 ; i < 4 ; i ++ ){
    Pt s = { mnx + dx[ i     ] * rr , mny + dy[ i     ] * rr };
    Pt t = { mnx + dx[ i + 1 ] * rr , mny + dy[ i + 1 ] * rr };
    bool res;
    Pt ret = interPnt( s , t , ss.first , ss.second , res );
    if( !res ) continue;
    double at = ((ret - ss.first) * (ss.second - ss.first)) /
      norm2(ss.second - ss.first);
    if( at < eps or at > 1. - eps ) continue;
    double at2 = ((ret - s) * (t - s)) / norm2( t - s );
    if( at2 < -eps or at2 > 1. + eps ) continue;
    mid.push_back( at );
  }
  sort( mid.begin() , mid.end() );
  if( not mid.empty() ){
    size_t sz = 1;
    for( size_t i = 1 ; i < mid.size() ; i ++ )
      if( mid[ i ] > mid[ sz - 1 ] + 1e-4 )
        mid[ sz ++ ] = mid[ i ];
    mid.resize( sz );
  }
  if( in1 ){
    if( mid.size() == 1u )
      return { { ss.first + (ss.second - ss.first) * mid[ 0 ] , ss.second } };
    return { ss };
  }
  if( mid.size() == 2u )
    return { { ss.first , ss.first + (ss.second - ss.first) * mid[ 0 ] } ,
             { ss.first + (ss.second - ss.first) * mid[ 1 ] , ss.second } };
  return { ss };
}

vector<Seg> divide( const vector<Seg>& cur ,
                    double mnx , double mny , double rr ){
  vector<Seg> ret;
  for( auto seg : cur ) 
    for( auto ss : divide( seg , mnx , mny , rr ) )
      ret.push_back( ss );
  return ret;
}



bool check( vector<Seg> cur , int k , double rr ){
  if( cur.empty() ) return true;
  if( k == 1 ) return solve1( cur ) < rr + eps;

  for( int i = 0 ; i < 4 ; i ++ ){
    double mnx = cur[ 0 ].first.X;
    double mny = cur[ 0 ].first.Y;

    for( auto seg : cur ){
      mnx = min( mnx , seg.first.X );
      mny = min( mny , seg.first.Y );
      mnx = min( mnx , seg.second.X );
      mny = min( mny , seg.second.Y );
    }
    

    if( check( divide( cur , mnx , mny , rr ) , k - 1 , rr ) )
      return true;

    rotate( cur );
  }
  return false;
}

int n , k;
vector<Pt> v;
void init(){
  cin >> n >> k;
  v.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    scan( v[ i ] );
}

void solve(){
  for( int i = 0 ; i < n ; i ++ )
    cand.push_back( { v[ i ] , v[ (i + 1) % n ] } );

  double bl = 0 , br = 4e4;
  for( int i = 0 ; i < 60 ; i ++ ){
    double bmid = (bl + br) * .5;
    if( check( cand , k , bmid ) )
      br = bmid;
    else
      bl = bmid;
  }
  printf( "%.9f\n" , (bl + br) * .5 );
}
int main(){
  init();
  solve();
}
