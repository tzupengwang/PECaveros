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
int psum[ N ];
void build(){

}
int mn;
void init(){
  scanf( "%s" , c + 1 );
  len = strlen( c + 1 );
  for( int i = 1 ; i <= len ; i ++ )
    if( c[ i ] == 'a' ) psum[ i ] = psum[ i - 1 ] + 1;
    else psum[ i ] = psum[ i - 1 ] - 1;
  mn = len;
  for( int i = 1 ; i <= len ; i ++ )
    mn = min( mn , psum[ i ] );
}
int cal( int pre ){
  int cst = 0;
  vector<int> tmp;
  for( int i = 1 ; i <= len ; i ++ )
    if( c[ i ] == 'a' ) pre ++;
    else{
      if( pre <= 1 ){
        if( c[ i + 1 ] == 'a' ){
          swap( c[ i ] , c[ i + 1 ] );
          tmp.PB( i );
          cst ++;
          pre ++;
        }else{
          swap( c[ i + 1 ] , c[ i + 2 ] );
          swap( c[ i ] , c[ i + 1 ] );
          tmp.PB( i + 1 );
          tmp.PB( i );
          cst += 2;
          pre ++;
        }
      }else pre --;
    }
  cst += ( pre - 1 );
  for( int i = (int)tmp.size() - 1 ; i >= 0 ; i -- )
    swap( c[ tmp[ i ] ] , c[ tmp[ i ] + 1 ] );
  return cst;
}
void solve(){
  if( mn >= 1 ){
    printf( "Case %d: %d\n" , ++cs , psum[ len ] - 1 );
    return;
  }
  int x = 1 - mn;
  int ans = len + len;
  ans = min( ans , cal( x ) + x );
  if( psum[ len ] != mn ){
    ans = min( ans , cal( x - 1 ) + x - 1 );
    if( x - 2 >= 0 )
      ans = min( ans , cal( x - 2 ) + x - 2 );
  }
  printf( "Case %d: %d\n" , ++ cs , ans );
}
int main(){
    build();
   __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
