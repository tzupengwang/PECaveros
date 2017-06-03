#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , s , c[ N ]; 
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  cin >> n >> s;
  while( n -- ){
    int a , b;
    cin >> a >> b;
    if( c[ a ] == 0 or b < c[ a ] )
      c[ a ] = b;
  }
  vector< int > v;
  for( int i = 1 ; i < N ; i ++ )
    if( c[ i ] )
      v.push_back( c[ i ] );
  sort( v.begin() , v.end() );
  int ans = 0;
  for( auto i : v ){
    if( i > s ) break;
    s -= i;
    ans ++;
  }
  cout << ans << endl;
}
