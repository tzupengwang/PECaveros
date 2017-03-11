#include <bits/stdc++.h>

using namespace std;

int main() {
#ifndef LOCAL
  freopen("input.txt" , "r" , stdin);
  freopen("output.txt" , "w" , stdout);
#endif
  int n , sx , sy;
  cin >> n >> sx >> sy;
  for ( int i = 0 ; i < n ; i++ ) {
    int x , y;
    cin >> x >> y;
    int dx = x-sx , dy = y-sy;
    int tx = dx+dy , ty = -dx;
    cout << sx+tx << ' ' << sy+ty << '\n';
  }
}
