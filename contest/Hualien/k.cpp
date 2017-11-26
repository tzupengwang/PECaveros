#include <bits/stdc++.h>
using namespace std;
#define N 30
int n , m;
bool vst[ N ];
int dep[N];
vector<int> g[ N ];
vector<int> tr[N];
void init(){
  cin >> n >> m;
  for( int i = 0 ; i < n ; i ++ ){
    vst[ i ] = false;
    g[ i ].clear();
    tr[ i ].clear();
    dep[i] = 0;
  }
  while( m -- ){
    int a , b;
    cin >> a >> b;
    g[ a ].push_back( b );
    g[ b ].push_back( a );
  }
}


bool okay , found;
int clr[ N ] , stmp;

bool chk(int u) {
  for (int v: g[u]) if (dep[v] < dep[u]) {
    if (clr[v] == clr[u]) return 0;
  }
  return 1;
}

bool dfs2(int u) {
  if (!chk(u)) return 0;
  for (int v: tr[u]) {
    bool flag = 0;
    for (int c = 1; c <= 3; ++c) if (c != clr[u]) {
      clr[v] = c;
      if (dfs2(v)) {
        flag = 1;
        break;
      }
    }
    if (!flag) return 0;
  }
  return 1;
}

void del(int u) {
  vst[u] = 1;
  for (int v: g[u]) if (!vst[v])
    del(v);
}

void dfs1(int u, int p, int d) {
  if (d > 1) {
    tr[p].push_back(u);
  }
  dep[u] = d;
  for (int v: g[u]) if (dep[v] == 0) {
    dfs1(v, u, d+1);
  }
}

void solve(){
  okay = true;
  fill(vst, vst+n, 0);
  fill(clr, clr+n, 0);
  for( int i = 0 ; i < n ; i ++ ){
    if( vst[ i ] ) continue;
    dfs1(i, 0, 1);
    clr[i] = 1;
    bool flag = dfs2(i);
    if (!flag) {
      okay = 0;
      break;
    }
    del(i);
  }
  puts(okay? "Y": "N");
}
int main(){
  int t; cin >> t; while( t -- ){
    init();
    solve();
  }
}
