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
ll n , t , x[ N ] , y[ N ];
int dir[ N ];
char tdir[ N ];
vector<PLL> e[ N ];
void build(){

}
bool cmp( int ii , int jj ){
  if( y[ ii ] != y[ jj ] )
    return y[ ii ] < y[ jj ];
  return x[ ii ] < x[ jj ];
}
bool cmp2( int ii , int jj ){
  if( x[ ii ] != x[ jj ] )
    return x[ ii ] < x[ jj ];
  return y[ ii ] < y[ jj ];
}
void build_edge(){
  vector< int > v;
  for( int i = 0 ; i < n ; i ++ )
    v.PB( i );
  sort( ALL( v ) , cmp );
  for( int l = 0 , r = 0 ; l < n ; l = r ){
    while( r < n && y[ v[ r ] ] == y[ v[ l ] ] ) r ++;
    int pre = -1;
    for( int i = l ; i < r ; i ++ ){
      if( pre != -1 ) e[ pre ].PB( MP( v[ i ] , x[ v[ i ] ] - x[ pre ] ) );
      if( dir[ v[ i ] ] == 2 ) pre = v[ i ];
    }
    pre = -1;
    for( int i = r - 1 ; i >= l ; i -- ){
      if( pre != -1 ) e[ pre ].PB( MP( v[ i ] , x[ pre ] - x[ v[ i ] ] ) );
      if( dir[ v[ i ] ] == 1 ) pre = v[ i ];
    }
  }
  sort( ALL( v ) , cmp2 );
  for( int l = 0 , r = 0 ; l < n ; l = r ){
    while( r < n && x[ v[ r ] ] == x[ v[ l ] ] ) r ++;
    int pre = -1;
    for( int i = l ; i < r ; i ++ ){
      if( pre != -1 ) e[ pre ].PB( MP( v[ i ] , y[ v[ i ] ] - y[ pre ] ) );
      if( dir[ v[ i ] ] == 0 ) pre = v[ i ];
    }
    pre = -1;
    for( int i = r - 1 ; i >= l ; i -- ){
      if( pre != -1 ) e[ pre ].PB( MP( v[ i ] , y[ pre ] - y[ v[ i ] ] ) );
      if( dir[ v[ i ] ] == 3 ) pre = v[ i ];
    }
  }
}
ll dx[]={0,-1,1,0};
ll dy[]={1,0,0,-1};
inline int trans( char ctmp ){
  if( ctmp == 'U' ) return 0;
  if( ctmp == 'L' ) return 1;
  if( ctmp == 'R' ) return 2;
  return 3;
}
void init(){
  n = getint(); t = getint();
  for( int i = 0 ; i < n ; i ++ ){
    x[ i ] = getint();
    y[ i ] = getint();
    scanf( "%s" , tdir );
    dir[ i ] = trans( tdir[ 0 ] );
  }
}
ll dst[ N ];
bool got[ N ];
priority_queue< PLL , vector<PLL> , greater<PLL> > heap;
inline void SP(){
  heap.push( MP( 0 , 0 ) );
  while( heap.size() ){
    PLL tp = heap.top(); heap.pop();
    ll tdist = tp.FI , tn = tp.SE;
    if( got[ tn ] ) continue;
    got[ tn ] = true;
    dst[ tn ] = tdist;
    for( size_t i = 0 ; i < e[ tn ].size() ; i ++ )
      if( !got[ e[ tn ][ i ].FI ] )
        heap.push( MP( tdist + e[ tn ][ i ].SE , e[ tn ][ i ].FI ) );
  }
}
void solve(){
  build_edge();
  SP();
  for( int i = 0 ; i < n ; i ++ )
    if( !got[ i ] || t <= dst[ i ] )
      printf( "%lld %lld\n" , x[ i ] , y[ i ] );
    else{
      ll tt = t - dst[ i ];
      printf( "%lld %lld\n" , x[ i ] + dx[ dir[ i ] ] * tt
                            , y[ i ] + dy[ dir[ i ] ] * tt );
    }
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
