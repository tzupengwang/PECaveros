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
int y , m , d , cnt;
int dy[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
void build(){

}
bool leaf(){
  if( y % 400 == 0 ) return true;
  if( y % 100 == 0 ) return false;
  if( y % 4 == 0 ) return true;
  return false;
}
void init(){
  cnt = 0;
  for( int i = 100 ; i < y ; i += 100 )
    if( i % 400 != 0 )
      cnt ++;
  if( y % 100 == 0 && y % 400 != 0 ){
    if( m > 2 || ( m == 2 && d == 29 ) )
      cnt ++;
  }
  cnt --;
}
void nxt_day(){
  d ++;
  if( ( m != 2 && d > dy[ m ] ) ||
      ( m == 2 && ( ( leaf()  && d > 29 ) ||
                    ( !leaf() && d > 28 ) ) ) ){
    d = 1;
    m ++;
  }
  if( m > 12 ){
    y ++;
    m = 1;
  }
}
void solve(){
  while( cnt -- )
    nxt_day();
  printf( "%d-%02d-%02d\n" , y , m , d );
}
int main(){
  build();
  //__ = getint();
  while( scanf( "%d-%d-%d" , &y , &m , &d ) == 3 ){
    init();
    solve();
  }
}
