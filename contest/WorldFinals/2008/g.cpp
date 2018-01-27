
#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

typedef double D;

const int N = 15;

int n, __cs;
D co[N], c;

void main2() {
  for (int i = 0; i <= n; ++i)
    cin >> co[n-i];
  cin >> c;
  D alpha = 0, beta = 0, gamma = 0;

  for (int i = 0; i <= n; ++i) {
    {
      gamma += (pow(1, i+1) - pow(-1, i+1)) * co[i] / (i+1);
    }
    {
      alpha += (pow(c, i+2) - pow(-1, i+2)) * co[i] / (i+2);
      alpha -= (pow(c, i+1) - pow(-1, i+1)) * c * co[i] / (i+1);
    }
    {
      beta += (pow(1, i+2) - pow(c, i+2)) * co[i] / (i+2);
      beta -= (pow(1, i+1) - pow(c, i+1)) * c * co[i] / (i+1);
    }
  }

  alpha *= -2;
  beta *= -2;
  gamma *= -2;

  D a = 0, b = 0, y = 0;

  y = -3 * alpha / (1+c) / 2.0 - gamma + 3 * beta / (1-c) / 2.0;
  a = (-beta - pow(1-c, 2) * y) * 3 * pow(1-c, -3) / 2.0;
  b = (-alpha + pow(1+c, 2) * y) * 3 * pow(1+c, -3) / 2.0;

  printf("Case %d: %.3f %.3f %.3f %.3f\n", ++__cs, b, y - b*c, a, y - a*c);

}

int main(){
  while (scanf("%d", &n) != EOF and n) {
    main2();
  }
}
