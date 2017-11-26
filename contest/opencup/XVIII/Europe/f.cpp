#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n , p , r;
inline LL mul( LL a , LL b , LL mod ){
  a *= b;
  return a >= mod ? a % mod : a;
}
inline LL mpow( LL a , LL b , LL mod ){
  if( !b ) return 1;
  LL ret = mpow( mul( a , a , mod ) , b >> 1 , mod );
  if( b & 1LL ) ret = mul( ret , a , mod );
  return ret;
}
inline LL inv( LL a , LL mod ){
  return mpow( a , mod - 2 , mod );
}
void no(){
  puts( "-1 -1" );
  exit(0);
}
#define N 20000000
int iv[ N ];
int main(){
  cin >> n >> p >> r;
  if( n == 3 and p == 2 and r == 0 ){
    cout << 3 << " " << 2 << endl;
    exit(0);
  }
  if( n >= p + p ){
    if( r == 0 ){
      cout << p + p << " " << p << endl;
      exit(0);
    }
    no();
  }
  if( n >= p ){
    if( r == 0 ){
      if( n == 2 and p == 2 ) no();
      cout << 2 << " " << 1 << endl;
      exit(0);
    }
    LL other = 1;
    for( LL i = 1 ; i <= n ; i ++ )
      if( i != p )
        other = (other * i) % p;
    // other * ? = r
    LL nd = mul( r , inv( other , p ) , p );
    cout << p << " " << nd << endl;
    exit(0);
  }
  iv[ 1 ] = 1;
  for( int i = 2 ; i < p ; i ++ )
		iv[ i ] = ((LL)(p - p / i) * iv[p % i]) % p;
  int rr = 1;
  for( int i = 1 ; i <= n ; i ++ )
    rr = mul( rr , i , p );
  if( r == rr ) no();
  for( int i = 1 ; i <= n ; i ++ ){
    //rr / i * ? = r
    //? = (r * i) / rr
    int tar = mul( mul( r , i , p ) , iv[ rr ] , p );
    if( tar < i and tar > 0 ){
      cout << i << " " << tar << endl;
      exit(0);
    }
  }
  no();
}
