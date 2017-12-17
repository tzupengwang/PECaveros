#include<bits/stdc++.h>
using namespace std;

int main() {
  int x;
  scanf("%d", &x);

  int sd = 1;
  int tot = 1;

  while (tot < x) {
    tot += sd * 6;
    sd ++;
  }

  int ans = sd * 6;
  int dlt = tot - x;
  vector<int> v;
  for (int i = 0; i < 6; i ++)
    v.push_back(sd);

  while (true) {
    int mn = 1000000000, id = -1;
    for (int i = 0; i < 6; i ++) {
      if (v[i] < mn) {
        mn = v[i], id = i;
      }
    }

    if (mn <= dlt) {
      ans --;
      dlt -= mn;
      v[id] ++;
      v[(id + 1) % 6] --;
      v[(id + 5) % 6] --;
    } else break;
  }
  printf("%d\n", ans);
}

