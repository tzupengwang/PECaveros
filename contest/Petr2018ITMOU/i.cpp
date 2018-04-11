#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
// Remember coefficient are mod P
/* p=a*2^n+1
   n		2^n 				p 				 a 		root
   20 	1048576		 	7340033 	 7 		3
   1 */
// (must be 2^k)
// To implement poly. multiply:
// NTT<P, root, MAXN> ntt;
// ntt( n , a ); // or ntt.tran( n , a );
// ntt( n , b );
// for( int i = 0 ; i < n ; i++ )
//   c[ i ] = a[ i ] * b[ i ];
// ntt( n , c , 1 );
//
// then you have the result in c :: [LL]
template<LL P, LL root, int MAXN>
struct NTT{
  static LL bigmod(LL a, LL b) {
    LL res = 1;
    for (LL bs = a; b; b >>= 1, bs = (bs * bs) % P) {
      if(b&1) res=(res*bs)%P;
    }
    return res;
  }
  static LL inv(LL a, LL b) {
    if(a==1)return 1;
    return (((LL)(a-inv(b%a,a))*b+1)/a)%b;
  }
  LL omega[MAXN+1];
  NTT() {
    omega[0] = 1;
    LL r = bigmod(root, (P-1)/MAXN);
    for (int i=1; i<=MAXN; i++)
      omega[i] = (omega[i-1]*r)%P;
  }
  // n must be 2^k
  void tran(int n, LL a[], bool inv_ntt=false){
    int basic = MAXN / n;
    int theta = basic;
    for (int m = n; m >= 2; m >>= 1) {
      int mh = m >> 1;
      for (int i = 0; i < mh; i++) {
        LL w = omega[i*theta%MAXN];
        for (int j = i; j < n; j += m) {
          int k = j + mh;
          LL x = a[j] - a[k];
          if (x < 0) x += P;
          a[j] += a[k];
          if (a[j] > P) a[j] -= P;
          a[k] = (w * x) % P;
        }
      }
      theta = (theta * 2) % MAXN;
    }
    int i = 0;
    for (int j = 1; j < n - 1; j++) {
      for (int k = n >> 1; k > (i ^= k); k >>= 1);
      if (j < i) swap(a[i], a[j]);
    }
    if (inv_ntt) {
      LL ni = inv(n,P);
      reverse( a+1 , a+n );
      for (i = 0; i < n; i++)
        a[i] = (a[i] * ni) % P;
    }
  }
  void operator()(int n, LL a[], bool inv_ntt=false) {
    tran(n, a, inv_ntt);
  }
};
const LL P=7340033,root=3;
const int MAXN=(1 << 20);
int myrand(){
  return (((rand() & ((1 << 14) - 1) << 14) ) |
           (rand() & ((1 << 14) - 1))) % P;
}
NTT<P, root, MAXN> ntt;
#define N (1 << 19)
int p[ N ] , mn[ N ];
int f( int x ){ return x == p[ x ] ? x : p[x] = f(p[x]); }
void uni( int x , int y ){
  x = f( x );
  y = f( y );
  p[y] = x;
  mn[ x ] = min( mn[x] , mn[y] );
}
int n , m , c , per[ N ] , a[ N ];
int clr[ N ] , fr[ N ];
LL A[ MAXN ];
clock_t s;
int n2;
void init(){
  s = clock();
  scanf( "%d%d%d" , &n , &m , &c );
  //n = m = c = 500000;
  for( int i = 1 ; i <= n ; i ++ )
    p[ i ] = mn[ i ] = i;
  for( int i = 1 ; i <= n ; i ++ ){
    scanf( "%d" , &per[ i ] );
    //per[ i ] = i == n ? 1 : i + 1;
    uni( i , per[ i ] );
  }
  for( int i = 1 ; i <= n ; i ++ )
    fr[ i ] = mn[ f( i ) ];
  for( int i = 1 ; i <= m ; i ++ )
    scanf( "%d" , &a[ i ] );
    //a[ i ] = i % c + 1;
  unordered_set<int> val;
  while( (int)val.size() < c )
    val.insert( myrand() );
  auto it = val.begin();
  for( int i = 1 ; i <= c ; i ++ ){
    clr[ i ] = *it;
    it ++;
  }
  n2 = 1;
  while( n2 <= n + m ) n2 <<= 1;
  n2 = min( n2 , MAXN );
  for( int i = 1 ; i <= m ; i ++ )
    A[ i ] = clr[ a[ i ] ];
  ntt( n2 , A );
}
bool okay[ (1 << 20) ];
LL B[ MAXN ];
void gogo(){
  for( int i = 0 ; i < n2 ; i ++ )
    B[ i ] = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    if( fr[ i ] == i ) continue;
    LL rnd = myrand();
    B[ n - i ] += rnd;
    if( B[ n - i ] >= P ) B[ n - i ] -= P;
    B[ n - fr[ i ] ] -= rnd;
    if( B[ n - fr[ i ] ] < 0 ) B[ n - fr[ i ] ] += P;
  }
  ntt( n2 , B );
  for( int i = 0 ; i < n2 ; i ++ )
    B[ i ] = (B[ i ] * A[ i ]) % P;
  ntt( n2 , B , 1 );
  for( int i = n ; i <= m ; i ++ )
    if( B[ i ] )
      okay[ i ] = false;
}
void solve(){
  for( int i = n ; i <= m ; i ++ )
    okay[ i ] = true;
  for( int _ = 0 ; ; _ ++ ){
    gogo();
    if( (clock() - s) > 4 * CLOCKS_PER_SEC )
      break;
  }
  for( int i = n ; i <= m ; i ++ )
    if( okay[ i ] )
      putchar( '1' );
    else
      putchar( '0' );
  puts( "" );
}
int main(){
  init();
  solve();
}
