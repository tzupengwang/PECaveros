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
int __ = 1;
/*********default*********/
#define N 610
int t[ N ][ N ] , cs[ N ];
int n , k , p , nn[ N ];
vector< PII > v[ N ];
void build(){

}
void init(){
  n = getint();
  k = getint();
  p = getint();
  for( int i = 1 ; i <= k ; i ++ )
    cs[ i ] = getint();
  for( int i = 1 ; i <= n ; i ++ ){
    int tcst = getint();
    int team = getint();
    v[ team ].PB( MP( tcst , i ) );
  }
  for( int i = 1 ; i <= k ; i ++ ){
    nn[ i ] = (int)v[ i ].size();
    sort( ALL( v[ i ] ) );
    for( int j = 1 ; j <= nn[ i ] ; j ++ )
      t[ i ][ j ] = t[ i ][ j - 1 ] + v[ i ][ j - 1 ].FI;
  }
}
int dp[ N ][ N ] , prn[ N ][ N ];
void solve(){
  for( int i = 0 ; i <= k ; i ++ )
    for( int j = 0 ; j <= n ; j ++ )
      dp[ i ][ j ] = 1000000000;
  dp[ 0 ][ 0 ] = 0;
  for( int i = 1 ; i <= k ; i ++ ){
    for( int j = 0 ; j <= n ; j ++ )
      dp[ i ][ j ] = dp[ i - 1 ][ j ];
    for( int j = 1 ; j <= nn[ i ] ; j ++ ){
      for( int tk = j ; tk <= n ; tk ++ )
        if( dp[ i - 1 ][ tk - j ] + cs[ i ] + t[ i ][ j ] <
            dp[ i ][ tk ] ){
          dp[ i ][ tk ] = dp[ i - 1 ][ tk - j ] + cs[ i ] + t[ i ][ j ];
          prn[ i ][ tk ] = j;
        }
    }
  }
  vector<int> vans;
  int ans = 0;
  for( int i = 0 ; i <= n ; i ++ )
    if( dp[ k ][ i ] <= p )
      ans = i;
  int nowj = ans;
  for( int i = k ; i >= 1 ; i -- ){
    int tk = prn[ i ][ nowj ];
    nowj -= tk;
    for( int j = 0 ; j < tk ; j ++ )
      vans.PB( v[ i ][ j ].SE );
  }
  printf( "%d\n" , ans );
  for( int i = 0 ; i < ans ; i ++ )
    printf( "%d%c" , vans[ i ] , " \n"[ i == ans - 1 ] );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
