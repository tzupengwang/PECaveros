#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;

#define SZ(c) ((int)c.size())
#define F first
#define S second

typedef long long ll;
typedef pair<int, int> pii;

const int N = 1e5+10;
const ll  INF = 1000000000000000;

int n, ip[N];
int out[N];

inline void calc(set_t a, vector<int> pos, vector<pii>& ans) {
  if (SZ(a) != SZ(pos)) return;
  static int cnta[N], cntb[N];
  fill(cnta, cnta+n+1, 0);
  fill(cntb, cntb+n+1, 0);
  for (auto i: a) cnta[i]++;
  for (int i: pos) cntb[i]++;
  int ca = 0, cb = 0;
  int prv = 1;
  for (int i = 1; i <= n; ++i) {
    ca += cnta[i];
    cb += cntb[i];
    if (ca != cb or ca == 0 or cb == 0) continue;

    int fa = i, fb = 0;
    for (int j = prv; j <= i; ++j) {
      if (cnta[j]) {
        fa = j;
        break;
      }
    }
    for (int j = prv; j <= i; ++j) {
      if (cntb[j]) {
        fb = j;
        break;
      }
    }
    if (fa > fb) {
      set<pii> st;
      for (int j = prv; j <= i; ++j) {
        if (cntb[j]) st.insert({ip[j], j});
        if (cnta[j]) {
          auto it = st.begin();
          ans.push_back({j, it->second});
          st.erase(it);
        }
      }
    } else {
      set<pii> st;
      for (int j = i; j >= prv; --j) {
        if (cntb[j]) st.insert({ip[j], j});
        if (cnta[j]) {
          auto it = st.rbegin();
          ans.push_back({j, it->second});
          st.erase(*it);
        }
      }
    }
    ca = 0;
    cb = 0;
    prv = i+1;
  }
}

inline ll cost(vector<pii>& plan) {
  if (SZ(plan) != n) return INF;
  ll res = 0;
  for (auto p: plan) {
    res += abs(p.F - p.S);
  }
  return res;
}

bool operator<(vector<int> a, vector<int> b) {
  for (int i = 0; i < min(SZ(a), SZ(b)); ++i)
    if (a[i] != b[i]) return a[i] < b[i];
  return 0;
}

inline vector<int> expand(vector<pii>& plan) {
  vector<int> res(n+1, 0);
  for (auto p: plan)
    res[p.F] = ip[p.S];
  return res;
}

int main() {
  scanf("%d", &n);
  set_t tar[2];
  vector<int> pos[2];
  for (int i = 1; i <= n; ++i) {
    scanf("%d", ip+i);
    tar[i&1].insert(i);
    pos[ip[i]&1].push_back(i);
  }
  vector<pii> ans[2];
  calc(tar[0], pos[0], ans[0]);
  calc(tar[1], pos[1], ans[0]);
  //for (auto p: ans[0]) printf("%d %d\n", p.F, p.S);
  //puts("");
  calc(tar[0], pos[1], ans[1]);
  calc(tar[1], pos[0], ans[1]);
  //for (auto p: ans[1]) printf("%d %d\n", p.F, p.S);
  //puts("");
  if (cost(ans[0]) > cost(ans[1]) or (cost(ans[0]) == cost(ans[1]) and expand(ans[0]) < expand(ans[1]))) {
    swap(ans[0], ans[1]);
  }
  for (auto p: ans[0]) out[p.first] = ip[p.second];
  for (int i = 1; i <= n; ++i) {
    printf("%d%c", out[i], " \n"[i == n]);
  }
}
