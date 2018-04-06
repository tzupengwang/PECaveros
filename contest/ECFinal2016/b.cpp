
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e5+10;
const LL INF = (1LL<<61);
const LL K = (1LL<<60);

int n; LL k;

int m[2];
char ss[2][N];
char ans[N];
int ok[2];

inline LL add(LL a, LL b) {
  a += b;
  return a >= INF? INF: a;
}

inline LL pw2(int e) {
  if (e >= 61) return INF;
  return (1LL << e);
}

inline LL f(int X, int Y, int Z) {
  if (X == -1 && Y == -1) return 0;
  if (Z == -1) return pw2(X == -1? Y: X);
  if (X < Y) swap(X, Y);
  if (X <= 60) {
    LL res = pw2(X) + pw2(Y) - pw2(Z);
    return res >= INF? INF: res;
  } else {
    return INF;
  }
}

LL chk(int i) {
  int tok[] = {ok[0], ok[1]};
  int par = i&1;
  int pos = (i+1)/2;
  if (pos > (m[par]+1) / 2) {
    tok[par] = tok[par] && (ss[par][m[par] - pos + 1] == '0');
  }
  int a = max(((n+1) / 2 + 1) / 2 - (i+1) / 2, 0);
  int b = max((n / 2 + 1) / 2 - i / 2, 0);
  int c = (n+1) / 2 - (i+1) / 2;
  int d = (n / 2) - i / 2;
  int X = d + a;
  if (!tok[1]) X = -1;
  int Y = c + b;
  if (!tok[0]) Y = -1;
  int Z = a + b;
  if (!tok[0] || !tok[1]) Z = -1;
  return f(X, Y, Z);
}

void push(int i, int b) {
  int par = i&1;
  int pos = (i+1)/2;
  ans[i] = '0' + b;
  ss[par][pos] = '0' + b;
  if (pos > (m[par]+1) / 2) {
    if (ss[par][pos] != ss[par][m[par] - pos + 1]) ok[par] = 0;
  }
}

int _cs;
void main2() {
  cin >> n >> k;
  m[0] = m[1] = 0;
  ok[0] = ok[1] = 1;
  for (int i = 1; i <= n; ++i) m[i&1]++;
  for (int i = 1; i <= n; ++i) {
    LL tmp = chk(i);
    //printf("%d %lld\n", i, tmp);
    if (k <= tmp) {
      push(i, 0);
    } else {
      k -= tmp;
      push(i, 1);
    }
  }
  if (k > 1) {
    printf("Case #%d: NOT FOUND!\n", ++_cs);
  } else {
    ans[n+1] = 0;
    printf("Case #%d: %s\n", ++_cs, ans+1);
  }
}

int main(){
  int t;scanf("%d", &t); while (t--) main2();
}
