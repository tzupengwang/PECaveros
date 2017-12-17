#include <bits/stdc++.h>
using namespace std;

string dir = "NSWE";

int main() {
  string s;
  cin >> s;
  set<char> st;
  for (char c: s) st.insert(c);
  if (st.size() == 1) {
    cout << "X\n";
  } else if (st.size() == 3) {
    for (char c: dir) if (!st.count(c)) {
      cout << c << endl;
      break;
    }
  } else {
    if (st.count('N') and st.count('S')) {
      cout << "X\n";
    }
    else if (st.count('W') and st.count('E')) {
      cout << "X\n";
    } else {
      for (char c: dir) if (!st.count(c)) {
        cout << c;
      }
      cout << endl;
    }
  }
}
