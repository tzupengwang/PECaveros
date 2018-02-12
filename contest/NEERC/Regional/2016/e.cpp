
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e5+10;

int n, q;
int t[N], c[N];
LL s[N], a[N];
int ord[N];

LL ss[N], sa[N];
vector<pair<LL,int>> oo;

int main(){
#define FN "expect"
#ifndef LOCAL
  freopen( FN ".in" , "r" , stdin );
  freopen( FN ".out" , "w" , stdout );
#endif
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    char tp[2];
    scanf("%s%d%d", tp, t+i, c+i);
    ord[i] = i;
    if (*tp == '+') c[i] = -c[i];
    s[i] = c[i] + s[i-1];
    oo.push_back({s[i], i});
  }
  for (int i = 1; i <= n; ++i) a[i] = t[i+1] - t[i];
  sort(ord+1, ord+1+n, [&](int i,int j) { return tie(s[i],i) < tie(s[j],j); });
  sort(oo.begin(), oo.end());
  ss[n+1] = sa[n+1] = 0;
  for (int i = n; i >= 1; --i) {
    ss[i] = ss[i+1] + s[ord[i]] * a[ord[i]];
    sa[i] = sa[i+1] + a[ord[i]];
  }

  for (int i = 0; i < q; ++i) {
    int x; scanf("%d", &x);
    if (x < s[n]) {
      puts("INFINITY");
      continue;
    }
    int j = upper_bound(oo.begin(), oo.end(), make_pair((LL)x, N)) - oo.begin();
    j++;
    LL ans = ss[j] - sa[j] * x;
    printf("%lld\n", ans);
  }
}
