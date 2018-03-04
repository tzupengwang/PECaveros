#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
double pmx;
double p , a , b , c , d;
double f( double k ){
  return p * ( sin( a * k + b ) + cos( c * k + d ) + 2 );
}
int main(){
  int n;
  cin >> p >> a >> b >> c >> d >> n;
  pmx = f( 1 );
  double ans = 0.;
  for( int i = 2 ; i <= n ; i ++ ){
    double v = f( i );
    ans = max( ans , pmx - v );
    pmx = max( pmx , v );
  }
  printf( "%.12f\n" , ans );
}
