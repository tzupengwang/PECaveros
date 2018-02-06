
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

const int N = 1e5+10;

int n;
int p[N];
int m;
vector<pii> twocyc[N];
bool vis[N];

int q[3][N];

void build(const vector<pii>& twos, int* tq) {
  for (int i = 1; i <= n; ++i) tq[i] = i;
  for (pii tp: twos) {
    int i, j; tie(i, j) = tp;
    swap(tq[i], tq[j]);
  }
  for (int i = 1; i <= n; i ++) {
    if (tq[tq[i]] != i) {
      puts("Not 2 cycle");
      assert(0);
    }
  }
}

void main2() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", p+i);
  }
  //n = 100000;
  //for (int i = 1; i <= n; ++i) p[i] = i;
  //random_shuffle(p+1, p+1+n);
  m = 0;
  for (int i = 0; i < n; ++i) twocyc[i].clear();
  fill(vis, vis+1+n, 0);
  for (int i = 1; i <= n; ++i) if (!vis[i]) {
    int cur = i;
    vector<int> cycle;
    while (!vis[cur]) {
      vis[cur] = 1;
      cycle.push_back(cur);
      cur = p[cur];
    }
    if (cycle.size() == 1) {
      //twocyc[0].push_back(pii(i,i));
    } else if (cycle.size() == 2) {
      m = max(m, 1);
      twocyc[0].push_back(pii(cycle[0],cycle[1]));
    } else {
      m = 2;
      int t = cycle.size();
      if (cycle.size() % 2 == 0) {
        for (int j = 1; j <= t/2-1; ++j) {
          twocyc[0].push_back(pii(cycle[j-1], cycle[t-j-1]));
        }
        for (int j = 1; j <= t/2-1; ++j) {
          twocyc[1].push_back(pii(cycle[j-1], cycle[t-j-1-1]));
        }
        twocyc[1].push_back(pii(cycle[t-1-1], cycle[t-1]));
      } else {
        for (int j = 1; j <= t/2; ++j) {
          twocyc[0].push_back(pii(cycle[j-1], cycle[t-j+1-1]));
        }
        for (int j = 1; j <= t/2; ++j) {
          twocyc[1].push_back(pii(cycle[j-1], cycle[t-j-1]));
        }
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    build(twocyc[i], q[i]);
  }
  for (int i = 1; i <= n; ++i) {
    int cur = i;
    for (int j = m-1; j >= 0; --j) cur = q[j][cur];
    if (p[i] != cur) {
      puts("WTF");
      assert(0);
    }
  }
  printf("%d\n", m);
  for (int i = 0; i < m; ++i) {
    for (int j = 1; j <= n; ++j) printf("%d%c", q[i][j], " \n"[j==n]);
  }
}

int main(){
  srand(time(0) ^ 514514);
  int tc; scanf("%d", &tc); while (tc--) main2();
}
