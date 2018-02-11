
//#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;


struct frac{
  LL p , q;
  frac( LL v = 0 ){
    p = v;
    q = 1;
  }
  frac( LL _p , LL _q ){
    p = _p; q = _q;
    trim();
  }
  void trim(){
    LL g = __gcd( abs( p ) , abs( q ) );
    p /= g;
    q /= g;
    if( q < 0 ) p = -p , q = -q;
  }
  frac operator+( const frac& he ) const{
    return frac( p * he.q + q * he.p , q * he.q );
  }
  frac operator-( const frac& he ) const{
    return frac( p * he.q - q * he.p , q * he.q );
  }
  frac operator*( const frac& he ) const{
    return frac( p * he.p , q * he.q );
  }
  frac operator/( const frac& he ) const{
    return frac( p * he.q , q * he.p );
  }
};

const int N = 1e5+10;

//typedef double D;
//const D eps = 1e-9;

int n, x[N], y[N];

//D t[N], u[N], s[N], a[N];
frac t[N], u[N], s[N], a[N];

void fail() {puts("No");exit(0);}

int main(){
  scanf("%d", &n);
  for (int i = 0; i <= n; ++i) {
    scanf("%d%d", x+i, y+i);
  }
  for (int i = 1; i <= n; ++i) {
    //t[i] = 1.*(D)(y[i] - y[i-1]) / (x[i] - x[i-1]);
    t[ i ] = frac( y[ i ] - y[ i - 1 ] ,  x[ i ] - x[ i - 1 ] );
    //u[i] = -t[i] * x[i-1] + y[i-1];
    u[ i ] = t[ i ] * frac( -x[ i - 1 ] ) + frac( y[ i - 1 ] );
  }
  for (int i = 1; i <= n-1; ++i) {
    a[i] = x[i];
    //s[i] = (t[i+1] - t[i]) / 2.0;
    s[ i ] = ( t[ i + 1 ] - t[ i ] ) / frac( 2 );
    //D tgt = -2.0 * s[i] * x[i];
    frac tgt = frac( -2 ) * s[ i ] * frac( x[ i ] );
    //D dif = u[i+1] - u[i];
    frac dif = u[ i + 1 ] - u[ i ];
    //if (fabs(tgt - dif) > eps) fail();
    if( tgt.p != dif.p or
        tgt.q != dif.q ) fail();
    //tgt = tgt - dif;
    //if( tgt.p ) fail();
  }
  //D sum = 0;
  //for (int i = 1; i <= n-1; ++i) sum += s[i];
  //if (fabs(t[n] - sum) > eps) fail();
  //if (fabs(t[1] + sum) > eps) fail();
  t[ n ] = t[ n ] + t[ 1 ];
  if( t[ n ].p ) fail();
  u[ n ] = u[ n ] + u[ 1 ];
  if( u[ n ].p ) fail();
  puts("Yes");
}
