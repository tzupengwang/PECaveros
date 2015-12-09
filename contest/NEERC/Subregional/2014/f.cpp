// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef __float128 D;
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
#define N 303030
int n , m , done[ N ];
int ti[ N ] , pmax[ N ];
D p[ N ] , good[ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  good[ 0 ] = 1.0;
  for( int i = 1 ; i <= n ; i ++ ){
    double tp;
    scanf( "%d%lf" , &ti[ i ] , &tp );
    p[ i ] = tp;
    good[ i ] = good[ i - 1 ] * p[ i ];
  }
}
multiset< int > S;
void solve(){
  for( int i = 1 ; i <= min( n , m ) ; i ++ ){
    done[ i ] = ti[ i ];
    S.insert( ti[ i ] );
  }
  for( int i = m + 1 ; i <= n ; i ++ ){
    done[ i ] = *S.begin() + ti[ i ];
    S.erase( S.find( *S.begin() ) );
    S.insert( done[ i ] );
  }
  for( int i = 1 ; i <= n ; i ++ )
    pmax[ i ] = max( pmax[ i - 1 ] , done[ i ] );
  D ans = good[ n ] * pmax[ n ];
  for( int i = 1 ; i <= n ; i ++ )
    ans += ( good[ i - 1 ] * ( 1.0 - p[ i ] ) ) * pmax[ i ];
  // D ans = pmax[ n ];
  // for( int i = 1 ; i <= n ; i ++ )
    // if( ans > eps )
      // ans *= p[ i ];
    // else break;
  // for( int i = 1 ; i <= n ; i ++ ){
    // D tans = pmax[ i ] * ( 1.0 - p[ i ] );
    // for( int j = 1 ; j < i ; j ++ )
      // if( tans > eps )
        // tans *= p[ j ];
      // else break;
    // ans += tans;
  // }
  printf( "%.12f\n" , (double)ans );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
