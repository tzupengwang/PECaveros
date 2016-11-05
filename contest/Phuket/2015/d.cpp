#include <bits/stdc++.h>
using namespace std;
#define N 111
int p[ N * N * 3 ];
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  p[ f( x ) ] = f( y );
}
int r , c , cst[ N ][ N ];
char cc[ N ][ N ];
int tot;
void init(){
  scanf( "%d%d" , &r , &c );
  for( int i = 0 ; i < r ; i ++ )
    scanf( "%s" , cc[ i ] );
  for( int i = 0 ; i < r ; i ++ )
    for( int j = 0 ; j < c ; j ++ )
      scanf( "%d" , &cst[ i ][ j ] );
  tot = ( r + 1 ) * c + r * ( c + 1 );
}
vector< pair< int , pair<int,int> > > vv;
void add_edge( int u , int v , int c ){
  vv.push_back( { c , { v , u } } );
}
int _cs;
void solve(){
  vv.clear();
  int pre = ( r + 1 ) * c;
  for( int i = 0 ; i < r ; i ++ )
    for( int j = 0 ; j < c ; j ++ ){
      int id[ 4 ] = { i * c + j , ( j + 1 ) * r + i + pre ,
                      ( i + 1 ) * c + j , j * r + i + pre };
      if( cc[ i ][ j ] == '/' ){
        add_edge( id[ 0 ] , id[ 3 ] , 0 );
        add_edge( id[ 1 ] , id[ 2 ] , 0 );
        add_edge( id[ 2 ] , id[ 3 ] , cst[ i ][ j ] );
        add_edge( id[ 0 ] , id[ 1 ] , cst[ i ][ j ] );
      }else{
        add_edge( id[ 0 ] , id[ 1 ] , 0 );
        add_edge( id[ 2 ] , id[ 3 ] , 0 );
        add_edge( id[ 0 ] , id[ 3 ] , cst[ i ][ j ] );
        add_edge( id[ 1 ] , id[ 2 ] , cst[ i ][ j ] );
      }
    }
  sort( vv.begin() , vv.end() );
  for( int i = 0 ; i < tot ; i ++ )
    p[ i ] = i;
  long long ans = 0;
  for( auto i : vv ){
    if( f( i.second.first ) ==
        f( i.second.second ) )
      continue;
    uni( i.second.first , i.second.second );
    ans += i.first;
  }
  printf( "Case %d: %lld\n" , ++ _cs , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
