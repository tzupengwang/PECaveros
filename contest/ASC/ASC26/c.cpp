// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long double LD;
typedef long long ll;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef pair<LD,LD> Pt;
typedef tuple<int,int,int> tiii;
typedef tuple<LL,LL,LL> tlll;
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
ll mypow( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 1ll;
  ll _tmp = mypow( _a , _x / 2 , _mod );
  _tmp = mul( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = mul( _tmp , _a , _mod );
  return _tmp;
}
ll mymul( ll _a , ll _x , ll _mod ){
  if( _x == 0 ) return 0ll;
  ll _tmp = mymul( _a , _x / 2 , _mod );
  _tmp = add( _tmp , _tmp , _mod );
  if( _x & 1 ) _tmp = add( _tmp , _a , _mod );
  return _tmp;
}
inline bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , _cs;
/*********default*********/
#define N 33
void build(){

}
struct Nd{
  LL bst , msk;
  int lnd , rnd;
  Nd(){
    bst = msk = 0;
    lnd = rnd = 0;
  }
} st[ 70 * 101010 ];
int ncnt = 1;
int newNd(){ return ncnt ++; }
#define mid ((l+r)>>1)
void modify( int no , LL l , LL r , LL p , LL vl , LL msk ){
  if( l == r ){
    if( vl <= st[ no ].bst ) return;
    st[ no ].bst = vl;
    st[ no ].msk = msk;
    return;
  }
  if( p <= mid ){
    if( !st[ no ].lnd ) st[ no ].lnd = newNd();
    modify( st[ no ].lnd , l , mid , p , vl , msk );
  }else{
    if( !st[ no ].rnd ) st[ no ].rnd = newNd();
    modify( st[ no ].rnd , mid + 1 , r , p , vl , msk );
  }
  int lc = st[ no ].lnd;
  int rc = st[ no ].rnd;
  if( lc && st[ lc ].bst > st[ no ].bst ){
    st[ no ].bst = st[ lc ].bst;
    st[ no ].msk = st[ lc ].msk;
  }
  if( rc && st[ rc ].bst > st[ no ].bst ){
    st[ no ].bst = st[ rc ].bst;
    st[ no ].msk = st[ rc ].msk;
  }
}
PLL query( int no , LL l , LL r , LL ql , LL qr ){
  if( !no || r < ql || l > qr || ql > qr ) return { 0 , 0 };
  if( ql <= l && r <= qr ) return { st[ no ].bst , st[ no ].msk };
  return max( query( st[ no ].lnd , l , mid , ql , qr ) ,
              query( st[ no ].rnd , mid + 1 , r , ql , qr ) );
}
int n;
LL l , r , w[ N ] , v[ N ];
void init(){
  n = getint();
  l = getint();
  r = getint();
  for( int i = 0 ; i < n ; i ++ ){
    w[ i ] = getint();
    v[ i ] = getint();
  }
}
vector< int > av;
LL ans;
void add_ans( LL tans , LL msk ){
  ans = tans;
  av.clear();
  for( int i = 0 ; i < n ; i ++ )
    if( ( msk >> i ) & 1ll )
      av.push_back( i + 1 );
}
#define MX 1000000000000000000ll
void solve(){
  int lhf = min( n , 16 );
  int rhf = max( 0 , n - 16 );
  int root = newNd();
  for( int i = 1 ; i < ( 1 << lhf ) ; i ++ ){
    LL sumw = 0 , sumv = 0;
    for( int j = 0 ; j < lhf ; j ++ )
      if( ( i >> j ) & 1 ){
        sumw += w[ j ];
        sumv += v[ j ];
      }
    if( l <= sumw && sumw <= r && sumv > ans )
      add_ans( sumv , (LL)i );
    modify( root , 0 , MX , sumw , sumv , i );
  }
  for( int i = 1 ; i < ( 1 << rhf ) ; i ++ ){
    LL sumw = 0 , sumv = 0;
    for( int j = 0 ; j < rhf ; j ++ )
      if( ( i >> j ) & 1 ){
        sumw += w[ 16 + j ];
        sumv += v[ 16 + j ];
      }
    if( l <= sumw && sumw <= r && sumv > ans )
      add_ans( sumv , ( (LL)i << 16 ) );
    LL lbdr = max( 0ll , l - sumw );
    LL rbdr = max( 0ll , r - sumw );
    PLL tp = query( root , 0 , MX , lbdr , rbdr );
    if( tp.FI == 0 ) continue;
    LL tans = tp.FI + sumv;
    if( tans > ans )
      add_ans( tans , ( (LL)i << 16 ) + tp.SE );
  }
  printf( "%d\n" , (int)av.size() );
  for( size_t i = 0 ; i < av.size() ; i ++ )
    printf( "%d%c" , av[ i ] , " \n"[ i + 1 == av.size() ] );
}
int main(){
  freopen( "dowry.in" , "r" , stdin );
  freopen( "dowry.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
