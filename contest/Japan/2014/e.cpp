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
#define N 52
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
int n , sx , sy , t;
bool pdir[ N ][ N ][ 4 ];
void build(){

}
void link( int fx , int fy , int tx , int ty ){
  int tdir = 0;
  if( fy < ty ) tdir = 1;
  if( fx > tx ) tdir = 2;
  if( fy > ty ) tdir = 3;
  while( fx != tx || fy != ty ){
    pdir[ fx ][ fy ][ tdir ] = true;
    fx += dx[ tdir ];
    fy += dy[ tdir ];
  }
}
void init(){
  n = getint();
  sx = getint();
  sy = getint();
  t = getint();
  for( int i = 0 ; i < n ; i ++ ){
    int fx = getint();
    int fy = getint();
    int tx = getint();
    int ty = getint();
    link( fx , fy , tx , ty );
    link( tx , ty , fx , fy );
  }
}
bool vst[ N ][ N ][ 4 ];
queue< tuple<int,int,int> > Q[ 2 ];
int trans( char ctmp ){
  if( ctmp == 'E' ) return 0;
  if( ctmp == 'N' ) return 1;
  if( ctmp == 'W' ) return 2;
  if( ctmp == 'S' ) return 3;
  return -1;
}
void solve(){
  for( int i = 0 ; i < 4 ; i ++ )
    if( pdir[ sx ][ sy ][ i ] )
      Q[ 0 ].push( MT( sx , sy , i ) );
  int tidx = 0;
  int ndir = 0;
  for( int _ = 0 ; _ < t ; _ ++ ){
    int dlt = getint(); char tc[ 9 ];
    scanf( "%s" , tc );
    ndir = trans( tc[ 0 ] );
    while( dlt -- ){
      bool last = (dlt == 0);
      int now = ( ++ tidx ) % 2;
      int pre = 1 - now;
      for( int i = 0 ; i < N ; i ++ )
        for( int j = 0 ; j < N ; j ++ )
          for( int k = 0 ; k < 4 ; k ++ )
            vst[ i ][ j ][ k ] = false;
      while( Q[ pre ].size() ){
        tuple<int,int,int> tp = Q[ pre ].front(); Q[ pre ].pop();
        int px = get<0>( tp );
        int py = get<1>( tp );
        int pd = get<2>( tp );
        if( !pdir[ px ][ py ][ pd ] ) continue;
        int nxtx = px + dx[ pd ];
        int nxty = py + dy[ pd ];
        for( int nxtdir = 0 ; nxtdir < 4 ; nxtdir ++ ){
          if( last && nxtdir != ndir && pd != ndir ) continue;
          if( abs( pd - nxtdir ) == 2 ) continue;
          if( nxtdir != pd && !pdir[ nxtx ][ nxty ][ nxtdir ] ) continue;
          if( !vst[ nxtx ][ nxty ][ nxtdir ] ){
            vst[ nxtx ][ nxty ][ nxtdir ] = true;
            Q[ now ].push( MT( nxtx , nxty , nxtdir ) );
          }
        }
      }
    }
  }
  for( int i = 0 ; i < N ; i ++ )
    for( int j = 0 ; j < N ; j ++ )
      if( vst[ i ][ j ][ ndir ] )
        printf( "%d %d\n" , i , j );
}
int main(){
  build();
  //__ = getint();
  while( __ -- ){
    init();
    solve();
  }
}
