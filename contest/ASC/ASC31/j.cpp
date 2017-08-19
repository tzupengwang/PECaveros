#include <bits/stdc++.h>
using namespace std;
#define N 22
#define SZ(c) ((int)(c).size())
struct Maxflow {
  static const int MAXV = 20010;
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
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;
//Maxflow::Edge e(1, 1, 1);
int p , n , m;
string buf;
map<string, int> res , building;
int nd[ N ][ N ] , has[ N ][ N ] , dlt[ N ][ N ] , f[ N ];
string name[ N ];
string name_of( int id , const map<string,int>& mm ){
  for( auto i : mm )
    if( i.second == id )
      return i.first;
  assert( false );
  return "";
}
vector<string> res_name;
void init(){
  getline( cin , buf );
  stringstream ss( buf );
  ss >> p >> n >> m;
  getline( cin , buf );
  ss = stringstream( buf );
  int id = 0;
  while( ss >> buf ){
    res_name.push_back( buf );
    //cout << buf << " " << id << endl;
    res[ buf ] = id ++;
  }
  for( int i = 0 ; i < m ; i ++ ){
    getline( cin , buf );
    ss = stringstream( buf );
    ss >> buf;
    building[ buf ] = i;
    ss >> buf; // requires
    int nn;
    while( ss >> nn >> buf ){
      int len = buf.length();
      if( buf[ len - 1 ] == ',' )
        buf = buf.substr( 0 , len - 1 );
      nd[ i ][ res[ buf ] ] += nn;
    }
    //for( int j = 0 ; j < n ; j ++ )
      //printf( "%d " , nd[ i ][ j ] );
    //puts( "" );
  }
  for( int i = 0 ; i < p ; i ++ ){
    getline( cin , buf );
    ss = stringstream( buf );
    ss >> name[ i ];
    ss >> buf; // wants
    int tar = 0;
    //cout << name[ i ] << endl;
    {
      ss >> buf;
      int len = buf.length();
      if( buf[ len - 1 ] == ',' )
        buf = buf.substr( 0 , len - 1 );
      tar = building[ buf ];
    }
    //cout << tar << endl;
    f[ i ] = tar;
    if( ss >> buf ){ // has
      int nn;
      while( ss >> nn >> buf ){
        int len = buf.length();
        if( buf[ len - 1 ] == ',' )
          buf = buf.substr( 0 , len - 1 );
        has[ i ][ res[ buf ] ] += nn;
      }
    }
    for( int j = 0 ; j < n ; j ++ )
      dlt[ i ][ j ] = has[ i ][ j ] - nd[ tar ][ j ];
  }
}
int in( int who , int which ){
  return who * n + which;
}
int out( int who , int which ){
  return p * n + who * n + which;
}
#define inf 514
void solve(){
  flow.init( p * ( n + n ) );
  int fans = 0;
  for( int i = 0 ; i < n ; i ++ ){
    if( has[ 0 ][ i ] )
      flow.addEdge( flow.s , in( 0 , i ) , has[ 0 ][ i ] );
    if( nd[ f[ 0 ] ][ i ] ){
      flow.addEdge( out( 0 , i ) , flow.t , nd[ f[ 0 ] ][ i ] );
      fans += nd[ f[ 0 ] ][ i ];
    }
    flow.addEdge( in( 0 , i ) , out( 0 , i ) , inf );
  }
  for( int j = 1 ; j < p ; j ++ ){
    for( int i = 0 ; i < n ; i ++ ) if( dlt[ j ][ i ] < 0 )
      for( int k = 0 ; k < n ; k ++ ) if( dlt[ j ][ k ] > 0 ){
        flow.addEdge( in( j , i ) , out( j , k ) , inf );
      }
    for( int i = 0 ; i < n ; i ++ ){
      if( dlt[ j ][ i ] < 0 )
        flow.addEdge( in( 0 , i ) , in( j , i ) , -dlt[ j ][ i ] );
      if( dlt[ j ][ i ] > 0 )
        flow.addEdge( out( j , i ) , in( 0 , i ) , dlt[ j ][ i ] );
    }
  }
  int ret = flow.solve();
  if( ret < fans ){
    puts( "No way" );
    exit(0);
  }
  queue< pair<int,pair<int,int>> > ans;
  for( int j = 1 ; j < p ; j ++ )
    for( int i = 0 ; i < n ; i ++ )
      for( auto e : flow.G[ in( j , i ) ] )
        if( e.c < inf and out( j , 0 ) <= e.v and e.v <= out( j , n - 1 ) ){
          for( int rep = 0 ; rep < inf - e.c ; rep ++ )
            ans.push( { j , { i , e.v - out( j , 0 ) } } );
        }
  while( ans.size() ){
    auto i = ans.front(); ans.pop();
    if( has[ 0 ][ i.second.first ] == 0 ){
      ans.push( i );
      continue;
    }
    cout << "trade with ";
    cout << name[ i.first ];
    cout << " ";
    cout << res_name[ i.second.first ];
    cout << " for ";
    cout << res_name[ i.second.second ];
    cout << "\n";
    has[ 0 ][ i.second.first ] --;
    has[ 0 ][ i.second.second ] ++;
  }
  cout << "build " << name_of( f[ 0 ] , building ) << endl;
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "trading.in" , "r" , stdin );
  freopen( "trading.out" , "w" , stdout );
#endif
  init();
  solve();
}
