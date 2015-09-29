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
#define N 2010
int n , s;
int num( char ctmp ){
  if( ctmp == 'A' ) return 11;
  if( ctmp == 'J' ) return 10;
  if( ctmp == 'Q' ) return 10;
  if( ctmp == 'K' ) return 10;
  if( ctmp == '1' ) return 10;
  return ctmp - '0';
}
int nxt[]={2,3,4,5,6,7,8,9,10,10,10,10,11};
// 10 2 ... 9 A J Q K
int a[ N ]; // -1;
D po[ N ]; // -1;
void build(){

}
void init(){
  for( int i = 1 ; i < s ; i ++ )
    a[ i ] = -1;
  for( int i = 1 ; i <= n ; i ++ ){
    char c[ 3 ];
    scanf( "%s" , c );
    int stp = num( c[ 0 ] );
    a[ s ] = stp;
    po[ s ] = 1.0;
    if( i < n ){
      for( int j = s + 1 ; j < s + stp ; j ++ )
        a[ j ] = -1;
      s += stp;
    }
  }
}
void solve(){
//  for( int i = 1 ; i <= s ; i ++ )
//    printf( "%d\n" , a[ i ] );
  for( int i = s ; i >= 1 ; i -- ) if( a[ i ] < 0 ){
    po[ i ] = 0.0;
    for( int k = 0 ; k < 13 ; k ++ )
      if( i + nxt[ k ] <= s )
        po[ i ] += po[ i + nxt[ k ] ] / 13.0;
  }
  D ans = 0.0;
  for( int i = 1 ; i <= min( 10 , s ) ; i ++ )
    ans += po[ i ] / 10.0;
  printf( "%.12f\n" , ans );
}
int main(){
  build();
  //__ = getint();
  while( cin >> n >> s ){
    init();
    solve();
  }
}
