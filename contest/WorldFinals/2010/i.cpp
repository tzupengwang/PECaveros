
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

typedef pair<int, int> pii;
typedef pair<pair<int, ULL>, LL> XD;

inline int bit(ULL x, int k) { return (x>>k)&1LL; }

const int N = 10;

int n, m, r[4], c[4];

inline int enc(int i, int j) { return i*m + j; }
inline void dec(int x, int &i, int &j) { i = x/m, j = x%m; }

int goal_x[70], goal_y[70], goal_d[70];

int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

inline void uniq(vector<XD>& v) {
  vector<XD> tmp;

  sort(v.begin(), v.end());

  for (int i = 0; i < (int)v.size(); ++i) {
    if (tmp.size() && tmp.back().first == v[i].first) {
      tmp.back().second += v[i].second;
    } else {
      tmp.push_back(v[i]);
    }
  }
  v.swap(tmp);
}

bool can[N][N];
bool vis[N][N];

void bfs(int i, int j) {
  static pii qu[N*N];
  int ql = 0, qr = 0;
  qu[qr++] = {i, j};
  vis[i][j] = 1;
  while (ql < qr) {
    int ci, cj; tie(ci, cj) = qu[ql++];
    for (int k = 0; k < 4; ++k) {
      int ni = ci + dx[k];
      int nj = cj + dy[k];
      if (0 <= ni && ni < n && 0 <= nj && nj < m) {
        if (can[ni][nj] && !vis[ni][nj]) {
          vis[ni][nj] = 1;
          qu[qr++] = {ni, nj};
        }
      }
    }
  }
}

inline bool chk(ULL S) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      can[i][j] = bit(S, enc(i, j)) ^ 1;
      vis[i][j] = 0;
    }
  bool flag = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) if (!vis[i][j] && can[i][j]) {
      if (flag) return 0;
      bfs(i, j);
      flag = 1;
    }
  return 1;
}

inline bool good(int t, XD state) {
  int cx, cy;
  dec(state.first.first, cx, cy);
  if (abs(cx - goal_x[t]) + abs(cy - goal_y[t]) <= goal_d[t]) {
    for (int i = 0; i <= 3; ++i) {
      int tt = ((i+1) * n * m) / 4;
      if (t < tt and bit(state.first.second, enc(r[i], c[i])))
        return 0;
    }
    return chk(state.first.second);
    //return 1;
  } else return 0;
}

inline void reg(int t, vector<XD>& v) {
  //printf("time %d %d %d %d\n", t, goal_x[t], goal_y[t], goal_d[t]);
  vector<XD> tmp2;
  for (XD state: v) {
    if (good(t, state)) {
      tmp2.push_back(state);
    }
  }
  v.swap(tmp2);
}

inline void relax(vector<XD>& v1, vector<XD>& v2) {
  for (XD state: v1) {
    int cx, cy; ULL S; LL cnt;
    dec(state.first.first, cx, cy);
    S = state.first.second;
    cnt = state.second;
    for (int k = 0; k < 4; ++k) {
      int tx = cx + dx[k];
      int ty = cy + dy[k];
      if (0 <= tx && tx < n && 0 <= ty && ty < m) {
        int j = enc(tx, ty);
        if ((S>>j)&1LL) continue;
        v2.push_back({{j, (S | (1LL << j))}, cnt});
      }
    }
  }
  uniq(v2);
}

vector<XD> ok[70], ko[70];

LL main2() {
  r[3] = 0, c[3] = 1;
  LL ans = 0;

  for (int i = 0; i <= 3; ++i) {
    int tt = ((i+1) * n * m) / 4;
    int pt = ((i) * n * m) / 4;
    for (int j = pt+1; j <= tt; ++j) {
      goal_x[j] = r[i];
      goal_y[j] = c[i];
      goal_d[j] = tt-j;
    }
  }

  for (int i = 0; i <= n*m; ++i) ok[i].clear();
  for (int i = 0; i <= n*m; ++i) ko[i].clear();

  int mid_t = (2 * n * m) / 4;

  ok[1].push_back({{enc(0, 0), 1 << enc(0, 0)}, 1});

  for (int t = 1; t < n*m; ++t) {
    relax(ok[t], ok[t+1]);
    reg(t+1, ok[t+1]);
  }
  ans = 0;
  if (ok[n*m].size())
    ans = ok[n*m][0].second;
  return ans;
  for (int t = 1; t < mid_t; ++t) {
    //printf("t %d %d\n", t, ok[t].size());
    relax(ok[t], ok[t+1]);
    reg(t+1, ok[t+1]);
  }
  ko[n*m].push_back({{enc(0, 1), 1 << enc(0, 1)}, 1});
  for (int t = n*m; t > mid_t; --t) {
    //printf("t %d %d\n", t, ko[t].size());
    relax(ko[t], ko[t-1]);
    reg(t-1, ko[t-1]);
  }

  ULL all = 0;

  for (int i = 0; i < n*m; ++i) all |= (1LL << i);
  map<ULL, LL> mp;

  for (XD state: ok[mid_t]) mp[state.first.second] += state.second;

  ans = 0;

  for (XD state: ko[mid_t]) {
    ULL S = state.first.second;
    ans += mp[(all ^ S) | (1LL << enc(r[1], c[1]))] * state.second;
  }
  return ans;
}

int _cs;

int main(){
  while (scanf("%d%d", &n, &m) == 2 && n) {
    for (int i = 0; i < 3; ++i) scanf("%d%d", r+i, c+i);
    LL ans = main2();
    printf("Case %d: %lld\n", ++_cs, ans);
  }
}
