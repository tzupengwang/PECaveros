#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 505050
LL d , n[ 3 ] , a[ 3 ][ N ];
vector<LL> cand;
void init(){
  cand.clear();
  for( int i = 0 ; i < 3 ; i ++ ){
    for( int j = 0 ; j < n[ i ] ; j ++ ){
      scanf( "%lld" , &a[ i ][ j ] );
      cand.push_back( a[ i ][ j ] );
    }
    sort( a[ i ] , a[ i ] + n[ i ] );
  }
  sort( cand.begin() , cand.end() );
  cand.resize( unique( cand.begin() , cand.end() ) - cand.begin() );
}
void solve(){
  int lb[ 3 ] = {} , rb[ 3 ] = {};
  // a[ i ][ rb[ i ] ] > cur
  // a[ i ][ lb[ i ] ] >= cur - d
  LL ans = 0;
  for( LL x : cand ){
    LL eq[ 3 ] = {};
    for( int i = 0 ; i < 3 ; i ++ ){
      while( lb[ i ] < n[ i ] and a[ i ][ lb[ i ] ] < x - d )
        lb[ i ] ++;
      while( rb[ i ] < n[ i ] and a[ i ][ rb[ i ] ] < x )
        rb[ i ] ++;
      while( rb[ i ] < n[ i ] and a[ i ][ rb[ i ] ] == x ){
        eq[ i ] ++;
        rb[ i ] ++;
      }
    }
    LL les[ 3 ] = {};
    for( int i = 0 ; i < 3 ; i ++ )
      les[ i ] = rb[ i ] - lb[ i ] - eq[ i ];
    //cerr << x << endl;
    //for( int i = 0 ; i < 3 ; i ++ )
      //cerr << les[ i ] << " ";
    //cerr << endl;
    //for( int i = 0 ; i < 3 ; i ++ )
      //cerr << eq[ i ] << " ";
    //cerr << endl;
    ans += eq[ 0 ] * (les[ 1 ] + eq[ 1 ]) * (les[ 2 ] + eq[ 2 ]);
    ans += eq[ 1 ] * les[ 0 ] * (les[ 2 ] + eq[ 2 ]);
    ans += eq[ 2 ] * les[ 0 ] * les[ 1 ];
    //cerr << "Ans = " << ans << endl;
  }
  printf( "%lld\n" , ans );
}
int main(){
  while( cin >> d >> n[ 0 ] >> n[ 1 ] >> n[ 2 ] ){
    init();
    solve();
  }
}
