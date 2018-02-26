#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 111
int n;
bool isleaf[ N ];
bitset<N> leafs[ N ];
vector<int> l , m;
vector<int> v[ N ];
int cnt[ N ] , ord[ N ];
bool cmp( int id1 , int id2 ){
  return cnt[ id1 ] < cnt[ id2 ];
}
int prt[ N ];
void go( int now , int pp ){
  prt[ now ] = pp;
  for( int son : v[ now ] ){
    if( son == pp ) continue;
    go( son , now );
  }
}
int main(){
  scanf( "%d" , &n );
  if( n == 2 ){
    puts( "! 1" );
    fflush( stdout );
    exit(0);
  }
  for( int i = 1 ; i <= n ; i ++ ){
    printf( "? %d" , n - 1 );
    for( int j = 1 ; j <= n ; j ++ ){
      if( i == j ) continue;
      printf( " %d" , j );
    }
    puts( "" );
    fflush( stdout );
    int ret; scanf( "%d" , &ret );
    if( ret == n - 1 )
      isleaf[ i ] = true;
    if( isleaf[ i ] )
      l.push_back( i );
    else
      m.push_back( i );
  }
  int root = l.back();
  l.pop_back();
  for( int x : m ){
    for( int cand : l ){
      printf( "? 3 %d %d %d\n" , x , cand , root );
      fflush( stdout );
      int ret; scanf( "%d" , &ret );
      if( ret == 3 )
        leafs[ x ][ cand ] = true;
    }
  }
  for( int cand : l ){
    leafs[ root ][ cand ] = true;
    leafs[ cand ][ cand ] = true;
  }
  leafs[ root ][ root ] = true;
  for( int i = 1 ; i <= n ; i ++ )
    cnt[ i ] = leafs[ i ].count();
  for( int i = 1 ; i <= n ; i ++ )
    ord[ i ] = i;
  sort( ord + 1 , ord + n + 1 , cmp );
  for( int _ = 1 ; _ < n ; _ ++ ){
    int i = ord[ _ ];
    for( int _2 = _ + 1 ; _2 <= n ; _2 ++ ){
      int j = ord[ _2 ];
      if( (leafs[ j ] & leafs[ i ]) == leafs[ i ] ){
        v[ i ].push_back( j );
        v[ j ].push_back( i );
        break;
      }
    }
  }
  go( 1 , 1 );
  printf( "!" );
  for( int i = 2 ; i <= n ; i ++ )
    printf( " %d" , prt[ i ] );
  puts( "" );
  fflush( stdout );
}
