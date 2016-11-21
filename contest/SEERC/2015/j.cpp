#include <bits/stdc++.h>
using namespace std;
#define N 101
#define M 10
int now[ N ] , n , m , bad[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 0 ; i < m ; i ++ ){
    int x; scanf( "%d" , &x );
    bad[ x ] = 1;
  }
  for( int i = 2 ; i <= n ; i ++ ){
    char c[ 9 ]; scanf( "%s" , c );
    if( c[ 0 ] == 'h' ) now[ i ] = 0;
    else now[ i ] = 1;
  }
}
int dp[ M ][ M ][ M ][ 2 ][ 2 ];
// round rest'bad he's'good leader'say
void solve(){
  for( int k = 0 ; k <= m ; k ++ )
    for( int u = 0 ; u <= m ; u ++ ){
      dp[ 0 ][ k ][ u ][ 0 ][ 0 ] = 0;
      dp[ 0 ][ k ][ u ][ 1 ][ 0 ] = 0;
      dp[ 0 ][ k ][ u ][ 0 ][ 1 ] = 1;
      dp[ 0 ][ k ][ u ][ 1 ][ 1 ] = 1;
    }
  for( int rd = 1 ; rd <= m ; rd ++ ){
    int to = n - ( m - rd - 1 );
    for( int j = 0 ; j <= m ; j ++ ){
      if( j > to ) continue;
      for( int rec = 0 ; rec <= m ; rec ++ )
        for( int good = 0 ; good < 2 ; good ++ )
        for( int say = 0 ; say < 2 ; say ++ ){
          if( j - good < 0 ) continue;
          // dp[ rd ][ j ][ good ][ say ]
          // from dp[ rd - 1 ][ j - good ][ good ][ good -> say , bad -> 1 ]
          int goodtell = dp[ rd - 1 ][ j - good ][ rec + ( say == 0 ) ][ good ][ say ];
          int goodres = to - j , badres = j;
          if( good ) badres --;
          else goodres --;
          int cnt[ 2 ] = { rec , ( m - rd ) - rec };
          cnt[ 1 ] += badres;
          cnt[ goodtell ] += goodres;
          cnt[ say ] ++;
          dp[ rd ][ j ][ rec ][ good ][ say ] = cnt[ 1 ] >= cnt[ 0 ];
        }
    }
  }
  for( int i = 2 ; i <= n ; i ++ )
    if( !bad[ i ] ){
      int cnt[ 2 ] = {};
      for( int j = 2 ; j <= n ; j ++ )
        if( i != j )
          cnt[ dp[ m - 1 ][ m - bad[ j ] - bad[ 1 ] ][ ( now[ j ] == 0 ) + ( bad[ j ] == 0 && now[ j ] == 0 ) ][ 1 ][ bad[ j ] ? 1 : now[ j ] ] ] ++;
      cnt[ now[ i ] ] ++;
      puts( cnt[ 1 ] >= cnt[ 0 ] ? "cat" : "hat" );
    }
}
int main(){
  init();
  solve();
}
