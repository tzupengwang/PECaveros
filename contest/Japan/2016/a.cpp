#include <bits/stdc++.h>
using namespace std;
#define N 303030
bool got[ N ];
vector<int> ans;
int n , m , a[ N ];
int main(){
  cin >> n >> m;
  for( int i = 0 ; i < m ; i ++ )
    cin >> a[ i ];
  for( int i = m - 1 ; i >= 0 ; i -- ){
    if( got[ a[ i ] ] ) continue;
    got[ a[ i ] ] = true;
    ans.push_back( a[ i ] );
  }
  for( int i = 1 ; i <= n ; i ++ )
    if( not got[ i ] )
      ans.push_back( i );
  for( auto i : ans )
    cout << i << endl;
}
