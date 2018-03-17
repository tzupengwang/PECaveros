#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int read(){
  char buf[ 64 ];
  scanf( "%s" , buf );
  int ret = 0;
  for( int i = 0 ; buf[ i ] ; i ++ )
    ret |= (1 << (buf[ i ] - 'A'));
  return ret;
}
#define N 25
int n , ans[ N ][ N ];
vector<int> v[ N ] , cv[ N ];
vector< pair<int,int> > rv[ N ];
int main(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    int ki; scanf( "%d" , &ki );
    v[ i ].resize( ki );
    cv[ i ].resize( ki );
    for( int j = 0 ; j < ki ; j ++ ){
      v[ i ][ j ] = read();
      for( int u = 0 ; u < n ; u ++ )
        if( (v[ i ][ j ] >> u) & 1 )
          rv[ u ].push_back( {i, j} );
    }
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      ans[ i ][ j ] = -1;
  for( int ed = 0 ; ed < n ; ed ++ ){
    ans[ ed ][ ed ] = 0;
    for( int i = 0 ; i < n ; i ++ )
      for( size_t j = 0 ; j < v[ i ].size() ; j ++ )
        cv[ i ][ j ] = v[ i ][ j ];
    queue<int> Q;
    Q.push( ed );
    while( Q.size() ){
      int tn = Q.front(); Q.pop();
      for( auto tp : rv[ tn ] ){
        int ii = tp.first;
        int jj = tp.second;
        if( ans[ ii ][ ed ] != -1 )
          continue;
        cv[ ii ][ jj ] &= ~(1 << tn);
        if( cv[ ii ][ jj ] == 0 ){
          Q.push( ii );
          ans[ ii ][ ed ] = ans[ tn ][ ed ] + 1;
        }
      }
    }
  }
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      printf( "%d%c" , ans[ i ][ j ] , " \n"[ j + 1 == n ] );
}
