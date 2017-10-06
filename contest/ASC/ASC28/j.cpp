#include <bits/stdc++.h>
using namespace std;
#define N 1515
bitset<N> to[ N ] , fr[ N ];
int n;
char c[ N ][ N ];
int main(){
#ifdef ONLINE_JUDGE
  freopen( "triatrip.in" , "r" , stdin );
  freopen( "triatrip.out" , "w" , stdout );
#endif
  cin >> n;
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%s" , c[ i ] );
    for( int j = 0 ; j < n ; j ++ )
      if( c[ i ][ j ] == '+' ){
        to[ i ][ j ] = 1;
        fr[ j ][ i ] = 1;
      }
  }
  long long ans = 0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      if( c[ i ][ j ] == '+' )
        ans += ( to[ j ] & fr[ i ] ).count();
  cout << ans / 3 << endl;
} 
