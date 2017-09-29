#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

inline LL getint(){
  LL _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}

inline int add( int a , int b , int P ){
  a += b;
  return a >= P ? a - P : a;
}
inline int mul( LL a , int b , int P ){
  a *= b;
  return a >= P ? a % P : a;
}

template<LL P, LL root, int MAXN>
struct NTT{
  static LL bigmod(LL a, LL b) {
    LL res = 1;
    for (LL bs = a; b; b >>= 1, bs = mul( bs , bs , P ) ) {
      if(b&1) res = mul( res , bs , P );
        //res=(res*bs)%P;
    }
    return res;
  }
  static LL inv(LL a, LL b) {
    if(a==1)return 1;
    return (((LL)(a-inv(b%a,a))*b+1)/a)%b;
  }
  LL omega[MAXN+1];
  NTT() {
    omega[0] = 1;
    LL r = bigmod(root, (P-1)/MAXN);
    for (int i=1; i<=MAXN; i++)
      omega[i] = mul(omega[i-1],r,P);
  }
  // n must be 2^k
  void tran(int n, LL a[], bool inv_ntt=false){
    int basic = MAXN / n;
    int theta = basic;
    for (int m = n; m >= 2; m >>= 1) {
      int mh = m >> 1;
      for (int i = 0; i < mh; i++) {
        LL w = omega[(i*theta)&(MAXN-1)];
        for (int j = i; j < n; j += m) {
          int k = j + mh;
          LL x = a[j] - a[k];
          if (x < 0) x += P;
          a[j] += a[k];
          if (a[j] > P) a[j] -= P;
          a[k] = mul(w , x , P);
        }
      }
      theta = (theta * 2) & (MAXN-1);
    }
    int i = 0;
    for (int j = 1; j < n - 1; j++) {
      for (int k = n >> 1; k > (i ^= k); k >>= 1);
      if (j < i) swap(a[i], a[j]);
    }
    if (inv_ntt) {
      LL ni = inv(n,P);
      reverse( a+1 , a+n );
      for (i = 0; i < n; i++)
        a[i] = mul(a[i] , ni, P);
    }
  }
  void operator()(int n, LL a[], bool inv_ntt=false) {
    tran(n, a, inv_ntt);
  }
};

const LL P = 1000210433;
const LL root = 3;
const int MAXN = 2048;

NTT<P, root, MAXN> ntt;

struct XD {
  int l, r, d, u;
  bool operator<(const XD& a) const {
    return l < a.l;
  }
};

vector<XD> xds;
int n, A, m;
LL ans[MAXN+5];

void push(XD xd) {
  vector<XD> res{xd};

  bool isin = 0;
  for (XD it: xds) {
    if (it.r < xd.l or xd.r < it.l) {
      res.push_back(it);
      continue;
    }
    else if (xd.l <= it.l and it.r <= xd.r) {
      continue;
    }
    else if (xd.l <= it.l and xd.r <= it.r) {
      XD tmp = it;
      tmp.l = xd.r + 1;
      if (tmp.l <= tmp.r) {
        res.push_back(tmp);
      }
    }
    else if (it.l <= xd.l and it.r <= xd.r) {
      XD tmp = it;
      tmp.r = xd.l - 1;
      if (tmp.l <= tmp.r) {
        res.push_back(tmp);
      }
    }
    else {
      XD tmpl = it;
      XD tmpr = it;
      tmpl.r = xd.l - 1;
      if (tmpl.l <= tmpl.r) {
        res.push_back(tmpl);
      }
      tmpr.l = xd.r + 1;
      if (tmpr.l <= tmpr.r) {
        res.push_back(tmpr);
      }
    }
  }
  sort(res.begin(), res.end());

  xds.swap(res);
}

void sq(LL a[MAXN+5]) {
  ntt(MAXN, a);
  for (int i = 0; i < MAXN; ++i) {
    a[ i ] = mul( a[ i ] , a[ i ] , P );
    //a[i] *= a[i];
    //a[i] %= P;
  }
  ntt(MAXN, a, 1);
  fill(a + 1024, a + MAXN, 0);
}

void mul(LL a[MAXN+5], LL b[MAXN+5]) {
  ntt(MAXN, a);
  ntt(MAXN, b);
  for (int i = 0; i < MAXN; ++i) {
    a[ i ] = mul( a[ i ] , b[ i ] , P );
    //a[i] *= b[i];
    //a[i] %= P;
  }
  ntt(MAXN, a, 1);
  ntt(MAXN, b, 1);
  fill(a + 1024, a + MAXN, 0);
}

void pow(LL g[MAXN+5], int pw) {
  static LL bs[MAXN+5], res[MAXN+5];
  fill(res, res+MAXN, 0);
  res[0] = 1;
  for (int i = 0; i < MAXN; ++i) {
    bs[i] = g[i];
  }
  while (pw) {
    if (pw & 1) {
      mul(res, bs);
    }
    sq(bs);
    pw >>= 1;
  }
  for (int i = 0; i < MAXN; ++i) {
    g[i] = res[i];
  }
}

LL f[MAXN+5], g[MAXN+5];

void calc() {
  fill(f, f+MAXN, 0);
  f[0] = 1;
  for (XD xd: xds) {
    fill(g, g+MAXN, 0);
    fill(g + xd.d, g + xd.u + 1, 1);

    int pw = xd.r - xd.l + 1;
    pow(g, pw);

    mul(f, g);
  }
}

int main() {
  //ios_base::sync_with_stdio(0);
  n = getint();
  A = getint();
  m = getint();
  //n = 1000000000;
  //A = 1000;
  //m = 100000;
  //cin >> n >> A >> m;
  xds.push_back({1, n, 0, 1000});
  calc();
  for( int i = 0 ; i < m ; i ++ ){
  //while (m--) {
    int tp = getint();
    //int tp = i < 30;
    //int tp;
    //cin >> tp;
    if (tp == 1) {
      int l = getint();
      int r = getint();
      int d = getint();
      int u = getint();
      //int l = rand() % 1000 + 10;
      //int r = 1e9 - rand() % 1000;
      //int d = 0;
      //int u = rand() % 1000 + 1;
      //int l, r, d, u;
      //cin >> l >> r >> d >> u;
      XD xd{l, r, d, u};
      push(xd);
      calc();
    } else {
      //A = 1000;
      A = getint();
      //cin >> A;
    }
    printf( "%lld\n" , f[A] );
    //cout << f[A] << '\n';
  }
}
