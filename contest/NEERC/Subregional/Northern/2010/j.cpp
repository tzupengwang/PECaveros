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
#define M 100010
#define int long long
int n , s , t;
int m1 , m2;
int tu1[ M ] , tv1[ M ] , tl1[ M ];
int tu2[ M ] , tv2[ M ] , tl2[ M ];
vector< PII > tg1[ N ] , tg2[ N ];
vector< PII > g[ N ];
void build(){

}
void init(){
  n = getint();
  s = getint();
  t = getint();
  m1 = getint();
  for( int i = 0 ; i < m1 ; i ++ ){
    tu1[ i ] = getint();
    tv1[ i ] = getint();
    tl1[ i ] = getint();
    tg1[ tu1[ i ] ].PB( MP( tv1[ i ] , tl1[ i ] ) );
    tg1[ tv1[ i ] ].PB( MP( tu1[ i ] , tl1[ i ] ) );
  }
  m2 = getint();
  for( int i = 0 ; i < m2 ; i ++ ){
    tu2[ i ] = getint();
    tv2[ i ] = getint();
    tl2[ i ] = getint();
    tg2[ tu2[ i ] ].PB( MP( tv2[ i ] , tl2[ i ] ) );
    tg2[ tv2[ i ] ].PB( MP( tu2[ i ] , tl2[ i ] ) );
  }
}
int dist1[ N ] , dist2[ N ];
bool inq[ N ];
queue<int> Q;
void SPFA(){
  for( int i = 1 ; i <= n ; i ++ )
    dist1[ i ] = dist2[ i ] = INF;
  dist1[ t ] = dist2[ t ] = 0;
  Q.push( t ); while( Q.size() ){
    int tn = Q.front(); Q.pop(); inq[ tn ] = false;
    for( int i = 0 ; i < (int)tg1[ tn ].size() ; i ++ )
      if( dist1[ tn ] + tg1[ tn ][ i ].SE <
          dist1[ tg1[ tn ][ i ].FI ] ){
          dist1[ tg1[ tn ][ i ].FI ] =
            dist1[ tn ] + tg1[ tn ][ i ].SE;
          if( !inq[ tg1[ tn ][ i ].FI ] ){
            inq[ tg1[ tn ][ i ].FI ] = true;
            Q.push( tg1[ tn ][ i ].FI );
          }
      }
  }
  Q.push( t ); while( Q.size() ){
    int tn = Q.front(); Q.pop(); inq[ tn ] = false;
    for( int i = 0 ; i < (int)tg2[ tn ].size() ; i ++ )
      if( dist2[ tn ] + tg2[ tn ][ i ].SE <
          dist2[ tg2[ tn ][ i ].FI ] ){
          dist2[ tg2[ tn ][ i ].FI ] =
            dist2[ tn ] + tg2[ tn ][ i ].SE;
          if( !inq[ tg2[ tn ][ i ].FI ] ){
            inq[ tg2[ tn ][ i ].FI ] = true;
            Q.push( tg2[ tn ][ i ].FI );
          }
      }
  }
}
// 1 ... n 1st
// n + 1 ... n + n 2nd
int dp[ N ];
int st[ N ];
// 1 running 2 done
int DFS( int now ){
  if( st[ now ] == 2 ) return dp[ now ];
  if( st[ now ] == 1 ){
    puts( "-1" );
    exit( 0 );
  }
  if( now == t || now == t + n )
    return dp[ now ] = 0;
  st[ now ] = 1;
  for( int i = 0 ; i < (int)g[ now ].size() ; i ++ )
    dp[ now ] = max( dp[ now ] , g[ now ][ i ].SE +
                                  DFS( g[ now ][ i ].FI ) );
  st[ now ] = 2;
  return dp[ now ];
}
void solve(){
  SPFA();
  for( int i = 1 ; i <= n ; i ++ ){
    for( int j = 0 ; j < (int)tg1[ i ].size() ; j ++ )
      if( dist1[ tg1[ i ][ j ].FI ] < dist1[ i ] ){
        g[ i ].PB( MP( tg1[ i ][ j ].FI + n ,
                        tg1[ i ][ j ].SE ) );
      }
    for( int j = 0 ; j < (int)tg2[ i ].size() ; j ++ )
      if( dist2[ tg2[ i ][ j ].FI ] < dist2[ i ] )
        g[ i + n ].PB( MP( tg2[ i ][ j ].FI ,
                        tg2[ i ][ j ].SE ) );
  }
  DFS( s );
  cout << dp[ s ] << endl;
}
signed main(){
  freopen( "journey.in" , "r" , stdin );
  freopen( "journey.out" , "w" , stdout );
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
