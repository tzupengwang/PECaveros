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
#define N 111
void build(){

}
int n;
D a , b;
D p[ N ] , q[ N ] , s[ N ];
void init(){
  n = getint();
  a = getint();
  b = getint();
  for( int i = 0 ; i < n ; i ++ ){
    p[ i ] = getint();
    q[ i ] = getint();
    s[ i ] = getint();
  }
}
inline D cal( D gt , bool print = false ){
  D cst = gt * b;
  for( int i = 0 ; i < n ; i ++ ){
    D got = s[ i ] * gt;
    if( got < p[ i ] )
      cst += ( p[ i ] - got ) / q[ i ] * a;
  }
  if( print ){
    printf( "%.12f\n" , cst );
    printf( "%.12f\n" , gt );
    for( int i = 0 ; i < n ; i ++ ){
      D got = s[ i ] * gt , nd = 0.0;
      if( got < p[ i ] )
        nd = ( p[ i ] - got ) / q[ i ];
      printf( "%.12f%c" , nd , " \n"[ i + 1 == n ] );
    }
  }
  return cst;
}
void solve(){
  D l = 0.0 , r = 1e20 , ai = 1e20 , ans = 1e20;
  for( int i = 0 ; i < 200 ; i ++ ){
    D m1 = l + ( r - l ) / 3;
    D m2 = r - ( r - l ) / 3;
    D ans1 = cal( m1 );
    D ans2 = cal( m2 );
    if( ans1 < ans2 ){
      if( ans1 < ans ){
        ans = ans1;
        ai = m1;
      }
      r = m2;
    }else{
      if( ans2 < ans ){
        ans = ans2;
        ai = m2;
      }
      l = m1;
    }
  }
  cal( ai , true );
}
int main(){
  freopen( "academy.in" , "r" , stdin );
  freopen( "academy.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
