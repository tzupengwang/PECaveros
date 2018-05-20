#include <bits/stdc++.h>
using namespace std;
int main(){
  int t; cin >> t; while(t --){
      int n;
      scanf("%d", &n);

      long long ans = 0;

      for (int i = 0; i < n; i ++) {
        int x; scanf("%d", &x);
        ans = ans * 2 + x;
      }
      printf("%lld\n", ans);
  }
}

