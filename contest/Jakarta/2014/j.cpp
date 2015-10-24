// eddy1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-9
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
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
bool equal( D _x ,  D _y ){
    return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 1000010
int n , m;
ll a[ N ] , pa[ N ] , b[ N ];
char c[ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  scanf( "%s" , c + 1 );
  a[ 0 ] = 1500000;
  for( int i = 1 ; i <= n ; i ++ )
    if( c[ i ] == '/' ) a[ i ] = a[ i - 1 ] + 1 , b[ i ] = a[ i ] - 1;
    else if( c[ i ] == '\\' ) a[ i ] = a[ i - 1 ] - 1 , b[ i ] = a[ i ];
    else a[ i ] = a[ i - 1 ] , b[ i ] = a[ i ];
  pa[ 0 ] = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( c[ i ] == '_' )
      pa[ i ] = pa[ i - 1 ] + 2 * a[ i ];
    else if( c[ i ] == '/' )
      pa[ i ] = pa[ i - 1 ] + 2 * a[ i ] - 1;
    else 
      pa[ i ] = pa[ i - 1 ] + 2 * a[ i ] + 1;
//  for( int i = 1 ; i <= n ; i ++ )
//    printf( "%lld " , pa[ i ] ); puts( "" );
}
int vl[ N ] , no[ N ] , pl , pr;
void pop_front(){ pl ++; }
void pop_back(){ pr --; }
void push( int tno , int tvl ){
  while( pl < pr ){
    if( tvl < vl[ pr - 1 ] ) pop_back();
    else break;
  }
  vl[ pr ] = tvl;
  no[ pr ++ ] = tno;
}
void solve(){
  pl = pr = 0;
  for( int i = 1 ; i < m ; i ++ )
    push( i , b[ i ] );
  ll fans = pa[ n ];
  for( int i = m ; i <= n ; i ++ ){
    while( pl < pr && no[ pl ] <= i - m )
      pop_front();
    push( i , b[ i ] );
    ll ans = pa[ i ] - pa[ i - m ];
    ll res = vl[ pl ] * (ll)m * 2;
    ans -= res;
//    printf( "%lld %lld\n" , ans , res );
    fans = min( fans , ans );
  }
  printf( "Case #%d: %lld.%lld\n" , ++ cs , fans / 2 , ( fans % 2 ) * 5 );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
