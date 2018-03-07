
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e5+10;

int n, a[N];
int ML[N], MR[N], mL[N], mR[N];

void predo() {
  {
    vector<int> stk;
    for (int i = 1; i <= n; ++i) {
      while (stk.size() && a[stk.back()] < a[i]) stk.pop_back();
      if (stk.size()) ML[i] = stk.back();
      else ML[i] = 0;
      stk.push_back(i);
    }
  }
  {
    vector<int> stk;
    for (int i = 1; i <= n; ++i) {
      while (stk.size() && a[stk.back()] > a[i]) stk.pop_back();
      if (stk.size()) mL[i] = stk.back();
      else mL[i] = 0;
      stk.push_back(i);
    }
  }
  {
    vector<int> stk;
    for (int i = n; i >= 1; --i) {
      while (stk.size() && a[stk.back()] < a[i]) stk.pop_back();
      if (stk.size()) MR[i] = stk.back();
      else MR[i] = n+1;
      stk.push_back(i);
    }
  }
  {
    vector<int> stk;
    for (int i = n; i >= 1; --i) {
      while (stk.size() && a[stk.back()] > a[i]) stk.pop_back();
      if (stk.size()) mR[i] = stk.back();
      else mR[i] = n+1;
      stk.push_back(i);
    }
  }
}

int lp[N], rp[N];

void solve() {
  {
    vector<int> stk;
    for (int i = 1; i <= n; ++i) {
      //printf("%d %d\n", ML[i], MR[i]);
      while (stk.size() && a[stk.back()] >= a[i]) stk.pop_back();
      if (stk.size() && stk.back() > ML[i]) {
        lp[i] = *upper_bound(stk.begin(), stk.end(), ML[i]);
      } else {
        lp[i] = 0;
      }
      stk.push_back(i);
    }
  }
  {
    vector<int> stk;
    for (int i = n; i >= 1; --i) {
      while (stk.size() && a[stk.back()] >= a[i]) stk.pop_back();
      if (stk.size() && stk.back() < MR[i]) {
        int s = 0, e = stk.size() - 1;
        rp[i] = 0;
        while (s <= e) {
          int mid = (s+e) / 2;
          if (stk[mid] < MR[i]) {
            rp[i] = stk[mid];
            e = mid-1;
          } else s = mid+1;
        }
      } else {
        rp[i] = 0;
      }
      stk.push_back(i);
    }
  }
  int ansl = 1, ansk = 1;
  for (int i = 1; i <= n; ++i) {
    if (lp[i]) {
      int ll = max(ML[i], mL[lp[i]]) + 1;
      int rr = min(MR[i], mR[lp[i]]) - 1;
      if (rr - ll + 1 > ansl) {
        ansl = rr-ll+1;
        ansk = ll;
      } else if (rr - ll + 1 == ansl && ll < ansk) ansk = ll;
    }
    if (rp[i]) {
      int ll = max(ML[i], mL[rp[i]]) + 1;
      int rr = min(MR[i], mR[rp[i]]) - 1;
      if (rr - ll + 1 > ansl) {
        ansl = rr-ll+1;
        ansk = ll;
      } else if (rr - ll + 1 == ansl && ll < ansk) ansk = ll;
    }
  }
  printf("%d %d\n", ansl, ansk);
}

int main(){
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", a+i);
  predo();
  solve();
}
