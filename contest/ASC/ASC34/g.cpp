#include <bits/stdc++.h>
using namespace std;
#define N 13
int p[ 1 << N ];
void djs_init( int _n ){
  for( int i = 0 ; i < _n ; i ++ )
    p[ i ] = i;
}
int f( int x ){
  if( x == -1 ) return -1;
  return p[ x ] == x ? x :
         p[ x ] = f( p[ x ] );
}
void uni( int x , int y ){
  x = f( x );
  y = f( y );
  if( x == y ) return;
  if( x < y ) swap( x , y );
  p[ x ] = y;
}
int n , state[ 1 << N ][ 2 ];
bool ac[ 1 << N ] , bye;
char in[ N + N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i < ( 1 << ( n + 1 ) ) ; i ++ ){
    scanf( "%s" , in );
    //puts( in );
    int len = strlen( in + 1 );
    int now = 0;
    for( int j = 1 ; j <= len ; j ++ )
      now = now * 2 + in[ j ] - '0' + 1;
    if( in[ 0 ] == '+' )
      ac[ now ] = true;
    else
      bye = true;
    if( len < n ){
      state[ now ][ 0 ] = now * 2 + 1;
      state[ now ][ 1 ] = now * 2 + 2;
    }else{
      state[ now ][ 0 ] = -1;
      state[ now ][ 1 ] = -1;
    }
  }
}
int id[ 1 << N ] , who[ 1 << N ];
bool **ok , **tg;
bool OK( int ii , int jj ){
  if( tg[ ii ][ jj ] ) return ok[ ii ][ jj ];
  tg[ ii ][ jj ] = true;
  ok[ ii ][ jj ] = true;
  if( ac[ who[ ii ] ] != ac[ who[ jj ] ] )
    return ok[ ii ][ jj ] = false;
  for( int i = 0 ; i < 2 ; i ++ ){
    int a1 = state[ f( who[ ii ] ) ][ i ];
    int a2 = state[ f( who[ jj ] ) ][ i ];
    if( a1 == -1 || a2 == -1 ) continue;
    if( !OK( id[ f( a1 ) ] , id[ f( a2 ) ] ) )
      return ok[ ii ][ jj ] = false;
  }
  uni( who[ ii ] , who[ jj ] );
  return ok[ ii ][ jj ] = true;
}
void solve(){
  if( !bye ){
    puts( "1 1" );
    puts( "1 1" );
    puts( "1 1" );
    exit( 0 );
  }
  int all = ( 1 << ( n + 1 ) ) - 1;
  djs_init( all );
  for( int i = n ; i > 0 ; i -- ){
    int lft = ( 1 << i ) - 1;
    int rgt = ( 1 << ( i + 1 ) ) - 2;
    if( i == n ){
      int pac = -1 , pnac = -1;
      for( int j = lft ; j <= rgt ; j ++ )
        if( ac[ j ] ){
          if( pac != -1 ) uni( pac , j );
          pac = j;
        }else{
          if( pnac != -1 ) uni( pnac , j );
          pnac = j;
        }
      continue;
    }
    vector< pair< pair<int,int> , int > > vv[ 2 ];
    for( int j = lft ; j <= rgt ; j ++ )
      vv[ ac[ j ] ].push_back( { { f( state[ j ][ 0 ] ) ,
                                   f( state[ j ][ 1 ] ) } , j } );
    for( int _ = 0 ; _ < 2 ; _ ++ ){
      sort( vv[ _ ].begin() , vv[ _ ].end() );
      for( size_t l = 0 , r = 0 ; l < vv[ _ ].size() ; l = r ){
        while( r < vv[ _ ].size() && vv[ _ ][ l ].first == vv[ _ ][ r ].first )
          r ++;
        for( size_t j = l + 1 ; j < r ; j ++ )
          uni( vv[ _ ][ j - 1 ].second , vv[ _ ][ j ].second );
      }
    }
  }
  int iid = 0;
  for( int i = 0 ; i < all ; i ++ )
    if( i == f( i ) ){
      id[ i ] = iid;
      who[ iid ] = i;
      iid ++;
      //printf( "%d : %d %d\n" , i , f( state[ i ][ 0 ] ) , f( state[ i ][ 1 ] ) );
    }
  ok = new bool*[ iid ];
  tg = new bool*[ iid ];
  for( int i = 0 ; i < iid ; i ++ ){
    ok[ i ] = new bool[ iid ];
    tg[ i ] = new bool[ iid ];
    for( int j = 0 ; j < iid ; j ++ )
      tg[ i ][ j ] = false;
  }
  for( int i = 0 ; i < iid ; i ++ ){
    if( who[ i ] != f( who[ i ]  ) )
      continue;
    for( int j = 0 ; j < i ; j ++ )
      ok[ i ][ j ] = OK( i , j );
  }
  //for( int i = 0 ; i < iid ; i ++ )
    //for( int j = i + 1 ; j < iid ; j ++ ){
      //ok[ i ][ j ] = OK( i , j );
      ////printf( "%d %d %d\n" , i , j , ok[ i ][ j ] );
    //}
  //for( int i = 0 ; i < iid ; i ++ )
    //for( int j = i + 1 ; j < iid ; j ++ )
      //if( ok[ i ][ j ] )
        //uni( who[ i ] , who[ j ] );
  iid = 0;
  vector< int > ter;
  for( int i = 0 ; i < all ; i ++ )
    if( i == f( i ) ){
      id[ i ] = ++ iid;
      if( ac[ i ] )
        ter.push_back( id[ i ] );
    }
  printf( "%d %d\n" , iid , id[ f( 0 ) ] );
  printf( "%d" , (int)ter.size() );
  for( auto i : ter ) printf( " %d" , i );
  puts( "" );
  for( int i = 0 ; i < all ; i ++ )
    if( i == f( i ) ){
      int i1 = state[ i ][ 0 ];
      int i2 = state[ i ][ 1 ];
      //printf( "%d -> %d %d\n" , i , i1 , i2 );
      if( i1 == -1 ) i1 = i;
      if( i2 == -1 ) i2 = i;
      printf( "%d %d\n" , id[ f( i1 ) ] , id[ f( i2 ) ] );
    }
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "learning.in" , "r" , stdin );
  freopen( "learning.out" , "w" , stdout );
#endif
  init();
  solve();
}
