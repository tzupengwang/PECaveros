#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 50505
int n , m , ind[ N ];
int ai[ N ] , bi[ N ] , ci[ N ];
LL dlt[ N ];
vector<int> g[ N ] , rg[ N ];
void init(){
  for( int i = 1 ; i <= n ; i ++ ){
    ind[ i ] = 0;
    g[ i ].clear();
    rg[ i ].clear();
  }
  for( int i = 0 ; i < m ; i ++ ){
    scanf( "%d%d%d" , &ai[ i ] , &bi[ i ] , &ci[ i ] );
    dlt[ i ] = 0;
    ind[ bi[ i ] ] ++;
    g[ ai[ i ] ].push_back( i );
    rg[ bi[ i ] ].push_back( i );
  }
}
LL dst[ N ];
vector<int> topo;
void reduce(){
  for( int _ = 0 ; _ < n ; _ ++ ){
    int i = topo[ _ ];
    set<LL> pd;
    for( int eid : rg[ i ] )
      pd.insert( dlt[ eid ] );
    if( pd.size() == 1u ){
      int vl = *pd.begin();
      for( int eid : rg[ i ] )
        dlt[ eid ] = 0;
      for( int eid : g[ i ] )
        dlt[ eid ] += vl;
    }
  }
}
bool gd[ N ];
bool okay(){
  for( int i = 1 ; i <= n ; i ++ )
    gd[ i ] = false;
  for( int _ = 0 ; _ < n ; _ ++ ){
    int i = topo[ _ ];
    for( int eid : g[ i ] ){
      if( dlt[ eid ] and gd[ i ] )
        return false;
      if( gd[ i ] or dlt[ eid ] )
        gd[ bi[ eid ] ] = true;
    }
  }
  return true;
}
int _cs;
void solve(){
  topo.clear();
  for( int i = 1 ; i <= n ; i ++ )
    if( !ind[ i ] )
      topo.push_back( i );
  for( size_t _ = 0 ; _ < topo.size() ; _ ++ ){
    int i = topo[ _ ];
    for( int eid : g[ i ] ){
      ind[ bi[ eid ] ] --;
      if( ind[ bi[ eid ] ] == 0 )
        topo.push_back( bi[ eid ] );
    }
  }
  for( int _ = n - 1 ; _ >= 0 ; _ -- ){
    int i = topo[ _ ];
    dst[ i ] = 0;
    for( int eid : g[ i ] )
      dst[ i ] = max( dst[ i ] , ci[ eid ] + dst[ bi[ eid ] ] );
    for( int eid : g[ i ] )
      dlt[ eid ] = dst[ i ] - (ci[ eid ] + dst[ bi[ eid ] ]);
  }
  reduce();
  printf( "Case %d: " , ++ _cs );
  if( !okay() )
    puts( "No solution" );
  else{
    vector< pair<int,LL> > va;
    for( int i = 0 ; i < m ; i ++ )
      if( dlt[ i ] )
        va.push_back( {i + 1 , dlt[ i ]} );
    printf( "%d %lld\n" , (int)va.size() , dst[ 1 ] );
    for( auto i : va )
      printf( "%d %lld\n" , i.first , i.second );
  }
}
int main(){
  while( scanf( "%d%d" , &n , &m ) == 2 and n ){
    init();
    solve();
  }
}
