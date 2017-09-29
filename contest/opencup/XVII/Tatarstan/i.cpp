#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;

#define SZ(c) ((int)(c).size())
struct Maxflow {
  static const int MAXV = 300010;
  static const int INF  = 1000000;
  struct Edge {
    int v, c, r;
    Edge(int _v, int _c, int _r):
      v(_v), c(_c), r(_r) {}
  };
  int s, t;
  vector<Edge> G[MAXV*2];
  int iter[MAXV*2], d[MAXV*2], gap[MAXV*2], tot;
  void init(int x) {
    tot = x+2;
    s = x+1, t = x+2;
    for(int i = 0; i <= tot; i++) {
      G[i].clear();
      iter[i] = d[i] = gap[i] = 0;
    }
  }
  void addEdge(int u, int v, int c) {
    G[u].push_back(Edge(v, c, SZ(G[v]) ));
    G[v].push_back(Edge(u, 0, SZ(G[u]) - 1));
  }
  int dfs(int p, int flow) {
    if(p == t) return flow;
    for(int &i = iter[p]; i < SZ(G[p]); i++) {
      Edge &e = G[p][i];
      if(e.c > 0 && d[p] == d[e.v]+1) {
        int f = dfs(e.v, min(flow, e.c));
        if(f) {
          e.c -= f;
          G[e.v][e.r].c += f;
          return f;
        }
      }
    }
    if( (--gap[d[p]]) == 0) d[s] = tot;
    else {
      d[p]++;
      iter[p] = 0;
      ++gap[d[p]];
    }
    return 0;
  }
  int solve() {
    int res = 0;
    gap[0] = tot;
    for(res = 0; d[s] < tot; res += dfs(s, INF));
    return res;
  }
} flow;

const LL P1 = 1e9+7;
const LL P2 = 1e9+9;
const LL BS = 13131;

const int N = 220;
const int L = 2e5 + 10;

int n;
int len[N];
string ip[N];

void input() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> ip[i];
    len[i] = ip[i].size();
    ip[i] += ip[i];
  }
}

template<LL P>
struct Hsh {
  int len;
  LL *pw, *hsh;
  inline LL add(LL a, LL b) {
    a += b;
    if (a >= P) a -= P;
    return a;
  }
  inline LL mul(LL a, LL b) {
    a *= b;
    if (a >= P) a %= P;
    return a;
  }
  inline LL sub(LL a, LL b) {
    a -= b;
    if (a < 0) a += P;
    return a;
  }
  void init(const string& s) {
    len = s.size();
    pw = new LL[len + 1];
    hsh = new LL[len + 1];
    pw[0] = 1;
    hsh[0] = 0;
    for (int i = 1; i <= len; ++i) {
      pw[i] = mul(BS, pw[i-1]);
      hsh[i] = add(s[i-1], mul(BS, hsh[i-1]));
    }
  }
  inline LL get(int l, int r) {
    return sub(hsh[r], mul(hsh[l-1], pw[r-l+1]));
  }
};

Hsh<P1> hsh1[N];
Hsh<P2> hsh2[N];
vector<int> pres[N];

void predo() {
  for (int i = 1; i <= n; ++i) {
    hsh1[i].init(ip[i]);
    hsh2[i].init(ip[i]);
  }
}

map<PLL, int> mp;

inline void get_pres(int id, int k) {
  pres[id].clear();
  k = min(k, len[id]);

  for (int i = 1; i <= len[id]; ++i) {
    LL h1 = hsh1[id].get(i, i+k-1);
    LL h2 = hsh2[id].get(i, i+k-1);

    PLL p{h1, h2};

    int sid = mp.size() + 1;
    if (mp.count(p)) sid = mp[p];
    else mp[p] = sid;

    pres[id].push_back(sid);
  }
}

void make_flow() {
  int m = mp.size();
  flow.init(n + m);
  for (int i = 1; i <= n; ++i) {
    flow.addEdge(flow.s, i, 1);
    for (int j: pres[i]) {
      flow.addEdge(i, n + j, 1);
    }
  }
  for (int i = 1; i <= m; ++i) {
    flow.addEdge(n + i, flow.t, 1);
  }
}

bool chk(int k) {
  mp.clear();
  for (int i = 1; i <= n; ++i) {
    get_pres(i, k);
  }
  make_flow();
  int mxf = flow.solve();
  return mxf >= n;
}

void solve() {
  int l = 1, r = *max_element(len + 1, len + 1 + n);
  int ans = -1;
  while (l <= r) {
    int mid = ( l+r ) / 2;
    if (chk(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << endl;
}

int main() {
  input();
  predo();
  solve();
}
