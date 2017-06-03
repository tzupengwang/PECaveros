#include <bits/stdc++.h>
using namespace std;
#define N 1021
#define S 50505
int n , s;
pair<int,int> v[ N ];
void init(){
  scanf( "%d%d" , &n , &s );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d%d" , &v[ i ].first , &v[ i ].second );
  sort( v + 1 , v + n + 1 );
}
void Max( pair<int,int>& p1 ,
          const pair<int,int>& p2 ){
  if( p2.first > p1.first or
      ( p2.first == p1.first and p2.second < p1.second ) )
    p1 = p2;
}
pair<int,int> dp[ S ];
void solve(){
  for( int i = 0 ; i <= s ; i ++ )
    dp[ i ] = {-1, -1};
  dp[ 0 ] = {0, 0};
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = s ; j >= v[ i ].second ; j -- ){
      int from = j - v[ i ].second;
      if( dp[ from ].first == -1 ) continue;
      pair<int,int> ndp = dp[ from ];
      if( v[ i ].first > ndp.second ){
        ndp.first ++;
        ndp.second = v[ i ].first;
      }
      Max( dp[ j ] , ndp );
    }
  }
  if( dp[ s ].first <= 0 )
    puts( "Impossible" );
  else
    printf( "%d\n" , dp[ s ].first );
}
int main(){
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
  init();
  solve();
}
