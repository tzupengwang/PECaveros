#include <bits/stdc++.h>

using namespace std;

const int N = 510;

int n, m;
char ip[N][N];
bool vis[N][N];

void dfs(int x, int y) {
  if (vis[x][y]) return;
  vis[x][y] = 1;
  if (x < n and ip[x+1][y] == '.') {
    dfs(x+1, y);
    return;
  }
  if (1 <= y-1 and ip[x][y-1] == '.')
    dfs(x, y-1);
  if (y+1 <= m and ip[x][y+1] == '.')
    dfs(x, y+1);
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("mole.in", "r", stdin);
  freopen("mole.out", "w", stdout)
#endif
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", ip[i]+1);
  for (int i = 1; i <= m; ++i) if (ip[1][i] != '#')
    dfs(1, i);
  bool flag = 0;
  for (int i = 1; i <= n and !flag; ++i)
    for (int j = 1; j <= m and !flag; ++j) {
      if (ip[i][j] == '.' and !vis[i][j]) {
        ip[i][j] = 'X';
        flag = 1;
      }
    }
  if (!flag) {
    puts("No");
    return 0;
  }
  puts("Yes");
  for (int i = 1; i <= n; ++i)
    puts(ip[i]+1);
}
