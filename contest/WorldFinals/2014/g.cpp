#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 514
int p[ N ];
int f( int x ){
  return x == p[ x ] ? x : p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  p[ f( x ) ] = f( y );
}
int n , c[ N ][ N ] , d[ N ][ N ];
const int inf = 1e9;
int main(){
  scanf( "%d" , &n );
  vector< pair<int, pair<int,int> > > cand;
  for( int i = 1 ; i <= n + n ; i ++ ){
    for( int j = 1 ; j <= n + n ; j ++ )
      d[ i ][ j ] = -1;
    d[ i ][ i ] = inf;
    p[ i ] = i;
  }
  if( n <= 2 ){
    puts( "0" );
    exit(0);
  }
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = i + 1 ; j <= n ; j ++ ){
      scanf( "%d" , &c[ i ][ j ] );
      cand.push_back( { c[ i ][ j ] , { i , j } } );
      d[ i ][ j + n ] = c[ i ][ j ];
      d[ j ][ i + n ] = c[ i ][ j ];
    }
  for( int k = 1 ; k <= n + n ; k ++ )
    for( int i = 1 ; i <= n + n ; i ++ )
      for( int j = 1 ; j <= n + n ; j ++ )
        d[ i ][ j ] = max( d[ i ][ j ] , min( d[ i ][ k ] , d[ k ][ j ] ) );
  sort( cand.begin() , cand.end() );
  reverse( cand.begin() , cand.end() );
  int ans = cand[ 0 ].first;
  for( auto e : cand ){
    int bst = 0;
    for( int i = 1 ; i <= n ; i ++ )
      bst = max( bst , min( d[ i ][ i + n ]  , d[ i + n ][ i ] ) );
    if( bst > e.first ) break;
    ans = min( ans , e.first + bst );
    //cerr << e.first << " " << bst << endl;
    int s = e.second.first;
    int t = e.second.second;
    if( f( s + n ) == f( t ) )
      continue;
    uni( s + n , t );
    uni( t + n , s );
    // s + n -> t
    d[ s + n ][ t ] = max( d[ s + n ][ t ] , e.first );
    d[ t + n ][ s ] = max( d[ t + n ][ s ] , e.first );
    //for( int k = 1 ; k <= n + n ; k ++ )
      //for( int i = 1 ; i <= n + n ; i ++ )
        //for( int j = 1 ; j <= n + n ; j ++ )
          //d[ i ][ j ] = max( d[ i ][ j ] , min( d[ i ][ k ] , d[ k ][ j ] ) );
    for( int k = 1 ; k <= n + n ; k ++ )
      for( int kk = 1 ; kk <= n + n ; kk ++ )
        d[ k ][ kk ] = max( d[ k ][ kk ] ,
                            min( d[ k ][ s + n ] , min( d[ t ][ kk ] , d[ s + n ][ t ] ) ) );
    for( int k = 1 ; k <= n + n ; k ++ )
      for( int kk = 1 ; kk <= n + n ; kk ++ )
        d[ k ][ kk ] = max( d[ k ][ kk ] ,
                            min( d[ k ][ t + n ] , min( d[ s ][ kk ] , d[ t + n ][ s ] ) ) );
    //for( int k = 1 ; k <= n + n ; k ++ , puts( "" ) )
      //for( int kk = 1 ; kk <= n + n ; kk ++ )
        //printf( "%d " , d[ k ][ kk ] );
    //exit(0);
  }
  printf( "%d\n" , ans );
}
