#include<bits/stdc++.h>
using namespace std;
#define N 10101
int n , l[ N ];
void init(){
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%d" , &l[ i ] );
  sort( l , l + n );
  reverse( l , l + n );
}
bool okay( int x ){
  if( l[ 0 ] - l[ 2 ] > x ) return false;
  int lft = l[ 1 ] , rgt = l[ 2 ];
  for( int i = 3 ; i < n ; i ++ ){
    if( lft < rgt ) swap( lft , rgt );
    if( lft - l[ i ] > x ) return false;
    lft = l[ i ];
  }
  if( lft < rgt ) swap( lft , rgt );
  return lft - rgt <= x;
}
void solve(){
  int bl = 0 , br = 100000 , ans = 0;
  while( bl <= br ){
    int mid = ( bl + br ) >> 1;
    if( okay( mid ) ) ans = mid , br = mid - 1;
    else bl = mid + 1;
  }
  printf( "%d\n" , ans );
}
int main(){
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
