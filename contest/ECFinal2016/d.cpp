#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 303030
int n , k;
LL a[ N ];
void init(){
  scanf( "%d%d" , &n , &k );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &a[ i ] );
  sort( a , a + n );
}
int vl[ N ];
bool okay( int goal ){
  for( int i = 0 ; i < goal ; i ++ )
    vl[ i ] = i;
  int ptr = goal;
  for( int _ = 1 ; _ < k ; _ ++ )
    for( int i = 0 ; i < goal ; i ++ ){
      int cur = vl[ i ];
      while( ptr < n and a[ ptr ] < a[ cur ] + a[ cur ] )
        ptr ++;
      if( ptr == n )
        return false;
      vl[ i ] = ptr ++;
    }
  return true;
}
int _cs;
void solve(){
  int bl = 1 , br = n / k , ba = 0;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( okay( bmid ) )
      ba = bmid , bl = bmid + 1;
    else
      br = bmid - 1;
  }
  printf( "Case #%d: %d\n" , ++ _cs , ba );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
