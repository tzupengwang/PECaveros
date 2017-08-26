#include <bits/stdc++.h>

using namespace std;

typedef double T;
const int N = 2010;
const int M = 16;
const T eps = 1e-6;

struct Pt {
  T x, y, z;
  Pt operator+(Pt a) {
    return {x+a.x, y+a.y, z+a.z};
  }
  Pt operator-(Pt a) {
    return {x-a.x, y-a.y, z-a.z};
  }
  T operator*(Pt a) {
    return x*a.x+y*a.y+z*a.z;
  }
  void read() {
    scanf("%lf%lf%lf", &x, &y, &z);
  }
};

int n, m, R;
Pt ball[N];
T r[N];
Pt light[M];
T phi[M];
T b[M];
bool bad[N][M];
Pt O;

inline bool isbad(int i, int j) {
  Pt p = light[j];
  Pt s = ball[i];
  T A = p*p;
  T B = -2.0 * (p * s);
  T C = (s*s) - r[i]*r[i];
  T D = B*B - 4.0*A*C;
  if (fabs(A) <= eps) return 0;
  if (D <= eps) return 0;
  T x1 = (-B + sqrt(D)) / (A+A);
  if (-eps < x1 && x1 < 1.0 + eps) return 1;
  T x2 = (-B - sqrt(D)) / (A+A);
  if (-eps < x2 && x2 < 1.0 + eps) return 1;
  return 0;
}

int main() {
  while (scanf("%d%d%d", &n, &m, &R)) {
    if (n == 0 && m == 0 && R == 0) break;
    for (int i = 0; i < n; ++i) {
      ball[i].read();
      scanf("%lf", r+i);
    }
    for (int i = 0; i < m; ++i) {
      light[i].read();
      scanf("%lf", b+i);
    }
    O.read();
    for (int i = 0; i < n; ++i) {
      ball[i] = ball[i] - O;
    }
    for (int i = 0; i < m; ++i) {
      light[i] = light[i] - O;
      phi[i] = b[i] / (light[i]*light[i]);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        bad[i][j] = isbad(i, j);
      }
    }
    T ans = 0;
    for (int cmb = 0; cmb < (1 << m); ++cmb) {
      int cnt = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) if ((cmb >> j) & 1) {
          if (bad[i][j]) {
            cnt++;
            break;
          }
        }
        if (cnt > R) break;
      }
      if (cnt > R) continue;
      T tmp = 0;
      for (int j = 0; j < m; ++j) if ((cmb >> j) & 1) {
        tmp += phi[j];
      }
      ans = max(ans, tmp);
    }
    printf("%.9f\n", ans);
  }
}
