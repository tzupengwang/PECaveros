#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 1021
typedef long long ll;
ll w , n;
ll h[100005];
ll S[100005];

int lft[100005];
int rgt[100005];

bool ok(ll H){
  for (int i = 0; i < n; i ++) {
    lft[i] = rgt[i] = -1;
  }
  for (int i = 0; i < n; i ++) {
    if (i + (H - h[i]) < n) {
      if (lft[i + (H - h[i])] == -1) lft[i + (H - h[i])] = i;
      else lft[i + (H - h[i])] = max(lft[i + (H - h[i])], i);
    }

    if (i - (H - h[i]) >= 0) {
      if (rgt[i - (H - h[i])] == -1) rgt[i - (H - h[i])] = i;
      else rgt[i - (H - h[i])] = min(rgt[i - (H - h[i])], i);
    }
  }
  for (int i = 1; i < n; i ++) {
    if (lft[i - 1] == -1) continue;
    lft[i] = max(lft[i], lft[i - 1]);
  }
  for (int i = n - 2; i >= 0; i --) {
    if (rgt[i + 1] == -1) continue;
    if (rgt[i] == -1) rgt[i] = rgt[i + 1];
    else rgt[i] = min(rgt[i], rgt[i + 1]);
  }

  for (int i = 0; i < n; i ++) {
    if (lft[i] == -1 || rgt[i] == -1) continue;
    
    ll need = 0;
    need += (H + H - i + lft[i] + 1) * (i - lft[i]) / 2;
    need += (H + H - rgt[i] + i) * (rgt[i] - i - 1) / 2;
    need -= (S[rgt[i] - 1] - S[lft[i]]);
    if (need <= w) return true;
  }
  return false;
}

int main(){
  freopen( "landscape.in" , "r" , stdin );
  freopen( "landscape.out" , "w" , stdout );
  scanf( "%lld%lld" , &n , &w );

  ll maxh = 0;
  for( int i = 0 ; i < n ; i ++ ){
    scanf("%lld", &h[ i ]);
    maxh = max(maxh, h[i]);
  }
  S[0] = h[0];
  for (int i = 1; i < n; i ++) S[i] = S[i - 1] + h[i];

  ll l = maxh + 1, r = 1005000000LL, ans = maxh;
  while (l <= r) {
    ll md = (l + r) / 2;
    if (ok(md)) {
      ans = md;
      l = md + 1;
    } else r = md - 1;
  }
  printf("%lld\n", ans);
}
