#include <bits/stdc++.h>
using namespace std;
#define N 1021
int n , m , tg[ N ][ N ] , stmp;
char c[ N ][ N ];
int dn[]={0,0,1,-1};
int dm[]={1,-1,0,0};
bool in( int xn , int xm ){
  return 1 <= xn and xn <= n and
         1 <= xm and xm <= m;
}
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 ){
    for( int i = 1 ; i <= n ; i ++ )
      scanf( "%s" , c[ i ] + 1 );
    ++ stmp;
    bool ok = false;
    for( int i = 1 ; i <= m and not ok ; i ++ )
      if( tg[ 1 ][ i ] != stmp and c[ 1 ][ i ] == '0' ){
        queue< pair<int,int> > Q;
        tg[ 1 ][ i ] = stmp;
        Q.push( { 1 , i } );
        while( Q.size() ){
          pair<int,int> tp = Q.front(); Q.pop();
          int cn = tp.first;
          int cm = tp.second;
          for( int dir = 0 ; dir < 4 ; dir ++ ){
            int nxtn = cn + dn[ dir ];
            int nxtm = cm + dm[ dir ];
            if( nxtn > n ){
              ok = true;
              break;
            }
            if( not in( nxtn , nxtm ) )
              continue;
            if( c[ nxtn ][ nxtm ] == '1' )
              continue;
            if( tg[ nxtn ][ nxtm ] == stmp )
              continue;
            Q.push( { nxtn , nxtm } );
            tg[ nxtn ][ nxtm ] = stmp;
          }
        }
      }
    puts( ok ? "YES" : "NO" );
  }
}
