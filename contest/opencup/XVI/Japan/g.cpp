#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair< pair<LL,LL> , LL > pt;
#define X first.first
#define Y first.second
#define Z second
LL a , b , c , n;
void scan( pt& x ){
  cin >> x.X >> x.Y >> x.Z;
}
set< pt > bye;
bool none( pt& xx ){
  if( xx.X < 0 or xx.X >= a ) return true;
  if( xx.Y < 0 or xx.Y >= b ) return true;
  if( xx.Z < 0 or xx.Z >= c ) return true;
  return bye.find( xx ) != bye.end();
}
int main(){
  cin >> a >> b >> c >> n;
  LL ans = 2 * ( a * b + a * c + b * c );
  while( n -- ){
    pt tmp; scan( tmp );
    {
      int cc = 0;
      pt tmp2 = tmp;
      tmp2.X ++;
      cc += none( tmp2 );
      tmp2.X -= 2;
      cc += none( tmp2 );
      if( cc == 2 ) ans -= 2;
      else if( cc == 0 ) ans += 2;
    }
    {
      int cc = 0;
      pt tmp2 = tmp;
      tmp2.Y ++;
      cc += none( tmp2 );
      tmp2.Y -= 2;
      cc += none( tmp2 );
      if( cc == 2 ) ans -= 2;
      else if( cc == 0 ) ans += 2;
    }
    {
      int cc = 0;
      pt tmp2 = tmp;
      tmp2.Z ++;
      cc += none( tmp2 );
      tmp2.Z -= 2;
      cc += none( tmp2 );
      if( cc == 2 ) ans -= 2;
      else if( cc == 0 ) ans += 2;
    }
    bye.insert( tmp );
  }
  cout << ans << endl;
}
