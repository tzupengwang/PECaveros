#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main(){
  LL a , b;
  cin >> a >> b;
  //LL pre = 0;
  //for( LL i = 1 ; i + 1 < a + b ; i ++ )
    //pre += i;
  LL s = (a + b) - 1;
  LL pre = ( s * ( s - 1 ) ) / 2;
  if( ( a + b ) & 1 )
    pre += s - b + 1;
  else
    pre += b;
  cout << pre << endl;
}
