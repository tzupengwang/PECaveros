#include <bits/stdc++.h>
using namespace std;
#define N 1021
int n , k , ans[ N ];
void go( int now ){
  vector< pair<int,int> > vv;
  for( int i = now + 1 ; i <= n ; i ++ )
    vv.push_back( { ans[ i ] , i } );
  sort( vv.begin() , vv.end() );
  int nd = 0;
  for( int i = 0 ; i < (int)vv.size() / 2 ; i ++ )
    nd += vv[ i ].first + 1;
  if( nd > k ){
    ans[ now ] = -1;
    return;
  }
  for( int i = now + 1 ; i <= n ; i ++ )
    ans[ i ] = 0;
  for( int i = 0 ; i < (int)vv.size() / 2 ; i ++ )
    ans[ vv[ i ].second ] = vv[ i ].first + 1;
  ans[ now ] = k - nd;
}
int main(){
  cin >> n >> k;
  ans[ n ] = k;
  for( int i = n - 1 ; i >= 1 ; i -- )
    go( i );
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i == n ] );
}
