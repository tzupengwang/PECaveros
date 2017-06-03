#include <bits/stdc++.h>
using namespace std;
#define SZ(c) ((int)(c).size())
struct Maxflow {
  static const int MAXV = 100010;
  static const int INF  = 1000000;
  struct Edge {
    int v, c, r;
    Edge(int _v, int _c, int _r):
      v(_v), c(_c), r(_r) {}
  };
  int s, t;
  vector<Edge> G[MAXV*2];
  int iter[MAXV*2], d[MAXV*2], gap[MAXV*2], tot;
  void init(int x) {
    tot = x+2;
    s = x+1, t = x+2;
    for(int i = 0; i <= tot; i++) {
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
  }
  void addEdge(int u, int v, int c) {
    G[u].push_back(Edge(v, c, SZ(G[v]) ));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1));
  }
  int dfs(int p, int flow) {
    if(p == t) return flow;
    for(int &i = iter[p]; i < SZ(G[p]); i++) {
      Edge &e = G[p][i];
      if(e.c > 0 && d[p] == d[e.v]+1) {
        int f = dfs(e.v, min(flow, e.c));
        if(f) {
          e.c -= f;
          G[e.v][e.r].c += f;
          return f;
        }
      }
    }
    if( (--gap[d[p]]) == 0) d[s] = tot;
    else {
      d[p]++;
      iter[p] = 0;
      ++gap[d[p]];
    }
    return 0;
  }
  int solve() {
    //puts("MF");
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
#define N 211111
int w , h , n , c , m;
set< pair<int,int> > mountain , city;
int cx[ N ] , cy[ N ] , hp[ N ];
int ax[ N ] , ay[ N ] , wp[ N ];
map< pair<int,int> , int > id;
vector< int > cat[ N ] , pos[ N ];
int mid;
int dist( int nx , int ny , int mx , int my ){
  if( nx > mx ){
    swap( nx , mx );
    swap( ny , my );
  }
  if( nx == mx ) return abs( ny - my );
  if( ny < my ) return my - ny + mx - nx;
  int atmst = nx + ny - my;
  if( mx <= atmst ) return abs( ny - my );
  return abs( ny - my ) + mx - atmst;
}
map< int , pair<int,int> > who;
void add( int nx , int ny ){
  if( id.count( { nx , ny } ) == 0 ){
    who[ mid ] = { nx , ny };
    id[ { nx , ny } ] = mid;
    for( int i = 0 ; i < n ; i ++ ){
      if( dist( nx , ny , cx[ i ] , cy[ i ] ) <= 2 ){
        pos[ mid ].push_back( i );
      }
    }
    mid ++;
  }
}
int dx[]={0,0,1,-1,1,-1};
int dy[]={1,-1,0,0,-1,1};
set< pair<int,int> > tag;
void go( int wwho , int nx , int ny , int d ){
  tag.clear();
  queue< pair<pair<int,int>,int> > Q;
  Q.push( { { nx , ny } , d } );
  tag.insert( { nx , ny } );
  while( Q.size() ){
    auto i = Q.front(); Q.pop();
    nx = i.first.first;
    ny = i.first.second;
    d = i.second;
    add( nx , ny );
    if( d == 0 ) continue;
    cat[ wwho ].push_back( id[ { nx , ny } ] );
    //printf( "%d %d\n" , wwho , id[ { nx , ny } ] );
    //printf( "%d -> %d %d\n" , wwho , nx , ny );
    if( d == 1 ) continue;
    for( int dir = 0 ; dir < 6 ; dir ++ ){
      int nxtx = nx + dx[ dir ];
      int nxty = ny + dy[ dir ];
      if( nxtx < 0 or nxtx >= w or
          nxty < 0 or nxty >= h )
        continue;
      if( mountain.count( { nxtx , nxty } ) )
        continue;
      if( city.count( { nxtx , nxty } ) )
        continue;
      if( tag.count( { nxtx , nxty } ) )
        continue;
      tag.insert( { nxtx , nxty } );
      Q.push( { { nxtx , nxty } , d - 1 } );
      //go( wwho , nxtx , nxty , d - 1 );
    }
  }
}
void init(){
  scanf( "%d%d" , &w , &h );
  scanf( "%d" , &n );
  for( int i = 0 ; i < n ; i ++ ){
    scanf( "%d%d%d" , &cx[ i ] , &cy[ i ] , &hp[ i ] );
    city.insert( { cx[ i ] , cy[ i ] } );
  }
  scanf( "%d" , &c );
  for( int i = 0 ; i < c ; i ++ )
    scanf( "%d%d%d" , &ax[ i ] , &ay[ i ] , &wp[ i ] );
  scanf( "%d" , &m );
  while( m -- ){
    int xx , yy; scanf( "%d%d" , &xx , &yy );
    mountain.insert( { xx , yy } );
  }
  mid = c + n;
  for( int i = 0 ; i < c ; i ++ )
    go( i , ax[ i ] , ay[ i ] , wp[ i ] );
}
void fire( int msk ){
  flow.init( mid + mid + 2 );
  int dump = mid + mid + 2;
  for( int i = 0 ; i < c ; i ++ )
    flow.addEdge( flow.s , i , 1 );
  for( int i = 0 ; i < c ; i ++ )
    for( int j : cat[ i ] )
      flow.addEdge( i , j , 1 );
  for( int i = c + n ; i < mid ; i ++ ){
    flow.addEdge( i , i + mid , 1 );
    for( int j : pos[ i ] )
      if( ( msk >> j ) & 1 )
        flow.addEdge( i + mid , j + c , 1 );
    flow.addEdge( i + mid , dump , 1 );
  }
  int res = c;
  for( int i = 0 ; i < n ; i ++ )
    if( ( msk >> i ) & 1 ){
      flow.addEdge( i + c , flow.t , hp[ i ] );
      res -= hp[ i ];
    }
  if( res < 0 ) return;
  if( res )
    flow.addEdge( dump , flow.t , res );
  if( flow.solve() != c ) return;
  printf( "%d\n" , __builtin_popcount( msk ) );
  set< pair<int,int> > oc;
  for( int i = 0 ; i < c ; i ++ ){
    int ansx = -1 , ansy = -1 , att = 0;
    for( auto e : flow.G[ i ] )
      if( e.c == 0 and c + n <= e.v and e.v < mid ){
        tie(ansx, ansy) = who[ e.v ];
        for( auto ee : flow.G[ mid + e.v ] )
          if( ee.c == 0 ){
            if( c <= ee.v and ee.v < c + n ){
              att = ee.v - c + 1;
              break;
            }
          }
        break;
      }
    //assert( ansx != -1 );
    //assert( mountain.count( { ansx , ansy } ) == 0 );
    //assert( city.count( { ansx , ansy } ) == 0 );
    assert( oc.count( { ansx , ansy } ) == 0 );
    oc.insert( { ansx , ansy } );
    printf( "%d %d %d\n" , ansx , ansy , att );
  }
  exit(0);
}
void solve(){
  vector< pair<int,int> > v;
  for( int i = 1 ; i < (1 << n) ; i ++ )
    v.push_back( { __builtin_popcount( i ) , i } );
  sort( v.begin() , v.end() );
  reverse( v.begin() , v.end() );
  for( auto i : v )
    fire( i.second );
  puts( "0" );
  for( int i = 0 ; i < c ; i ++ )
    printf( "%d %d 0\n" , ax[ i ] , ay[ i ] );
}
int main(){
#ifndef eddy
  freopen( "input.txt" , "r" , stdin );
  freopen( "output.txt" , "w" , stdout );
#endif
  init();
  solve();
}
