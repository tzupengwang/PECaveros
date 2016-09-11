#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
LL n , k , t[ N ];
vector< LL > v;
inline void cal(){
  for( int i = 0 ; i < n ; i ++ )
    if( i != k )
      v.push_back( t[ i ] );
  sort( v.begin() , v.end() );
  reverse( v.begin() , v.end() );
  v.push_back( t[ k ] );
  int ans = 0 , pen = 0 , now = 0;
  reverse( v.begin() , v.end() );
  for( LL i : v ){
    now += i;
    if( now > 300 ) break;
    ans += 1;
    pen += now;
  }
  printf( "%d %d\n" , ans , pen );
}
int main(){
  scanf( "%lld%lld" , &n , &k );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &t[ i ] );
  cal();
}
