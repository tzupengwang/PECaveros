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
int n , k;
vector<int> pr1 , pr2;
void build(){

}
void init(){
  n = getint();
  k = getint();
  pr1.clear();
  pr2.clear();
  for( int i = 1 ; i <= k ; i ++ ){
    int tp = getint();
    if( tp * tp <= 1000 ) pr1.push_back( tp );
    else pr2.push_back( tp );
  }
}
bool tk[ N ];
int test( int msk ){
  for( int i = 1 ; i <= n ; i ++ ) tk[ i ] = false;
  for( int i = 0 ; i < (int)pr1.size() ; i ++ )
    if( ( msk >> i ) & 1 ){
      for( int j = pr1[ i ] ; j <= n ; j += pr1[ i ] )
        tk[ j ] = !tk[ j ];
    }
  for( int i = 0 ; i < (int)pr2.size() ; i ++ ){
    int dlt = 0;
    for( int j = pr2[ i ] ; j <= n ; j += pr2[ i ] )
      if( tk[ j ] ) dlt --;
      else dlt ++;
    if( dlt > 0 ){
      for( int j = pr2[ i ] ; j <= n ; j += pr2[ i ] )
        tk[ j ] = !tk[ j ];
    }
  }
  int tans = 0;
  for( int i = 1 ; i <= n ; i ++ )
    if( tk[ i ] ) tans ++;
  return tans;
}
void solve(){
  int _sz = (int)pr1.size();
  int ans = 0;
  if( _sz == 0 ){
    for( int i = 0 ; i < (int)pr2.size() ; i ++ )
        ans += n / pr2[ i ];
  }else{
    for( int i = 0 ; i < ( 1 << _sz ) ; i ++ )
      ans = max( ans , test( i ) );
  }
  printf( "Case #%d: %d\n" , ++ cs , ans );
}
int main(){
  build();
  __ = getint();
  while( __ -- ){
      init();
      solve();
  }
}
