#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N = 2e5+2;

int n, k;
LL T;
int x[N];
int y[N];
bool vis[N];
vector<int> psum[N];
int sz[N], rt[N], xr[N], all[N], id[N];

void solve() {
  LL tt = T; int p2 = 1;
  while (tt) {
    if (tt&1) {
      fill(y, y+n, 0);
      fill(vis, vis+n, 0);
      for (int i = 0; i < n; ++i) {
        psum[i].clear();
        sz[i] = 0;
        all[i] = 0;
      }
      for (int i = 0; i < n; ++i) if (!vis[i]) {
        int cur = i, prv = 0, cid = 0;
        while (!vis[cur]) {
          vis[cur] = 1;
          rt[cur] = i;
          id[cur] = cid++;
          prv ^= x[cur];
          xr[cur] = prv;

          psum[i].push_back(xr[cur]);
          sz[i]++;
          cur = (cur+p2) % n;
        }
        all[i] = prv;
        for(int j = 0; j < sz[i]; ++j)
          psum[i].push_back(prv ^ psum[i][j]);
      }
      for (int i = 0; i < n; ++i) {
        int rnd = k / sz[rt[i]];
        y[i] = (rnd&1) * all[rt[i]];
        int rst = k % sz[rt[i]];
        //printf("i %d %d %d\n", i, id[i], id[i]+rst-1);
        y[i] ^= psum[rt[i]][id[i]+rst-1];
        if (id[i]) {
          y[i] ^= psum[rt[i]][id[i]-1];
        }
      }
      copy(y, y+n, x);
    }
    tt >>= 1;
    p2 <<= 1;
    p2 %= n;
  }
  for (int i = 0; i < n; ++i) printf("%d%c", y[i], " \n"[i+1==n]);
}

int main(){
  scanf("%d%d%lld", &n, &k, &T);
  for (int i = 0; i < n; ++i)
    scanf("%d", x+i);
  //n = 1e5, k = 4e4, T = (1ll<<60)-1;
  //for (int i = 0; i < n; ++i) x[i] = rand() * rand() % int(1e9);
  solve();
}
