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
int ans[ N ] , aidx = 2;
map<PII,int> M;
int dx[]={0,-1,-1,0,1,1};
int dy[]={1,1,0,-1,-1,0};
int mx[]={-1,-1,0,1,1,0};
int my[]={1,0,-1,-1,0,1};
int got[ 7 ];
int chk( int nx , int ny ){
  bool can[ 7 ] = {};
  for( int i = 1 ; i <= 5 ; i ++ ) can[ i ] = true;
  for( int i = 0 ; i < 6 ; i ++ )
    if( M.count( MP( nx + dx[ i ] , ny + dy[ i ] ) ) )
      can[ M[ MP( nx + dx[ i ] , ny + dy[ i ] ) ] ] = false;
  int num = 1 , mn = N * N;
  for( int i = 1 ; i <= 5 ; i ++ ) if( can[ i ] && got[ i ] < mn )
    mn = got[ i ] , num = i;
  return num;
}
void Set( int nx , int ny ){
  int vl = chk( nx , ny );
  M[ MP( nx , ny ) ] = vl;
  if( aidx < N ) ans[ aidx ++ ] = vl;
  got[ vl ] ++;
}
void build(){
  M[ MP( 0 , 0 ) ] = 1;
  got[ 1 ] ++;
  ans[ 1 ] = 1;
  for( int i = 0 , j = 1 ; (int)M.size() < N ; i ++ , j ++ ){
    int sx = i , sy = 1;
    for( int k = 1 ; k < j ; k ++ ){
      Set( sx , sy );
      sx += mx[ 0 ];
      sy += my[ 0 ];
    }
    for( int dir = 1 ; dir < 6 ; dir ++ ){
      for( int k = 0 ; k < j ; k ++ ){
        Set( sx , sy );
        sx += mx[ dir ];
        sy += my[ dir ];
      }
    }
    Set( sx , sy );
  }
}
int n;
void init(){
  n = getint();
}
void solve(){
  printf( "%d\n" , ans[ n ] );
}
int main(){
    build();
    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
