#include <bits/stdc++.h>
using namespace std;
#define N 514
int n , a[ N ] , ps[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &a[ i ] );
    ps[ i ] = ps[ i - 1 ] + a[ i ];
  }
}
#define K 1514
int dp[ 2 ][ K ][ K ];
int tag[ 2 ][ K ][ K ];
bool got[ 2 ][ K ][ K ];
queue< pair< int , pair<int,int> > > Q;
void solve(){
  for( int i = 0 ; i <= max( ps[ n ] / n + n / 2 + 3 , a[ 1 ] ) ; i ++ )
    Q.push( { 1 , { i , i } } );
  int ans = 2147483647;
  while( Q.size() ){
    pair< int , pair<int,int> > tp = Q.front(); Q.pop();
    int now = tp.first;
    int nxt = now + 1;
    int nowv = tp.second.first;
    int nowsum = tp.second.second;
    if( now == n ){
      if( nowsum == ps[ n ] )
        ans = min( ans , dp[ now & 1 ][ nowv ][ ps[ n ] ] );
      continue;
    }
    for( int j = -1 ; j <= 1 ; j ++ ){
      int cst = dp[ now & 1 ][ nowv ][ nowsum ] + abs( ps[ now ] - nowsum );
      int nd = nowv + j;
      if( nd < 0 ) continue;
      int nxtsum = nowsum + nd;
      if( nxtsum > ps[ n ] ) continue;
      if( tag[ nxt & 1 ][ nd ][ nxtsum ] != nxt ||
          cst < dp[ nxt & 1 ][ nd ][ nxtsum ] ){
        if( tag[ nxt & 1 ][ nd ][ nxtsum ] != nxt )
          got[ nxt & 1 ][ nd ][ nxtsum ] = false;
        tag[ nxt & 1 ][ nd ][ nxtsum ] = nxt;
        dp[ nxt & 1 ][ nd ][ nxtsum ] = cst;
        if( !got[ nxt & 1 ][ nd ][ nxtsum ] ){
          got[ nxt & 1 ][ nd ][ nxtsum ] = true;
          Q.push( { nxt , { nd , nxtsum } } );
        }
      }
    }
  }
  printf( "%d\n" , ans );
}
int main(){
  init();
  solve();
}
