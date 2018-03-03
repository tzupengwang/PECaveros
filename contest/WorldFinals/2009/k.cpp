
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int RR = 111;
const int N = 222;
const int L = 22;
const LL INF = 1e16;

int NR, tot;
string S, T, X[RR], Y[RR];

vector<string> ss[L];

void adds(string s) {
  for (int i = 0; i < s.size(); ++i) {
    int tl = s.size() - i;
    ss[tl].push_back(s.substr(i));
  }
}

inline int id(const string& s) {
  int tl = s.size();
  if (!tl) return 0;
  return lower_bound(ss[tl].begin(), ss[tl].end(), s) - ss[tl].begin();
}

int _cs = 0;
LL dis[L][N][N];

void main2() {
  tot = S.size();
  for (int i = 0; i <= tot; ++i) ss[i].clear();
  for (int i = 0; i < NR; ++i) {
    cin >> X[i] >> Y[i];
  }
  adds(S);
  adds(T);
  for (int i = 0; i < NR; ++i) {
    adds(X[i]);
    adds(Y[i]);
  }
  for (int i = 0; i <= tot; ++i) {
    sort(ss[i].begin(), ss[i].end());
    ss[i].resize(unique(ss[i].begin(), ss[i].end()) - ss[i].begin());
  }
  for (int l = 1; l <= tot; ++l) {
    int tn = ss[l].size();
    for (int i = 0; i < tn; ++i) for (int j = 0; j < tn; ++j)
      dis[l][i][j] = INF;
    for (int i = 0; i < tn; ++i) dis[l][i][i] = 0;
    for (int i = 0; i < NR; ++i) {
      if (X[i].size() == l) {
        int ii = id(X[i]), jj = id(Y[i]);
        dis[l][ii][jj] = min(dis[l][ii][jj], 1LL);
      }
    }
    for (int i = 0; i < tn; ++i) for (int j = 0; j < tn; ++j) {
      if (ss[l][i][0] == ss[l][j][0]) {
        int ii = id(ss[l][i].substr(1));
        int jj = id(ss[l][j].substr(1));
        dis[l][i][j] = min(dis[l][i][j], dis[l-1][ii][jj]);
      }
    }
    for (int k = 0; k < tn; ++k) for (int i = 0; i < tn; ++i) for (int j = 0; j < tn; ++j)
      dis[l][i][j] = min(dis[l][i][j], dis[l][i][k] + dis[l][k][j]);
  }
  LL ans = dis[tot][id(S)][id(T)];
  if (ans >= INF) printf("Case %d: No solution\n", ++_cs);
  else printf("Case %d: %lld\n", ++_cs, ans);
}

int main(){
  while (cin >> S and S[0] != '.') {
    cin >> T >> NR;
    main2();
  }
}
