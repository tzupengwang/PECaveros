#include <bits/stdc++.h>
using namespace std;
#define N 1000001
bool p[ N ];
int rev( int x ){
  int ret = 0;
  while( x ){
    ret = ret * 10 + x % 10;
    x /= 10;
  }
  return ret;
}
void build(){
  for( int i = 2 ; i < N ; i ++ )
    p[ i ] = true;
  for( int i = 2 ; i < N ; i ++ ) if( p[ i ] )
    for( int j = i + i ; j < N ; j += i )
      p[ j ] = false;
}
int main(){
  build();
  vector<int> ans;
  for( int i = 2 ; i < N ; i ++ )
    if( i != rev( i ) and p[ i ] and p[ rev( i ) ] )
      ans.push_back( i );
  int k; cin >> k;
  if( k > (int)ans.size() ) puts( "-1" );
  else cout << ans[ k - 1 ] << endl;
}
