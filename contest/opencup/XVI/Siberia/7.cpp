#include <bits/stdc++.h>
using namespace std;
#define N 10210
const int bs = N;
int n , m , c , vt[ N ];
vector<int> v[ N ];
void init(){
  scanf( "%d%d%d" , &n , &m , &c );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &vt[ i ] );
  for( int i = 1 ; i <= m ; i ++ ){
    int ki; scanf( "%d" , &ki ); while( ki -- ){
      int ai; scanf( "%d" , &ai );
      if( ai < 0 ) ai = bs + ai;
      v[ bs - i ].push_back( ai );
    }
  }
}
int dp[ N ][ 4 ];
int dp_fr[ N ][ 4 ];
int id[ 22 ][ 22 ][ 22 ];
#define X 2222
int aa[ X ];
int bb[ X ];
int cc[ X ];
int tdp[ X ];
void go( int now ){
  if( now <= n ){
    for( int i = 0 ; i <= c ; i ++ )
      dp[ now ][ i ] = ( i != vt[ now ] );
    return;
  }
  for( auto son : v[ now ] )
    go( son );
  for( int i = 0 ; i < X ; i ++ )
    tdp[ i ] = N;
  tdp[ id[ 0 ][ 0 ][ 0 ] ] = 0;
  for( auto son : v[ now ] ){
    for( int i = X - 1 ; i >= 0 ; i -- ){
      int bst = tdp[ i ] + dp[ son ][ 0 ];
      if( aa[ i ] )
        bst = min( bst , tdp[ id[ aa[ i ] - 1 ][ bb[ i ] ][ cc[ i ] ] ] + dp[ son ][ 1 ] );
      if( bb[ i ] )
        bst = min( bst , tdp[ id[ aa[ i ] ][ bb[ i ] - 1 ][ cc[ i ] ] ] + dp[ son ][ 2 ] );
      if( cc[ i ] and c == 3 )
        bst = min( bst , tdp[ id[ aa[ i ] ][ bb[ i ] ][ cc[ i ] - 1 ] ] + dp[ son ][ 3 ] );
      tdp[ i ] = bst;
    }
  }
  for( int i = 0 ; i <= c ; i ++ )
    dp[ now ][ i ] = N;
  for( int i = 0 ; i < X ; i ++ ){
    int ret = tdp[ id[ aa[ i ] ][ bb[ i ] ][ cc[ i ] ] ];
    if( cc[ i ] > 0 and c < 3 ) continue;
    int mst = max( aa[ i ] , max( bb[ i ] , cc[ i ] ) );
    int to = 0;
    if( mst == aa[ i ] and mst > bb[ i ] and mst > cc[ i ] ) to = 1;
    if( mst == bb[ i ] and mst > aa[ i ] and mst > cc[ i ] ) to = 2;
    if( mst == cc[ i ] and mst > aa[ i ] and mst > bb[ i ] ) to = 3;
    if( ret < dp[ now ][ to ] ){
      dp[ now ][ to ] = ret;
      dp_fr[ now ][ to ] = i;
    }
  }
}
int ttdp[ 22 ][ X ];
int fr[ 22 ][ X ];
int nd[ 22 ][ X ];
void find_ans( int now , int req ){
  if( now <= n ){
    if( req != vt[ now ] )
      printf( "%d %d\n" , now , req );
    return;
  }
  req = dp_fr[ now ][ req ];
  int deg = (int)v[ now ].size();
  for( int i = 0 ; i <= deg ; i ++ )
    for( int j = 0 ; j < X ; j ++ )
      ttdp[ i ][ j ] = N;
  ttdp[ 0 ][ id[0][0][0] ] = 0;
  for( size_t j = 0 ; j < v[ now ].size() ; j ++ ){
    int son = v[ now ][ j ];
    for( int i = X - 1 ; i >= 0 ; i -- ){
      int bst = ttdp[ j ][ i ] + dp[ son ][ 0 ] , tnd = 0;
      int tfr = i;
      if( aa[ i ] ){
        if( ttdp[ j ][ id[ aa[ i ] - 1 ][ bb[ i ] ][ cc[ i ] ] ] + dp[ son ][ 1 ] < bst ){
          bst = ttdp[ j ][ id[ aa[ i ] - 1 ][ bb[ i ] ][ cc[ i ] ] ] + dp[ son ][ 1 ];
          tnd = 1;
          tfr = id[ aa[ i ] - 1 ][ bb[ i ] ][ cc[ i ] ];
        }
      }
      if( bb[ i ] ){
        if( ttdp[ j ][ id[ aa[ i ] ][ bb[ i ] - 1 ][ cc[ i ] ] ] + dp[ son ][ 2 ] < bst ){
          bst = ttdp[ j ][ id[ aa[ i ] ][ bb[ i ] - 1 ][ cc[ i ] ] ] + dp[ son ][ 2 ];
          tnd = 2;
          tfr = id[ aa[ i ] ][ bb[ i ] - 1 ][ cc[ i ] ];
        }
      }
      if( cc[ i ] and c == 3 ){
        if( ttdp[ j ][ id[ aa[ i ] ][ bb[ i ] ][ cc[ i ] - 1 ] ] + dp[ son ][ 3 ] < bst ){
          bst = ttdp[ j ][ id[ aa[ i ] ][ bb[ i ] ][ cc[ i ] - 1 ] ] + dp[ son ][ 3 ];
          tnd = 3;
          tfr = id[ aa[ i ] ][ bb[ i ] ][ cc[ i ] - 1 ];
        }
      }
      ttdp[ j + 1 ][ i ] = bst;
      nd[ j + 1 ][ i ] = tnd;
      fr[ j + 1 ][ i ] = tfr;
    }
  }
  vector<int> nnd;
  for( int i = deg ; i >= 1 ; i -- ){
    nnd.push_back( nd[ i ][ req ] );
    req = fr[ i ][ req ];
  }
  reverse( nnd.begin() , nnd.end() );
  for( size_t i = 0 ; i < v[ now ].size() ; i ++ )
    find_ans( v[ now ][ i ] , nnd[ i ] );
}
void solve(){
  int tid = 0;
  for( int id1 = 0 ; id1 <= 20 ; id1 ++ )
    for( int id2 = 0 ; id2 <= 20 ; id2 ++ )
      for( int id3 = 0 ; id3 <= 20 ; id3 ++ )
        if( id1 + id2 + id3 <= 20 ){
          id[ id1 ][ id2 ][ id3 ] = tid;
          aa[ tid ] = id1;
          bb[ tid ] = id2;
          cc[ tid ] = id3;
          tid ++;
        }
  go( bs - 1 );
  printf( "%d\n" , dp[ bs - 1 ][ 1 ] );
  find_ans( bs - 1 , 1 );
}
int main(){
#ifndef LOCAL
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  init();
  solve();
}
