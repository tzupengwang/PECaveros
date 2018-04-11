#include <bits/stdc++.h>

using namespace std;

const int N = 1e6;
const int S = 11;

int n, s, m;
char ip[S][N];
int ord[S];
vector<int> fails[N];
int fail[N];

void proc(char *str, vector<int> &res) {
  int j = -1;
  fail[0] = -1;
  for (int i = 1; i < m; ++i) {
    while (j >= 0 && str[i] != str[j + 1]) j = fail[j];
    if (str[i] == str[j + 1]) ++j;
    fail[i] = j;
  }
  int cur = fail[m-1];
  while (cur >= 0) {
    if (m + m - (cur + 1) <= n) res.push_back(cur + 1);
    cur = fail[cur];
  }
  sort(res.begin(), res.end(), greater<int>());
}

void build() {
  for (int i = 0; i < s; ++i) {
    proc(ip[i], fails[i]);
  }
}

inline bool cmp(int a, int b) {
  if (fails[a] == fails[b]) return a < b;
  return fails[a] < fails[b];
}

int main() {
  scanf("%d%d", &n, &s);
  for (int i = 0; i < s; ++i) scanf("%s", ip[i]), ord[i] = i;
  m = strlen(ip[0]);
  build();
  sort(ord, ord+s, cmp);
  for (int i = 0; i < s; ++i)
    printf("%s\n", ip[ord[i]]);
}
