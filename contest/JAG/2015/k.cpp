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
#define N 1021
#define K 52
int n , k , a[ N ];
ll dp[ N ][ N ][ K ];
bool got[ N ][ N ][ K ];
int bst[ N ][ N ][ K ];
void build(){

}
void init(){
  n = getint(); k = getint();
  for( int i = 1 ; i <= n ; i ++ )
    a[ i ] = getint();
  sort( a + 1 , a + n + 1 );
}
ll DP( int l , int r , int dep ){
  if( dep > k ){
    dp[ l ][ r ][ dep ] = INF16;
    bst[ l ][ r ][ dep ] = l;
    return INF16;
  }
  if( l == r ){
    dp[ l ][ r ][ dep ] = 0;
    bst[ l ][ r ][ dep ] = l;
    return 0;
  }
  if( got[ l ][ r ][ dep ] )
    return dp[ l ][ r ][ dep ];
  got[ l ][ r ][ dep ] = true;
  dp[ l ][ r ][ dep ] = INF16;
  DP( l , r - 1 , dep );
  DP( l + 1 , r , dep );
  for( int u = bst[ l ][ r - 1 ][ dep ] ;
           u <= min( bst[ l + 1 ][ r ][ dep ] , r - 1 ) ; u ++ ){
    ll tcst = a[ r ] - a[ u ] + DP( l , u , dep + 1 ) +
                                DP( u + 1 , r , dep + 1 );
    if( tcst < dp[ l ][ r ][ dep ] ){
      dp[ l ][ r ][ dep ] = tcst;
      bst[ l ][ r ][ dep ] = u;
    }
  }
  return dp[ l ][ r ][ dep ];
}
void solve(){
  printf( "%lld\n" , DP( 1 , n , 0 ) );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
