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
#define N 10
int dp[ N ][ 1 << N ][ 64 ];
bool inq[ N ][ 1 << N ][ 64 ];
int n , m , k;
void build(){

}
void init(){
//  n = getint();
//  m = getint();
//  k = getint();
  if( n > m ) swap( n , m );
  for( int i = 0 ; i <= m ; i ++ )
    for( int j = 0 ; j < ( 1 << n ) ; j ++ )
      for( int u = 0 ; u <= k ; u ++ ){
        inq[ i ][ j ][ u ] = false;
        dp[ i ][ j ][ u ] = 0;
      }
}
queue< tuple<int,int,int> > Q;
void solve(){
  for( int i = 0 ; i < ( 1 << n ) ; i ++ ){
    int nd = __builtin_popcount( i );
    if( nd <= k ){
      int nmsk = 0;
      for( int j = 0 ; j < n ; j ++ )
        if( ( i >> j ) & 1 ) break;
        else nmsk |= ( 1 << j );
      dp[ 1 ][ nmsk ][ k - nd ] ++;
      if( !inq[ 1 ][ nmsk ][ k - nd ] ){
        inq[ 1 ][ nmsk ][ k - nd ] = true;
        Q.push( MT( 1 , nmsk , k - nd ) );
      }
    }
  }
  while( Q.size() ){
    tuple<int,int,int> tp = Q.front(); Q.pop();
    int tn = get<0>( tp );
    int tmsk = get<1>( tp );
    int tres = get<2>( tp );
    if( tn == m ) continue;
    for( int i = 0 ; i < ( 1 << n ) ; i ++ ){
      int nd = __builtin_popcount( i );
      if( nd <= tres ){
        int nxtn = tn + 1;
        int nxtmsk = 0;
        if( ( tmsk & 1 ) && !( i & 1 ) ) nxtmsk |= 1;
        for( int j = 1 ; j < n ; j ++ )
          if( !( ( i >> j ) & 1 ) &&
              ( ( ( tmsk >> j ) & 1 ) ||
                ( ( nxtmsk >> ( j - 1 ) ) & 1 ) ) )
            nxtmsk |= ( 1 << j );
        int nxtres = tres - nd;
        dp[ nxtn ][ nxtmsk ][ nxtres ] += dp[ tn ][ tmsk ][ tres ];
        if( dp[ nxtn ][ nxtmsk ][ nxtres ] >= mod7 )
          dp[ nxtn ][ nxtmsk ][ nxtres ] -= mod7;
        if( !inq[ nxtn ][ nxtmsk ][ nxtres ] ){
          inq[ nxtn ][ nxtmsk ][ nxtres ] = true;
          Q.push( MT( nxtn , nxtmsk , nxtres ) );
        }
      }
    }
  }
  int ans = 0;
  for( int i = 0 ; i < ( 1 << ( n - 1 ) ) ; i ++ )
    for( int j = 0 ; j <= k ; j ++ ){
      ans += dp[ m ][ i ][ j ];
      if( ans >= mod7 ) ans -= mod7;
    }
//  printf( "Case #%d: %d\n" , ++ cs , ans );
  printf( "a[%d][%d][%d]=%d;\n" , n , m , k , ans );
}
int main(){
    build();
//    __ = getint();
//    while( __ -- ){
    for( int i = 1 ; i <= 8 ; i ++ )
      for( int j = 1 ; j <= 8 ; j ++ )
        for( int u = 0 ; u <= i * j ; u ++ ){
          n = i;
          m = j;
          k = u;
          init();
          solve();
        }
//    }
}
