typedef long long LL;
// Remember coefficient are mod P
/* p=a*2^n+1
   n		2^n 				p 				 a 		root
   5		32 					97 				 3 		5
   6		64 					193 			 3 		5
   7		128					257				 2 		3
   8		256 				257 			 1 		3
   9		512 				7681 			 15 	17
   10 	1024 				12289 		 12 	11
   11 	2048 				12289 		 6 		11
   12 	4096 				12289 		 3 		11
   13 	8192 				40961 		 5		3
   14 	16384				65537 		 4 		3
   15 	32768 			65537 		 2 		3
   16 	65536 			65537 		 1 		3
   17 	131072 			786433 		 6 		10
   18 	262144 			786433 		 3 		10 (605028353, 2308, 3)
   19 	524288 			5767169 	 11 	3
   20 	1048576		 	7340033 	 7 		3
   21 	2097152			23068673 	 11 	3
   22 	4194304 		104857601  25 	3
   23 	8388608		 	167772161  20 	3
   24 	16777216 		167772161  10 	3
   25 	33554432 		167772161  5 		3 (1107296257, 33, 10)
   26 	67108864 		469762049  7 		3
   27 	134217728 	2013265921 15 	31 */
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
const LL P=2013265921,root=31;
const int MAXN=4194304;
NTT<P, root, MAXN> ntt;
