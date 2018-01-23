#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 101010
int n , m , ind[ N ] , outd[ N ];
vector<int> v[ N ];
void init(){
  scanf( "%d%d" , &n , &m );
  while( m -- ){
    int ui , vi;
    scanf( "%d%d" , &ui , &vi );
    v[ ui ].push_back( vi );
    ind[ vi ] ++;
    outd[ ui ] ++;
  }
}
void no(){
  puts( "There is no route, Karl!" );
  exit(0);
}
map< pair<int,int> , int > ID;
int mid;
inline int id( int ui , int vi ){
  auto it = ID.find( { ui , vi } );
  if( it != ID.end() ) return it->second;
  return ID[ { ui , vi } ] = mid ++;
}
vector<int> wt[ N ];
vector<int> g[ N ];
bool gg[ N ] , got_e[ N ];
int cand[ N ] , ct , stk[ N ];
void go( int st , int now , int dep ){
  stk[ dep ] = now;
  if( dep and !gg[ now ] ){
    if( st == now ){
      if( 1 < dep )
        no();
      return;
    }
    int nid = id( st , now );
    if( not got_e[ nid ] ){
      got_e[ nid ] = true;
      g[ st ].push_back( now );
    }
    if( wt[ nid ].empty() ){
      for( int i = 1 ; i < dep ; i ++ )
        wt[ nid ].push_back( stk[ i ] );
    }else if( 1 < dep )
      no();
    return;
  }
  for( int nxt : v[ now ] )
    go( st , nxt , dep + 1 );
}
bool vst[ N ];
vector<int> ans;
void link( int st , int ed ){
  int nid = id( st , ed );
  for( auto i : wt[ nid ] )
    ans.push_back( i );
}
void dfs( int now , int dep ){
  stk[ dep ] = now;
  if( dep + 1 == ct ){
    for( int x : g[ now ] )
      if( x == cand[ 0 ] ){
        stk[ dep + 1 ] = cand[ 0 ];
        for( int i = 0 ; i <= dep ; i ++ ){
          ans.push_back( stk[ i ] );
          link( stk[ i ] , stk[ i + 1 ] ); 
        }
        if( (int)ans.size() != n ){
          ans.clear();
          return;
        }
        int s = -1;
        for( int i = 0 ; i < n ; i ++ )
          if( ans[ i ] == 1 ){
            s = i;
            break;
          }
        if( s == -1 ) no();
        for( int i = 0 ; i < n ; i ++ )
          printf( "%d " , ans[ (s + i) % n ] );
        puts( "1" );
        exit(0);
      }
    return;
  }
  for( int nxt : g[ now ] ){
    if( vst[ nxt ] ) continue;
    vst[ nxt ] = true;
    dfs( nxt , dep + 1 );
    vst[ nxt ] = false;
  }
}
void solve(){
  int other = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    if( !ind[ i ] or !outd[ i ] )
      no();
    if( ind[ i ] == 1 and outd[ i ] == 1 )
      gg[ i ] = true;
    else
      other ++;
  }
  if( other == 0 ){
    int st = 1;
    while( gg[ st ] ){
      gg[ st ] = false;
      ans.push_back( st );
      st = v[ st ][ 0 ];
    }
    if( (int)ans.size() < n )
      no();
    for( auto i : ans )
      printf( "%d " , i );
    printf( "%d\n" , ans[ 0 ] );
    exit(0);
  }
  for( int i = 1 ; i <= n ; i ++ ){
    if( gg[ i ] ) continue;
    cand[ ct ++ ] = i;
    go( i , i , 0 );
  }
  vst[ cand[ 0 ] ] = true;
  dfs( cand[ 0 ] , 0 );
}
int main(){
#ifndef EDDY
  freopen( "king.in" , "r" , stdin );
  freopen( "king.out" , "w" , stdout );
#endif
  init();
  solve();
  no();
}
