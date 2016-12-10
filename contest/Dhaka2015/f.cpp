#include <bits/stdc++.h>
using namespace std;
#define N 256
int r , c , a[ N ][ N ] , b[ N ][ N ] , q;
void init(){
  scanf( "%d%d" , &r , &c );
  for( int i = 1 ; i <= r ; i ++ )
    for( int j = 1 ; j <= c ; j ++ )
      scanf( "%d" , &a[ i ][ j ] );
}
int cs , d[ N ] , dd[ N ];
int h[ 20 ] , ans[ 20 ];
int bst[ N ][ N ];
void go( int id , int i1 , int i2 ){
  if( bst[ i1 ][ i2 ] * ( i2 - i1 + 1 ) <= ans[ id ] )
    return;
  for( int i = 1 ; i <= c ; i ++ ){
    d[ i ] = b[ i2 ][ i ] - b[ i1 - 1 ][ i ];
    d[ i ] += d[ i - 1 ];
    dd[ i ] = min( dd[ i - 1 ] , d[ i ] );
  }
  int tbst = 0;
  for( int i = 1 ; i <= c ; i ++ ){
    int bl = 0 , br = i - 1 , kk = N;
    while( bl <= br ){
      int mid = ( bl + br ) >> 1;
      if( dd[ mid ] <= d[ i ] ) kk = mid , br = mid - 1;
      else bl = mid + 1;
    }
    int len = i - kk;
    ans[ id ] = max( ans[ id ] , ( i2 - i1 + 1 ) * len );
    tbst = max( tbst , len ); 
  }
  bst[ i1 ][ i2 ] = min( bst[ i1 ][ i2 ] , tbst );
}
void find_ans( int id ){
  ans[ id ] = 0;
  for( int hh = r ; hh >= 1 ; hh -- ){
    if( hh * c <= ans[ id ] ) break;
    for( int r1 = 1 ; r1 + hh - 1 <= r ; r1 ++ )
      go( id , r1 , r1 + hh - 1 );
  }
}
void solve(){
  printf( "Case %d:\n" , ++ cs );
  scanf( "%d" , &q );
  vector< pair<int,int> > qry;
  for( int i = 0 ; i < q ; i ++ ){
    scanf( "%d" , &h[ i ] );
    qry.push_back( { h[ i ] , i } );
  }
  sort( qry.begin() , qry.end() );
  for( int i = 1 ; i <= r ; i ++ )
    for( int j = i ; j <= r ; j ++ )
      bst[ i ][ j ] = c;
  for( auto qq : qry ){
    for( int i = 1 ; i <= r ; i ++ )
      for( int j = 1 ; j <= c ; j ++ ){
        if( a[ i ][ j ] >= qq.first )
          b[ i ][ j ] = 1;
        else
          b[ i ][ j ] = -1;
        b[ i ][ j ] += b[ i - 1 ][ j ];
      }
    find_ans( qq.second );
  }
  for( int i = 0 ; i < q ; i ++ )
    printf( "%d\n" , ans[ i ] );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
