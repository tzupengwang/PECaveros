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
#define eps 1e-12
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
inline Pt operator-( const Pt& p1 , const Pt& p2 ){
  return { p1.X - p2.X , p1.Y - p2.Y };
}
int n;
LD a , b , alpha;
Pt p[ N ];
inline D getD(){
  D tmp;
  scanf( "%lf" , &tmp );
  return tmp;
}
inline void scan( Pt& tp ){
  tp.X = getint();
  tp.Y = getint();
}
void init(){
  a = getD();
  b = getD();
  alpha = getD();
  for( int i = 0 ; i <= n ; i ++ )
    scan( p[ i ] );
}
inline Pt cal(){
  LD sum = 0.0;
  vector< Pt > vv;
  for( int i = 1 ; i <= n ; i ++ ){
    if( equal( p[ i ].Y , p[ i - 1 ].Y ) ){
      if( a - eps < p[ i ].Y && p[ i ].Y < b + eps ){
        sum += p[ i ].X - p[ i - 1 ].X;
        vv.PB( { p[ i - 1 ].X , p[ i ].X } );
      }
    }else{
      Pt dlt = p[ i ] - p[ i - 1 ];
      LD ka = ( a - p[ i - 1 ].Y ) / dlt.Y;
      LD kb = ( b - p[ i - 1 ].Y ) / dlt.Y;
      LD pa = p[ i - 1 ].X + ka * dlt.X;
      LD pb = p[ i - 1 ].X + kb * dlt.X;
      if( pa > pb ) swap( pa , pb );
      pa = max( pa , p[ i - 1 ].X );
      pb = min( pb , p[ i     ].X );
      if( pa < pb + eps ){
        sum += pb - pa;
        vv.PB( { pa , pb } );
      }
    }
  }
  LD nd = sum * alpha;
  LD al = 0.0 , ar = p[ n ].X;
  LD got = 0.0;
  for( size_t l = 0 , r = 0 ; l < vv.size() ; l ++ ){
    while( r < vv.size() && got + vv[ r ].SE - vv[ r ].FI < nd - eps ){
      got += vv[ r ].SE - vv[ r ].FI; r ++;
    }
    if( got < nd - eps ){
      if( r >= vv.size() ) break;
      got += vv[ r ].SE - vv[ r ].FI; r ++;
    }
    LD ls = vv[ l ].FI;
    LD rs = vv[ r - 1 ].SE - ( got - nd );
    if( rs - ls < ar - al )
      al = ls , ar = rs;
    got -= vv[ l ].SE - vv[ l ].FI;
  }
  return { al , ar };
}
void solve(){
  Pt ans = cal();
  printf( "%.12f %.12f\n" , (D)ans.X , (D)ans.Y );
}
int main(){
  build();
  freopen( "bayes.in" , "r" , stdin );
  freopen( "bayes.out" , "w" , stdout );
  //__ = getint();
  // while( __ -- ){
  while( scanf( "%d" , &n ) == 1 ){
    if( n == 0 ) break;
    init();
    solve();
  }
}
