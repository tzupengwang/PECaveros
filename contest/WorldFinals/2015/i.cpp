#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const double eps = 1e-9;
int n , w;
double u , v , t1 , t2;
vector< pair<double,int> > gg;
int main(){
  scanf( "%d%d%lf%lf%lf%lf" , &n , &w , &u , &v , &t1 , &t2 );
  for( int i = 1 ; i <= n ; i ++ ){
    char dir[ 8 ]; int wi;
    scanf( "%s%d" , dir , &wi );
    double bns = 1;
    if( dir[ 0 ] == 'E' ) bns = -1;
    while( wi -- ){
      double l , p; scanf( "%lf%lf" , &l , &p );
      p *= bns;
      double lg = p / u - i * (double)w / v;
      double rg = (p + l) / u - (i - 1) * (double)w / v;
      lg = max( lg , t1 );
      rg = min( rg , t2 );
      //printf( "%.12f %.12f\n" , lg , rg );
      if( lg < rg + eps ){
        gg.push_back( {lg      , +1} );
        gg.push_back( {rg + eps, -1} );
      }
    }
  }
  gg.push_back( {t2, 0} );
  sort( gg.begin() , gg.end() );
  double pre = t1 , ans = 0;
  int sum = 0;
  for( auto i : gg ){
    if( sum == 0 )
      ans = max( ans , i.first - pre );
    sum += i.second;
    pre = i.first;
  }
  printf( "%.12f\n" , ans );
}
