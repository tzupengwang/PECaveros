#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

void reduce(vector<ll> &v1, vector<ll> &v2) {
  if (v1.size() == 0 || v2.size() == 0) return;
  if (v1.size() == 1) {
    if (v1.back() > v2.back()) v2.pop_back();
    return;
  }
  ll p1 = v1[v1.size() - 1] + v1[v1.size() - 2];
  if (v1.back() < v2.back()) {
    v1.pop_back();
    v1.pop_back();
    v1.push_back(p1);
    return;
  }
  ll p2 = v2.back();
  if (v2.size() >= 2) p2 += v2[v2.size() - 2];
  if (p1 > p2) {
    v1.pop_back();
    v1.pop_back();
    v1.push_back(p1);
    return;
  }
  v2.pop_back();
}

int main() {
  int cs = 0;
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<ll> v1, v2;
    for (int i = 0; i < n; i ++) {
      ll x; scanf("%lld", &x);
      v1.push_back(x);
    }
    for (int i = 0; i < m; i ++) {
      ll x; scanf("%lld", &x);
      v2.push_back(x);
    }

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    int turn = 0;
    printf("Case %d: ", ++cs);
    while (true) {
      if (turn == 0) {
        if (v1.size() == 0) break;
        reduce(v1, v2);
      } else {
        if (v2.size() == 0) break;
        reduce(v2, v1);
      }
      turn = 1 - turn;
    }
    if (v2.size() == 0) puts("Takeover Incorporated");
    else if (v1.size() == 0) puts("Buyout Limited");
  }
}
