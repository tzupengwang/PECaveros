#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 40
const double eps = 1e-7;
int n;
double a[ N ] , b[ N ];
double xl , xr , inc;
const double pi = acos( -1. );
double f( double lx , double rx ){
  double ret = 0. , lxx = 1 , rxx = 1;
  for( int i = 0 ; i <= n + n ; i ++ ){
    lxx *= lx;
    rxx *= rx;
    ret += (b[ i ] * (rxx - lxx)) / (i + 1);
  }
  return ret * pi;
}
int _cs;
int main(){
  while( cin >> n ){
    for( int i = 0 ; i <= n ; i ++ )
      cin >> a[ i ];
    for( int i = 0 ; i <= n + n ; i ++ )
      b[ i ] = 0;
    for( int i = 0 ; i <= n ; i ++ )
      for( int j = 0 ; j <= n ; j ++ )
        b[ i + j ] += a[ i ] * a[ j ];
    cin >> xl >> xr >> inc;
    double vol = f( xl , xr );
    double ol = xl;
    vector<double> ans;
    for( int iter = 0 ; iter < 8 ; iter ++ ){
      double bl = xl , br = xr , ba = xr;
      for( int _ = 0 ; _ < 60 ; _ ++ ){
        double bmid = (bl + br) * .5;
        if( f( xl , bmid ) < inc )
          ba = bmid , bl = bmid;
        else
          br = bmid;
      }
      if( f( xl , ba ) < inc - eps )
        break;
      ans.push_back( ba );
      xl = ba;
    }
    printf( "Case %d: %.2f\n" , ++ _cs , vol );
    if( ans.empty() ) puts( "insufficient volume" );
    for( size_t i = 0 ; i < ans.size() ; i ++ )
      printf( "%.2f%c" , ans[ i ] - ol , " \n"[ i + 1 == ans.size() ] );
  }
}
