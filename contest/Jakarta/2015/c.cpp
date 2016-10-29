#include <bits/stdc++.h>
using namespace std;
#define N 101010
typedef long long LL;
LL n , q , a[ N ] , b[ N ] , mcnt;
map< LL , LL > M;
vector< LL > v[ N ];
vector< pair<LL,LL> > qry[ N ];
void init(){
  assert( scanf( "%lld%lld" , &n , &q ) == 2 );
  assert( 1 <= n && n <= 100000 );
  assert( 1 <= q && q <= 100000 );
  mcnt = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%lld" , &a[ i ] );
    assert( 1 <= a[ i ] && a[ i ] <= 1000000000 );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%lld" , &b[ i ] );
    assert( 1 <= b[ i ] && b[ i ] <= n );
  }
}
LL _cs , ans[ N ];
void gogo(){
  for( auto i : M ){
    LL idx = i.second;
    LL rrr = -1 , pans = -1;
    sort( qry[ idx ].begin() , qry[ idx ].end() );
    for( auto qq : qry[ idx ] ){
      if( qq.first == rrr ){
        ans[ qq.second ] = pans;
        continue;
      }
      LL yy = qq.first;
      LL tans = 0 , st = 0 , pre = 0;
      while( st < (int)v[ idx ].size() ){
        LL bl = st + yy - 1 , br = (int)v[ idx ].size() - 1 , ba = -1;
        while( bl <= br ){
          LL mid = ( bl + br ) >> 1;
          if( v[ idx ][ mid ] - pre >= b[ yy ] ){
            ba = mid , br = mid - 1;
          }else
            bl = mid + 1;
        }
        if( ba == -1 ) break;
        tans ++; st = ba + 1;
        pre = v[ idx ][ ba ];
      }
      if( pre != n ) tans ++;
      rrr = qq.first;
      pans = tans;
      ans[ qq.second ] = tans;
    }
  }
}
void solve(){
  M.clear();
  for( int i = 1 ; i <= n ; i ++ ){
    if( M.count( a[ i ] ) == 0 ) M[ a[ i ] ] = mcnt ++;
    v[ M[ a[ i ] ] ].push_back( i );
  }
  for( int i = 1 ; i <= q ; i ++ ){
    LL xi , yi; scanf( "%lld%lld" , &xi , &yi );
    assert( 1 <= xi && xi <= 1000000000 );
    assert( 1 <= yi && yi <= n );
    if( M.count( xi ) == 0 ){
      ans[ i ] = 1;
      continue;
    }
    qry[ M[ xi ] ].push_back( { yi , i } );
  }
  gogo();
  printf( "Case #%lld:\n" , ++ _cs );
  for( int i = 1 ; i <= q ; i ++ )
    printf( "%lld\n" , ans[ i ] );
  for( int i = 0 ; i < mcnt ; i ++ ){
    v[ i ].clear();
    qry[ i ].clear();
  }
}
int main(){
  int _; scanf( "%d" , &_ );
  assert( _ <= 20 );
  while( _ -- ){
    init();
    solve();
  }
}
