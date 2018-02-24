#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
int keys[30][2];
vector<int> v[30];
bool ext[30];
int tkey[2];

int whos[30];
ii ans;
bool vis[30];
int dp[30][2];

bool dfs(int x) {
  bool ret = false;

  vis[x] = true;
  dp[x][0] = dp[x][1] = 1000000;
  if (whos[x] != 0) ret = true;
  if (whos[x] != 1) dp[x][1] = 0;
  if (whos[x] != 2) dp[x][0] = 0;

  for (int y: v[x]) if (!vis[y]) {
    bool tmp = dfs(y);
    ret = ret or tmp;
    if (whos[x] != 1) {
      dp[x][1] += min(dp[y][0] + 1, dp[y][1]);
    }
    if (whos[x] != 2) {
      dp[x][0] += min(dp[y][1] + 1, dp[y][0]);
    }
  }
  return ret;
}

void solve() {
  int ca1 = 0, ca2 = 0;
  for (int i = 0; i < 26; i ++) if (ext[i]) {
    if (whos[i] == 1) ca1 ++;
    if (whos[i] == 2) ca2 ++;
  }
  if (ca1 == 0 && tkey[0]) return;
  if (ca2 == 0 && tkey[1]) return;

  int cc = 0;
  int ans1 = 0, ans2 = 0;
  for (int i = 0; i < 26; i ++) vis[i] = false;

  for (int i = 0; i < 26; i ++) if (ext[i] && !vis[i]) {
    if (!dfs(i)) continue;
    cc ++;
    int ret = min(dp[i][0], dp[i][1]);
    cc += ret;
    ans2 += ret;
  }
  ans2 += cc - (ca1 != 0) - (ca2 != 0);

  for (int i = 0; i < 26; i ++) if (ext[i]) {
    if (whos[i] == 1)
      ans1 += keys[i][1] * 2;
    if (whos[i] == 2)
      ans1 += keys[i][0] * 2;
  }
  ans = min(ans, ii(ans1, ans2));
}

void try1() {
  int ca1 = 0, ca2 = 0;
  for (int i = 0; i < 26; i ++) if (ext[i]) {
    if (whos[i] == 1) ca1 ++;
    if (whos[i] == 2) ca2 ++;
  }

  if (ca1 == 0 && tkey[0] == 0) {
    solve();
  } else if (ca1 == 0 && tkey[0] != 0) {
    for (int i = 0; i < 26; i ++) if (ext[i]) {
      int tmp = whos[i];
      whos[i] = 1;
      solve();
      whos[i] = tmp;
    }
  } else if (ca2 == 0 && tkey[1] == 0) {
    solve();
  } else if (ca2 == 0 && tkey[1] != 0) {
    for (int i = 0; i < 26; i ++) if (ext[i]) {
      int tmp = whos[i];
      whos[i] = 2;
      solve();
      whos[i] = tmp;
    }
  } else {
    solve();
  }
}

void brt1(int now) {
  if (now == 26) {
    return try1();
  }

  if (!ext[now]) return brt1(now + 1);

  if (keys[now][0] == 0 && keys[now][1] == 0) {
    whos[now] = 0;
    return brt1(now + 1);
  }

  if (keys[now][0] > keys[now][1]) {
    whos[now] = 1;
    return brt1(now + 1);
  } else if (keys[now][0] < keys[now][1]) {
    whos[now] = 2;
    return brt1(now + 1);
  } else {
    whos[now] = 1;
    brt1(now + 1);
    whos[now] = 2;
    brt1(now + 1);
  }
}

int cs = 0;
int main() {
  while (true) {
    char buf[10];
    if (scanf("%s", buf) == EOF) break;

    tkey[0] = tkey[1] = 0;
    for (int i = 0; i < 30; i ++) {
      keys[i][0] = keys[i][1] = 0;
      v[i].clear();
      ext[i] = false;
    }
    ans = ii(100, 100);

    do {
      if (buf[0] == '0') break;
      sort(buf, buf + 2);

      if ('A' <= buf[0] && buf[0] <= 'M') {
        int a1 = buf[1] - 'a';
        keys[a1][0] ++;

        ext[a1] = true;
        tkey[0] ++;
      } else if ('N' <= buf[0] && buf[0] <= 'Z') {
        int a1 = buf[1] - 'a';
        keys[a1][1] ++;

        ext[a1] = true;
        tkey[1] ++;
      } else {
        int a1 = buf[0] - 'a';
        int a2 = buf[1] - 'a';
        v[a1].push_back(a2);
        v[a2].push_back(a1);

        ext[a1] = true;
        ext[a2] = true;
      }
    } while (scanf("%s", buf));

    brt1(0);
    if (ans.first == 100) {
      printf("Case %d: impossible\n", ++cs);
    } else printf("Case %d: %d %d\n", ++cs, ans.first, ans.second);
  }
}
