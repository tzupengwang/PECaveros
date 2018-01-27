#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
int n;

bool tend[1000005];
int val[1000005];
deque<ii> dq;
int ans;

void go() {
  if (dq.size() == 0) {
    ans ++;
    return;
  }
  ii nw = dq.back(); dq.pop_back();
  int x = nw.second;
  int v = nw.first;

  if (tend[x]) {
    go();
  } else {
    int bnd = 100;
    if (dq.size()) bnd = dq[0].first;

    for (int i = 1; i + i <= v; i ++) {
      int j = v - i;
      if (j > bnd) continue;
      dq.push_front(ii(j, x + x + 1));
      dq.push_front(ii(i, x + x));
      go();
      dq.pop_front();
      dq.pop_front();
    }
  }

  dq.push_back(nw);
}

int main(){
  int cs = 1;
  while (scanf("%d", &n) == 1 && n) {
    char buf[25];
    ans = 0;
    dq.clear();

    for (int k = 0; k < n; k ++) {
      scanf("%s", buf);
      int l = strlen(buf);

      int nw = 1;
      for (int i = 0; i < l; i ++) {
        tend[nw] = false;
        if (buf[i] == '0') nw = nw * 2;
        else if (buf[i] == '1') nw = nw * 2 + 1;
      }
      tend[nw] = true;
    }

    //st.insert(ii(100, 1));
    dq.push_front(ii(100, 1));
    go();
    printf("Case %d: %d\n", cs ++, ans);
  }
}
