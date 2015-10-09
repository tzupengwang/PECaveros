#include <bits/stdc++.h>
using namespace std;
#define N 10010
vector<int> pset;
bool p[ N ];
void build(){
  for( int i = 2 ; i < N ; i ++ ) if( !p[ i ] ){
    pset.push_back( i );
    for( int j = N / i ; j >= i ; j -- )
      p[ i * j ] = true;
  }
}
int n , ans;
void solve(){
  int pn = (int)pset.size() - 1;
  while( pset[ pn ] > n ) pn --;
  int l = 0;
  while( l <= pn ){
    int now = pset[ pn ];
    while( l < pn && now * pset[ l ] <= n )
      now *= pset[ l ++ ];
    ans ++;
    pn --;
  }
  cout << ans << endl;
}
int main(){
  build();
  freopen( "gcd.in" , "r" , stdin );
  freopen( "gcd.out" , "w" , stdout );
  scanf( "%d" , &n );
  solve();
}
