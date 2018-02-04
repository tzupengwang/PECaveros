#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 2e5+2;

inline LL getint(){
  LL _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
int n, k;
LL T;
bitset<N> f, F, tF, msk;
int x[N];

void predo() {
  for (int i = 0; i < n; ++i) msk[i] = 1;
  for (int i = 0; i < k; ++i) f[i] = 1;
  F[0] = 1;
  LL tt = T;
  while (tt) {
    if (tt&1) {
      tF.reset();
      if( F.count() < f.count() ){
        for (int i = 0; i < n; ++i) if (F[i])
          tF ^= (f << i);
      }else{
        for (int i = 0; i < n; ++i) if (f[i])
          tF ^= (F << i);
      }
      F = (tF ^ (tF >> n)) & msk;
      //polyop.Mul(n, f, n, F, F);
      //for (int i = n; i < n+n; ++i) F[i-n] += F[i];
      //for (int i = 0; i < n; ++i) F[i] &= 1;
    }
    tF.reset();
    for (int i = 0; i < n; ++i) if (f[i]) 
      tF ^= (f << i);
    f = (tF ^ (tF >> n)) & msk;
    //polyop.Mul(n, f, n, f, f);
    //for (int i = n; i < n+n; ++i) f[i-n] += f[i];
    //for (int i = 0; i < n; ++i) f[i] &= 1;
    //printf("tt %lld\n", tt);
    tt >>= 1;
  }
  //for (int i = 0; i < n; ++i) printf("%c", "01"[F[i]]); puts("");
}

int y[N];
bitset<N> xb, yb;

void solve() {

  for (int b = 0; b < 30; ++b) {
    for (int i = 0; i < n; ++i) xb[i+n] = xb[i] = ((x[i]>>b)&1);
    yb.reset();
    for (int i = 0; i < n; ++i) if (F[i]) {
      yb ^= (xb>>i);
    }
    for (int i = 0; i < n; ++i) if (yb[i]) y[i] |= (1<<b);
  }
  for (int i = 0; i < n; ++i) printf("%d%c", y[i], " \n"[i+1==n]);
}

int main(){
  //scanf("%d%d%lld", &n, &k, &T);
  n = getint();
  k = getint();
  T = getint();
  for (int i = 0; i < n; ++i)
    x[ i ] = getint();
    //scanf("%d", x+i);
  //n = 100000, k = 90000, T = (1LL<<60)-1;
  //for (int i = 0; i < n; ++i) x[i] = rand()*rand() % (int(1e9));
  predo();
  //exit(0);
  solve();
}
