#include <bits/stdc++.h>
using namespace std;
#define N 101010
vector< pair<int,int> > v[ N ];
int n , k , l;
bool tag[ N ];
void init(){
  scanf( "%d%d%d" , &n , &k , &l );
  for( int i = 0 ; i < n ; i ++ ){
    int xi; scanf( "%d" , &xi );
    if( tag[ xi ] ){
      puts( "0" );
      exit( 0 );
    }
    tag[ xi ] = true;
  }
  for( int i = 0 ; i < l ; i ++ ){
    int ai , bi , ci;
    scanf( "%d%d%d" , &ai , &bi , &ci );
    v[ ai ].push_back( { bi , ci } );
    v[ bi ].push_back( { ai , ci } );
  }
}
typedef pair<int,int> PII;
typedef pair<PII,int> data;
priority_queue< data , vector<data> , greater<data> > heap;
unordered_set<int> s[ N ];
void solve(){
  for( int i = 1 ; i <= k ; i ++ )
    if( tag[ i ] )
      heap.push( { { 0 , i } , i } );
  while( heap.size() ){
    data td = heap.top(); heap.pop();
    int now = td.first.second;
    int dst = td.first.first;
    int from = td.second;
    if( s[ from ].count( now ) ) continue;
    s[ from ].insert( now );
    if( tag[ now ] && now != from ){
      printf( "%d\n" , 3 * dst );
      exit( 0 );
    }
    for( PII nxt : v[ now ] )
      heap.push( { { nxt.second + dst , nxt.first } , from } );
  }
}
int main(){
  init();
  solve();
}
