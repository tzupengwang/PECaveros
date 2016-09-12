#include <bits/stdc++.h>
using namespace std;
#define N 222
int n , k , ans[ N ] , cnt[ N ] , all , nd[ N ];
bool got[ N ][ N ];
int req[ N ][ N ] , sent[ N ][ N ] , cnt2[ N ];
int give[ N ];
void solve(){
  for( int i = 1 ; i <= k ; i ++ ){
    got[ 1 ][ i ] = true;
    cnt2[ i ] ++;
  }
  cnt[ 1 ] = k;
  all = k;
  for( int t = 1 ; all < n * k ; t ++ ){
    for( int i = 1 ; i <= n ; i ++ ){
      nd[ i ] = -1;
      if( cnt[ i ] == k ) continue;
      for( int j = 1 ; j <= k ; j ++ )
        if( !got[ i ][ j ] ){
          if( nd[ i ] == -1 || cnt2[ j ] < cnt2[ nd[ i ] ] )
            nd[ i ] = j;
        }
      if( nd[ i ] == -1 ) continue;
      int want = -1;
      for( int j = 1 ; j <= n ; j ++ )
        if( got[ j ][ nd[ i ] ] ){
          if( want == -1 || cnt[ j ] < cnt[ want ] )
            want = j;
        }
      if( want == -1 ) continue;
      req[ want ][ i ] = t;
    }
    for( int i = 1 ; i <= n ; i ++ ){
      int to = -1;
      for( int j = 1 ; j <= n ; j ++ )
        if( req[ i ][ j ] == t ){
          if( to == -1 || sent[ j ][ i ] > sent[ to ][ i ] ||
              ( sent[ j ][ i ] == sent[ to ][ i ] && cnt[ j ] < cnt[ to ] ) )
            to = j;
        }
      give[ i ] = to;
    }
    for( int i = 1 ; i <= n ; i ++ ){
      int to = give[ i ];
      if( to == -1 ) continue;
      sent[ i ][ to ] ++;
      got[ to ][ nd[ to ] ] = true;
      cnt2[ nd[ to ] ] ++;
      cnt[ to ] ++;
      all ++;
      if( cnt[ to ] == k )
        ans[ to ] = t;
    }
  }
  for( int i = 2 ; i <= n ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i == n ] );
}
int main(){
  freopen( "epig.in" , "r" , stdin );
  freopen( "epig.out" , "w" , stdout );
  scanf( "%d%d" , &n , &k );
  solve();
}
