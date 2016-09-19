#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , sum , cnt;
char c[ N ];
long long ans;
int main(){
  freopen( "energy.in" , "r" , stdin );
  freopen( "energy.out" , "w" , stdout );
  scanf( "%d" , &n );
  scanf( "%s" , c );
  priority_queue< int > heap;
  for( int i = 0 ; c[ i ] ; i ++ ){
    int vl = c[ i ] - '0';
    if( sum + vl <= n ){
      heap.push( vl );
      sum += vl;
      cnt ++;
    }else if( vl == 1 && heap.top() == 2 ){
      heap.pop();
      heap.push( 1 );
      sum --;
    }
    ans += cnt;
  }
  printf( "%lld\n" , ans );
}
