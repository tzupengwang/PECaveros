#include <bits/stdc++.h>
using namespace std;
int main(){
  int n , l , r;
  cin >> n >> l >> r;
  string ans = "";
  for( int i = l ; i <= r ; i += 2 )
    ans += "[]";
  int lft = l - 1 , rgt = n - r;
  while( lft and rgt ){
    ans = "(" + ans + ")";
    lft --; rgt --;
  }
  while( lft > 0 ){
    ans = "()" + ans;
    lft -= 2;
  }
  while( rgt > 0 ){
    ans = ans + "()";
    rgt -= 2;
  }
  cout << ans << endl;
}
