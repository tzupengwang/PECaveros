
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 3e5+10;

int n, m, A[N], B[N], C[N];
int U;
vector<int> ds;

int cl[N], cr[N], s[N];

int _cs;
void main2() {
  ds.clear();

  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", A+i, B+i);
    ds.push_back(A[i]);
    ds.push_back(B[i]);
  }
  for (int i = 1; i <= m; ++i) {
    scanf("%d", C+i);
    ds.push_back(C[i]);
  }

  sort(ds.begin(), ds.end());
  ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
  U = ds.size();

  for (int i = 1; i <= n; ++i) {
    A[i] = lower_bound(ds.begin(), ds.end(), A[i]) - ds.begin() + 1;
    B[i] = lower_bound(ds.begin(), ds.end(), B[i]) - ds.begin() + 1;
  }
  for (int i = 1; i <= m; ++i) {
    C[i] = lower_bound(ds.begin(), ds.end(), C[i]) - ds.begin() + 1;
  }

  fill(cl, cl+U+2, 0);
  fill(cr, cr+U+2, 0);
  fill(s, s+U+2, 0);

  for (int i = 1; i <= n; ++i) {
    cl[B[i]]++;

    cr[A[i]]++;
  }

  for (int i = 1; i <= m; ++i) {
    s[C[i]]++;
  }

  for (int i = 1; i <= U+1; ++i) {
    cl[i] += cl[i-1];
    s[i] += s[i-1];
  }
  for (int i = U-1; i >= 0; --i) {
    cr[i] += cr[i+1];
  }

  int val = cl[0] - s[0];

  int ans = m;

  for (int i = 1; i <= U; ++i) {
    val = max(val, cl[i-1] - s[i-1]);

    if (s[i-1] == s[i]) continue;

    int x = s[i] + cr[i + 1];

    ans = max(ans, x + val);
  }

  if (ans > n) {
    printf("Case #%d: IMPOSSIBLE!\n", ++_cs);
  } else {
    printf("Case #%d: %d\n", ++_cs, ans);
  }
}

int main(){
  int tc; scanf("%d", &tc); while (tc--) main2();

}
