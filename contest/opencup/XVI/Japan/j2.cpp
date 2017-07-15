#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef pair<int, int> PII;

const int N = 505050;

int n, m;
vector<int> g[N];
int c[N];

int nn;
vector<int> gg[N];

inline void build(int u) {
  if (g[u].empty()) return;
  vector<PII> nei;
  for (int v: g[u]) nei.push_back(PII{c[v], v});
  sort(nei.begin(), nei.end());
  if (nei[0].first == nei.back().first) return;
  int pre = -1;
  for (int i = 0; i < (int)nei.size();) {
    int j = i;
    while (j < (int)nei.size() && nei[j].first == nei[i].first) {
      ++j;
    }
    if (pre != -1) {
      for (int k = i; k < j; ++k) {
        gg[pre].push_back(nei[k].second);
      }
    }
    if( j == (int)nei.size() ) break;
    assert( nn < N );
    pre = ++ nn;
    for (int k = i; k < j; ++k) {
      gg[nei[k].second].push_back(pre);
    }
    i = j;
  }
}

int indeg[N];
int ans[N];

int32_t main() {
  scanf("%lld", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", c+i);
  }
  scanf("%lld", &m);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%lld%lld", &u, &v);
    if (c[u] < c[v]) {
      gg[u].push_back(v);
    }
    if (c[v] < c[u]) {
      gg[v].push_back(u);
    }
    g[u].push_back(v);
    g[v].push_back(u);
  }
  nn = n;
  for (int i = 1; i <= n; ++i) {
    build(i);
  }
  for (int i = 1; i <= nn; ++i) {
    for (int v: gg[i]){
      //printf( "==%d %d\n" , i , v );
      indeg[v]++;
    }
  }
  queue<int> Q;
  for( int i = 1 ; i <= nn ; i ++ ){
    ans[ i ] = 1;
    if( indeg[ i ] == 0 )
      Q.push( i );
  }
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    for( int nxt : gg[ tn ] ){
      if( nxt > n )
        ans[ nxt ] = max( ans[ nxt ] , ans[ tn ] );
      else
        ans[ nxt ] = max( ans[ nxt ] , ans[ tn ] + 1 );
      indeg[ nxt ] --;
      if( indeg[ nxt ] == 0 )
        Q.push( nxt );
    }
  }
  //for( int i = 1 ; i <= n ; i ++ )
    //printf( "%d %d\n" , i , ans[ i ] );
  long long f = 0;
  for( int i = 1 ; i <= n ; i ++ )
    f += ans[ i ];
  cout << f << endl;
  //cout << accumulat( ans + 1 , ans + n + 1 , 0LL ) << endl;
}
