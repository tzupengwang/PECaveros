#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10000
#define QLIM 10700
int p[ N + 10 ] , qid;
bool query( int i , int j ){
  assert( ++ qid <= QLIM );
#ifdef TEST
  return p[ i ] < p[ j ];
#else
  printf( "? %d %d\n" , i , j );
  fflush( stdout );
  char buf[ 8 ];
  scanf( "%s" , buf );
  return buf[ 0 ] == '<';
#endif
}
int n , k , ans[ N + 10 ];
void answer(){
  printf( "!" );
  for( int i = 1 ; i <= k ; i ++ )
    printf( " %d" , ans[ i ] );
  puts( "" );
  fflush( stdout );
  exit(0);
}
int rnd[ 20 ][ N ] , rsz[ 20 ] , rt;
int from[ 20 ][ N ];
set<int> cand;
int lst_rnd[ N ] , lst_pos[ N ];
void up( int cur , int pos ){
  if( cur == 0 ) return;
  int fr = from[ cur ][ pos ];
  if( fr + 1 == rsz[ cur - 1 ] ){
    up( cur - 1 , fr );
    return;
  }
  if( rnd[ cur ][ pos ] == rnd[ cur - 1 ][ fr ] ){
    cand.insert( rnd[ cur - 1 ][ fr + 1 ] );
    up( cur - 1 , fr );
  }else{
    cand.insert( rnd[ cur - 1 ][ fr ] );
    up( cur - 1 , fr + 1 );
  }
}
void solve(){
  for( int i = 1 ; i <= n ; i ++ )
    rnd[ rt ][ rsz[ rt ] ++ ] = i;

  while( true ){
    for( int i = 0 ; i < rsz[ rt ] ; i ++ ){
      int who = rnd[ rt ][ i ];
      lst_rnd[ who ] = rt;
      lst_pos[ who ] = i;
    }
    if( rsz[ rt ] <= 1 ) break;
    int nrt = rt + 1;
    for( int i = 0 ; i + 1 < rsz[ rt ] ; i += 2 )
      if( query( rnd[ rt ][ i ] , rnd[ rt ][ i + 1 ] ) ){
        from[ nrt ][ rsz[ nrt ] ] = i;
        rnd[ nrt ][ rsz[ nrt ] ++ ] = rnd[ rt ][ i ];
      }else{
        from[ nrt ][ rsz[ nrt ] ] = i;
        rnd[ nrt ][ rsz[ nrt ] ++ ] = rnd[ rt ][ i + 1 ];
      }
    if( rsz[ rt ] & 1 ){
      from[ nrt ][ rsz[ nrt ] ] = rsz[ rt ] - 1;
      rnd[ nrt ][ rsz[ nrt ] ++ ] = rnd[ rt ][ rsz[ rt ] - 1 ];
    }

    rt = nrt;
  }
  ans[ 1 ] = rnd[ rt ][ 0 ];
  up( rt , 0 );
  for( int i = 2 ; i <= k ; i ++ ){
    for( int j = 1 ; j < i ; j ++ )
      cand.erase( ans[ j ] );
    vector<int> vv;
    for( auto j : cand )
      vv.push_back( j );
    int bst = vv[ 0 ];
    for( size_t j = 1 ; j < vv.size() ; j ++ )
      if( query( vv[ j ] , bst ) )
        bst = vv[ j ];
    ans[ i ] = bst;
    up( lst_rnd[ bst ] , lst_pos[ bst ] );
  }

  answer();
}
int pa[ N ];
int main(){
#ifdef TEST
  srand( 1021 );
  n = 10000;
  k = 10;
  for( int i = 1 ; i <= n ; i ++ )
    p[ i ] = i;
  random_shuffle( p + 1 , p + n + 1 );
  for( int i = 1 ; i <= n ; i ++ )
    pa[ p[ i ] ] = i;
  printf( "$" );
  for( int i = 1 ; i <= k ; i ++ )
    printf( " %d" , pa[ i ] );
  puts( "" );
#else
  scanf( "%d%d" , &n , &k );
#endif

  solve();
}
