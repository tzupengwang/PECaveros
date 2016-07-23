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
#define N 101010
void build(){

}
LL n , d[ N ] , p[ N ];
LL m , s[ N ] , t[ N ];
vector< PLL > vv , qv;
bool cmp( PLL p1 , PLL p2 ){
  if( p1.FI != p2.FI  ) return p1.FI < p2.FI;
  return p[ p1.SE ] < p[ p2.SE ];
}
void init(){
  qv.clear();
  vv.clear();
  for( int i = 0 ; i < n ; i ++ ){
    d[ i ] = getint();
    p[ i ] = getint();
    qv.push_back( { d[ i ] , i } );
  }
  m = getint();
  for( int i = 0 ; i < m ; i ++ ){
    s[ i ] = getint();
    t[ i ] = getint();
    vv.push_back( { s[ i ] , t[ i ] } );
  }
  sort( ALL( qv ) , cmp );
  sort( ALL( vv ) );
  int sz = 1;
  for( size_t i = 1 ; i < qv.size() ; i ++ )
    if( qv[ i ].FI != qv[ i - 1 ].FI )
      qv[ sz ++ ] = qv[ i ];
  qv.resize( sz );
}
void solve(){
  priority_queue< PLL > heap;
  LL pre = 0 , res = 0;
  size_t ptr = 0;
  for( size_t _ = 0 ; _ < qv.size() ; _ ++ ){
    res += qv[ _ ].FI - pre - 1;
    pre = qv[ _ ].FI;
    while( ptr < vv.size() && vv[ ptr ].SE <= qv[ _ ].FI ){
      res -= vv[ ptr ].SE - vv[ ptr ].FI + 1;
      ptr ++;
    }
    // printf( "%lld %lld\n" , qv[ _ ].FI , res );
    int i = qv[ _ ].SE;
    if( res >= p[ i ] ){
      heap.push( { p[ i ] , i } );
      res -= p[ i ];
    }else{
      if( heap.size() && heap.top().FI > p[ i ] ){
        res += heap.top().FI + 1;
        heap.pop();
        res -= p[ i ];
        heap.push( { p[ i ] , i } );
      }else res ++;
    }
    // printf( "%lld %lld\n" , qv[ _ ].FI , res );
  }
  vector< LL > ans;
  while( heap.size() ){
    ans.push_back( heap.top().SE + 1 );
    heap.pop();
  }
  sort( ALL( ans ) );
  printf( "%d\n" , (int)ans.size() );
  for( size_t i = 0 ; i < ans.size() ; i ++ )
    printf( "%lld%c" , ans[ i ] , " \n"[ i + 1 == ans.size() ] );
}
int main(){
  freopen( "intelligent.in" , "r" , stdin );
  freopen( "intelligent.out" , "w" , stdout );
  build();
  while( scanf( "%lld" , &n ) == 1 && n ){
    init();
    solve();
  }
}
