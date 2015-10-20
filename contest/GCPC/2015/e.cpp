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
#define N 10010
int n , m , k;
bool a[ N ];
vector<PII> v[ N ];
void build(){

}
void init(){
  n = getint();
  m = getint();
  k = getint();
  for( int i = 0 ; i < k ; i ++ )
    a[ getint() ] = true;
  while( m -- ){
    int tu = getint();
    int tv = getint();
    int tk = getint();
    v[ tu ].PB( MP( tv , tk ) );
    v[ tv ].PB( MP( tu , tk ) );
  }
}
int dist[ 2 ][ N ];
bool got[ 2 ][ N ];
priority_queue< PII,vector<PII>,greater<PII> > heap;
void SPFA( int idx , int source ){
  heap.push( MP( 0 , source ) );
  while( heap.size() ){
    int ndist = heap.top().FI;
    int nidx =  heap.top().SE;
    heap.pop();
    if( got[ idx ][ nidx ] ) continue;
    got[ idx ][ nidx ] = true;
    dist[ idx ][ nidx ] = ndist;
    for( int i = 0 ; i < (int)v[ nidx ].size() ; i ++ )
      heap.push( MP( ndist + v[ nidx ][ i ].SE ,
                     v[ nidx ][ i ].FI ) );
  }
}
int dp[ N ] , indeg[ N ];
queue<int> Q;
bool cal(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 0 ; j < (int)v[ i ].size() ; j ++ )
      if( dist[ 0 ][ i ] + dist[ 1 ][ v[ i ][ j ].FI ] +
          v[ i ][ j ].SE == dist[ 0 ][ n ] )
        indeg[ v[ i ][ j ].FI ] ++;
  dp[ 1 ] = 1;
  Q.push( 1 );
  while( Q.size() ){
    int tn = Q.front(); Q.pop();
    for( int j = 0 ; j < (int)v[ tn ].size() ; j ++ )
      if( dist[ 0 ][ tn ] + dist[ 1 ][ v[ tn ][ j ].FI ] +
          v[ tn ][ j ].SE == dist[ 0 ][ n ] ){
        dp[ v[ tn ][ j ].FI ] += dp[ tn ];
        if( dp[ v[ tn ][ j ].FI ] > 1 ) 
          dp[ v[ tn ][ j ].FI ] = 2;
        indeg[ v[ tn ][ j ].FI ] --;
        if( indeg[ v[ tn ][ j ].FI ] == 0 )
          Q.push( v[ tn ][ j ].FI );
      }
  }
  return dp[ n ] > 1;
}
void solve(){
  SPFA( 0 , 1 );
  SPFA( 1 , n );
  bool flag = false;
  for( int i = 1 ; i <= n ; i ++ )
    if( dist[ 0 ][ i ] + dist[ 1 ][ i ] == dist[ 0 ][ n ] &&
        !a[ i ] ){
      flag = true;
      break;
    }
  if( cal() ) flag = true;
  puts( flag ? "yes" : "no" );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
