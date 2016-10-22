#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define SZ(X) ((int)X.size())

struct Bigint{
  static const int LEN = 100;
  static const int BIGMOD = 10000;

  int s;
  int vl, v[LEN];
  //  vector<int> v;
  Bigint() : s(1) { vl = 0; }
  Bigint(long long a) {
    s = 1; vl = 0;
    if (a < 0) { s = -1; a = -a; }
    while (a) {
      push_back(a % BIGMOD);
      a /= BIGMOD;
    }
  }
  Bigint(string str) {
    s = 1; vl = 0;
    int stPos = 0, num = 0;
    if (!str.empty() && str[0] == '-') {
      stPos = 1;
      s = -1;
    }
    for (int i=SZ(str)-1, q=1; i>=stPos; i--) {
      num += (str[i] - '0') * q;
      if ((q *= 10) >= BIGMOD) {
        push_back(num);
        num = 0; q = 1;
      }
    }
    if (num) push_back(num);
    n();
  }

  int len() const {
    return vl;
    //    return SZ(v);
  }
  bool empty() const { return len() == 0; }
  void push_back(int x) {
    v[vl++] = x;
    //    v.PB(x);
  }
  void pop_back() {
    vl--;
    //    v.pop_back();
  }
  int back() const {
    return v[vl-1];
    //    return v.back();
  }
  void n() {
    while (!empty() && !back()) pop_back();
  }
  void resize(int nl) {
    vl = nl;
    fill(v, v+vl, 0);
    //    v.resize(nl);
    //    fill(ALL(v), 0);
  }

  void print() const {
    if (empty()) { putchar('0'); return; }
    if (s == -1) putchar('-');
    printf("%d", back());
    for (int i=len()-2; i>=0; i--) printf("%.4d",v[i]);
  }
  friend std::ostream& operator << (std::ostream& out, const Bigint &a) {
    if (a.empty()) { out << "0"; return out; } 
    if (a.s == -1) out << "-";
    out << a.back();
    for (int i=a.len()-2; i>=0; i--) {
      char str[10];
      snprintf(str, 5, "%.4d", a.v[i]);
      out << str;
    }
    return out;
  }

  int cp3(const Bigint &b)const {
    if (s != b.s) return s - b.s;
    if (s == -1) return -(-*this).cp3(-b);
    if (len() != b.len()) return len()-b.len();//int
    for (int i=len()-1; i>=0; i--)
      if (v[i]!=b.v[i]) return v[i]-b.v[i];
    return 0;
  }

  bool operator < (const Bigint &b)const{ return cp3(b)<0; }
  bool operator <= (const Bigint &b)const{ return cp3(b)<=0; }
  bool operator == (const Bigint &b)const{ return cp3(b)==0; }
  bool operator != (const Bigint &b)const{ return cp3(b)!=0; }
  bool operator > (const Bigint &b)const{ return cp3(b)>0; }
  bool operator >= (const Bigint &b)const{ return cp3(b)>=0; }

  Bigint operator - () const {
    Bigint r = (*this);
    r.s = -r.s;
    return r;
  }
  Bigint operator + (const Bigint &b) const {
    if (s == -1) return -(-(*this)+(-b));
    if (b.s == -1) return (*this)-(-b);
    Bigint r;
    int nl = max(len(), b.len());
    r.resize(nl + 1);
    for (int i=0; i<nl; i++) {
      if (i < len()) r.v[i] += v[i];
      if (i < b.len()) r.v[i] += b.v[i];
      if(r.v[i] >= BIGMOD) {
        r.v[i+1] += r.v[i] / BIGMOD;
        r.v[i] %= BIGMOD;
      }
    }
    r.n();
    return r;
  }
  Bigint operator - (const Bigint &b) const {
    if (s == -1) return -(-(*this)-(-b));
    if (b.s == -1) return (*this)+(-b);
    if ((*this) < b) return -(b-(*this));
    Bigint r;
    r.resize(len());
    for (int i=0; i<len(); i++) {
      r.v[i] += v[i];
      if (i < b.len()) r.v[i] -= b.v[i];
      if (r.v[i] < 0) {
        r.v[i] += BIGMOD;
        r.v[i+1]--;
      }
    }
    r.n();
    return r;
  }
  Bigint operator * (const Bigint &b) const{
    Bigint r;
    r.resize(len() + b.len() + 1);
    r.s = s * b.s;
    for (int i=0; i<len(); i++) {
      for (int j=0; j<b.len(); j++) {
        r.v[i+j] += v[i] * b.v[j];
        if(r.v[i+j] >= BIGMOD) {
          r.v[i+j+1] += r.v[i+j] / BIGMOD;
          r.v[i+j] %= BIGMOD;
        }
      }
    }
    r.n();
    return r;
  }
  Bigint operator / (const Bigint &b) {
    Bigint r;
    r.resize(max(1, len()-b.len()+1));
    int oriS = s;
    Bigint b2 = b; // b2 = abs(b)
    s = b2.s = r.s = 1;
    for (int i=r.len()-1; i>=0; i--) {
      int d=0, u=BIGMOD-1;
      while(d<u) {
        int m = (d+u+1)>>1;
        r.v[i] = m;
        if((r*b2) > (*this)) u = m-1;
        else d = m;
      }
      r.v[i] = d;
    }
    s = oriS;
    r.s = s * b.s;
    r.n();
    return r;
  }
  Bigint operator % (const Bigint &b) {
    return (*this)-(*this)/b*b;
  }
};

#define N 300
#define K 300
Bigint C[ K ][ K ];
void build(){
  for( int i = 0 ; i < K ; i ++ )
    C[ i ][ 0 ] = C[ i ][ i ] = Bigint( 1 );
  for( int i = 2 ; i < K ; i ++ )
    for( int j = 1 ; j < i ; j ++ )
      C[ i ][ j ] = C[ i - 1 ][ j - 1 ] + C[ i - 1 ][ j ];
}
struct frac{
  Bigint p , q;
  frac(){ p = Bigint( 0 ); q = Bigint( 1 ); }
  frac( LL v ){
    p = Bigint( v ); q = Bigint( 1 );
  }
  frac( Bigint v ){
    p = v; q = Bigint( 1 );
  }
  frac( LL _p , LL _q ){
    p = Bigint( _p ); q = Bigint( _q );
    reduce();
  }
  frac( Bigint _p , Bigint _q ){
    p = _p; q = _q;
    reduce();
  }
  Bigint gcd( Bigint b1 , Bigint b2 ){
    if( b1 == Bigint( 0 ) ||
        b2 == Bigint( 0 ) )
      return b1 + b2;
    return gcd( b2 , b1 % b2 );
  }
  void reduce(){
    Bigint _g = gcd( p , q );
    p = p / _g; q = q / _g;
    if( q < Bigint( 0 ) ){
      p = -p; q = -q;
    }
  }
  frac operator+( const frac& ff ) const{
    frac ret = frac( p * ff.q + q * ff.p , q * ff.q );
    return ret;
  }
  frac operator-( const frac& ff ) const{
    frac ret = frac( p * ff.q - q * ff.p , q * ff.q );
    return ret;
  }
  frac operator*( const frac& ff ) const{
    frac ret = frac( p * ff.p , q * ff.q );
    return ret;
  }
  frac operator/( const frac& ff ) const{
    frac ret = frac( p * ff.q , q * ff.p );
    return ret;
  }
};
LL n , c[ N ];
Bigint ans;
void init(){
  scanf( "%lld" , &n );
  ans = Bigint( 0 );
  for( int i = 0 ; i <= n ; i ++ )
    scanf( "%lld" , &c[ i ] );
}
frac g[ N ] , f[ N ];
frac a[ N ];
void solve(){
  for( int i = 0 ; i <= n ; i ++ )
    f[ i ] = frac( c[ i ] );
  for( int i = n ; i >= 0 ; i -- ){
    g[ i + 1 ] = f[ i ] / frac( i + 1 );
    for( int j = 0 ; j < i ; j ++ ){
      frac tf = frac( C[ i + 1 ][ j ] ) * g[ i + 1 ];
      f[ j ] = f[ j ] - tf;
    }
  }
  for( int i = 0 ; i <= n + 1 ; i ++ )
    a[ i ] = frac( 0 );
  for( int i = 0 ; i <= n ; i ++ )
    for( int j = 0 ; j <= i + 1 ; j ++ )
      a[ j ] = a[ j ] + frac( C[ i + 1 ][ j ] ) * g[ i + 1 ];
  for( int i = 0 ; i <= n + 1 ; i ++ )
    if( a[ i ].p < Bigint( 0 ) )
      ans = ans - a[ i ].p;
    else
      ans = ans + a[ i ].p;
    //ans += abs( a[ i ].p );
  //for( int i = 0 ; i <= n + 1 ; i ++ )
    //printf( "%lld/%lld\n" , a[ i ].p , a[ i ].q );
  ans.print();
  //printf( "%lld\n" , ans );
}
int main(){
  build();
  int _; scanf( "%d" , &_ ); while( _ -- ){
    init();
    solve();
  }
}
