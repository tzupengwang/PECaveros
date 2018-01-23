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
#define eps 1e-8
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
#define N 100010
ll n , m;
vector<ll> v[ N ];
ll x[ N ] , idx[ N ];
vector< pair<ll,ll> > ch;
void build(){

}
void init(){
  n = getint(); m = getint();
  for( int i = 0 ; i < m ; i ++ ){
    ll tx = getint();
    ll tp = getint();
    v[ tp ].PB( tx );
  }
  for( int i = 1 ; i <= n ; i ++ ){
    sort( ALL( v[ i ] ) );
    for( int j = 1 ; j < (int)v[ i ].size() ; j ++ )
      ch.PB( MP( v[ i ][ j ] + v[ i ][ j - 1 ] , i ) );
  }
  ch.PB( MP( -2000000 , -1 ) );
  ch.PB( MP( 2000000 , -1 ) );
  sort( ALL( ch ) );
}
void solve(){
  D tans , mx = 0 , mx2 = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    x[ i ] = v[ i ][ 0 ];
    mx += x[ i ] * x[ i ];
    mx2 += x[ i ];
  }
  tans = n * mx - mx2 * mx2;
  D ans = tans;
  vector<D> ap; ap.PB( (D)mx2 / (D)n );
  for( int i = 0 ; i < (int)ch.size() ; i ++ ){
    int np = ch[ i ].SE;
    if( np != -1 ){
      mx -= x[ np ] * x[ np ];
      mx2 -= x[ np ];
      idx[ np ] ++;
      x[ np ] = v[ np ][ idx[ np ] ];
      mx += x[ np ] * x[ np ];
      mx2 += x[ np ];
      tans = n * mx - mx2 * mx2;
      if( equal( tans , ans ) ) ap.PB( (D)mx2 / (D)n );
      else if( tans < ans - eps ){
        ans = tans;
        ap.clear();
        ap.PB( (D)mx2 / (D)n );
      }
    }
    if( i ){
      D bl = (D)ch[ i - 1 ].FI / 2.0 , br = (D)ch[ i ].FI / 2.0 , bmid1 , bmid2;
      for( int _ = 0 ; _ < 100 ; _ ++ ){
        bmid1 = bl + ( br - bl ) / 3.0;
        bmid2 = br - ( br - bl ) / 3.0;
        D tans1 = (D)n * mx - (D)n * 2.0 * bmid1 * mx2 +
                  (D)n * (D)n * bmid1 * bmid1;
        D tans2 = (D)n * mx - (D)n * 2.0 * bmid2 * mx2 +
                  (D)n * (D)n * bmid2 * bmid2;
        if( tans1 < tans2 ) br = bmid2;
        else bl = bmid2;
      }
      D ba = ( bl + br ) / 2.0;
      D tans1 = (D)n * mx - (D)n * 2.0 * ba * mx2 +
                (D)n * (D)n * ba * ba;
      if( equal( tans1 , ans ) ) ap.PB( ba );
      else if( tans1 < ans - eps ){
        ans = tans1;
        ap.clear();
        ap.PB( ba );
      }
    }
  }
  printf( "%d\n" , (int)ap.size() );
  sort( ALL( ap ) );
  for( int i = 0 ; i < (int)ap.size() ; i ++ )
    printf( "%.12f\n" , ap[ i ] );
}
int main(){
  freopen( "gadgets.in" , "r" , stdin );
  freopen( "gadgets.out" , "w" , stdout );
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
