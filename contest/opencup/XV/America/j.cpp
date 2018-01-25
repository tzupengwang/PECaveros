#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
char s[1000005];

int maxk(char x, int l) {
  if (l == 0) return 0;
  return max('z' - x, x - 'a') + 25 * (l - 1);
}

int main(){
  int k;
  scanf("%d", &k);

  s[0] = 'a';
  int ml = (k + 24) / 25;

  int nd = k;
  for (int i = 1; i < ml; i ++) {
    for (char c = 'a'; c <= 'z'; c ++) {
      int tl = abs(c - s[i - 1]);
      if (tl + maxk(c, ml - i) >= nd) {
        s[i] = c;
        nd -= tl;
        break;
      }
    }
  }
  for (char c = 'a'; c <= 'z'; c ++) {
    int tl = abs(c - s[ml - 1]);
    if (tl == nd) {
      s[ml] = c;
      break;
    }
  }
  s[ml + 1] = '\0';
  printf("%s\n", s);
}
