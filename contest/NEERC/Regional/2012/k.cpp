#include <bits/stdc++.h>
using namespace std;
#define N 100010
#define FI first
#define SE second
#define PB push_back
typedef pair<int,int> PII;
int n , deg[ N ] , p[ N ] , d[ N ] , dno[ N ];
vector<int> v[ N ];
priority_queue< PII > heap;
void init(){
  freopen( "kingdom.in" , "r" , stdin );
  freopen( "kingdom.out" , "w" , stdout );
  scanf( "%d" , &n );
  for( int i = 1 ; i < n ; i ++ ){
    int ti , tj;
    scanf( "%d%d" , &ti , &tj );
    v[ ti ].PB( tj );
    v[ tj ].PB( ti );
  }
}
void DFS( int now , int prt = -1 ){
  p[ now ] = prt;
  d[ now ] = 1; dno[ now ] = now;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( v[ now ][ i ] != prt ){
      DFS( v[ now ][ i ] , now );
      if( d[ v[ now ][ i ] ] + 1 > d[ now ] ){
        d[ now ] = d[ v[ now ][ i ] ] + 1;
        dno[ now ] = dno[ v[ now ][ i ] ];
      }
    }
}
bool in[ N ];
void Push( int x ){
  while( p[ x ] != -1 ){
    int px = p[ x ];
    if( in[ px ] ) break;
    for( int i = 0 ; i < (int)v[ px ].size() ; i ++ )
      if( v[ px ][ i ] != x && v[ px ][ i ] != p[ px ] ){
        int son = v[ px ][ i ];
        heap.push( make_pair( d[ son ] , dno[ son ] ) );
      }
    in[ px ] = true;
    in[ x ] = true;
    x = p[ x ];
  }
}
vector<PII> ans;
void build_p(){
  DFS( 1 );
  for( int i = 0 ; i < (int)v[ 1 ].size() ; i ++ )
    heap.push( make_pair( d[ v[ 1 ][ i ] ] , dno[ v[ 1 ][ i ] ] ) );
  in[ 1 ] = true;
}
void solve(){
  build_p();
  while( heap.size() ){
    if( heap.size() == 1 ){
      PII tp = heap.top(); heap.pop();
      ans.push_back( make_pair( 1 , tp.SE ) );
      Push( tp.SE );
    }else{
      PII tp1 = heap.top(); heap.pop();
      PII tp2 = heap.top(); heap.pop();
      ans.push_back( make_pair( tp1.SE , tp2.SE ) );
      Push( tp1.SE );
      Push( tp2.SE );
    }
  }
  printf( "%d\n" , (int)ans.size() );
  for( int i = 0 ; i < (int)ans.size() ; i ++ )
    printf( "%d %d\n" , ans[ i ].FI , ans[ i ].SE );
}
int main(){
  init();
  solve();
}
