#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL base = 1e6;
inline LL to_sec( LL h , LL m , LL s ){
  return h * base * base + m * base + s;
}
inline LL read(){
  LL h , m , s;
  cin >> h >> m >> s;
  return to_sec( h , m , s );
}
int n;
LL s[ N ];
int main(){
  cin >> n;
  for( int i = 0 ; i < n ; i ++ )
    s[ i ] = read();
  sort( s , s + n );
  LL sum = accumulate( s , s + n , 0LL );
  LL ans = s[ n - 1 ] * n - sum;
  //LL ans = sum - s[ 0 ] * n;
  for( int i = n - 2 ; i >= 0 ; i -- ){
    sum -= base * base * 12;
    ans = min( ans , s[ i ] * n - sum );
  }
  printf( "%lld %lld %lld\n" , (ans / base) / base ,
                               (ans / base) % base , 
                               ans % base );
}
