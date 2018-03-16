#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N (1 << 20)
int n , k , p[ N ] , tk[ N ] , tot;
bool okay( int d ){
  for( int i = 0 ; i < tot ; i ++ )
    tk[ i ] = 0;
  int ptr = 0;
  for( int i = 0 ; i < n ; i ++ ){
    while( ptr + 1 < tot and p[ ptr + 1 ] > p[ ptr ] + d )
      ptr ++;
    if( ptr + 1 >= tot )
      return false;
    tk[ ptr     ] = 1;
    tk[ ptr + 1 ] = 1;
    ptr += 2;
  }
  int res = 0;
  for( int i = tot - 1 ; i >= 0 ; i -- ){
    if( tk[ i ] ){
      if( res < k - 1 )
        return false;
      res -= k - 1;
    }else
      res ++;
  }
  return true;
}
int main(){
  scanf( "%d%d" , &n , &k );
  tot = n * k * 2;
  for( int i = 0 ; i < tot ; i ++ )
    scanf( "%d" , &p[ i ] );
  sort( p , p + tot );
  int bl = 0 , br = 1e9 , ba = 0;
  while( bl <= br ){
    int bmid = (bl + br) >> 1;
    if( okay( bmid ) ) ba = bmid , br = bmid - 1;
    else bl = bmid + 1;
  }
  printf( "%d\n" , ba );
}
