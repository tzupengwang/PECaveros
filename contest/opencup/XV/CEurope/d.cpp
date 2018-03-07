#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 2020202
int n , c[ N ];
LL ans;
LL C2( LL x ){
  return x * (x - 1);
}
int main(){
  scanf( "%d" , &n );
  for( int i = 0 , x ; i < n ; i ++ ){
    scanf( "%d" , &x );
    c[ x ] ++;
  }
  for( int i = 1 ; i < N ; i ++ ){
    ans += C2( c[ i ] );
    for( int j = i + i ; j < N ; j += i )
      ans += (LL)c[ i ] * c[ j ];
  }
  printf( "%lld\n" , ans );
}
