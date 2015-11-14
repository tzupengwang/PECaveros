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
#define N 514514
char c[ N ];
int len;
void build(){

}
int cnta, cntp, adda;
void init(){
  scanf( "%s" , c );
  len = strlen( c );
  cnta = 0; cntp = 0;
  for( int i = 0 ; i < len ; i ++ )
    if( c[ i ] == 'a' ) cnta ++;
    else cntp ++;
  adda = max( 0 , ( cntp + 1 - cnta ) );
  for( int i = len - 1 ; i >= 0 ; i -- )
    c[ i + adda ] = c[ i ];
  for( int i = 0 ; i < adda ; i ++ )
    c[ i ] = 'a';
  len += adda;
}
int cal( int pre ){
  int ans = 0;
  vector<int> tmp;
  for( int i = 1 ; i < len ; i ++ ){
    if( c[ i ] == 'a' ) pre ++;
    else if( c[ i ] == '+' ){
      if( pre == 1 ){
        if( i + 1 < len && c[ i + 1 ] == 'a' ){
          swap( c[ i ] , c[ i + 1 ] );
          tmp.PB( i );
          ans ++;
          pre ++;
        }else ans ++;
      }else pre --;
    }
  }
  for( int i = (int)tmp.size() - 1 ; i >= 0 ; i -- )
    swap( c[ tmp[ i ] ] , c[ tmp[ i ] + 1 ] );
  return ans + ( pre - 1 );
}
void solve(){
  int ans = len + len;
  if( c[ 0 ] == '+' ){
    ans = min( ans , cal( 1 ) + 2 );
    if( 1 < len && c[ 1 ] == 'a' ){
      swap( c[ 0 ] , c[ 1 ] );
      ans = min( ans , cal( 2 ) + 2 );
      if( 2 < len && c[ 2 ] == 'a' ){
        swap( c[ 1 ] , c[ 2 ] );
        ans = min( ans , cal( 1 ) + 2 );
        swap( c[ 1 ] , c[ 2 ] );
      }
      swap( c[ 0 ] , c[ 1 ] );
    }
  }else ans = cal( 1 );
  printf( "Case %d: %d\n" , ++cs , ans + adda );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
