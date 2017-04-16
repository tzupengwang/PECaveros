#include <bits/stdc++.h>
using namespace std;
#define N 505050
struct DJS{
  int sz , p[ N ];
  void init( int _n ){
    sz = _n;
    for( int i = 1 ; i <= sz ; i ++ )
      p[ i ] = i;
  }
  int f( int x ){
    return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
  }
  void uni( int x , int y ){
    x = f( x );
    y = f( y );
    if( x == y ) return;
    sz --;
    p[ x ] = y;
  }
} djs;
int n , m , k , w;
bool spe[ N ];
int a[ N ] , b[ N ] , c[ N ];
int cal( int dlt , bool flag = false ){
  vector< pair<int,int> > e;
  //for( int i = 0 ; i < m ; i ++ )
    //printf( "%d %d\n" , i , c[ i ] );
  for( int i = 0 ; i < m ; i ++ )
    if( spe[ a[ i ] ] == spe[ b[ i ] ] )
      e.push_back( { c[ i ] , i } );
    else
      e.push_back( { c[ i ] + dlt , i } );
  sort( e.begin() , e.end() );
  djs.init( n );
  long long ans = 0;
  int cc = 0;
  for( auto i : e ){
    //printf( "%d : %d\n" , i.second , i.first );
    int id = i.second;
    if( djs.f( a[ id ] ) == djs.f( b[ id ] ) )
      continue;
    ans += i.first;
    djs.uni( a[ id ] , b[ id ] );
    if( spe[ a[ id ] ] != spe[ b[ id ] ] )
      cc ++;
  }
  if( djs.sz > 1 ){
    puts( "-1" );
    exit( 0 );
  }
  if( cc == w or flag ){
    printf( "%lld\n" , ( ans - (long long)dlt * w ) / 2 );
    exit( 0 );
  }
  return cc;
}
int main(){
  scanf( "%d%d%d%d" , &n , &m , &k , &w ); 
  while( k -- ){
    int x; scanf( "%d" , &x );
    spe[ x ] = true;
  }
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d%d" , &a[ i ] , &b[ i ] , &c[ i ] );
    c[ i ] *= 2;
  }
  int bl = 0 , br = 400000;
  int mx = -1 , mn = 400001;
  bool hasl = false , hasr = false;
  while( bl <= br ){
    int bmid = ( bl + br ) >> 1;
    int ret = cal( bmid - 200000 );
    if( ret > w ){
      bl = bmid + 1;
      hasl = true;
      mx = max( mx , bmid );
    }else{
      br = bmid - 1;
      hasr = true;
      mn = min( mn , bmid );
    }
  }
  if( hasl and hasr )
    cal( mn - 200000 , true );
  puts( "-1" );
}
