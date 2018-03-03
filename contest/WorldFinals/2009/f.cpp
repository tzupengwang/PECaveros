#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> Pt;
const double pi = acos( -1. );
#define N 12
#define X first
#define Y second
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y};
}
LL operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
LL operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
double norm( const Pt& pp ){
  return sqrt( pp * pp );
}
void scan( Pt& pp ){
  cin >> pp.X >> pp.Y;
}
double ch( vector<Pt> x ){
  if( x.size() <= 1u ) return 0;
  vector<Pt> ret;
  sort( x.begin() , x.end() );
  for( auto i : x ){
    while( ret.size() > 1u ){
      Pt p1 = ret[ ret.size() - 2 ];
      Pt p2 = ret[ ret.size() - 1 ];
      if( ((p2 - p1) ^ (i - p1)) <= 0 )
        ret.pop_back();
      else
        break;
    }
    ret.push_back( i );
  }
  reverse( x.begin() , x.end() );
  size_t psz = ret.size();
  for( auto i : x ){
    while( ret.size() > psz ){
      Pt p1 = ret[ ret.size() - 2 ];
      Pt p2 = ret[ ret.size() - 1 ];
      if( ((p2 - p1) ^ (i - p1)) <= 0 )
        ret.pop_back();
      else
        break;
    }
    ret.push_back( i );
  }
  double rr = 0;
  for( size_t i = 0 ; i + 1 < ret.size() ; i ++ )
    rr += norm( ret[ i ] - ret[ i + 1 ] );
  return rr;
}
int n;
Pt p[ N ];
double rnd;
double cal( int msk ){
  if( !msk ) return 0;
  vector<Pt> vv;
  for( int i = 0 ; i < n ; i ++ )
    if( (msk >> i) & 1 )
      vv.push_back( p[ i ] );
  return ch( vv ) + rnd;
}
double m , ans[ 1 << 12 ];
int _cs;
int main(){
  while( cin >> n >> m and n ){
    for( int i = 0 ; i < n ; i ++ )
      scan( p[ i ] );
    rnd = (pi + pi) * m;
    ans[ 0 ] = 0;
    for( int i = 1 ; i < (1 << n) ; i ++ ){
      ans[ i ] = cal( i );
      for( int j = i ; j ; j = (j - 1) & i )
        ans[ i ] = min( ans[ i ] , cal( j ) + ans[ i ^ j ] );
    }
    printf( "Case %d: length = %.2f\n" , ++ _cs , ans[ (1 << n) - 1 ] );
  }
}
