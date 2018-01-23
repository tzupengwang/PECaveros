#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define N 10
char c[ N ][ N ][ N ];
bool vis[N][N][N];
int m , n , K;
int dx[]={1,-1,0,0,0,0};
int dy[]={0,0,1,-1,0,0};
int dz[]={0,0,0,0,1,-1};

struct X {
  int a1, a2, a3;
} st;
set<int> ss;

void go(X p, int w, X co) {
  int x = p.a1, y = p.a2, z = p.a3;
  vis[x][y][z] = true;
  //printf("%d %d %d %d\n", x, y, z, w);
  ss.insert(w);


  if (x + 1 < K && c[x + 1][y][z] == 'x' && !vis[x + 1][y][z]) {
    go({x + 1, y, z}, co.a1, {-w, co.a2, co.a3});
  }
  if (x - 1 >= 0 && c[x - 1][y][z] == 'x' && !vis[x - 1][y][z]) {
    go({x - 1, y, z}, -co.a1, {w, co.a2, co.a3});
  }
  if (y + 1 < n && c[x][y + 1][z] == 'x' && !vis[x][y + 1][z]) {
    go({x, y + 1, z}, co.a2, {co.a1, -w, co.a3});
  }
  if (y - 1 >= 0 && c[x][y - 1][z] == 'x' && !vis[x][y - 1][z]) {
    go({x, y - 1, z}, -co.a2, {co.a1, w, co.a3});
  }
  if (z + 1 < m && c[x][y][z + 1] == 'x' && !vis[x][y][z + 1]) {
    go({x, y, z + 1}, co.a3, {co.a1, co.a2, -w});
  }
  if (z - 1 >= 0 && c[x][y][z - 1] == 'x' && !vis[x][y][z - 1]) {
    go({x, y, z - 1}, -co.a3, {co.a1, co.a2, w});
  }
}

void check() {
  if (ss.size() == 8u) puts("Yes");
  else puts("No");
}

int main(){
#ifndef EDDY
  freopen( "hypercube.in" , "r" , stdin );
  freopen( "hypercube.out" , "w" , stdout );
#endif
  scanf( "%d%d%d" , &m , &n , &K );
  for( int i = 0 ; i < K ; i ++ )
    for( int j = 0 ; j < n ; j ++ )
      scanf( "%s" , c[ i ][ j ] );

  for (int i = 0; i < n; i ++) {
    for (int j = 0; j < m; j ++) {
      for (int k = 0; k < K; k ++) {
        if (c[k][i][j] == 'x') {
          st = {k, i, j};
          go(st, 4, {1, 2, 3});
          check();
          exit(0);
        }
      }
    }
  }
}
