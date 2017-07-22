#include <bits/stdc++.h>

using namespace std;

const int N = (1<<10);

int n, b;
char ip[N][N];
int ord[N*N];
int rnk[N*N];
int trnk[N*N];

inline int enc(int i, int j) {
  return (i<<b)+j;
}

inline void dec(int x, int &i, int &j) {
  i = x>>b;
  j = x&((1<<b)-1);
}

inline int nxt(int x, int len) {
  int i, j;
  dec(x, i, j);
  int ri, rj;
  if (len < n) {
    ri = i, rj = (j+len) & (n-1);
  } else {
    ri = (i+(len>>b)) & (n-1), rj = j;
  }
  //printf("nxt %d(%d, %d) %d %d %d\n", x, i, j, len, ri, rj);
  return enc(ri, rj);
}

inline bool le(int x, int y, int k) {
  int nx = nxt(x, k);
  int ny = nxt(y, k);
  return tie(rnk[x], rnk[nx]) < tie(rnk[y], rnk[ny]);
}

int main() {
#ifdef ONLINE_JUDGE
  freopen("matrix.in", "r", stdin);
  freopen("matrix.out", "w", stdout);
#endif
  while (scanf("%s", ip[n]) != EOF) {
    ++n;
  }
  while((1<<b) < n) ++b;
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    int id = enc(i, j);
    rnk[id] = ip[i][j];
    ord[id] = id;
  }
  sort(ord, ord+n*n, [&](int x, int y) {return rnk[x] < rnk[y];});
  for (int k = 1; k <= n*n; k<<=1) {
    sort(ord, ord+n*n, [&](int x, int y) {
      return le(x, y, k);
    });
    int tmp = 0;
    for (int i = 0; i < n*n; ++i) {
      if (i > 0 and le(ord[i-1], ord[i], k)) {
    //    printf("le %d %d %d\n", ord[i-1], ord[i], k);
        tmp++;
      }
      trnk[ord[i]] = tmp;
    }
    for (int i = 0; i < n*n; ++i) {
      rnk[i] = trnk[i];
    }
  }
  int x = ord[0];
  int ii, jj;
  dec(x, ii, jj);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      putchar(ip[(ii+i)%n][(jj+j)%n]);
    }
    putchar('\n');
  }
}
