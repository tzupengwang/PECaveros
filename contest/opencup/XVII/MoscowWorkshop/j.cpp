#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long double ld;
LL n , m;
const ld pi = acosl( -1.0 );
int main(){
  scanf( "%lld%lld" , &n , &m );
  LL lcm = ( n / __gcd( n , m ) ) * m;
  ld ret = cosl( pi / lcm ) / sinl( pi / n ) * tanl( pi / m );
  printf( "%.12f\n" , (double)ret );
}
