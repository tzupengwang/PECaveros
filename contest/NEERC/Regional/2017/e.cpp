#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
int cnt[ N ] , n , a[ N ];
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    cin >> a[ i ];
  int zer = 0;
  vector<int> ans;
  for( int i = 0 ; i < n ; i ++ ){
    if( a[ i ] > 0 ){
      cnt[ a[ i ] ] ++;
      continue;
    }
    if( a[ i ] == 0 ){
      zer ++;
      continue;
    }
    if( cnt[ -a[ i ] ] ){
      cnt[ -a[ i ] ] --;
      continue;
    }
    if( zer == 0 ){
      puts( "No" );
      exit(0);
    }
    ans.push_back( -a[ i ] );
    zer --;
  }
  while( zer -- )
    ans.push_back( 1 );
  puts( "Yes" );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
