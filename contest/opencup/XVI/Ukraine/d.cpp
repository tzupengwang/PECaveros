#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
int n , k , a[ N ];
void init(){
  scanf( "%d" , &n );
  scanf( "%d" , &k );
  for( int i = 0 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
}
void solve(){
  int m = a[ n ] / k;
  map<int,int> cc;
  for( int i = 0 ; i < n ; i ++ )
    cc[ a[ i ] % m ] ++;
  for( auto i : cc )
    if( i.second >= k ){
      puts( "1" );
      return;
    }
  puts( "0" );
}
int main(){
  init();
  solve();
}
