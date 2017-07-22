#include <bits/stdc++.h>
using namespace std;
#define N 55
typedef long long LL;
int n , cnt[ N ] , mx;
LL ans[ N ] , c , a[ N ];
void init(){
  cin >> n;
  for( int i = 1 ; i <= n ; i ++ ){
    cin >> a[ i ];
    cnt[ i ] = __builtin_popcountll( a[ i ] );
    for( int j = 0 ; j < 60 ; j ++ )
      if( ( a[ i ] >> j ) & 1ll )
        mx = max( mx , j );
  }
}
bool dp[ N ][ 66 ];
int bk[ N ][ 66 ];
LL vv[ N ][ 66 ];
LL aa[ N ][ 66 ];
void solve(){
  dp[ 0 ][ 0 ] = true;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j <= mx + 1 ; j ++ ){
      if( not dp[ i ][ j ] ) continue;
      LL cur = vv[ i ][ j ];
      vector<int> one , zer;
      for( int k = 0 ; k <= mx ; k ++ )
        if( ( cur >> k ) & 1LL )
          one.push_back( k );
        else
          zer.push_back( k );
      for( int inter = 0 ; inter <= min( j , cnt[ i + 1 ] ) ; inter ++ ){
        if( inter > (int)one.size() ) continue;
        int res = cnt[ i + 1 ] - inter;
        if( res > (int)zer.size() ) continue;
        int totone = j + cnt[ i + 1 ] - inter;
        if( totone > mx + 1 ) continue;
        LL nxt = 0;
        for( int ii = 0 ; ii < inter ; ii ++ )
          nxt |= ( 1LL << one[ ii ] );
        for( int ii = 0 ; ii < res ; ii ++ )
          nxt |= ( 1LL << zer[ ii ] );
        int pp = __builtin_popcountll( nxt ^ cur );
        dp[ i + 1 ][ pp ] = true;
        //printf( "%d %d %lld nxt=%lld, cur=%lld, inter=%d, res=%d, cnt=%d\n" ,
                //i + 1 , pp , nxt ^ cur , nxt , cur , inter , res , cnt[ i + 1 ] );
        vv[ i + 1 ][ pp ] = nxt ^ cur;
        bk[ i + 1 ][ pp ] = j;
        aa[ i + 1 ][ pp ] = nxt;
      }
    }
  if( not dp[ n ][ 0 ] ){
    puts( "impossible" );
    exit(0);
  }
  int at = 0;
  for( int i = n ; i >= 1 ; i -- ){
    ans[ i ] = aa[ i ][ at ];
    at = bk[ i ][ at ];
  }
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%lld%c" , ans[ i ] , " \n"[ i == n ] );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "xor.in" , "r" , stdin );
  freopen( "xor.out" , "w" , stdout );
#endif
  init();
  solve();
}
