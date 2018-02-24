#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10001
int n , ans , cnt[ N ];
vector<int> v[ N ];
int dp[ N ] , pdp[ N ];
int dp2[ N ][ N ];
const int inf = 1e6;
int _cs;
int main(){
  while( cin >> n ){
    for( int i = 0 ; i < N ; i ++ )
      v[ i ].clear();
    ans = 0;
    int tot = 0;
    for( int i = 0 , hi ; i < n ; i ++ ){
      cin >> hi;
      for( int j = 0 , ai ; j < hi ; j ++ ){
        cin >> ai;
        v[ ai ].push_back( i );
      }
      ans += hi - 1;
      tot += hi;
    }
    ans += tot - 1;
    bool first = true;
    for( int i = 0 ; i < N ; i ++ ){
      if( v[ i ].empty() ) continue;
      for( int j = 0 ; j < n ; j ++ )
        cnt[ j ] = 0;
      for( int j : v[ i ] )
        cnt[ j ] ++;
      int atmst = 0;
      for( int j = 0 ; j < n ; j ++ )
        if( cnt[ j ] )
          atmst += cnt[ j ] - 1;
      if( first ){
        for( int j = 0 ; j < n ; j ++ )
          dp[ j ] = cnt[ j ] ? atmst : -inf;
        first = false;
        continue;
      }
      for( int j = 0 ; j < n ; j ++ ){
        pdp[ j ] = dp[ j ];
        dp[ j ] = -inf;
      }
      for( int pre = 0 ; pre < n ; pre ++ ){
        if( pdp[ pre ] <= -inf ) continue;
        for( int j = 0 ; j < n ; j ++ ){
          for( int k = 0 ; k < n ; k ++ ){
            if( j == k ) continue;
            if( cnt[ j ] and cnt[ k ] ){
              int dlt = atmst + (j == pre);
              dp[ k ] = max( dp[ k ] ,
                             pdp[ pre ] + dlt );
            }
          }
          if( !cnt[ j ] ) continue;
          if( cnt[ j ] == (int)v[ i ].size() ){
            dp[ j ] = max( dp[ j ] ,
                           pdp[ pre ] + atmst + (pre == j) );
            continue;
          }
          if( cnt[ j ] <= 1 ) continue;
          int dlt = atmst - 1 + (j == pre);
          dp[ j ] = max( dp[ j ] ,
                         pdp[ pre ] + dlt );
        }
      }
    }
    ans -= 2 * (*max_element( dp , dp + n ));
    printf( "Case %d: %d\n" , ++ _cs , ans );
  }
}
