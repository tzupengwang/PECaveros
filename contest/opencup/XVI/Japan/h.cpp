#include <bits/stdc++.h>
using namespace std;
typedef double type;
typedef pair<type,type> Pt;
typedef pair<Pt,Pt> Line;
typedef pair<Pt,type> Circle;
#define X first
#define Y second
#define O first
#define R second
const double eps = 1e-9;
Pt operator+( const Pt& p1 , const Pt& p2 ){
  return { p1.X + p2.X , p1.Y + p2.Y };
}
Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
Pt operator*( const Pt& tp , const type& tk ){
  return { tp.X * tk , tp.Y * tk };
}
Pt operator/( const Pt& tp , const type& tk ){
  return { tp.X / tk , tp.Y / tk };
}
type operator*( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.X + p1.Y * p2.Y;
}
type operator^( const Pt& p1 , const Pt& p2 ){
  return p1.X * p2.Y - p1.Y * p2.X;
}
type norm2( const Pt& tp ){
  return tp * tp;
}
double norm( const Pt& tp ){
  return sqrt( norm2( tp ) );
}
Pt perp( const Pt& tp ){
  return { tp.Y , -tp.X };
}
void scan( Pt& tp ){
  scanf( "%lf%lf" , &tp.X , &tp.Y );
}
bool on_line( const Pt& p1 , const Pt& aa , const Pt& p2 ){
  if( fabs( ( aa - p1 ) ^ ( p2 - p1 ) ) > eps )
    return false;
  double ret = ( ( p2 - p1 ) * ( aa - p1 ) )
    / norm( p2 - p1 ) / norm( aa - p1 );
  return eps < ret and ret < 1 - eps;
}
/*
  A template for Min Cost Max Flow
  tested with TIOJ 1724
*/
static const int INF  = 1e6;
struct MinCostMaxFlow{
  static const int MAXV = 20010;
  struct Edge{
    int v, cap;
    double w;
    int rev;
    Edge(){}
    Edge(int t2, int t3, double t4, int t5)
    : v(t2), cap(t3), w(t4), rev(t5) {}
  };
  int V, s, t;
  vector<Edge> g[MAXV];
  void init(int n){
    V = n+2;
    s = n+1, t = n+2;
    for(int i = 0; i <= V; i++) g[i].clear();
  }
  void addEdge(int a, int b, int cap, double w){
    g[a].push_back(Edge(b, cap, w, (int)g[b].size()));
    g[b].push_back(Edge(a, 0, -w, (int)g[a].size()-1));
  }
  double d[MAXV];
  int id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  queue<int> qu;
  //int qu[200000 ], ql, qr;
  //the size of qu should be much large than MAXV
  double solve(){
    int mxf = 0;
    double mnc = 0;
    while(1){
      fill(d+1, d+1+V, INF);
      fill(inqu+1, inqu+1+V, 0);
      fill(mom+1, mom+1+V, -1);
      mom[s] = s;
      d[s] = 0;
      while( qu.size() ) qu.pop();
      qu.push( s );
      //qu[++qr] = s;
      inqu[s] = 1;
      while(qu.size()){
        int u = qu.front(); qu.pop();
        inqu[u] = 0;
        for(int i = 0; i < (int) g[u].size(); i++){
          Edge &e = g[u][i];
          int v = e.v;
          if(e.cap > 0 && d[v] > d[u]+e.w){
            d[v] = d[u]+e.w;
            mom[v] = u;
            id[v] = i;
            if(!inqu[v]){
              qu.push( v );
              //qu[++qr] = v;
              inqu[v] = 1;
            }
          }
        }
      }
      if(mom[t] == -1) break ;
      int df = INF;
      for(int u = t; u != s; u = mom[u])
        df = min(df, g[mom[u]][id[u]].cap);
      for(int u = t; u != s; u = mom[u]){
        Edge &e = g[mom[u]][id[u]];
        e.cap             -= df;
        g[e.v][e.rev].cap += df;
      }
      mxf += df;
      mnc += df*d[t];
    }
    return mnc;
  }
} flow;
#define N 333
vector< pair<Pt,Pt> > v;
Pt s;
void init(){
  int n; cin >> n;
  scan( s );
  while( n -- ){
    Pt x , y;
    scan( x );
    scan( y );
    if( on_line( x , s , y ) ){
      v.push_back( { x , s } );
      v.push_back( { s , y } );
    }else
      v.push_back( { x , y } );
  }
}
int n;
const double inf = 1e6;
void solve(){
  n = (int)v.size();
  flow.init( n + n + 1 );
  int ss = n + n + 1;
  flow.addEdge( flow.s , ss , 1 , 0 );
  for( int i = 1 ; i <= n ; i ++ ){
    flow.addEdge( ss , i , 1 , norm( s - v[ i - 1 ].first ) );
    flow.addEdge( n + i , flow.t , 1 , norm( s - v[ i - 1 ].second ) );
    flow.addEdge( i , n + 1 , 1 , norm( v[ i - 1 ].first - v[ i - 1 ].second ) - inf );
    for( int j = 1 ; j <= n ; j ++ ){
      if( i == j ) continue;
      flow.addEdge( n + i , j , 1 , norm( v[ i - 1 ].second - v[ j - 1 ].first ) );
    }
  }
  printf( "%.12f\n" , flow.solve() + inf * n );
}
int main(){
  init();
  solve();
}
