#include <bits/stdc++.h>

using namespace std;

const int N = 3e5+10;
typedef long long ll;

char pat[N], txt[N];
int nxt[N][100];
int L, n;

inline int enc(char c) {
  if (c == ' ') return -1;
  return (int)c - (int)'!';
}

int main() {
  scanf("%s", pat);
  L = strlen(pat);
  copy(pat, pat+L, pat+L);
  copy(pat, pat+L, pat+L+L);
  for (int i = 0; i < 100; ++i) {
    nxt[L+L+L][i] = L+L+L;
  }
  for (int i = L+L+L-1; i >= 0; --i) {
    copy(nxt[i+1], nxt[i+1]+100, nxt[i]);
    nxt[i][enc(pat[i])] = i;
  }
  ll cur_t = 0;
  fgets(txt, N, stdin);
  while (fgets(txt, N, stdin) != NULL) {
    int s = cur_t % L;
    n = strlen(txt) - 1;
    txt[n] = 0;
    int mx = 0;
    for (int i = 0; i < n; ++i) {
      if (txt[i] != ' ') {
        int dif = nxt[s + i][enc(txt[i])] - (s + i);
        //printf("%d %d %d %d\n", i, dif, enc(txt[i]), enc(pat[s+i]));
        mx = max(mx, dif);
      }
    }
    //printf("::%s:: %d\n", txt, mx);
    cur_t += mx + 1;
  }
  cout << cur_t << endl;
}
