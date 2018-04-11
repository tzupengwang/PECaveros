#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N (1 << 20)
vector<int> clr[ N ];
vector<int> ch[ N ];
vector<int> sw[ N ];
size_t ptr[ N ];
int n , c , a[ N ];
LL ans;
LL after , ac;
LL before , bc;
void init(){
  scanf( "%d%d" , &n , &c );
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &a[ i ] );
    clr[ a[ i ] ].push_back( i );
  }
  for( int i = 1 ; i <= c ; i ++ ){
    for( int x : clr[ i ] )
      ch[ x ].push_back( i );
    for( size_t j = 1 ; j < clr[ i ].size() ; j ++ )
      sw[ (clr[ i ][ j ] + clr[ i ][ j - 1 ]) >> 1 ].push_back( i );
  }
}
void solve(){
  for( int i = 1 ; i <= c ; i ++ ){
    after ++;
    ac += clr[ i ][ 0 ];
  }
  ans = (ac - (LL)c * 1);
  for( int i = 1 ; i < n ; i ++ ){
    for( auto tclr : ch[ i ] ){
      after --;
      ac -= clr[ tclr ][ ptr[ tclr ] ];
      before ++;
      bc += clr[ tclr ][ ptr[ tclr ] ];
    }
    for( auto tclr : sw[ i ] ){
      before --;
      bc -= clr[ tclr ][ ptr[ tclr ] ];
      ptr[ tclr ] ++;
      after ++;
      ac += clr[ tclr ][ ptr[ tclr ] ];
    }
    LL tans = (ac - after * (i + 1)) +
              (before * (i + 1) - bc);
    ans = min( ans , tans );
  }
  LL aq = c;
  LL g = __gcd( ans , aq );
  ans /= g;
  aq /= g;
  printf( "%lld/%lld\n" , ans , aq );
}
int main(){
  init();
  solve();
}
