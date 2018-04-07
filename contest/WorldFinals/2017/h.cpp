#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> ii;

int n, t;
vector<ii> v;

int main(){
  scanf("%d%d", &n, &t);
  for (int i = 0, x, y; i < n; i ++) {
    scanf("%d%d", &x, &y);
    y -= t;
    v.push_back(ii(x, y));
  }

  sort(v.begin(), v.end());

  int ps = 0;
  while (true) {
    if (ps == n) {
      puts("yes");
      break;
    }
    int st = ps;

    bool ok = false;
    while (true) {
      if (st == n || v[st].first >= v[ps].first + t) break;

      int tm = v[st].first + t;
      priority_queue<int, vector<int>, greater<int>> pq;
      int pt = ps;
      bool good = true;
      while (true) {
        while (pt < n && (pt == st || v[pt].first <= tm)) {
          if (pt != st)
            pq.push(v[pt].second);
          pt ++;
        }
        int pt2 = pt;
        int cnt = 0, pp = -1;
        while (pt2 < n && v[pt2].first < tm + t) {
          if (v[pt2].second < tm + t) {
            pp = pt2;
            cnt ++;
          }
          pt2 ++;
        }
        if (cnt > 1) {
          good = false;
          break;
        } else if (cnt == 1) {
          tm = v[pp].first + t;
          while (pt < n && (pt == pp || v[pt].first <= tm)) {
            if (pt != pp) {
              if (v[pt].second < tm) {
                good = false;
                break;
              }
              pq.push(v[pt].second);
            }
            pt ++;
          }
          if (!good) break;
          continue;
        }

        if (pq.empty()) break;
        int x = pq.top(); pq.pop();
        if (x < tm) {
          good = false;
          break;
        } else {
          tm += t;
        }
      }
      if (good) {
        ok = true;
        ps = pt;
        break;
      } else {
        st ++;
      }
    }

    if (!ok) {
      puts("no");
      return 0;
    }
  }

}
