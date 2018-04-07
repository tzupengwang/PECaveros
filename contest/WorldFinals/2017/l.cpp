
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
typedef pair<pii, pii> piiii;
#define X first
#define Y second
const int N = 2e5+10;
const int INF = 1e9+10;

void fail() {
  puts("syntax error");
  exit(0);
}

int n, r[N], c[N];
int ans[N];

inline bool chk(int L, int R, pii intv) {
  int tL, tR; tie(tL, tR) = intv;
  return (L < tL && tR < R) || (tL < L && R < tR) || (R < tL) || (tR < L);
}

void check() {
  {
  set<piii> st;
  vector<piiii> events;
  for (int i = 1; i <= n; ++i) {
    int j = ans[i];
    int L = c[i], R = c[j];
    int U = r[i], D = r[j];
    events.push_back({{U, -i}, {L, R}});
    events.push_back({{D, i}, {L, R}});
  }
  sort(events.begin(), events.end());
  for (piiii e: events) {
    bool in = e.first.second < 0;
    int i = abs(e.first.second);
    int L = e.second.first;
    int R = e.second.second;
    if (in) {
      auto it = st.lower_bound({{R, INF}, 0});
      if (it != st.begin()) {
        --it;
        if (!chk(L, R, it->first)) fail();
      }
      st.insert({{L, R}, i});
    } else {
      st.erase({{L, R}, i});
    }
  }
  }
  {
  set<piii> st;
  vector<piiii> events;
  for (int i = 1; i <= n; ++i) {
    int j = ans[i];
    int U = c[i], D = c[j];
    int L = r[i], R = r[j];
    events.push_back({{U, -i}, {L, R}});
    events.push_back({{D, i}, {L, R}});
  }
  sort(events.begin(), events.end());
  for (piiii e: events) {
    bool in = e.first.second < 0;
    int i = abs(e.first.second);
    int L = e.second.first;
    int R = e.second.second;
    if (in) {
      auto it = st.lower_bound({{R, INF}, 0});
      if (it != st.begin()) {
        --it;
        if (!chk(L, R, it->first)) fail();
      }
      st.insert({{L, R}, i});
    } else {
      st.erase({{L, R}, i});
    }
  }
  }
}

int main(){
  scanf("%d", &n);
  vector<piii> ip;
  for (int i = 1; i <= n+n; ++i) {
    scanf("%d%d", r+i, c+i);
    ip.push_back({{r[i], c[i]}, i});
  }
  sort(ip.begin(), ip.end());
  set<pii> st;
  for (auto p: ip) {
    pii pt = p.first;
    int i = p.second;
    if (i <= n) {
      st.insert({pt.Y, i});
    } else {
      auto it = st.upper_bound({pt.Y, N});
      if (it == st.begin()) fail();
      --it;
      ans[it->second] = i;
      st.erase(*it);
    }
  }
  check();
  for (int i = 1; i <= n; ++i) printf("%d\n", ans[i] - n);
}
