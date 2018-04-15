#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int M = 16;
const int S = (1<<15);
const int S3 = 2e7;
const int N = 1e5+10;
const int MOD = 1e9+7;

inline int add(int a,int b){a+=b;return a>=MOD?a-MOD:a;}
inline int sub(int a,int b){a-=b;return a<0?a+MOD:a;}
inline int mul(LL a,int b){a*=b;return a>=MOD?a%MOD:a;}

inline int bit(int a, int b){return (a>>b)&1;}

int n, m, U, U3;
char ip[N][M];
int cnt1[S], cnt0[S];
int two[N], three[N];
int ST3[S];
int sz[S];
int bt[S];
int dp[S3];

int dp2[S];

void dfs(int i, int st2, int st3, int lst2) {
  if (i == m) {
    if (lst2 == -1) {
      dp[st3] = cnt1[st2];
    } else {
      int p0 = st3 - 2 * three[lst2];
      int p1 = p0 + three[lst2];

      dp[st3] = dp[p0] + dp[p1];
    }
    return;
  }

  dfs(i+1, st2, st3, lst2);

  dfs(i+1, st2 | (1<<i), st3 + three[i], lst2);

  dfs(i+1, st2, st3 + 2 * three[i], i);
}

inline int calc(int msk) {
  int res = sub(two[n], 1);

//  printf("calc %d\n", msk);

  for (int ss = msk; ss > 0; ss = (ss-1) & msk) {
    int coe = (sz[ss] % 2 == 0)? 1: (MOD - 1);
    int tmp = dp2[ss];

    res = add(res, mul(tmp, coe));
  }

  return res;
}

int _cs;

void main2() {
  scanf("%d%d", &n, &m);
  //n = 100000;
  //m = 15;

  U = (1<<m);

  fill(cnt1, cnt1+U, 0);
  fill(cnt0, cnt0+U, 0);

  U3 = 0;
  for (int i = 0; i < m; ++i) U3 += three[i];

  for (int i = 0; i < n; ++i) {
    scanf("%s", ip[i]);
    int msk = 0;
    for (int j = 0; j < m; ++j) if (ip[i][j] == 'Y') {
      msk |= (1 << j);
    }
    //msk = rand() % U;

    cnt1[msk]++;
  }

  dfs(0, 0, 0, -1);

  for (int msk = 1; msk < U; ++msk) {
    int com = (U-1) ^ msk;

    int com3 = 2 * ST3[com];

    dp2[msk] = 0;

    for (int ss = msk; ss >= 0; ss = (ss-1) & msk) {
      int tmp_ss = ST3[ss];
      tmp_ss += com3;

      dp2[msk] = add(dp2[msk], sub(two[dp[tmp_ss]], 1));

      if (ss == 0) break;
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

  three[0] = 1;
  for (int i = 1; i < N; ++i) three[i] = mul(3, three[i-1]);

  sz[0] = 0;
  for (int i = 1; i < S; ++i) sz[i] = 1 + sz[i - (i&-i)];

  for (int i = 0; i < 15; ++i) bt[(1<<i)] = i;

  for (int i = 1; i < S; ++i) {
    int pi = bt[(i&-i)];
    ST3[i] = ST3[i ^ (i&-i)] + three[pi];
  }

  int tc; scanf("%d", &tc); while(tc--) main2();
}
