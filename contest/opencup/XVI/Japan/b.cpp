#include <bits/stdc++.h>
using namespace std;

const int N = 3010;

struct XD {
  int x, y;
  char d;
  void read() {
    string s;
    cin >> x >> y >> s;
    d = s[0];
  }
};

int n;
XD ip[N];
vector<int> nxt[N];

inline int go(int s) {
  static bool vis[N];
  fill(vis, vis+n, 0);
  int res = 0;
  int cur = s;
  while (1) {
    ++res;
    vis[cur] = 1;
    int nx = -1;
    for (int v: nxt[cur]) if(!vis[v]) {
      nx = v;
      break;
    }
    cur = nx;
    if (nx == -1) break;
  }
  return res;
}

inline bool can(int i, int j) {
  switch(ip[i].d) {
    case '<':
      return ip[i].x > ip[j].x && ip[i].y == ip[j].y;
    case 'v':
      return ip[i].x == ip[j].x && ip[i].y < ip[j].y;
    case '>':
      return ip[i].x < ip[j].x && ip[i].y == ip[j].y;
    default:
      return ip[i].x == ip[j].x && ip[i].y > ip[j].y;
  }
  return 0;
}

typedef long long LL;
inline LL dis(int i, int j) {
  return (LL)abs(ip[i].x-ip[j].x) + (LL)abs(ip[i].y-ip[j].y);
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    ip[i].read();
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) if (j != i) {
      if (can(i, j)) {
        nxt[i].push_back(j);
      }
    }
    sort(nxt[i].begin(), nxt[i].end(), [&](int a, int b) {
      return dis(i, a) < dis(i, b);
    });
  }
  int mx = 0;
  for (int i = 0; i < n; ++i) {
    int tmp = go(i);
    mx = max(mx, tmp);
  }
  cout << mx << endl;
}
