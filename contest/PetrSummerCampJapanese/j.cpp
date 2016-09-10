#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pii;
pii gcd(LL a, LL b){
	if(b == 0) return make_pair(1, 0);
	else{
		LL p = a / b;
		pii q = gcd(b, a % b);
		return make_pair(q.second, q.first - q.second * p);
	}
}
LL n , m , a , k;
void solve(){
  pii tp = gcd( m , a );
  LL tgcd = __gcd( m , a );
  if( ( k + a - n ) % tgcd ){
    puts( "Impossible" );
    return;
  }
  LL tms = ( k + a - n ) / tgcd;
  LL res = tp.first % ( a / tgcd );
  if( res && tms < 0 ) res -= ( a / tgcd );
  printf( "%lld\n" , n + m * res * tms );
}
int main(){
  while( scanf( "%lld%lld%lld%lld" , &n , &m , &a , &k ) == 4 ){
    if( n + m + a + k == 0 ) break;
    solve();
  }
}
