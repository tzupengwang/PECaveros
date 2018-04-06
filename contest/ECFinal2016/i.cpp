#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1000000007;
inline int add( int ai , int bi ){
  ai += bi;
  return ai >= mod ? ai - mod : ai;
}
inline int sub( int ai , int bi ){
  ai -= bi;
  return ai < 0 ? ai + mod : ai;
}
inline int mul( LL ai , int bi ){
  ai *= bi;
  return ai >= mod ? ai % mod : ai;
}
inline int mpow( int ai , int bi ){
  int ret = 1;
  while( bi ){
    if( bi & 1 ) ret = mul( ret , ai );
    ai = mul( ai , ai );
    bi >>= 1;
  }
  return ret;
}
inline int inv(int a) { return mpow(a, mod-2); }

const int MAXN = (1<<16);
typedef double ld;
typedef complex<ld> cplx;
const ld PI = acosl(-1);
const cplx I(0, 1);

cplx omega[MAXN+1];

void pre_fft(){
  for(int i=0; i<=MAXN; i++)
    omega[i] = exp(i * 2 * PI / MAXN * I);
}

void fft(int n, cplx a[], bool inv=false){
  int basic = MAXN / n;
  int theta = basic;
  for (int m = n; m >= 2; m >>= 1) {
    int mh = m >> 1;
    for (int i = 0; i < mh; i++) {
      cplx w = omega[inv ? MAXN-(i*theta%MAXN)
                         : i*theta%MAXN];
      for (int j = i; j < n; j += m) {
        int k = j + mh;
        cplx x = a[j] - a[k];
        a[j] += a[k];
        a[k] = w * x;
      }
    }
    theta = (theta * 2) % MAXN;
  }
  int i = 0;
  for (int j = 1; j < n - 1; j++) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1);
    if (j < i) swap(a[i], a[j]);
  }
  if (inv)
    for (i = 0; i < n; i++)
      a[i] /= n;
}


const int M = 111;
const int K = 2e5+10;

int n, m, P, G;
int c[M];

void mul(LL a[], LL b[], LL res[]) {
  static cplx A[MAXN], B[MAXN];
  int D = 1; while (D < 2*G) D <<= 1;
  for (int i = 0; i < D; ++i) A[i] = cplx(0, 0);
  for (int i = 0; i < D; ++i) B[i] = cplx(0, 0);
  for (int i = 0; i < G; ++i) A[i] = cplx(a[i], 0);
  for (int i = 0; i < G; ++i) B[i] = cplx(b[i], 0);
  fft(D, A);
  fft(D, B);
  for (int i = 0; i < D; ++i) A[i] *= B[i];
  fft(D, A, 1);
  fill(res, res+G, 0);
  for (int i = 0; i < D; ++i) {
    LL x = round(A[i].real());
    res[i % G] = res[i % G] + x;
  }
}

void mul(int a[], int b[]) {
  static LL ta[2][MAXN], tb[2][MAXN], tmp[MAXN];
  for (int i = 0; i < G; ++i) {
    ta[1][i] = a[i] >> 15;
    ta[0][i] = a[i] & (0x7fff);
    tb[1][i] = b[i] >> 15;
    tb[0][i] = b[i] & (0x7fff);
  }
  fill(a, a+G, 0);
  mul(ta[1], tb[1], tmp);
  for (int i = 0; i < G; ++i) {
    LL tx = (tmp[i] % mod + mod) % mod;
    tx <<= 30; tx %= mod;
    a[i] = add(a[i], tx);
  }
  mul(ta[1], tb[0], tmp);
  for (int i = 0; i < G; ++i) {
    LL tx = (tmp[i] % mod + mod) % mod;
    tx <<= 15; tx %= mod;
    a[i] = add(a[i], tx);
  }
  mul(ta[0], tb[1], tmp);
  for (int i = 0; i < G; ++i) {
    LL tx = (tmp[i] % mod + mod) % mod;
    tx <<= 15; tx %= mod;
    a[i] = add(a[i], tx);
  }
  mul(ta[0], tb[0], tmp);
  for (int i = 0; i < G; ++i) {
    LL tx = (tmp[i] % mod + mod) % mod;
    a[i] = add(a[i], tx);
  }
}

void build() {
  pre_fft();
}

void init() {
  scanf("%d%d%d", &n, &m, &P);
  G = 0;
  for (int i = 1; i <= m; ++i) {
    scanf("%d", c+i);
    G = __gcd(G, c[i]);
  }
  //printf("G %d\n", G);
}

bitset<K> can;
int nxt[K];

int dp[MAXN], base[MAXN], tdp[MAXN];

void build_dp() {
  fill(dp, dp+G, 0);
  dp[0] = 1;
  fill(base, base+G, 0);
  base[0] = 100 - P;
  base[1 % G] += P;
  for (int e = n; e; e >>= 1) {
    if (e & 1) mul(dp, base);
    mul(base, base);
  }
}

int _cs;

void solve() {
  can.reset();
  can[0] = 1;
  for (int i = 1; i <= m; ++i) {
    for (int j = 0; j < K; ++j) if (j >= c[i] && can[j - c[i]])
      can[j] = 1;
  }
  nxt[K-1] = K;
  for (int i = K-1; i >= 1; --i) {
    if (can[i]) nxt[i] = i;
    else if (i+1 < K) nxt[i] = nxt[i+1];
  }
  build_dp();
  int ans = 0;
  for (int r = 1; r < G; ++r) {
    int tmp = mul(G - r, dp[r]);
    ans = add(ans, tmp);
  }
  int way = mpow(100 - P, n);
  for (int i = 1; i <= min(n, K/2); ++i) {
    way = mul(way, P);
    way = mul(way, inv(100 - P));
    way = mul(way, n - i + 1);
    way = mul(way, inv(i));
    if (P == 0 && i == 0) way = mpow(100, n);
    if (P == 100 && i == n) way = mpow(100, n);
    int ori_cst = (G - i % G) % G;
    int real_cst = nxt[i] - i;
    int dlt = sub(real_cst, ori_cst);
    ans = add(ans, mul(dlt, way));
  }
  printf("Case #%d: %d\n", ++_cs, ans);
}

int main(){
  build();
  int t; scanf( "%d" , &t ); while( t -- ){
    init();
    solve();
  }
}
