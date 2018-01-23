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
int n , k , res;
void build(){

}
void init(){
  scanf( "%s" , c + 1 );
  n = strlen( c + 1 );
  k = getint();
  res = n - k;
}
void solve(){
  int pre = 0;
  for( int i = 1 ; i <= res ; i ++ ){
    for( int j = 9 ; j >= 0 ; j -- ){
      bool got = false;
      for( int tk = pre + 1 ; n - tk + 1 >= res - i + 1 ; tk ++ )
        if( c[ tk ] - '0' == j ){
          putchar( c[ tk ] );
          pre = tk;
          got = true;
          break;
        }
      if( got ) break;
    }
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
