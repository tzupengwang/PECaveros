#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
int n;
double t;
double d[ N ] , s[ N ];
int main(){
  cin >> n >> t;
  for( int i = 0 ; i < n ; i ++ )
    cin >> d[ i ] >> s[ i ];
  double bl = -*min_element( s , s + n ) + 1e-7 , br = 1e8;
  for( int i = 0 ; i < 60 ; i ++ ){
    double bmid = (bl + br) * .5;
    double used = 0;
    for( int j = 0 ; j < n ; j ++ )
      used += d[ j ] / (s[ j ] + bmid);
    if( used < t ) br = bmid;
    else bl = bmid;
  }
  printf( "%.12f\n" , bl );
}
