#include <bits/stdc++.h>
using namespace std;
int main(){
  int sum = 0 , c = 0 , x;
  while( cin >> x ){
    sum += x;
    c ++;
  }
  sum -= c - 1;
  cout << sum << endl;
}
