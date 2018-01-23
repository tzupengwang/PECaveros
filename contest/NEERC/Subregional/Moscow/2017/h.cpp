#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;

const int M = 1e5+10;

LL T, n;
int m;
LL qa[M], qb[M];

inline LL f(LL a, LL b) {
  if (a > b) return 0;
  return ((a+b) * (b-a+1)) / 2;
}

inline PLL add(PLL a, PLL b) {
  return {a.first + b.first, a.second + b.second};
}

inline bool okay(PLL a) {
  return a.first <= T and T <= a.second;
}

inline PLL tail(LL a, LL k) {
  if (k == 0) return {0, 0};
  LL mx = f(a+1, a+k);
  LL mn = f(max(a-k, 0LL), max(a-1, 0LL));
  return {mn, mx};
}

void fail() {
  puts("No");
  exit(0);
}

inline PLL calc(LL a, LL b, LL k) {
  //printf("calc %lld %lld %lld\n", a, b, k);
  if (k == 0) return {0, 0};
  if (a > b) swap(a, b);
  if (b-a > k) fail();
  LL mx = 0, mn = 0;
  {
    LL tmp = b-a+k;
    LL t = tmp / 2;
    if (tmp == k+k) mx = f(a+1, a+t-1);
    else mx = f(a+1, a+t) + f(b+1, b+(k-t-1));
  }
  {
    if (a <= k-b) {
      mn = f(0, a-1) + f(0, b-1);
    } else {
      LL tmp = a - b + k;
      LL t = tmp / 2;
      //printf("  t %lld\n", t);
      if (tmp == 0) mn = f(a+1, b-1);
      else mn = f(a - t, a - 1) + f(b - (k-t-1), b-1);
    }
  }
  //printf("calc %lld %lld %lld -> %lld %lld\n", a, b, k, mn, mx);
  return {mn, mx};
}

int main() {
  scanf("%lld%lld%d", &T, &n, &m);
  PLL cur = {0, 0};
  for (int i = 1; i <= m; ++i) {
    scanf("%lld%lld", qa+i, qb+i);
    cur = add(cur, {qb[i], qb[i]});
  }
  cur = add(cur, tail(qb[1], qa[1] - 1));
  cur = add(cur, tail(qb[m], n - qa[m]));
  //printf("%lld %lld\n", cur.first, cur.second);
  if (T < cur.first) fail();
  for (int i = 1; i <= m-1; ++i) {
    cur = add(cur, calc(qb[i], qb[i+1], qa[i+1] - qa[i]));
    if (T < cur.first) fail();
  }
  if (okay(cur)) puts("Yes");
  else puts("No");
}
