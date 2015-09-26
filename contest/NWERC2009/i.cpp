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
#define N 4010
int n;
vector< pair<PII,int> > v , v2;
int operator^( const PII& p1 , const PII& p2 ){
  return p1.FI * p2.SE - p1.SE * p2.FI;
}
PII operator-( const PII& p1 , const PII& p2 ){
  return MP( p1.FI - p2.FI , p1.SE - p2.SE );
}
int dist( const PII& tp ){
  return tp.FI * tp.FI +
         tp.SE * tp.SE;
}
bool cmp( pair<PII,int> p1 , pair<PII,int> p2 ){
  if( ( p1.FI ^ p2.FI ) != 0 )
    return ( p1.FI ^ p2.FI ) < 0;
  return dist( p1.FI ) < dist( p2.FI );
}
void build(){

}
bool vst[ N ];
vector<int> r[ N ] , ans;
void init(){
  n = getint();
  v.clear();
  ans.clear();
  v2.clear();
  for( int i = 0 ; i < n + n ; i ++ ){
    r[ i ].resize( 0 );
    vst[ i ] = false;
  }
  for( int i = 0 ; i < n ; i ++ ){
    int tx = getint();
    int ty = getint();
    v.PB( MP( MP( tx , ty ) , i ) );
  }
  sort( ALL( v ) );
}
void DFS( int now ){
  vst[ now ] = true;
  ans.PB( now );
  for( int i = 0 ; i < (int)r[ now ].size() ; i ++ )
    if( !vst[ r[ now ][ i ] ] ){
      DFS( r[ now ][ i ] );
      break;
    }
}
void solve(){
  int sp = v[ 0 ].SE;
  PII o = v[ 0 ].FI;
  for( int i = 1 ; i < n ; i ++ )
    v2.PB( MP( v[ i ].FI - o , v[ i ].SE ) );
  sort( ALL( v2 ) , cmp );
  int lst = n - 2;
  while( lst >= 0 && ( v2[ lst - 1 ].FI ^ v2[ lst ].FI ) == 0 ) lst --;
  for( int i = 1 ; i < lst ; i ++ ){
    r[ v2[ i - 1 ].SE ].PB( v2[ i ].SE );
    r[ v2[ i ].SE ].PB( v2[ i - 1 ].SE );
  }
  r[ v2[ lst - 1 ].SE ].PB( v2.back().SE );
  r[ v2.back().SE ].PB( v2[ lst - 1 ].SE );
  for( int i = lst ; i < (int)v2.size() - 1 ; i ++ ){
    r[ v2[ i ].SE ].PB( v2[ i + 1 ].SE );
    r[ v2[ i + 1 ].SE ].PB( v2[ i ].SE );
  }
  r[ sp ].PB( v2[ 0 ].SE );
  r[ v2[ 0 ].SE ].PB( sp );
  r[ sp ].PB( v2[ lst ].SE );
  r[ v2[ lst ].SE ].PB( sp );
  DFS( 0 );
  for( int i = 0 ; i < n ; i ++ )
    printf( "%d%c" , ans[ i ] , i == n - 1 ? '\n' : ' ' );
//  for( int i = 0 ; i < n ; i ++ )
//    for( int j = 0 ; j < (int)r[ i ].size() ; j ++ )
//      printf( "%d <-> %d\n" , i , r[ i ][ j ] );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
