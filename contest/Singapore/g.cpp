#include <bits/stdc++.h>
using namespace std;
#define N 3030
typedef long long LL;
const LL INF = 10000000000000000ll;
typedef pair<LL,LL> PLL;
LL n , a[ N ] , s[ N ];
void init(){
  scanf( "%lld" , &n );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%lld" , &a[ i ] );
    s[ i ] = s[ i - 1 ] + a[ i ];
  }
}
LL dp[ N ][ N ];
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    dp[ 1 ][ i ] = s[ i ];
  for( int i = 2 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      dp[ i ][ j ] = INF;
  for( int j = 2 ; j <= n ; j ++ ){
    priority_queue< PLL , vector<PLL> , greater<PLL> > heap;
    LL bst = -1;
    heap.push( { dp[ j - 1 ][ j - 1 ] + s[ j - 1 ] , j - 1 } );
    for( int i = j ; i <= n ; i ++ ){
      while( !heap.empty() &&
            heap.top().first <= s[ i ] ){
        bst = max( bst , heap.top().second );
        heap.pop();
      }
      if( bst != -1 && dp[ j - 1 ][ bst ] != INF )
        dp[ j ][ i ] = s[ i ] - s[ bst ];
      heap.push( { dp[ j - 1 ][ i ] + s[ i ] , i } );
    }
  }
  LL ans = 1;
  for( int i = 2 ; i <= n ; i ++ )
    if( dp[ i ][ n ] != INF )
      ans = i;
  printf( "%lld\n" , ans );
}
int main(){
  init();
  solve();
}
