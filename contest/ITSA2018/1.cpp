#include <bits/stdc++.h>
using namespace std;
set< tuple<int,int,int> > s;
int main(){
  for(int x=-100; x<=100; x++)
    for(int y=x; y<=100; y++){
      int a=x+y;
      int b=y-x;
      int c=(x * y + 50) / 100;
      s.insert(make_tuple(a, b, c));
      s.insert(make_tuple(a, c, b));
      s.insert(make_tuple(b, a, c));
      s.insert(make_tuple(b, c, a));
      s.insert(make_tuple(c, a, b));
      s.insert(make_tuple(c, b, a));
      //s.insert(make_tuple(x+y,y-x, (int)round(0.01 * x * y)));
    }
      //s.insert(make_tuple(x+y,y-x, (int)round(0.01 * x * y)));
  int t; cin >> t; while(t --){
      int a, b, c;
      cin >> a >> b >> c;
      auto it = s.find(make_tuple(a, b, c));
      if( it == s.end() ) puts("No");
      else puts("Yes");
  }
}
