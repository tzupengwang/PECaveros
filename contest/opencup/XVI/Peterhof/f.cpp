#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
pair<LL,LL> gcd(LL a, LL b){
	if(b == 0) return {1, 0};
  pair<LL,LL> q = gcd(b, a % b);
  return {q.second, q.first - q.second * (a / b)};
}
LL p , q;
int main(){
  cin >> p >> q;
  if( __gcd( abs( p - q ) , p + q ) != 1 ){
    puts( "-1" );
    return 0;
  }
  pair<LL,LL> ret = gcd( p , q );
  LL a = ret.first;
  LL b = ret.second;
  LL ans = -1;
  for( LL dlt = -3 ; dlt <= 3 ; dlt ++ ){
    LL tmpa = a + dlt * q;
    LL tmpb = b - dlt * p;
    if( ( abs( tmpa ) & 1 ) !=
        ( abs( p ) & 1 ) )
      continue;
    if( ( abs( tmpb ) & 1 ) !=
        ( abs( q ) & 1 ) )
      continue;
    LL tans = abs( tmpa ) + abs( tmpb );
    if( abs( tmpa ) < p )
      tans += ( p - abs( tmpa ) + 1 ) / 2 * 2;
    if( abs( tmpb ) < q )
      tans += ( q - abs( tmpb ) + 1 ) / 2 * 2;
    //cerr << tmpa << " " << tmpb << " " << tans << endl;
    if( ans == -1 or tans < ans )
      ans = tans;
  }
  cout << ans << endl;
}
