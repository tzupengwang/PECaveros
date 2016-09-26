#include <bits/stdc++.h>
using namespace std;
#define N 303030
struct Tree{
  int n , lc[ N ] , rc[ N ] , by[ N ] , po[ N ] , stp , p[ N ];
  bool leaf[ N ];
  void go( int now ){
    if( now == 0 ) return;
    go( lc[ now ] );
    po[ now ] = ++ stp;
    go( rc[ now ] );
  }
  void build(){
    stp = 0;
    go( 1 );
    priority_queue< pair<int,int> > heap;
    for( int i = 1 ; i <= n ; i ++ )
      if( !leaf[ i ] && leaf[ lc[ i ] ] && leaf[ rc[ i ] ] )
        heap.push( { po[ i ] , i } );
    int cnt = 1;
    while( heap.size() ){
      pair<int,int> tp = heap.top(); heap.pop();
      int idx = tp.second;
      by[ lc[ idx ] ] = cnt;
      by[ rc[ idx ] ] = cnt;
      if( idx == 1 ) continue;
      leaf[ idx ] = true;
      if( leaf[ lc[ p[ idx ] ] ] &&
          leaf[ rc[ p[ idx ] ] ] )
        heap.push( { po[ p[ idx ] ] , p[ idx ] } );
      cnt ++;
    }
    by[ 1 ] = cnt;
  }
  void init( int _n ){
    n = _n;
    for( int i = 0 ; i <= n ; i ++ )
      leaf[ i ] = false;
    for( int i = 1 ; i <= n ; i ++ ){
      scanf( "%d%d" , &lc[ i ] , &rc[ i ] );
      if( lc[ i ] == 0 && rc[ i ] == 0 )
        leaf[ i ] = true;
      p[ lc[ i ] ] = p[ rc[ i ] ] = i;
    }
    build();
  }
} t[ 2 ];
bool equal( int id1 , int id2 , int out1 , int out2 ){
  if( ( id1 == 0 || t[ 0 ].by[ id1 ] <= out1 ) &&
      ( id2 == 0 || t[ 1 ].by[ id2 ] <= out2 ) )
    return true;
  if( ( id1 == 0 || t[ 0 ].by[ id1 ] <= out1 ) ^
      ( id2 == 0 || t[ 1 ].by[ id2 ] <= out2 ) )
    return false;
  return equal( t[ 0 ].lc[ id1 ] , t[ 1 ].lc[ id2 ] , out1 , out2 ) &&
         equal( t[ 0 ].rc[ id1 ] , t[ 1 ].rc[ id2 ] , out1 , out2 );
}
inline bool same( int out1 , int out2 ){
  return equal( 1 , 1 , out1 , out2 );
}
int idx[ N ] , ic , a[ N ][ 2 ];
void mark( int id , int out ){
  if( id == 0 || t[ 0 ].by[ id ] <= out ){
    idx[ id ] = 0;
    return;
  }
  idx[ id ] = ++ ic;
  mark( t[ 0 ].lc[ id ] , out );
  mark( t[ 0 ].rc[ id ] , out );
  a[ idx[ id ] ][ 0 ] = idx[ t[ 0 ].lc[ id ] ];
  a[ idx[ id ] ][ 1 ] = idx[ t[ 0 ].rc[ id ] ];
}
void print( int out ){
  ic = 0;
  mark( 1 , out );
  printf( "%d\n" , ic );
  for( int i = 1 ; i <= ic ; i ++ )
    printf( "%d %d\n" , a[ i ][ 0 ] , a[ i ][ 1 ] );
}
int n[ 2 ] , lvl[ 2 ];
bool init(){
  scanf( "%d" , &n[ 0 ] );
  if( n[ 0 ] == 0 ) return false;
  t[ 0 ].init( n[ 0 ] );
  scanf( "%d" , &n[ 1 ] );
  t[ 1 ].init( n[ 1 ] );
  return true;
}
void solve(){
  lvl[ 0 ] = n[ 0 ] / 2;
  lvl[ 1 ] = n[ 1 ] / 2;
  int dlt[ 2 ] = { 0 , 0 };
  if( lvl[ 0 ] > lvl[ 1 ] ) dlt[ 0 ] = lvl[ 0 ] - lvl[ 1 ];
  if( lvl[ 0 ] < lvl[ 1 ] ) dlt[ 1 ] = lvl[ 1 ] - lvl[ 0 ];
  int bl = 0 , br = min( lvl[ 0 ] , lvl[ 1 ] ) , ba = br;
  while( bl <= br ){
    int bmid = ( bl + br ) >> 1;
    if( same( bmid + dlt[ 0 ] , bmid + dlt[ 1 ] ) )
      ba = bmid , br = bmid - 1;
    else
      bl = bmid + 1;
  }
  print( ba + dlt[ 0 ] );
}
int main(){
  freopen( "lca.in" , "r" , stdin );
  freopen( "lca.out" , "w" , stdout );
  while( init() ) solve();
}
