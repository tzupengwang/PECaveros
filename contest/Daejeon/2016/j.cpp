#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 505050
typedef long long LL;
int n , t[ N ];
LL x[ N ] , y[ N ];
bool solve(){
  vector< pair<LL,LL> > v;
  for( int i = 0 ; i < n ; i ++ )
    v.push_back( { { x[ i ] , y[ i ] } , t[ i ] } );
  if( v[ 0 ].second != 1 ) return false;
  if( v.back().second != 1 ) return false;

  return true;
}
int main(){
  while( scanf( "%d" , &n ) == 1 ){
    for( int i = 0 ; i < n ; i ++ )
      scanf( "%lld%lld%d" , &x[ i ] , &y[ i ] , &t[ i ] );
    if( not solve() )
      puts( "-1" );
  }
}
