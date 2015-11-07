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
#define N 32
int r , c , all;
int oa[ N ][ N ];
int a[ N ][ N ];
void build(){

}
void init(){
  r = getint();
  c = getint();
  all = 0;
  for( int i = 1 ; i <= r ; i ++ )
    for( int j = 1 ; j <= c ; j ++ ){
      oa[ i ][ j ] = a[ i ][ j ] = getint();
      all += a[ i ][ j ];
    }
}
bool flag;
int ansi[ N ], ansj[ N ];
bool okay( int ni , int nj , int hf ){
  if( ni + hf > r || ni - hf < 1 ||
      nj + hf > c || nj - hf < 1 ) return false;
  for( int i = -hf ; i <= hf ; i ++ )
    if( a[ ni + i ][ nj ] == 0 ||
        a[ ni ][ nj + i ] == 0 ) return false;
  return true;
}
void md( int ni , int nj , int hf , int dlt ){
  for( int i = -hf ; i <= hf ; i ++ ){
    a[ ni + i ][ nj ] += dlt;
    a[ ni ][ nj + i ] += dlt;
    if( i == 0 ) a[ ni ][ nj ] -= dlt;
  }
}
void DFS( int ni , int nj , int got , int gott ){
  if( flag ) return;
  if( got == all ){
    int xi = 0 , xj = 0;
    for( int i = 0 ; i < gott ; i ++ )
      if( ansi[ i ] > xi ||
          ( ansi[ i ] == xi && ansj[ i ] > xj ) )
        xi = ansi[ i ], xj = ansj[ i ];
    printf( "%d\n%d %d\n" , gott , xi , xj );
    flag = true;
    return;
  }
  if( nj > c ) ni ++, nj = 1;
  if( ni > r - 2 ) return;
  for( int i = ni ; i <= r ; i ++ )
    for( int j = i == ni ? nj : 1 ; j <= c ; j ++ )
      if( a[ i ][ j ] > 0 ){
        for( int k = 3 ; k <= 11 ; k += 2 ){
          int hf = k / 2;
          if( okay( i + hf , j , hf ) &&
              oa[ i + hf ][ j ] == 1 ){
            md( i + hf , j , hf , -1 );
            ansi[ gott ] = i + hf;
            ansj[ gott ] = j;
            DFS( i , j + 1 , got + k + k - 1 , gott + 1 );
            if( flag ) return;
            md( i + hf , j , hf , 1 );
          }
        }
        break;
      }
}
void solve(){
  flag = false;
  DFS( 1 , 1 , 0 , 0 );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
