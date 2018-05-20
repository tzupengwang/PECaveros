#include <bits/stdc++.h>
using namespace std;
const int N = 5140;
vector< pair<int,pair<int,double>> > v[N];
double dp[N], cdp[N];
int n, m;
clock_t st;
void init(){
  scanf("%d%d", &n, &m);
  //n=5000;
  //m=100000;
  for(int i=1; i<=n; i++)
    v[i].clear();

  /*for(int i=1; i<=n and m>0; i++)
    for(int j=i+1; j<=n and m>0; j++){
      m--;
      int s=i, t=j, c=100, p=1, q=1;
      v[s].push_back({t, {c, 1. - p / 100.}});
      v[t].push_back({s, {c, 1. - q / 100.}});
    }
  return;*/
  while(m--){
    int s, t, c, p, q;
    scanf("%d%d%d%d%d", &s, &t, &c, &p, &q);
    v[s].push_back({t, {c, 1. - p / 100.}});
    v[t].push_back({s, {c, 1. - q / 100.}});
  }
}
void solve(){
  for(int i=1; i<=n; i++){
    dp[i]=1e9;
    for(auto e: v[i])
      dp[i]=min(dp[i], (double)e.second.first / e.second.second);
  }
  int iter=0;
  while((clock() - st) < 0.24 * CLOCKS_PER_SEC){
    for(int i=1; i<=n ; i++){
      cdp[i]=dp[i];
      dp[i]=1e9;
    }
    for(int i=1; i<=n; i++)
      for(auto e: v[i]){
        double tmp=e.second.first + e.second.second * cdp[e.first];
        dp[i]=min(dp[i], tmp);
      }
    ++iter;
    if(fabs(dp[1] - cdp[1]) > 1e-7) iter=0;
    if(iter == n) break;
  }
  printf("%.6f\n", dp[1]);
}
int main(){
  int t;
  scanf("%d", &t);
  //t=1;
  while(t--){
    st=clock();
    init();
    solve();
  }
}
