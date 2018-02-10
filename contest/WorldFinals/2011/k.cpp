#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
#define X first
#define Y second
typedef pair<double,double> Pt;
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return {p1.X - p2.X, p1.Y - p2.Y};
}
double operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
double operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
Pt perp( const Pt& pp ){
  return { -pp.Y , pp.X };
}
double norm( const Pt& pp ){
  return sqrt( pp * pp );
}
void scan( Pt& pp ){
  cin >> pp.X >> pp.Y;
}
int n;
vector<Pt> v;
void init(){
  v.resize( n );
  for( int i = 0 ; i < n ; i ++ )
    scan( v[ i ] );
}
vector<Pt> ch;
void find_ch(){
  ch.clear();
  sort( v.begin() , v.end() );
  for( auto pp : v ){
    while( ch.size() > 1u ){
      int chsz = (int)ch.size();
      if( ((ch[ chsz - 1 ] - ch[ chsz - 2 ]) ^
           (pp - ch[ chsz - 2 ])) <= 0 )
        ch.pop_back();
      else
        break;
    }
    ch.push_back( pp );
  }
  reverse( v.begin() , v.end() );
  size_t psz = ch.size();
  for( auto pp : v ){
    while( ch.size() - psz > 0 ){
      int chsz = (int)ch.size();
      if( ((ch[ chsz - 1 ] - ch[ chsz - 2 ]) ^
           (pp - ch[ chsz - 2 ])) <= 0 )
        ch.pop_back();
      else
        break;
    }
    ch.push_back( pp );
  }
}
int _cs;
double dist( const Pt& p1 , const Pt& p2 , const Pt& pp ){
  return fabs( ((pp - p1) ^ (p2 - p1)) / norm( p2 - p1 ) );
}
double find_ans(){
  //for( size_t i = 0 ; i < ch.size() ; i ++ )
    //printf( "%.6f %.6f\n" , ch[ i ].X , ch[ i ].Y );
  double ans = 1e9;
  for( size_t i = 0 ; i + 1 < ch.size() ; i ++ ){
    Pt p1 = ch[ i ] , p2 = ch[ i + 1 ];
    Pt pp = perp( p2 - p1 );
    size_t mx = 0;
    for( size_t j = 0 ; j < ch.size() ; j ++ ){
      if( (pp * ch[ j ]) > (pp * ch[ mx ]) )
        mx = j;
    }
    ans = min( ans , dist( p1 , p2 , ch[ mx ] ) );
  }
  return ans;
}
void solve(){
  find_ch();
  LL ans = ceil( find_ans() * 100 );
  printf( "Case %d: %lld.%02lld\n" , ++ _cs , ans / 100 , ans % 100 );
}
int main(){
  while( scanf( "%d" , &n ) == 1 and n ){
    init();
    solve();
  }
}
