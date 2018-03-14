#include<bits/stdc++.h>
using namespace std;

int c[1005];

int main() {
  int n;
  scanf("%d", &n);

  int free;
  vector<int> ans;

  for (int i = 0; i < n; i ++) {
    int x;
    scanf("%d", &x);
    if (x > 0) {
      c[x] ++;
    } else if (x < 0) {
      x = -x;
      if (c[x] > 0) c[x] --;
      else if (free > 0) {
        ans.push_back(x);
        free --;
      } else {
        puts("No");
        return 0;
      }
    } else {
      free ++;
    }
  }
  while (free) {
    ans.push_back(1);
    free --;
  }
  puts("Yes");
  if (ans.size()) {
    for (int i = 0; i < (int)ans.size(); i ++) {
      printf("%d%c", ans[i], " \n"[i + 1 == (int)ans.size()]);
    }
  } else {
    puts("");
  }
}

