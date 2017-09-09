#include <bits/stdc++.h>
using namespace std;
#define N 214
#define M (N/2)
int nxt[ 22 ][ 3 ];
void build(){
  for( int i = 0 ; i < 5 ; i ++ ){
    nxt[ i ][ 0 ] = ( i + 1 ) % 5;
    nxt[ i ][ 1 ] = ( i + 4 ) % 5;
    nxt[ i ][ 2 ] = i + 5;
  }
  for( int i = 5 ; i < 10 ; i ++ ){
    nxt[ i ][ 0 ] = i + 5;
    nxt[ i ][ 1 ] = i + 6;
    if( nxt[ i ][ 1 ] == 15 )
      nxt[ i ][ 1 ] = 10;
    nxt[ i ][ 2 ] = i - 5;
  }
  for( int i = 10 ; i < 15 ; i ++ ){
    nxt[ i ][ 0 ] = i - 5;
    nxt[ i ][ 1 ] = i - 6;
    if( nxt[ i ][ 1 ] == 4 )
      nxt[ i ][ 1 ] = 9;
    nxt[ i ][ 2 ] = i + 5;
  }
  for( int i = 15 ; i < 20 ; i ++ ){
    nxt[ i ][ 0 ] = i - 1;
    if( nxt[ i ][ 0 ] == 14 )
      nxt[ i ][ 0 ] = 19;
    nxt[ i ][ 1 ] = i + 1;
    if( nxt[ i ][ 1 ] == 20 )
      nxt[ i ][ 1 ] = 15;
    nxt[ i ][ 2 ] = i - 5;
  }
}
int vst[ N ][ N ][ 22 ][ 3 ][ 3 ][ 3 ] , tx , ty , f , stmp;
pair<int,int> next( pair<int,int> cur , int dir ){
  if( ( cur.first + cur.second ) & 1 ){
    if( dir == 0 ) return { cur.first , cur.second - 1 };
    if( dir == 1 ) return { cur.first - 1 , cur.second };
    if( dir == 2 ) return { cur.first + 1 , cur.second };
  }else{
    if( dir == 0 ) return { cur.first + 1 , cur.second };
    if( dir == 1 ) return { cur.first - 1 , cur.second };
    if( dir == 2 ) return { cur.first , cur.second + 1 };
  }
  assert( false );
}
typedef tuple<int,int,int,int,int,int> data;
void solve(){
  ++ stmp;
  vst[ M ][ M ][ 0 ][ 0 ][ 1 ][ 2 ] = stmp;
  queue< pair<int,data> > Q;
  Q.push( { 0 , make_tuple( M , M , 0 , 0 , 1 , 2 ) } );
  while( Q.size() ){
    int nd; data td;
    tie( nd , td ) = Q.front(); Q.pop();
    int nx , ny , nf , nnxt[ 3 ];
    tie( nx , ny , nf , nnxt[ 0 ] , nnxt[ 1 ] , nnxt[ 2 ] ) = td;
    //printf( "step %d at(%d, %d) face %d ,0=%d, 1=%d, 2=%d\n",
            //nd , nx , ny , nf , nnxt[ 0 ] , nnxt[ 1 ] , nnxt[ 2 ] );
    if( nx - M == tx and ny - M == ty and nf == f ){
      printf( "%d\n" , nd );
      return;
    }
    if( nd >= 100 ) continue;
    for( int i = 0 ; i < 3 ; i ++ ){
      int tox , toy;     
      tie( tox , toy ) = next( { nx , ny } , i );
      int nxtf = nxt[ nf ][ nnxt[ i ] ];
      int tnxt[ 3 ];
      //printf( "-> (%d, %d) %d\n" , tox , toy , nxtf );
      if( ( nx + ny ) & 1 ){
        int st = 0;
        for( int j = 0 ; j < 3 ; j ++ )
          if( nxt[ nxtf ][ j ] == nf ){
            st = j;
            break;
          }
        for( int j = 0 ; j < 3 ; j ++ )
          tnxt[ ( i + 2 + j ) % 3 ] = ( st + j ) % 3;
        if( vst[ tox ][ toy ][ nxtf ][ tnxt[ 0 ] ][ tnxt[ 1 ] ][ tnxt[ 2 ] ] ==
            stmp )
          continue;
        vst[ tox ][ toy ][ nxtf ][ tnxt[ 0 ] ][ tnxt[ 1 ] ][ tnxt[ 2 ] ] = stmp;
        Q.push( { nd + 1 , make_tuple( tox , toy , nxtf ,
                                       tnxt[ 0 ] ,
                                       tnxt[ 1 ] ,
                                       tnxt[ 2 ] ) } );
      }else{
        int st = 0;
        for( int j = 0 ; j < 3 ; j ++ )
          if( nxt[ nxtf ][ j ] == nf ){
            st = j;
            break;
          }
        for( int j = 0 ; j < 3 ; j ++ )
          tnxt[ ( i + 1 + j ) % 3 ] = ( st + j ) % 3;
        if( vst[ tox ][ toy ][ nxtf ][ tnxt[ 0 ] ][ tnxt[ 1 ] ][ tnxt[ 2 ] ] ==
            stmp )
          continue;
        vst[ tox ][ toy ][ nxtf ][ tnxt[ 0 ] ][ tnxt[ 1 ] ][ tnxt[ 2 ] ] = stmp;
        Q.push( { nd + 1 , make_tuple( tox , toy , nxtf ,
                                       tnxt[ 0 ] ,
                                       tnxt[ 1 ] ,
                                       tnxt[ 2 ] ) } );
      }
    }
  }
  assert( false );
}
int main (){
  build();
  while( scanf( "%d%d%d" , &tx , &ty , &f ) == 3 ){
    if( tx == 0 and ty == 0 and f == 0 ) break;
    solve();
  }
}
