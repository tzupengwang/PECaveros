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
#define N 2010
int n , x , y , dst[ 2 ][ N ] , m;
vector< PII > v[ N ];
void build(){

}
void init(){
  n = getint();
  x = getint();
  y = getint();
  for( int j = 0 ; j < 2 ; j ++ )
    for( int i = 1 ; i <= n ; i ++ )
      dst[ j ][ i ] = 2100000000;
  m = getint(); while( m -- ){
    int tu = getint();
    int tv = getint();
    int tc = getint();
    v[ tu ].PB( MP( tv , tc ) );
    v[ tv ].PB( MP( tu , tc ) );
  }
}
priority_queue< PII , vector<PII> , greater<PII> > heap;
bool done[ N ];
void SP( int idx , int st ){ 
  heap.push( MP( 0 , st ) );
  for( int i = 1 ; i <= n ; i ++ ) done[ i ] = false;
  while( heap.size() ){
    PII tp = heap.top(); heap.pop();
    if( done[ tp.SE ] ) continue;
    done[ tp.SE ] = true;
    dst[ idx ][ tp.SE ] = tp.FI;
    for( int i = 0 ; i < (int)v[ tp.SE ].size() ; i ++ )
      if( !done[ v[ tp.SE ][ i ].FI ] )
        heap.push( MP( dst[ idx ][ tp.SE ] + v[ tp.SE ][ i ].SE ,
                       v[ tp.SE ][ i ].FI ) );
  }
}
int cnt1[ N ] , ans[ N ];
bool ons[ N ];
vector< PII > pt;
void solve(){
  SP( 0 , x );
  SP( 1 , y );
//  for( int i = 1 ; i <= n ; i ++ )
//    printf( "%d %d\n" , dst[ 0 ][ i ] , dst[ 1 ][ i ] );
  for( int i = 1 ; i <= n ; i ++ )
    if( dst[ 0 ][ i ] + dst[ 1 ][ i ] == dst[ 0 ][ y ] ){
      ons[ i ] = true;
      pt.PB( MP( dst[ 0 ][ i ] , i ) );
    }
  sort( ALL( pt ) );
  pt.PB( MP( 2100000000 , 2100000000 ) );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 0 ; j < (int)v[ i ].size() ; j ++ )
      if( dst[ 0 ][ i ] + v[ i ][ j ].SE + dst[ 1 ][ v[ i ][ j ].FI ] ==
          dst[ 0 ][ y ] ){
        int vl = dst[ 0 ][ i ] + 1;
        int vr = dst[ 0 ][ i ] + v[ i ][ j ].SE - 1;
        if( vl <= vr ){
          int idxl = lower_bound( ALL( pt ) , MP( vl , -1 ) ) - pt.begin();
          int idxr = upper_bound( ALL( pt ) , MP( vr , 10000 ) ) - pt.begin();
          cnt1[ idxl ] ++;
          cnt1[ idxr ] --;
        }
      }
  for( int i = 1 ; i < (int)pt.size() ; i ++ )
    cnt1[ i ] += cnt1[ i - 1 ];
  for( int i = 0 ; i < (int)pt.size() - 1 ; i ++ )
    ans[ pt[ i ].SE ] = cnt1[ i ];
  for( int i = 1 ; i <= n ; i ++ ) if( ons[ i ] )
    for( int j = 1 ; j <= n ; j ++ ) if( ons[ j ] )
      if( dst[ 0 ][ i ] == dst[ 0 ][ j ] )
        ans[ i ] ++;
  for( int i = 1 ; i <= n ; i ++ )
    printf( "%d%c" , ans[ i ] , " \n"[ i == n ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
