// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef pair<LD,LD> Pt;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define X FI
#define Y SE
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
#ifndef ONLINE_JUDGE
#define debug(...) printf(__VA_ARGS__)
#else 
#define debug(...)
#endif
inline ll getint(){
  ll _x=0,_tmp=1; char _tc=getchar();    
  while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
  if( _tc == '-' ) _tc=getchar() , _tmp = -1;
  while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
  return _x*_tmp;
}
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = ( _tmp * _tmp ) % _mod;
  if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
  return _tmp;
}
inline ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
inline ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
inline ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
struct Bigint{
  static const int LEN = 256;
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
  }
  int len() const { return vl; /* return SZ(v);*/ }
  bool empty() const { return len() == 0; }
  void push_back(int x) { v[vl++] = x; /* v.PB(x); */}
  void pop_back() { vl--; /* v.pop_back(); */ }
  int back() const { return v[vl-1]; /* return v.back(); */ }
  void n() { while (!empty() && !back()) pop_back(); }
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
    if (s != b.s) return s > b.s;
    if (s == -1) return -(-*this).cp3(-b);
    if (len() != b.len()) return len()>b.len()?1:-1;
    for (int i=len()-1; i>=0; i--)
      if (v[i]!=b.v[i]) return v[i]>b.v[i]?1:-1;
    return 0;
  }
  bool operator < (const Bigint &b)const{ return cp3(b)==-1; }
  bool operator == (const Bigint &b)const{ return cp3(b)==0; }
  bool operator > (const Bigint &b)const{ return cp3(b)==1; }

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
  Bigint operator * (const Bigint &b) {
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
#define N 1111
#define K 36
int b;
bool can[ N ];
char num[ N ];
void build(){

}
int trans( char ctmp ){
  if( ctmp >= '0' && ctmp <= '9' ) return ctmp - '0';
  return ctmp - 'A' + 10;
}
char rtrans( int tk ){
  if( tk < 10 ) return tk + '0';
  return tk - 10 + 'A';
}
vector<int> v;
string in;
Bigint a;
int n;
void init(){
  b = getint();
  scanf( "%s" , num );
  int len = strlen( num );
  for( int i = 0 ; i < len ; i ++ )
    can[ trans( num[ i ] ) ] = true;
  cin >> in;
  a = Bigint( in );
  Bigint _b( b );
  while( !( a == Bigint( 0 ) ) ){
    Bigint k = a % _b;
    v.PB( k.v[ 0 ] );
    a = a / _b;
  }
  n = (int)v.size();
  // for( int i = n - 1 ; i >= 0 ; i -- )
    // printf( "%d " , v[ i ] );
  // puts( "" );
}
int dp[ N ][ K ];
int back[ N ][ K ];
int bn[ N ][ K ];
void find_ans(){
  int ta = 0 , tb = 0;
  vector< char > vans;
  while( ta < n ){
    vans.PB( rtrans( bn[ ta ][ tb ] ) );
    tb = back[ ta ][ tb ];
    ta ++;
  }
  while( vans.size() && vans.back() == '0' ) vans.pop_back();
  if( vans.size() == 0 ) vans.PB( '0' );
  reverse( ALL( vans ) );
  for( int i = 0 ; i < (int)vans.size() ; i ++ )
    putchar( vans[ i ] );
  puts( "" );
}
void solve(){
  for( int i = 0 ; i < K && i <= v[ n - 1 ] ; i ++ )
    if( can[ i ] ){
      dp[ n - 1 ][ v[ n - 1 ] - i ] = 1;
      bn[ n - 1 ][ v[ n - 1 ] - i ] = i;
    }
  for( int i = n - 1 ; i > 0 ; i -- )
    for( int j = 0 ; j < K ; j ++ ) if( dp[ i ][ j ] ){
      int now = i - 1;
      int sum = j * b + v[ i - 1 ];
      for( int tk = 0 ; tk < K && tk <= sum ; tk ++ )
        if( can[ tk ] ){
          int nxt = sum - tk;
          if( nxt < K ){
            dp[ now ][ nxt ] += dp[ i ][ j ];
            back[ now ][ nxt ] = j;
            bn[ now ][ nxt ] = tk;
          }
        }
    }
  if( dp[ 0 ][ 0 ] == 0 ) puts( "Impossible" );
  else{
    if( dp[ 0 ][ 0 ] == 1 ) puts( "Unique" );
    else puts( "Ambiguous" );
    find_ans();
  }
}
int main(){
  freopen( "digits.in" , "r" , stdin );
  freopen( "digits.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
