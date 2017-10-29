#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
char s[100005];

int main(){
  scanf("%s", s);
  int l = strlen(s);
  int rpt = l - 1;
  while (rpt > 0 && s[rpt] == '9') rpt --;

  for (int i = 0; i < rpt; i ++) {
    if (s[i] > '1') s[i] --;
  }

  int mn = 9;
  for (int i = 0; i < l; i ++) {
    if (s[i] != '0') mn = min(mn, s[i] - '0');
  }
  printf("%d\n", mn);
}
