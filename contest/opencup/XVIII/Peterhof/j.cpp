#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define K 30
inline int mul( LL a , int b , LL p ){
  a *= b;
  return a >= p ? a % p : a;
}
inline int mypow( int a , int b , int p ){
  if( !b ) return 1 % p;
  int ret = mypow( mul( a , a , p ) , b >> 1 , p );
  if( b & 1 ) ret = mul( ret , a , p );
  return ret;
}
void calcH(int &t, int &h, const int p) {
	int tmp=p-1; for(t=0;(tmp&1)==0;tmp/=2) t++; h=tmp;
}
// solve equation x^2 mod p = a
bool solve(int a, int p) {
  if( a == 0 ) return true;
	if(p == 2) return true;
	int p2 = p / 2, tmp = mypow(a, p2, p);
	if (tmp == p - 1) return false;
  return true;
	//if ((p + 1) % 4 == 0) {
		//return true;
	//} else {
		//int t, h, b, pb; calcH(t, h, p);
		//if (t >= 2) {
			//do {b = rand() % (p - 2) + 2;
			//} while (mypow(b, p / 2, p) != p - 1);
			//pb = mypow(b, h, p);
		//} int s = mypow(a, h / 2, p);
		//for (int step = 2; step <= t; step++) {
			//int ss = (((LL)(s * s) % p) * a) % p;
			//for(int i=0;i<t-step;i++) ss=mul(ss,ss,p);
			//if (ss + 1 == p) s = (s * pb) % p;
      //pb = ((LL)pb * pb) % p;
		//} x = ((LL)s * a) % p; y = p - x;
	//} return true; 
}
char c[ 1048576 ];
vector<int> modp = {999983, 1097774749, 1076767633, 100102021, 999997771,
  1001010013, 1000512343, 987654361, 999991231,
  999888733, 98789101, 987777733, 999991921, 1010101333 };
inline int randint( int lb , int rb ){
  return (LL)rand() * rand() % (rb - lb + 1) + lb;
}
int main(){
  while( (int)modp.size() < K ){
    int pp = randint( 9e8 , 1e9 + 1e8 );
    bool ok = true;
    for( LL i = 2 ; i * i <= pp and ok ; i ++ )
      if( pp % i == 0 )
        ok = false;
    if( ok )
      modp.push_back( pp );
  }
  scanf( "%s" , c );
  int len = strlen( c );
  bool good = true;
  for( int pp : modp ){
    LL v = 0;
    for( int i = 0 ; i < len ; i ++ )
      v = (v * 10 + c[ i ] - '0') % pp;
    if( not solve( v , pp ) ){
      good = false;
      break;
    }
  }
  puts( good ? "Yes" : "No" );
}
