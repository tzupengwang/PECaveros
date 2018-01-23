#include <bits/stdc++.h>
using namespace std;
#define N 111
#define K 101010
typedef long long LL;
LL a[ K ] , n , k;
LL cal(){
  for( int i = 1 ; ; i ++ ){
    for( int j = 0 ; j <= k ; j ++ ){
      a[ j ] += min( a[ j ] , ( n - a[ j ] ) / 2 );
      if( a[ j ] >= n ) return i;
    }
    for( int j = 1 ; j <= k ; j ++ ){
      a[ j ] = max( a[ j ] , a[ j - 1 ] + 1 );
      if( a[ j ] >= n ) return i;
    }
  }
}
int main(){
  cin >> n >> k;
  cout << cal() << endl;
}
