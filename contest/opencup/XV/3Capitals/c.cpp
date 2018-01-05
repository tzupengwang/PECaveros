#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n;
inline LL rev( LL x ){
  LL ret = 0;
  for( int i = 0 ; i < 32 ; i ++ )
    ret = (ret << 1) | ((x >> i) & 1);
  return ret;
}
int main(){
  int T;
  cin >> T; while (T --) {
    cin >> n;
    if (n == 3) {
      cout << "3\n0 0\n1 0\n2 0\n";
    } else if (n == 4) {
      cout << "8\n0 0\n1 0\n2 0\n3 0\n0 1\n1 1\n2 1\n3 1\n";
    } else {
      cout << n * 3 << "\n";
      for (int i = 0; i < n; i ++) {
        for (int j = i; j < i + 3; j ++) {
          cout << i << " " << j % (n - 2) << "\n";
        }
      }
    }
  }
}

