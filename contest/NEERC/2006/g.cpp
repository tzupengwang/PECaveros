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
#define N 1010
char c[ N ];
vector<int> v;
char toC( char ctmp ){
  if( ctmp >= 'a' && ctmp <= 'z' )
    return ctmp - 'a' + 'A';
  return ctmp;
}
char toS( char ctmp ){
  if( ctmp >= 'A' && ctmp <= 'Z' )
    return ctmp - 'A' + 'a';
  return ctmp;
}
int n;
void build(){

}
void init(){
  scanf( "%s" , c );
  n = strlen( c );
}
void solve(){
  for( int i = 0 ; i < n ; i ++ )
    if( c[ i ] == '<' ){
      if( c[ i + 1 ] == '/' ){
        if( c[ i + 2 ] == 'U' ) i += 4;
        else i += 6;
        v.pop_back();
      }else if( c[ i + 1 ] == 'U' ) v.PB( 1 ) , i += 3;
      else v.PB( 2 ) , i += 5;
    }else{
      if( v.size() && v.back() == 1 ) putchar( toC( c[ i ] ) );
      else if( v.size() && v.back() == 2 ) putchar( toS( c[ i ] ) );
      else putchar( c[ i ] );
    }
  puts( "" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
