#include <bits/stdc++.h>
using namespace std;
#define N 30000010
int n , m , k , a , b , c , x[ N ];
long long ans;
int dq[ N ] , df , dt;
int main(){
#ifdef ONLINE_JUDGE
  freopen( "minima.in" , "r" , stdin );
  freopen( "minima.out" , "w" , stdout );
#endif
  cin >> n >> m >> k;
  cin >> a >> b >> c;
  for( int i = 1 ; i <= k ; i ++ )
    cin >> x[ i ];
  for( int i = k + 1 ; i <= n ; i ++ )
    x[ i ] = a * x[ i - 2 ] + b * x[ i - 1 ] + c;
  for( int i = 1 ; i < m ; i ++ ){
    while( dt and x[ dq[ dt - 1 ] ] >= x[ i ] )
      dt --;
    dq[ dt ++ ] = i;
  }
  for( int i = m ; i <= n ; i ++ ){
    while( dt - df > 0 and x[ dq[ dt - 1 ] ] >= x[ i ] )
      dt --;
    dq[ dt ++ ] = i;
    while( dt - df > 0 and dq[ df ] <= i - m ) df ++;
    ans += x[ dq[ df ] ];
  }
  printf( "%lld\n" , ans );
}
