#include <bits/stdc++.h>
using namespace std;
#define N 111
int a[ N ][ N ] , n , p , aa;
int main(){
  cin >> n >> p;
  if( p == 1 ){
    for( int i = 1 ; i <= n ; i ++ )
      if( i & 1 ){
        for( int j = 1 ; j <= n ; j ++ )
          a[ i ][ j ] = ++ aa;
      }else{
        for( int j = n ; j >= 1 ; j -- )
          a[ i ][ j ] = ++ aa;
      }
  }else if( p == 2 ){
    for( int i = 1 ; i <= n ; i ++ )
      if( i & 1 ){
        for( int j = 1 ; j <= n ; j ++ )
          a[ j ][ i ] = ++ aa;
      }else{
        for( int j = n ; j >= 1 ; j -- )
          a[ j ][ i ] = ++ aa;
      }
  }else{
    int dx[4], dy[4];
    if( p == 3 ){
      dx[0] = 0; dy[0] = 1;
      dx[1] = 1; dy[1] = 0;
      dx[2] = 0; dy[2] = -1;
      dx[3] = -1; dy[3] = 0;
    }else{
      dx[0] = 1; dy[0] = 0;
      dx[1] = 0; dy[1] = 1;
      dx[2] = -1; dy[2] = 0;
      dx[3] = 0; dy[3] = -1;
    }
    int nowx = 1 , nowy = 1;
    for( int i = 1 , cur = 0 ; i <= n * n ; i ++ ){
      a[ nowx ][ nowy ] = i;
      int nxtx = nowx + dx[ cur ];
      int nxty = nowy + dy[ cur ];
      if( nxtx < 1 or nxtx > n or
          nxty < 1 or nxty > n or
          a[ nxtx ][ nxty ] ){
        cur = ( cur + 1 ) % 4;
        nowx += dx[ cur ];
        nowy += dy[ cur ];
      }else{
        nowx = nxtx;
        nowy = nxty;
      }
    }
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      cout << a[ i ][ j ] << " \n"[ j == n ];
}
