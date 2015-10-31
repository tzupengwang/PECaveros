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
#define N 20
int n , m , a[ N ] , p[ 2 ][ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  for( int i = 1 ; i <= n ; i ++ )
    a[ i ] = getint();
  int ptr = 1 , bt = 0;
  for( int i = 0 ; i < m ; i ++ ){
    int tmp = getint();
    while( tmp -- ){
      p[ 0 ][ ptr ] = bt;
      p[ 1 ][ ptr ] = 1 - bt;
      ptr ++;
    }
    bt = 1 - bt;
  }
}
int dist( int idx ){
  vector<int> b1 , b0;
  vector<int> d1 , d0;
  for( int i = 1 ; i <= n ; i ++ ){
    if( a[ i ] ) b1.PB( i );
    else b0.PB( i );
    if( p[ idx ][ i ] ) d1.PB( i );
    else d0.PB( i );
  }
  if( b1.size() != d1.size() ||
      b0.size() != d0.size() )
    return n * n;
  int ans = 0;
  for( int i = 0 ; i < (int)b1.size() ; i ++ )
    ans += abs( b1[ i ] - d1[ i ] );
  for( int i = 0 ; i < (int)b0.size() ; i ++ )
    ans += abs( b0[ i ] - d0[ i ] );
  return ans / 2;
}
void solve(){
  printf( "%d\n" , min( dist( 0 ) , dist( 1 ) ) );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
