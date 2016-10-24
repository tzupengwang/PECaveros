#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
#define N 202020
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;
int n , q , a[ N ] , ans[ N ];
vector< pair< int , pair<int,int> > > qry;
void init(){
  scanf( "%d" , &n );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &a[ i ] );
  scanf( "%d" , &q );
  for( int i = 0 ; i < q ; i ++ ){
    int ii , pp; scanf( "%d%d" , &ii , &pp );
    qry.push_back( { ii , { pp , i } } );
  }
  sort( qry.begin() , qry.end() );
  reverse( qry.begin() , qry.end() );
}
map< int , int > pre;
void solve(){
  size_t ptr = 0;
  set_t s;
  for( int i = n ; i >= 1 ; i -- ){
    if( pre.count( a[ i ] ) ) s.erase( pre[ a[ i ] ] );
    pre[ a[ i ] ] = i;
    s.insert( i );
    while( ptr < qry.size() && qry[ ptr ].first == i ){
      int who = a[ i + qry[ ptr ].second.first - 1 ];
      ans[ qry[ ptr ].second.second ] = 1 + s.order_of_key( pre[ who ] );
      ptr ++;
    }
  }
  for( int i = 0 ; i < q ; i ++ )
    printf( "%d\n" , ans[ i ] );
}
int main(){
  freopen( "data.in" , "r" , stdin );
  freopen( "data.out" , "w" , stdout );
  init();
  solve();
}
