#include <bits/stdc++.h>
using namespace std;
int n , m , cap;
#define K 321
#define N 6666
vector< pair<int,int> > v[ N ];
map<string, int> M;
int mid , s , t;
string buf;
int id(){
  auto it = M.find( buf );
  if( it != M.end() )
    return it->second;
  return M[ buf ] = mid ++;
}
vector<int> gasid;
void init(){
  mid = 0;
  cap *= 10;
  M.clear();
  cin >> buf; s = id();
  cin >> buf; t = id();
  while( n -- ){
    int ui , vi , di;
    cin >> buf; ui = id();
    cin >> buf; vi = id();
    cin >> di;
    v[ ui ].push_back( { vi , di } );
    v[ vi ].push_back( { ui , di } );
  }
  gasid.clear();
  while( m -- ){
    int tmp;
    cin >> buf; tmp = id();
    gasid.push_back( tmp );
  }
}
#define INF 1234567
int g , dis[ K ][ N ] , vst[ N ] , stmp;
void sp( int gid ){
  ++ stmp;
  int who = gasid[ gid ];
  for( int i = 0 ; i < mid ; i ++ )
    dis[ gid ][ i ] = INF;
  dis[ gid ][ who ] = 0;
  priority_queue< pair<int,int> ,
    vector< pair<int,int> >,
    greater< pair<int,int> > > heap;
  heap.push( { 0 , who } );
  while( heap.size() ){
    pair<int,int> tp = heap.top(); heap.pop();
    int cur = tp.second;
    int dd = tp.first;
    if( dd > cap ) break;
    if( vst[ cur ] == stmp ) continue;
    vst[ cur ] = stmp;
    dis[ gid ][ cur ] = dd;
    for( auto e : v[ cur ] ){
      int nxt = e.first;
      int nd = dd + e.second;
      if( vst[ nxt ] == stmp ) continue;
      heap.push( { nd , nxt } );
    }
  }
}
int ddd[ N ][ N ];
void solve(){
  g = (int)gasid.size();
  for( int i = 0 ; i < g ; i ++ )
    sp( i );
  for( int i = 0 ; i < g ; i ++ )
    for( int j = 0 ; j < g ; j ++ )
      ddd[ i ][ j ] = dis[ i ][ gasid[ j ] ];
  for( int k = 0 ; k < g ; k ++ )
    for( int i = 0 ; i < g ; i ++ )
      for( int j = 0 ; j < g ; j ++ )
        ddd[ i ][ j ] = min( ddd[ i ][ j ], 
                             ddd[ i ][ k ] + ddd[ k ][ j ] );
  gasid.push_back( s );
  sp( g );
  gasid.push_back( t );
  sp( g + 1 );
  int ans = dis[ g ][ t ];
  for( int i = 0 ; i < g ; i ++ )
    for( int j = 0 ; j < g ; j ++ )
      ans = min( ans , dis[ g ][ gasid[ i ] ] +
                       ddd[ i ][ j ] +
                       dis[ g + 1 ][ gasid[ j ] ] );
  if( ans >= INF ) ans = -1;
  printf( "%d\n" , ans );
}
void clear(){
  for( int i = 0 ; i < mid ; i ++ )
    v[ i ].clear();
}
int main(){
  while( cin >> n >> m >> cap ){
    if( n == 0 ) break;
    init();
    solve();
    clear();
  }
}
