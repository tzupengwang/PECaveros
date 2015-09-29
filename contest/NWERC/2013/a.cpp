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
int p[ N ];
int n , a[ N ][ N ];
vector< pair< int,PII > > r;
vector< PII > v[ N ];
vector< pair<PII,int> > ans;
int find_p( int x ){
  return x == p[ x ] ? x : p[ x ] = find_p( p[ x ] );
}
void Union( int x , int y ){
  x = find_p( x );
  y = find_p( y );
  p[ x ] = y;
}
void build(){

}
void init(){
  r.clear();
  ans.clear();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ ){
      a[ i ][ j ] = getint();
      r.PB( MP( a[ i ][ j ] , MP( i , j ) ) );
    }
  for( int i = 1 ; i <= n ; i ++ ){
    p[ i ] = i;
    v[ i ].clear();
  }
  sort( ALL( r ) );
}
int ds[ N ][ N ];
bool got[ N ];
void DFS( int st , int now , int dst ){
  ds[ st ][ now ] = dst;
  got[ now ] = true;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( !got[ v[ now ][ i ].FI ] )
      DFS( st , v[ now ][ i ].FI , dst + v[ now ][ i ].SE );
}
void SP( int now ){
  for( int i = 1 ; i <= n ; i ++ ){
    ds[ now ][ i ] = 2147483647;
    got[ i ] = false;
  }
  DFS( now , now , 0 );
}
void solve(){
  int g = n;
  for( int i = 0 ; g > 1 ; i ++ )
    if( find_p( r[ i ].SE.FI ) != find_p( r[ i ].SE.SE ) ){
      Union( r[ i ].SE.FI , r[ i ].SE.SE );
      v[ r[ i ].SE.FI ].PB( MP( r[ i ].SE.SE , r[ i ].FI ) );
      v[ r[ i ].SE.SE ].PB( MP( r[ i ].SE.FI , r[ i ].FI ) );
      ans.PB( MP( r[ i ].SE , r[ i ].FI ) );
      g --;
    }
  for( int i = 1 ; i <= n ; i ++ )
    SP( i );
  int ax = 1 , ay = 2 , ad = 1000001;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= n ; j ++ )
      if( ds[ i ][ j ] != a[ i ][ j ] )
        if( a[ i ][ j ] < ad ){
          ax = i;
          ay = j;
          ad = a[ i ][ j ];
        }
  ans.PB( MP( MP( ax , ay ) , ad ) );
  for( int i = 0 ; i < (int)ans.size() ; i ++ )
    printf( "%d %d %d\n" , ans[ i ].FI.FI ,
                           ans[ i ].FI.SE ,
                           min( 1000000 , ans[ i ].SE ) );
}
int main(){
  build();
  //__ = getint();
  bool first = true;
  while( cin >> n ){
    if( !first ) puts( "" );
    first = false;
    init();
    solve();
  }
}
