#include <bits/stdc++.h>
using namespace std;
#define N 101010
int n , m , c[ N ];
vector< pair<int,int> > v[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= n ; i ++ )
    scanf( "%d" , &c[ i ] );
  while( m -- ){
    int ai , bi , ci;
    scanf( "%d%d%d" , &ai , &bi , &ci );
    v[ bi ].push_back( { ci , ai } );
    v[ ci ].push_back( { bi , ai } );
  }
}
void solve(){
  priority_queue< pair<int,int> , vector< pair<int,int> > ,
                                  greater< pair<int,int> > > heap;
  for( int i = 1 ; i <= n ; i ++ )
    heap.push( { c[ i ] , i } );
  while( heap.size() ){
    pair<int,int> tp = heap.top(); heap.pop();
    int cst = tp.first;
    int who = tp.second;
    if( c[ who ] != cst ) continue;
    for( pair<int,int> pp : v[ who ] )
      if( c[ who ] + c[ pp.first ] < c[ pp.second ] ){
        c[ pp.second ] = c[ who ] + c[ pp.first ];
        heap.push( { c[ pp.second ] , pp.second } );
      }
  }
  printf( "%d\n" , c[ 1 ] );
}
int main(){
  freopen( "dwarf.in" , "r" , stdin );
  freopen( "dwarf.out" , "w" , stdout );
  init();
  solve();
}
