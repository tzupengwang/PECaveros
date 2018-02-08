#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 4
const int inf = 100000;
char c[ 9 ][ 9 ];
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
char dc[] = "RLDU";
int blk , stmp;
int sp[ 1 << 16 ][ 16 ];
int tg[ 1 << 16 ][ 16 ];
int all_sp;
inline bool in( int x , int y ){
  return 0 <= x and x < N and
         0 <= y and y < N;
}
inline int id( int x , int y ){ return (x << 2) | y; }
inline int SP( int noway , int cx , int cy ){
  if( cx + 1 == N and cy + 1 == N ) return 0;
  if( tg[ noway ][ id( cx , cy ) ] == stmp )
    return sp[ noway ][ id( cx , cy ) ];
  int ret = inf;
  for( int dir = 0 ; dir < 4 ; dir ++ ){
    int nxtx = cx + dx[ dir ];
    int nxty = cy + dy[ dir ];
    if( not in( nxtx , nxty ) ) continue;
    if( (noway >> id( nxtx , nxty )) & 1 ) continue;
    ret = min( ret , SP( noway | (1 << id( nxtx , nxty )) , nxtx , nxty ) + 1 );
  }
  tg[ noway ][ id( cx , cy ) ] = stmp;
  return sp[ noway ][ id( cx , cy ) ] = ret;
}
int vst[ 1 << 16 ][ 16 ];
char buf[ 32 ];
bool got;
void go( int noway , int cx , int cy , int stp ){
  if( cx + 1 == N and cy + 1 == N ){
    if( stp > all_sp ){
      got = true;
      for( int i = 0 ; i < stp ; i ++ )
        putchar( buf[ i ] );
      puts( "" );
    }
    return;
  }
  if( vst[ noway ][ id( cx , cy ) ] == stmp ) return;
  vst[ noway ][ id( cx , cy ) ] = stmp;
  for( int dir = 0 ; dir < 4 ; dir ++ ){
    int nxtx = cx + dx[ dir ];
    int nxty = cy + dy[ dir ];
    if( not in( nxtx , nxty ) ) continue;
    if( (noway >> id( nxtx , nxty )) & 1 ) continue;
    buf[ stp ] = dc[ dir ];
    go( noway | (1 << id( nxtx , nxty )) , nxtx , nxty , stp + 1 );
    if( got ) return;
  }
}
void gogo(){
  got = false;
  go( blk | (1 << id( 0 , 0 )) , 0 , 0 , 0 );
  if( not got )
    puts( "-1" );
}
int main(){
  while( scanf( "%s" , c[ 0 ] ) == 1 ){
    for( int i = 1 ; i < N ; i ++ )
      scanf( "%s" , c[ i ] );
    blk = 0;
    for( int i = 0 ; i < N ; i ++ )
      for( int j = 0 ; j < N ; j ++ )
        if( c[ i ][ j ] != '.' )
          blk |= (1 << id( i , j ));
    ++ stmp;
    all_sp = SP( blk | (1 << id( 0 , 0 )) , 0 , 0 );
    if( all_sp >= inf )
      puts( "-1" );
    else
      gogo();
    scanf( "%s" , c[ 8 ] );
  }
}
