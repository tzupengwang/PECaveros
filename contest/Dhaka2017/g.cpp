#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int MAXN = (1<<16);
inline void fwt( LL x[ MAXN ] , int N , bool inv=0 ) {
  for( int d = 1 ; d < N ; d <<= 1 ) {
    int d2 = d<<1;
    for( int s = 0 ; s < N ; s += d2 ) {
      for( int i = s , j = s+d ; i < s+d ; i++, j++ ){
        LL ta = x[ i ] , tb = x[ j ];
        x[ i ] = ta+tb;
        x[ j ] = ta-tb;
      }
    }
  }
  if( inv )
    for( int i = 0 ; i < N ; i++ ) {
      x[i] /= N;
    }
}

const int N = 1e5+10;
const int X = (1<<16);

typedef pair<int, int> pii;
typedef long long ll;
int n;
vector<pii> g[N];
int d[N];

void dfs(int u, int p, int xr) {
  d[u] = xr;
  for (auto e: g[u]) {
    int v, w; tie(v, w) = e;
    if (v == p) continue;
    dfs(v, u, xr ^ w);
  }
}

ll a[X];
int _cs;

void main2() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    g[i].clear();
  }
  for (int i = 0; i < n-1; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    g[u].push_back({v, w});
    g[v].push_back({u, w});
  }
  dfs(1, 0, 0);
  fill(a, a+X, 0);
  for (int i = 1; i <= n; ++i) a[d[i]]++;
  fwt(a, X);
  for (int i = 0; i < X; ++i) a[i] *= a[i];
  fwt(a, X, true);
  a[0] -= n;
  printf("Case %d:\n", ++_cs);
  //for (int i = 0; i < 15; ++i) {
    //a[i] /= 2;
    //printf("%lld\n", a[i]);
  //}
  for (int i = 0; i < X; ++i) {
    a[i] /= 2;
    printf("%lld\n", a[i]);
  }
}

int main() {
  int tc;scanf("%d", &tc);while (tc--) main2();
}
