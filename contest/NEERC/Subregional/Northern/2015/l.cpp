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
#define N 111
int n , m , a[ N ][ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      a[ i ][ j ] = getint();
}
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
bool in( int xn , int xm ){
  return 1 <= xn && xn <= n &&
         1 <= xm && xm <= m;
}
void solve(){
  int ans = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = 1 ; j <= m ; j ++ ){
      for( int k = 0 ; k < 4 ; k ++ ){
        bool flag = true;
        for( int l = 1 ; l <= max( n , m ) ; l ++ ){
          if( !in( i + l * dx[ k ] , j + l * dy[ k ] ) ) break;
          if( a[ i + l * dx[ k ] ][ j + l * dy[ k ] ] >= a[ i ][ j ] )
            flag = false;
        }
       if( flag ) ans ++;
      }
    }
  }
  printf( "%d\n" , ans );
}
int main(){
  freopen( "lucky.in" , "r" , stdin );
  freopen( "lucky.out" , "w" , stdout );
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
