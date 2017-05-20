#include <bits/stdc++.h>
using namespace std;
#define N 202020
int n;
int ind[ N ] , to[ N ];
bool got[ N ];
void init(){
  for( int i = 1 ; i <= n + n ; i ++ ){
    ind[ i ] = 0;
    got[ i ] = false;
  }
  for( int i = 1 ; i <= n + n ; i ++ ){
    scanf( "%d" , &to[ i ] );
    ind[ to[ i ] ] ++;
  }
}
void solve(){
  vector<int> ans;
  queue<int> que;
  for( int i = 1 ; i <= n + n ; i ++ )
    if( ind[ i ] == 0 ){
      ans.push_back( i );
      que.push( i );
      got[ i ] = true;
      if( not got[ to[ i ] ] ){
        que.push( to[ i ] );
        got[ to[ i ] ] = true;
      }
    }
  while( not que.empty() ){
    int who = que.front(); que.pop();
    ind[ to[ who ] ] --;
    if( ind[ to[ who ] ] == 0 and not got[ to[ who ] ] ){
      got[ to[ who ] ] = true;
      ans.push_back( to[ who ] );
      que.push( to[ who ] );
      if( not got[ to[ to[ who ] ] ] ){
        que.push( to[ to[ who ] ] );
        got[ to[ to[ who ] ] ] = true;
      }
    }
  }
  for( int i = 1 ; i <= n + n ; i ++ )
    if( not got[ i ] ){
      int now = i , vv = 0;
      while( not got[ now ] ){
        got[ now ] = true;
        if( vv == 0 ) ans.push_back( now );
        now = to[ now ];
        vv = 1 - vv;
      }
    }
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
int main(){
  while( scanf( "%d" , &n ) == 1 ){
    init();
    solve();
  }
}
