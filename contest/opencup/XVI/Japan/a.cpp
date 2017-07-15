#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , m , e[ N ] , w[ N ];
string s;
int main(){
  cin >> n >> m;
  while( m -- ){
    cin >> s;
    for( int i = 1 ; i <= n ; i ++ )
      if( s[ i - 1 ] == 'E' )
        e[ i ] ++;
      else
        w[ i ] ++;
  }
  for( int i = 2 ; i <= n ; i ++ )
    e[ i ] += e[ i - 1 ];
  for( int i = n - 1 ; i >= 1 ; i -- )
    w[ i ] += w[ i + 1 ];
  int ans = w[ 1 ] , l = 0 , r = 1;
  for( int i = 1 ; i <= n ; i ++ ){
    int tans = e[ i ] + w[ i + 1 ];
    if( tans < ans ){
      ans = tans;
      l = i;
      r = i + 1;
    }
  }
  cout << l << " " << r << endl;
}
