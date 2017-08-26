#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, c) for (int i = 0; i < (c); ++i)

typedef long long LL;

inline LL getint(){
  LL _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}

#define x1 fsjfklx1
#define y1 fsjfkly1
#define x2 fsjfklx2
#define y2 fsjfkly2

int x1, y1, z1, x2, y2, z2;

char ip[3][3][9];

int ccc;

bool init() {
  x1 = getint();
  y1 = getint();
  z1 = getint();
  x2 = getint();
  y2 = getint();
  z2 = getint();
  //cin >> x1 >> y1 >> z1;
  //cin >> x2 >> y2 >> z2;
  if (x1 == 0 && y1 == 0 && z1 == 0 && x2 == 0 && y2 == 0 && z2 == 0) return 0;
  swap(x1, z1);
  swap(x2, z2);
  FOR(i, 3) FOR(j, 3) cin >> ip[i][j];
  //if( +  ccc == 50 ){
    //cerr << x1 << " " << y1 << " " << z1 << endl;
    //cerr << x2 << " " << y2 << " " << z2 << endl;
    //FOR(i, 3) FOR(j, 3)
      //cerr << ip[ i ][ j ] << endl;
  //}
  return 1;
}

struct XD {
  int x, y, z;
  bool operator<(const XD& a) const {
    return tie(x, y, z) < tie(a.x, a.y, a.z);
  }
  bool operator==(const XD& a) const {
    return tie(x, y, z) == tie(a.x, a.y, a.z);
  }
};

map<pair<XD, XD>, int> planes;

void add(int i, int j, int k, int ii, int jj, int kk) {
  pair<XD, XD> p{
    XD{min(i, ii), min(j, jj), min(k, kk)},
    XD{max(i, ii), max(j, jj), max(k, kk)}
  };
  planes[p]++;
}


#define BS 60

inline int enc(int x, int y, int z) {
  return x*(3 * BS + 1) * (3 * BS + 1) +
         y*(3 * BS + 1) + z;
}

struct E {
  int u, v;
  double c;
};

double sq(double x) {return x*x;}

double dis(XD a, XD b) {
  double res = sq(a.x-b.x) + sq(a.y-b.y) + sq(a.z-b.z);
  return sqrt(res) / BS;
}

vector<E> edges;

void build(pair<XD, XD> p) {
  XD p1, p2;tie(p1, p2) = p;
  p1.x *= BS;
  p1.y *= BS;
  p1.z *= BS;
  p2.x *= BS;
  p2.y *= BS;
  p2.z *= BS;
  vector<XD> pts;
  for (int i = p1.x; i <= p2.x; ++i) {
    pts.push_back(XD{i, p1.y, p1.z});
  }
  for (int i = p1.y; i <= p2.y; ++i) {
    pts.push_back(XD{p1.x, i, p1.z});
  }
  for (int i = p1.z; i <= p2.z; ++i) {
    pts.push_back(XD{p1.x, p1.y, i});
  }
  for (int i = p1.x; i <= p2.x; ++i) {
    pts.push_back(XD{i, p2.y, p2.z});
  }
  for (int i = p1.y; i <= p2.y; ++i) {
    pts.push_back(XD{p2.x, i, p2.z});
  }
  for (int i = p1.z; i <= p2.z; ++i) {
    pts.push_back(XD{p2.x, p2.y, i});
  }
  sort( pts.begin() , pts.end() );
  pts.resize( unique( pts.begin() , pts.end() ) - pts.begin() );
  for (XD a: pts) for (XD b: pts) {
    int u = enc(a.x, a.y, a.z);
    int v = enc(b.x, b.y, b.z);
    if( u == v ) continue;
    double c = dis(a, b);
    edges.push_back(E{u, v, c});
    //edges.push_back(E{v, u, c});
  }
}

const int V = 10000;

//vector<pair<int, double>> g[V ;
unordered_map< int , vector<pair<int, double>> > g;
unordered_map<int , bool> vis;
unordered_map<int, double> dist;

void solve() {
  g.clear();
  vis.clear();
  dist.clear();
  planes.clear();
  FOR(i, 3) FOR(j, 3) FOR(k, 3) if(ip[i][j][k] == '#') {
    add(i, j, k, i+1, j+1, k);
    add(i, j, k, i, j+1, k+1);
    add(i, j, k, i+1, j, k+1);
    add(i+1, j+1, k+1, i+1, j, k);
    add(i+1, j+1, k+1, i, j+1, k);
    add(i+1, j+1, k+1, i, j, k+1);
  }
  edges.clear();
  for (auto it: planes) if(it.second == 1) {
    build(it.first);
  }
  //cerr << (int)edges.size() << endl;
  //for (int i = 0; i < V; ++i) {
    //g[i].clear();
    //vis[i] = 0;
  //}
  for (auto e: edges) g[e.u].push_back({e.v, e.c});
  typedef pair<double,int> data;
  priority_queue< data , vector<data> , greater<data> > heap;
  int start = enc( x1 * BS , y1 * BS , z1 * BS );
  int tar =   enc( x2 * BS , y2 * BS , z2 * BS );
  heap.push( { 0 , start } );
  while( heap.size() ){
    double dd ; int now ;
    tie( dd , now ) = heap.top(); heap.pop();
    if( vis[ now ] ) continue; 
    vis[ now ] = true;
    dist[ now ] = dd;
    if( now == tar ){
      printf( "%.12f\n" , dist[ tar ] );
      break;
    }
    for( auto i : g[ now ] ){
      if( vis[ i.first ] ) continue;
      heap.push( { dd + i.second , i.first } );
    }
  }
  //printf( "%.12f\n" , dist[ tar ] );
}

int main(){
  while (init()) {
    solve();
  }
}
