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
#define N 20010
int p[ N ] , prt[ N ];
int find_p( int x ){
  return x == p[ x ] ? x : p[ x ] = find_p( p[ x ] );
}
void Union( int x , int y ){
  x = find_p( x );
  y = find_p( y );
  p[ x ] = y;
}
int n , k;
int cnt[ N ];
int tp[ N ] , qa[ N ] , qb[ N ];
void build(){

}
void init(){
  n = getint(); k = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    prt[ i ] = getint();
    if( prt[ i ] == 0 ) prt[ i ] = i;
    p[ i ] = i;
  }
  for( int i = 1 ; i <= n ; i ++ )
    cnt[ i ] = 0;
  for( int i = 1 ; i <= k ; i ++ ){
    char tc[ 5 ]; scanf( "%s" , tc );
    if( tc[ 0 ] == 'Q' ){
      tp[ i ] = 1;
      qa[ i ] = getint();
      qb[ i ] = getint();
    }else{
      tp[ i ] = 2;
      qa[ i ] = getint();
      if( !cnt[ qa[ i ] ] )
        cnt[ qa[ i ] ] =i;
    }
  }
//  for( int i = 0 ; i < n ; i ++ )
//    printf( "%d\n" , cnt[ i ] );
}
vector<bool> ans;
void solve(){
  ans.clear();
  for( int i = 1 ; i <= n ; i ++ )
    if( !cnt[ i ] )
      Union( i , prt[ i ] );
  for( int i = k ; i >= 1 ; i -- )
    if( tp[ i ] == 1 ){
      ans.PB( find_p( qa[ i ] ) ==
              find_p( qb[ i ] ) );
    }else if( cnt[ qa[ i ] ] == i ){
      Union( qa[ i ] , prt[ qa[ i ] ] );
    }
  printf( "Case #%d:\n" , ++ cs );
  for( int i = (int)ans.size() - 1 ; i >= 0 ; i -- )
    puts( ans[ i ] ? "YES" : "NO" );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
