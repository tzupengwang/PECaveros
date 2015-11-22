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
ll add( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x + _y;
  if( _ >= _mod ) _ -= _mod;
  return _;
}
ll sub( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x - _y;
  if( _ < 0 ) _ += _mod;
  return _;
}
ll mul( ll _x , ll _y , ll _mod = mod7 ){
  ll _ = _x * _y;
  if( _ >= _mod ) _ %= _mod;
  return _;
}
bool equal( D _x ,  D _y ){
  return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 1010
void build(){

}
int n , a[ N ] , xn;
bool del[ N ];
vector< PII > v;
void init(){
  n = getint(); xn = 0;
  for( int i = 0 ; i < n ; i ++ ){
    char tc[ 5 ]; int x;
    scanf( "%s%d" , tc , &x );
    a[ i ] = x;
    del[ i ] = ( tc[ 0 ] == 'y' );
    if( i == 0 ){
      a[ xn ] = a[ i ];
      del[ xn ++ ] = del[ i ];
    }else if( del[ i ] ){
      if( del[ i ] == del[ xn - 1 ] )
        a[ xn - 1 ] = min( a[ xn - 1 ] , a[ i ] );
      else{
        a[ xn ] = a[ i ];
        del[ xn ++ ] = del[ i ];
      }
    }else{
      if( del[ i ] == del[ xn - 1 ] )
        a[ xn - 1 ] = max( a[ xn - 1 ] , a[ i ] );
      else{
        a[ xn ] = a[ i ];
        del[ xn ++ ] = del[ i ];
      }
    }
  }
  n = xn;
  // for( int i = 0 ; i < n ; i ++ )
    // printf( "%d %d\n" , a[ i ] , del[ i ] );
}
bool er[ N ];
int ecnt;
int cal( int l , int r ){
  int nd = 0, cst = 0;
  for( int i = l ; i <= r ; i ++ )
    if( del[ i ] ) nd ++;
  while( ecnt < nd ){
    int mn = INF;
    for( int i = l ; i <= r ; i ++ )
      if( del[ i ] && !er[ i ] )
        mn = min( mn , a[ i ] );
    if( mn == INF ) break;
    for( int i = l ; i <= r ; i ++ )
      if( del[ i ] && !er[ i ] && a[ i ] == mn ){
        cst ++;
        er[ i ] = true;
        for( int j = i ; j >= l ; j -- ){
          if( !del[ j ] && a[ j ] >= mn ) break;
          if( del[ j ] ) er[ j ] = true;
        }
        for( int j = i ; j <= r ; j ++ ){
          if( !del[ j ] && a[ j ] >= mn ) break;
          if( del[ j ] ) er[ j ] = true;
        }
      }
  }
  return cst;
}
void solve(){
  int ans = cal( 0 , n - 1 );
  printf( "%d\n" , ans );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
