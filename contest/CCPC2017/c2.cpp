
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int M = 16;
const int S = (1<<15);
const int N = 1e5+10;
const int MOD = 1e9+7;

inline int add(int a,int b){a+=b;return a>=MOD?a-MOD:a;}
inline int sub(int a,int b){a-=b;return a<0?a+MOD:a;}
inline int mul(LL a,int b){a*=b;return a>=MOD?a%MOD:a;}

inline int bit(int a, int b){return (a>>b)&1;}

int n, m, U;
char ip[N][M];
int cnt1[S], cnt0[S];
int two[N];
int sz[S];

inline int f0(int msk) {
  int cmsk = (U-1) ^ msk;
  return cnt1[cmsk];
}

inline int f1(int msk) {
  int cmsk = (U-1) ^ msk;
  return cnt0[cmsk];
}

inline int calc(int msk) {
  int res = sub(two[n], 1);

  printf("calc %d\n", msk);

  for (int ss = msk; ss > 0; ss = (ss-1) & msk) {
    int coe = (sz[ss] % 2 == 0)? 1: (MOD - 1);

    int c0 = f0(ss);
    int c1 = f1(ss);
    printf("%d %d\n", c0, c1);
    int tmp = add(sub(two[c0], 1), sub(two[c1], 1));

    res = add(res, mul(tmp, coe));
  }

  return res;
}

int _cs;

void main2() {
  scanf("%d%d", &n, &m);
  U = (1<<m);
  fill(cnt1, cnt1+U, 0);
  fill(cnt0, cnt0+U, 0);

  for (int i = 0; i < n; ++i) {
    scanf("%s", ip[i]);
    int msk = 0;
    for (int j = 0; j < m; ++j) if (ip[i][j] == 'Y') {
      msk |= (1 << j);
    }

    cnt1[msk]++;

    int cmsk = (U-1) ^ msk;

    cnt0[cmsk]++;
  }

  for (int k = 0; k < m; ++k) {
    for (int msk = 0; msk < U; msk++) if (bit(msk, k)) {
      cnt1[msk] = add(cnt1[msk], cnt1[msk ^ (1 << k)]);
      cnt0[msk] = add(cnt0[msk], cnt0[msk ^ (1 << k)]);
    }
  }

  int ans = 0;

  for (int msk = 1; msk < U; ++msk) {
    ans ^= calc(msk);
  }

  printf("Case #%d: %d\n", ++_cs, ans);
}

int main(){
  two[0] = 1;
  for (int i = 1; i < N; ++i) two[i] = add(two[i-1], two[i-1]);

  sz[0] = 0;
  for (int i = 1; i < S; ++i) sz[i] = 1 + sz[i - (i&-i)];

  int tc; scanf("%d", &tc); while(tc--) main2();
}
