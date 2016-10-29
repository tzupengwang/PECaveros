#include <bits/stdc++.h>
using namespace std;
#define N 111
int n , m;
char c[ N ][ N ];
int cst[ 2 ][ N ][ N ];
bool got[ 2 ][ N ][ N ];
int px[ 2 ] , py[ 2 ] , sum;
bool in( int x , int y ){
  return 1 <= x && x <= n &&
         1 <= y && y <= m;
}
void init(){
  scanf( "%d%d" , &n , &m );
  sum = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%s" , c[ i ] + 1 );
    for( int j = 1 ; j <= m ; j ++ ){
      if( isalpha( c[ i ][ j ] ) ){
        px[ c[ i ][ j ] - 'A' ] = i;
        py[ c[ i ][ j ] - 'A' ] = j;
      }else
        sum += c[ i ][ j ] - '0';
      for( int k = 0 ; k < 2 ; k ++ )
        got[ k ][ i ][ j ] = false;
    }
  }
}
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
void find_sp(){
  for( int i = 0 ; i < 2 ; i ++ ){
typedef pair< int , pair<int,int> > data;
    priority_queue< data , vector< data > , greater< data > > heap;
    heap.push( { 0 , { px[ i ] , py[ i ] } } );
    while( heap.size() ){
      data td = heap.top(); heap.pop();
      int dd = td.first;
      int nx = td.second.first , ny = td.second.second;
      if( got[ i ][ nx ][ ny ] ) continue;
      got[ i ][ nx ][ ny ] = true;
      cst[ i ][ nx ][ ny ] = dd;
      for( int j = 0 ; j < 4 ; j ++ ){
        int nxtx = nx + dx[ j ];
        int nxty = ny + dy[ j ];
        if( in( nxtx , nxty ) &&
            '1' <= c[ nxtx ][ nxty ] &&
            c[ nxtx ][ nxty ] <= '9' &&
            !got[ i ][ nxtx ][ nxty ] )
          heap.push( { dd + c[ nxtx ][ nxty ] - '0' , { nxtx , nxty } } );
      }
    }
  }
}
int _cs;
void solve(){
  find_sp();
  int bst = sum;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      if( '1' <= c[ i ][ j ] && c[ i ][ j ] <= '9' ){
        if( !got[ 0 ][ i ][ j ] ) continue;
        if( !got[ 1 ][ i ][ j ] ) continue;
        int aa = cst[ 0 ][ i ][ j ] + cst[ 1 ][ i ][ j ] -
                 2 * ( c[ i ][ j ] - '0' );
        if( aa < bst ) bst = aa;
      }
  printf( "Case #%d: %d\n" , ++ _cs , sum - bst );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
