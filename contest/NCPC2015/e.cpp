#include <bits/stdc++.h>
using namespace std;
#define N 13
int n , d , s , t , __ = 1;
vector<int> v[ N ];
long long dp[ 1 << N ][ N ];
void init(){
  scanf( "%d%d%d%d" , &n , &d , &s , &t );
  s --; t --;
  for( int i = 0 ; i < n ; i ++ ) v[ i ].clear();
  for( int i = 0 ; i < n ; i ++ ){
    int x; scanf( "%d" , &x );
    while( x -- ){
      int y; scanf( "%d" , &y );
      y --;
      v[ i ].push_back( y );
    }
  }
  for( int i = 0 ; i < ( 1 << n ) ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      dp[ i ][ j ] = 0;
  dp[ ( 1 << s ) ][ s ] = 1;
}
void solve(){
  for( int i = 0 ; i < ( 1 << n ) ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      for( int k = 0 ; k < (int)v[ j ].size() ; k ++ ){
        int nxt = v[ j ][ k ];
        if( ( i & ( 1 << nxt ) ) == 0 ){
          int nxtst = i ^ ( 1 << nxt );
          dp[ nxtst ][ nxt ] += dp[ i ][ j ];
        }
      }
  long long ans = 0;
  for( int i = 0 ; i < ( 1 << n ) ; i ++ )
    ans += dp[ i ][ t ];
  cout << ans << endl;
}
int main(){
  scanf( "%d" , &__ ); while( __ -- ){
    init();
    solve();
  }
}
