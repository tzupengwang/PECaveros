#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll A, B, n;

bool ok(ll xn, ll yn, ll xe, ll ye, ll st) {
  ll a = (xn - xe);
  if (a < 0) a = -a;
  ll b = (yn - ye);
  if (b < 0) b = -b;

  ll t1 = max(a - st * (n - 1), 0LL);
  ll t2 = max(b - st * (n - 1), 0LL);
  return a < st * n && b < st * n && t1 + t2 <= st - 1;
}

ll getk(ll a, ll b) {
  ll l = 0, h = 200000;
  while (l < h) {
    ll m = (l + h) / 2;
    if (ok(0, 0, a, b, m)) h = m;
    else l = m + 1;
  }
  return l;
}

void output(ll a, ll b, ll c, ll d) {
  printf("%lld %lld %lld %lld\n", a, b, c, d);
}

void go(ll xn, ll yn, ll xe, ll ye, ll stp, ll dir, ll dx, ll dy) {
  if (xe > xn) dx = (n - 1);
  if (xe < xn) dx = -(n - 1);

  if (ye > yn) dy = (n - 1);
  if (ye < yn) dy = -(n - 1);

  ll xt = xn + dx, yt = yn + dy;

  if (stp == 1) {
    if (dir == 0) {
      ll delx = xe - xt;
      if (yn == ye) delx = 0;
      output(xt + delx, yt, xn + delx, yn);
    } else {
      ll dely = ye - yt;
      if (xn == xe) dely = 0;
      output(xn, yn + dely, xt, yt + dely);
    }
  } else {
    if (dir == 0) {
      output(xt, yt, xn, yn);
    } else output(xn, yn, xt, yt);

    dx /= (n - 1);
    dy /= (n - 1);
    if (ok(xt + dx, yt, xe, ye, stp - 1))
      go(xt + dx, yt, xe, ye, stp - 1, 1, dx * (n - 1), dy * (n - 1));
    else 
      go(xt, yt + dy, xe, ye, stp - 1, 0, dx * (n - 1), dy * (n - 1));
  }
}

int main() {
  int T; scanf("%d", &T); while (T --) {
    scanf("%lld%lld%lld", &A, &B, &n);

    ll stp = getk(A, B);

    printf("%lld\n", stp);
    go(0, 0, A, B, stp, 0, n - 1, n - 1);
  }
}
