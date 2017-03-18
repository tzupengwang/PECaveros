#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL n , k , a[ N ];
int main(){
  scanf( "%lld%lld" , &n , &k );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &a[ i ] );
  priority_queue<LL , vector<LL>, greater<LL> > heap;
  LL sum = 0;
  for( int i = 0 ; i < k ; i ++ ){
    sum += a[ i ];
    heap.push( a[ i ] );
  }
  printf( "%lld" , sum );
  for( int i = k ; i < n ; i ++ ){
    sum += a[ i ]; heap.push( a[ i ] );
    sum -= heap.top(); heap.pop();
    printf( " %lld" , sum );
  }
  puts( "" );
}
