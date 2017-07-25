#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

const int N = 3e5+10;

int n;
vector<PII> ip;
map<int, vector<PII>> mp;

inline LL cnt(PII p) {
  LL res = p.second-p.first;
  return res/2+1;
}

inline LL work(int y, vector<PII> vec) {
  if (vec.empty()) return 0;
  sort(vec.begin(), vec.end());
  LL ans = 0;
  PII cur = vec[0];
  //printf("work %d %d\n", y, vec.size());
  for (size_t i = 1; i < vec.size(); ++i) {
    PII p = vec[i];
    //printf("  [%d, %d]\n", p.first, p.second);
    if (cur.second+2 >= p.first) {
      cur.second = max(cur.second, p.second);
    }
    else {
      LL tmp = cnt(cur);
      ans += tmp;
      if (tmp > 1) {
        //printf("  %d PB %d %d\n", y+1, cur.first+1, cur.second-1);
        mp[y+1].push_back(PII{cur.first+1, cur.second-1});
      }
      cur = p;
    }
  }
  LL tmp = cnt(cur);
  ans += tmp;
  if (tmp > 1) {
    //printf("  %d PB %d %d\n", y+1, cur.first+1, cur.second-1);
    mp[y+1].push_back(PII{cur.first+1, cur.second-1});
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int x, y;scanf("%d%d", &x, &y);
    mp[x].push_back(PII{y, y});
  }
  LL ans = 0;
  auto it = mp.begin();
  while (it != mp.end()) {
    ans += work(it->first, it->second);
    it = mp.upper_bound(it->first);
  }
  cout << ans << endl;
}
