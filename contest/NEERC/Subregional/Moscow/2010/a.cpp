#include <bits/stdc++.h>
using namespace std;
typedef double D;
int n , r;
vector< int > v;
void init(){
  scanf( "%d%d" , &n , &r );
  for( int i = 0 ; i < n ; i ++ ){
    int xi; scanf( "%d" , &xi );
    v.push_back( xi );
  }
}
double inter( double dst ){
  if( dst > r + r ) return 0;
  D theta = dst / ( 2.0 * r );
  D ret = r * r * acos( theta ) - 0.5 * r * r * sin( 2.0 * acos( theta ) );
  return ret * 2;
}
const double pi = acos( -1.0 );
void solve(){
  D answer = pi * r * r;
  sort( v.begin() , v.end() );
  for( int i = 1 ; i < n ; i ++ ){
    answer += pi * r * r;
    answer -= inter( v[ i ] - v[ i - 1 ] );
  }
  printf( "%.9f\n" , answer );
}
int main(){
  init();
  solve();
}
