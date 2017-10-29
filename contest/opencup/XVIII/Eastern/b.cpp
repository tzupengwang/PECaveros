#include <bits/stdc++.h>

using namespace std;

const int N = 5e5+10;

int n;
char s[N];
set<int> ls, rs;

int main() {
  scanf("%s", s+1);
  n = strlen(s+1);
  for (int i = 1; i <= n; ++i) {
    if (s[i] == '(') ls.insert(i);
    else rs.insert(i);
  }
  int q;
  scanf("%d", &q);
  auto prv = [&] (int x, set<int>& st) {
    auto it = st.upper_bound(x);
    if (it == st.begin()) return -1;
    it--;
    return *it;
  };
  while (q--) {
    int L, R;
    scanf("%d%d", &L, &R);
    int ans = 0;
    do {
      int tR = prv(R, rs);
      if (tR == -1 or tR < L) break;

      int tL = prv(tR, ls);

      if (tL == -1 or tL < L) break;

      auto it = rs.lower_bound(tL);
      if (it == rs.end()) break;
      tR = *it;
      if (tR > R) break;

      ls.erase(tL);
      rs.erase(tR);
      ans++;
    } while(ls.size());
    printf("%d\n", ans*2);
  }
}
