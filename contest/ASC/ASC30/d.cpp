#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int v[ 19 ] , til;

bool vis[22][11][11];
LL dp[22][11][11];

bool ok(LL x) {
  int cnt[10];
  fill(cnt, cnt+10, 0);
  while (x) {
    cnt[x%10]++;
    x /= 10;
  }
  return *max_element(cnt, cnt+10) <= 2;
}

LL f(int k, int a, int b) {
  if (k == 0) return 1;
  if (a + b <= 0) return 0;
  if (vis[k][a][b]) return dp[k][a][b];
  vis[k][a][b] = 1;
  LL r1 = 0, r2 = 0;
  if (a) r1 = a * f(k-1, a-1, b);
  if (b) r2 = b * f(k-1, a+1, b-1);
  return dp[k][a][b] = r1 + r2;
}

LL cal( LL x ){
  if( x == 0 ) return 0;
  LL tx = x;
  til = 0;
  while( tx ){
    v[ til ++ ] = tx % 10;
    tx /= 10;
  }

  LL ans = 0;
  for (int i = 0; i <= til-2; ++i) {
    ans += f(i, 1, 9) * 9;
  }
  ans += f(til-1, 1, 9) * (v[til-1] - 1);

  //printf("cal %lld %lld\n", x, ans);

  int cnt[10];
  for (int i = 0; i < 10; ++i) cnt[i] = 0;

  cnt[v[til-1]]++;

  for (int i = til-2; i >= 0; --i) {

    for (int ld = 0; ld < v[i]; ++ld) {

      int a = 0, b = 0;
      cnt[ld]++;
      bool flag = 1;
      for (int d = 0; d < 10; ++d) {
        if (cnt[d] > 2) {
          flag = 0;
          break;
        }
        if (cnt[d] == 1) a++;
        if (cnt[d] == 0) b++;
      }
      cnt[ld]--;
      if (!flag) continue;

      ans += f(i, a, b);
    }
    cnt[v[i]]++;
  }
  for (int d = 0; d < 10; ++d) if(cnt[d] > 2) return ans;
  ans++;
  return ans;
//  return DP( til - 1 , 0 , false , false );
}
int main(){
#ifdef ONLINE_JUDGE
  freopen( "exchange.in" , "r" , stdin );
  freopen( "exchange.out" , "w" , stdout );
#endif
  int X = 100000;
  int ans = 0;
  for (int i = 1; i <= X; ++i) {
    if (ok(i)) ans++;
    if (cal(i) != ans) {
      printf("X %d\n", i);
      break;
    }
  }
  LL l , r;
  cin >> l >> r;
  cout << cal( r ) - cal( l - 1 ) << endl;
}
