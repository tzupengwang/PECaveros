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
#define N 1000010
int n , a[ N ] , b[ N ] , c[ N ];
void build(){

}
int cnt[ N ];
vector<PII> v;
set<int> S;
bool done[ N ];
void init(){
  n = getint();
  v.clear();
  S.clear();
  for( int i = 0 ; i < N ; i ++ ) cnt[ i ] = 0;
  for( int i = 1 ; i <= n ; i ++ ){
    a[ i ] = getint();
    b[ i ] = getint();
    c[ i ] = getint();
    done[ i ] = false;
    if( cnt[ a[ i ] ] == 0 )
      cnt[ a[ i ] ] ++;
    S.insert( a[ i ] );
  }
  for( int i = 1 ; i < N ; i ++ )
    cnt[ i ] += cnt[ i - 1 ];
  for( int i = 1 ; i <= n ; i ++ ){
    int got = cnt[ c[ i ] ] - cnt[ b[ i ] - 1 ];
    if( b[ i ] <= a[ i ] && a[ i ] <= c[ i ] ){
      if( got <= 1 ){
        v.PB( MP( b[ i ] , -i ) );
        v.PB( MP( c[ i ] , i ) );
      }
    }else if( got == 0 ){
      v.PB( MP( b[ i ] , -i ) );
      v.PB( MP( c[ i ] , i ) );
    }
  }
  sort( v.begin() , v.end() );
}
vector<int> tmp;
void solve(){
  int ans = (int)S.size();
  for( int i = 0 ; i < (int)v.size()  ; i ++ )
    if( v[ i ].SE < 0 ){
      tmp.PB( -v[ i ].SE );
    }else{
      if( !done[ v[ i ].SE ] ){
        ans ++;
        while( tmp.size() ){
          done[ tmp.back() ] = true;
          tmp.pop_back();
        }
      }
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
