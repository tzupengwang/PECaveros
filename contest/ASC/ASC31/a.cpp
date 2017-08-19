#include <bits/stdc++.h>
using namespace std;
#define N 55
int n , m , s;
double ans;
void init(){
  cin >> n >> m >> s;
  //n = 50;
  //m = 20;
  //s = 100;
}
double dp[ N ] , ndp[ N ] , win[ N ];
int p[ N ] , w[ N ];
void cal(){
  dp[ n + 1 ] = 1.;
  for( int i = 0 ; i < 1e5 ; i ++ ){
    for( int j = 1 ; j <= n ; j ++ )
      for( int k = 0 ; k < m ; k ++ ){
        double bst = win[ k ] * dp[ min( n + 1 , j + w[ k ] ) ] +
                     ( 1 - win[ k ] ) * dp[ j - 1 ];
        dp[ j ] = max( dp[ j ] , bst );
      }
  }
  ans = dp[ n ];
}
void solve(){
  for( int i = 0 ; i < m ; i ++ ){
    cin >> p[ i ] >> w[ i ];
    //p[ i ] = 50;
    //w[ i ] = 2;
    win[ i ] = (double)p[ i ] / s;
  }
  cal();
  printf( "%.12f\n" , ans );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "casino.in" , "r" , stdin );
  freopen( "casino.out" , "w" , stdout );
#endif
  init();
  solve();
}
