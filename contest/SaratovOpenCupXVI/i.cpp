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
int __ = 1 , _cs;
/*********default*********/
#define N 303030
int st[ N << 2 ];
#define L(X) (X<<1)
#define R(X) (1+(X<<1))
#define mid ((l+r)>>1)
void modify( int no , int l , int r , int p , int x ){
  if( l == r ){
    st[ no ] = x;
    return;
  }
  if( p <= mid ) modify( L( no ) , l , mid , p , x );
  else modify( R( no ) , mid + 1 , r , p , x );
  st[ no ] = min( st[ L( no ) ] , st[ R( no ) ] );
}
int query( int no , int l , int r , int ql ){
  if( l == r ) return l;
  if( st[ L( no ) ] < ql ) return query( L( no ) , l , mid , ql );
  return query( R( no ) , mid + 1 , r , ql );
}
int n , ff[ N ];
void build(){

}
void init(){
  n = getint();
  for( int i = 1 ; i <= n ; i ++ )
    ff[ i ] = INF;
  for( int i = 1 ; i <= n ; i ++ ){
    int ci = getint(); while( ci -- ){
      int tmp = getint();
      ff[ tmp ] = min( ff[ tmp ] , i );
    }
  }
}
int ans[ N ];
void solve(){
  ans[ 1 ] = 1;
  modify( 1 , 1 , n , ans[ 1 ] , 1 );
  for( int i = 2 ; i <= n ; i ++ ){
    int tmp = ff[ i ];
    if( tmp == INF ) ans[ i ] = 1;
    else{
      if( tmp == i - 1 ) ans[ i ] = 1;
      else ans[ i ] = query( 1 , 1 , n , tmp + 1 );
    }
    modify( 1 , 1 , n , ans[ i ] , i );
  }
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i == n ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
