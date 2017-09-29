#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
int n , m , k , lst[ N ] , a[ N ] , sz[ N ];
LL ans;
bool ok[ N ];
int bst;
int main(){
  scanf( "%d%d%d" , &n , &m , &k );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &a[ i ] );
    lst[ a[ i ] ] = i;
    sz[ a[ i ] ] ++;
  }
  ans = -1;
  ok[ 0 ] = true;
  for( int i = 1 ; i <= n ; i ++ ){
    if( lst[ a[ i ] ] == i ){
      int cursz = sz[ a[ i ] ];
      for( int j = k ; j >= cursz ; j -- )
        if( ok[ j - cursz ] ){
          ok[ j ] = true;
          bst = max( bst , j );
        }
    }
    if( bst <= k and n - bst <= k ){
      LL tans = (LL)bst * ( i - n ) + (LL)n * n;
      //cout << i << " " << tans << endl;
      if( ans == -1 or tans < ans )
        ans = tans;
    }
  }
  printf( "%lld\n" , ans );
}
