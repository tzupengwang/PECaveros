#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef double D;
double eps = 1e-12;
int d , n , id[ N ];
D s[ N ] , p[ N ] , a[ N ];
bool cmp( int i1 , int i2 ){
  return s[ i1 ] * p[ i1 ] <
         s[ i2 ] * p[ i2 ];
}
void init(){
  scanf( "%d%d" , &d , &n );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%lf%lf%lf" , &s[ i ] , &p[ i ] , &a[ i ] );
    id[ i ] = i;
  }
  sort( id , id + n , cmp );
}
bool okay( double wt ){
  double gt = 0;
  for( int _ = 0 ; _ < n ; _ ++ ){
    int i = id[ _ ];
    double l = ( s[ i ] * a[ i ] - wt ) / ( s[ i ] * p[ i ] );
    if( l < eps ) continue;
    gt += l;
    wt += l * s[ i ] * p[ i ];
  }
  return gt > d - eps;
}
void solve(){
  double bl = 0 , br = 1e9;
  for( int i = 0 ; i < 100 ; i ++ ){
    double bmid = ( bl + br ) * 0.5;
    if( okay( bmid ) ) bl = bmid;
    else br = bmid;
  }
  printf( "%.12f\n" , (bl + br) * 0.5 );
}
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  init();
  solve();
}
