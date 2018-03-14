#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10101
int query( int i , int j ){
  printf( "? %d %d\n" , i , j );
  fflush( stdout );
  char buf[ 9 ];
  scanf( "%s" , buf );
  return buf[ 0 ] == '<';
}
int n , ord[ N ];
int nxt[ N ] , nsz;
int nxte[ N ];
vector<int> v[ N ];
int arr[ N ] , asz;
void go(){
  for( int _ = 2 ; _ <= n / 2 ; _ ++ ){
    int cur = ord[ _ ];
    {
      asz = 0;
      for( int i = 1 ; i ; i = nxt[ i ] )
        arr[ asz ++ ] = i;
    }
    int bl = 0 , br = asz - 2 , ba = 0;
    while( bl <= br ){
      int bmid = (bl + br) >> 1;
      if( query( cur , v[ arr[ bmid ] ][ 0 ] ) )
        br = bmid - 1;
      else
        ba = bmid , bl = bmid + 1;
    }
    {
      vector<int> lft , rgt;
      for( auto id : v[ arr[ ba ] ] )
        if( query( cur , id ) )
          rgt.push_back( id );
        else
          lft.push_back( id );
      if( not lft.empty() and
          not rgt.empty() ){
        v[ arr[ ba ] ] = lft;
        v[ ++ nsz ] = rgt;
        nxt[ nsz ] = nxt[ arr[ ba ] ];
        nxte[ nsz ] = nxte[ arr[ ba ] ];
        nxt[ arr[ ba ] ] = nsz;
        nxte[ arr[ ba ] ] = cur;
        continue;
      }
    }
    ba ++;
    {
      vector<int> lft , rgt;
      for( auto id : v[ arr[ ba ] ] )
        if( query( cur , id ) )
          rgt.push_back( id );
        else
          lft.push_back( id );
      if( not lft.empty() and
          not rgt.empty() ){
        v[ arr[ ba ] ] = lft;
        v[ ++ nsz ] = rgt;
        nxt[ nsz ] = nxt[ arr[ ba ] ];
        nxte[ nsz ] = nxte[ arr[ ba ] ];
        nxt[ arr[ ba ] ] = nsz;
        nxte[ arr[ ba ] ] = cur;
        continue;
      }
    }
    nxte[ arr[ ba ] ] = cur;
    continue;
  }
}
int ao[ N ] , ae[ N ];
int main(){
  scanf( "%d" , &n );
  if( n == 1 ){
    puts( "! 1" );
    exit(0);
  }
  if( n == 2 ){
    puts( "! 2 1" );
    exit(0);
  }
  for( int i = 1 ; i <= n / 2 ; i ++ )
    ord[ i ] = i;
  random_shuffle( ord + 1 , ord + n / 2 + 1 );
  for( int i = 1 ; i <= (n + 1) / 2 ; i ++ ){
    int ret = query( ord[ 1 ] , i );
    if( ret == 1 )
      v[ 2 ].push_back( i );
    else
      v[ 1 ].push_back( i );
  }
  nxt[ 1 ] = 2;
  nxte[ 1 ] = ord[ 1 ];
  nxt[ 2 ] = 0;
  nsz = 2;
  go();
  for( int i = 1 , ii = 1 ; i ; i = nxt[ i ] , ii += 2 ){
    ao[ v[ i ][ 0 ] ] = ii;
    ae[ nxte[ i ] ] = ii + 1;
  }
  printf( "!" );
  for( int i = 1 ; i <= n / 2 ; i ++ )
    printf( " %d" , ae[ i ] );
  for( int i = 1 ; i <= (n + 1) / 2 ; i ++ )
    printf( " %d" , ao[ i ] );
  puts( "" );
  fflush( stdout );
}
