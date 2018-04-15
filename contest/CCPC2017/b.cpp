#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
int l , n , m;
LL w[ N ] , d[ N ];
void init(){
  scanf( "%d%d%d" , &l , &n , &m );
  for( int i = 0 ; i < n ; i ++ )
    scanf( "%lld" , &w[ i ] );
  for( int i = 0 ; i < m ; i ++ )
    scanf( "%lld" , &d[ i ] );
}
vector<LL> washed , dried;
int cs;
void solve(){
  washed.clear();
  dried.clear();
  {
    priority_queue< pair<LL,LL> ,
            vector< pair<LL,LL> > ,
           greater< pair<LL,LL> > > heap;
    for( int i = 0 ; i < n ; i ++ )
      heap.push( { w[ i ] , w[ i ] } );
    for( int i = 0 ; i < l ; i ++ ){
      pair<LL,LL> tp = heap.top(); heap.pop();
      washed.push_back( tp.first );
      heap.push( {tp.first + tp.second , tp.second} );
    }
  }
  {
    priority_queue< pair<LL,LL> > heap;
    for( int i = 0 ; i < m ; i ++ )
      heap.push( {-d[ i ] , d[ i ]} );
    for( int i = 0 ; i < l ; i ++ ){
      pair<LL,LL> tp = heap.top(); heap.pop();
      dried.push_back( tp.first );
      heap.push( {tp.first - tp.second , tp.second} );
    }
    reverse( dried.begin() , dried.end() );
  }
  LL ans = 0;
  for( int i = 0 ; i < l ; i ++ )
    ans = max( ans , washed[ i ] - dried[ i ] );
  printf( "Case #%d: %lld\n" , ++ cs , ans );
}
int main(){
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
