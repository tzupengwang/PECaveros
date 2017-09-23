#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL d , b , t , p;
int main(){
#ifdef ONLINE_JUDGE
  freopen( "video.in" , "r" , stdin );
  freopen( "video.out" , "w" , stdout );
#endif
  cin >> d >> b >> t >> p;
  LL up = ( ( b - d ) * t ) , dn = d * p;
  LL vl = up / dn;
  while( vl * dn < up ) vl ++;

  up = t * ( b - d );
  dn = vl;
  vl = up / dn;
  while( vl * dn < up ) vl ++;
  cout << vl << endl;
}
