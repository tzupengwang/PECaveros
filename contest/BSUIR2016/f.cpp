#include <bits/stdc++.h>
using namespace std;
#define N 514
char c[ N ][ N ];
bool burn[ N ][ N ];
int keep[ N ][ N ];
int n , m , k;
inline bool in( int xn , int xm ){
  return 1 <= xn and xn <= n and
         1 <= xm and xm <= m;
}
int dn[]={0,0,1,-1};
int dm[]={1,-1,0,0};
int main(){
  cin >> n >> m >> k;
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%s" , c[ i ] + 1 );
  priority_queue< pair<int, pair<int,int>> > heap;
  while( k -- ){
    int xi , yi , ci;
    scanf( "%d%d%d" , &xi , &yi , &ci );
    if( c[ xi ][ yi ] == 'X' )
      continue;
    heap.push( { ci , { xi , yi } } );
    burn[ xi ][ yi ] = true;
    keep[ xi ][ yi ] = ci;
  }
  while( heap.size() ){
    pair<int, pair<int,int> > tp = heap.top(); heap.pop();
    int cn = tp.second.first;
    int cm = tp.second.second;
    if( keep[ cn ][ cm ] == 0 ) continue;
    if( keep[ cn ][ cm ] != tp.first ) continue;
    int nxtc = keep[ cn ][ cm ] - 1;
    for( int dir = 0 ; dir < 4 ; dir ++ ){
      int nxtn = cn + dn[ dir ];
      int nxtm = cm + dm[ dir ];
      if( not in( nxtn , nxtm ) )
        continue;
      if( c[ nxtn ][ nxtm ] == 'X' )
        continue;
      if( not burn[ nxtn ][ nxtm ] or
          nxtc > keep[ nxtn ][ nxtm ] ){
        burn[ nxtn ][ nxtm ] = true;
        keep[ nxtn ][ nxtm ] = nxtc;
        heap.push( { nxtc , { nxtn , nxtm } } );
      }
    }
  }
  int ans = 0;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      ans += (burn[ i ][ j ] ? 1 : 0);
  cout << ans << endl;
}
