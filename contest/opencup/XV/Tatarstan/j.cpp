
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL, int> pLi;
typedef pair<int, int> pii;

pii gcd(int a, int b){
	if(b == 0) return {1, 0};
  pii q = gcd(b, a % b);
  return {q.second, q.first - q.second * (a / b)};
}
inline int mul(LL a, int b, int mod) {
  a *= b;
  if (a >= mod) a %= mod;
  return a;
}

inline int pw(int a, LL b, int mod) {
  int res = 1;
  for (; b; b >>= 1) {
    if (b&1) res = mul(res, a, mod);
    a = mul(a, a, mod);
  }
  return res;
}

const int M = 1e6+10;

int facnop[M];

void predo(int pe, int p) {
  facnop[0] = 1;
  for (int i = 1; i <= pe; ++i) {
    facnop[i] = mul(facnop[i-1], i%p == 0? 1: i, pe);
  }
}

pLi f(LL n, int pe, int p) {
  if (n < p) return {0, facnop[n]};
  pLi tp = f(n/p, pe, p);
  tp.first += n/p;
  LL k = n / pe;
  LL tmp = pw(facnop[pe-1], k, pe);
  tmp = mul(tmp, facnop[n % pe], pe);
  tp.second = mul(tp.second, tmp, pe);
  return tp;
}

int C(LL n, LL m, int pe, int p) {
  predo(pe, p);
  int phi = pe / p * (p-1);
  pLi A = f(n, pe, p);
  pLi B = f(n-m, pe, p);
  pLi C = f(m, pe, p);
  LL k = A.first - B.first - C.first;
  int iB = pw(B.second, phi-1, pe);
  int iC = pw(C.second, phi-1, pe);

  int e = 1;
  for (int tp = p; tp < pe; tp *= p, ++e);
  if (k >= e) return 0;

  int res = A.second;
  res = mul(res, iB, pe);
  res = mul(res, iC, pe);
  res = mul(res, pw(p, k, pe), pe);
  return res;
}

int __lcm(int a, int b) {
  return a * (b / __gcd(a, b));
}

int solve(int x1, int m1, int x2, int m2) {
  pii p = gcd(m1, m2);
  //printf("solve %d %d %d %d\n", x1, m1, x2, m2);
  //cout << p.first << " " << p.second << endl;
  int lcm = m1 * m2;
  LL scale = (LL)(x2 - x1);
  LL res = (LL)p.first * scale * m1 + x1;
  res %= lcm;
  if (res < 0) res += lcm;
  return res;
}

int x[30], m[30];

LL c[100][100];

int solve(LL n, LL k, int mod) {
  int cur = mod;
  int l = 0;
  for (int i = 2; i <= cur; ++i) if (cur % i == 0) {
    int p = i;
    int pe = 1;
    while (cur % p == 0) {
      cur /= p;
      pe *= p;
    }
    ++l;
    m[l] = pe;
    x[l] = C(n, k, pe, p);
    //printf("x %d m %d\n", x[l], pe);
  }
  int x1 = x[1];
  int m1 = m[1];
  for (int i = 2; i <= l; ++i) {
    x1 = solve(x1, m1, x[i], m[i]);
    m1 = __lcm(m1, m[i]);
  }
  return x1;
}

void test() {
  c[0][0] = 1;
  for (int i = 1; i < 50; ++i) {
    c[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      c[i][j] = c[i-1][j] + c[i-1][j-1];
      LL mod = rand() % 999998 + 2;
      LL ans = solve(i, j, mod);
      if (c[i][j] % mod != ans) {
        printf("WTF %d %d %lld %d %d\n", i, j, mod, c[i][j]%mod, ans);
        // exit(0);
      }
    }
  }
}

int main() {
 //test();
  LL n, k;
  int mod;
  cin >> n >> k >> mod;
  cout << solve(n, k, mod) << endl;
}
